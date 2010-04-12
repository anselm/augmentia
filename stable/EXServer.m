//
//  EXServer.m
//  Entropy
//  (C) 2007-2009 Codesign
//  Licensed under LGPL (v3)
//

#import "EXServer.h"
#import "EXObjectProxy.h"
#import "LXSocket.h"

@implementation EXServer

+ (id)server {
	return  [[[self alloc] init] autorelease];
}

- (id)init {
	if (self = [super init]) {
		objects = [[NSMutableDictionary alloc] init];
		expirationDates = [[NSMutableDictionary alloc] init];
		leaseTimer = [NSTimer scheduledTimerWithTimeInterval: LEASETIME target: self selector: @selector(checkObjects) userInfo: nil repeats: YES];
	}
	return self;
}

- (void)runInThreadWithPort:(unsigned)port {
	[NSThread detachNewThreadSelector: @selector(runWithPort:) toTarget: self withObject: [NSNumber numberWithUnsignedInt: port]];
}

- (void)checkObjects {
	NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];
	@synchronized (objects) {
	NSDate* now = [NSDate date];
	for (id key in [expirationDates allKeys]) {
		NSDate* expiration = [expirationDates objectForKey: key];
		if ([expiration compare: now] == NSOrderedAscending) {
			NSLog(@"Server - releasing outdated object");
			[expirationDates removeObjectForKey: key];
			[objects removeObjectForKey: key];
		}
	}
	}
	[pool release];
}

- (void)runWithPort:(NSNumber*)port {
	NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];
	LXSocket* serverSocket = [[LXSocket alloc] init];
	if ([serverSocket bindToPort: [port unsignedIntValue]]) {
		if ([serverSocket listen: 10]) {
			while (YES) {
				NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];
				@try {
					LXSocket* socket = [serverSocket accept];
					//NSLog(@"EX server: new connection");
					int action = [socket readInt];
					id object;
					NSValue* key;
					switch (action) {
						case 1:;
							NSString* className = [socket readString];
							//NSLog(@"EX server: 1 - %@", className);
							object = [[NSClassFromString(className) alloc] init];
							key = [NSNumber numberWithLongLong: (((long long) random()) << 32) | (long) object];
							@synchronized (objects) {
							[objects setObject: object forKey: key];
							[expirationDates setObject: [[NSDate date] addTimeInterval: LEASETIME] forKey: key];
							}
							[object release];
							[socket sendObject: key];
							break;
						case 4:; // renewing lease
							key = [socket readObject];
							@synchronized (objects) {
							object = [objects objectForKey: key];
							}
							if (object != nil) {
								[socket sendInt: 1];
								@synchronized (objects) {
								[expirationDates setObject: [[NSDate date] addTimeInterval: LEASETIME] forKey: key];
								}
								NSLog(@"Server - renewed");
							} else {
								[socket sendInt: 0];
								NSLog(@"Server - object doesn't exist any more");
							}
							break;
						case 2:;
							key = [socket readObject];
							@synchronized (objects) {
							object = [objects objectForKey: key];
							}
							if (object != nil) {
								[socket sendInt: 1];
								SEL selector = NSSelectorFromString([socket readString]);
								NSMethodSignature* signature = [object methodSignatureForSelector: selector];
								NSInvocation* invocation = [NSInvocation invocationWithMethodSignature: signature];
								[invocation setSelector: selector];
								int numberOfArguments = [socket readInt];
								for (int i = 2; i < numberOfArguments; i++) {
									id argument = [socket readObject];
									[invocation setArgument: &argument atIndex: i];
								}
								[invocation invokeWithTarget: object];
								const char* returnType = [signature methodReturnType];
								if (!strcmp(returnType, "v")) {
									[socket sendInt: 0];
								} else {
									[socket sendInt: 1];
									id result;
									[invocation getReturnValue: &result];
									[socket sendObject: result];
								}
							} else {
								[socket sendInt: 0];
								NSLog(@"Server - object doesn't exist any more");
							}
							break;
						case 3:;
							key = [socket readObject];
							if (object != nil) {
								[socket sendInt: 1];
								@synchronized (objects) {
								[objects removeObjectForKey: key];
								}
							} else {
								[socket sendInt: 0];
								NSLog(@"Server - object doesn't exist any more");
							}
							break;
					}
					[socket release];
				} @finally {
					[pool release];
				}
			}
		}
	}
	[serverSocket release];
	[pool release];
}

- (void)dealloc {
	[leaseTimer invalidate];
	[objects release];
	[expirationDates release];
	[super dealloc];
}

@end
