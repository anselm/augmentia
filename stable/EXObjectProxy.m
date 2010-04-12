//
//  EXProxy.m
//  CRo
//  Entropy
//  (C) 2007-2009 Codesign
//  Licensed under LGPL (v3)
//

#import "EXObjectProxy.h"
#import "EXRemoteInvocationException.h"
#import "LXSocket.h"

@implementation EXObjectProxy

+ (id)proxyForClass:(Class)_cls port:(unsigned)_port host:(NSString*)_host {
	return [[[self alloc] initWithClass: _cls port: _port host: _host] autorelease];
}

- (id)initWithClass:(Class)_cls port:(unsigned)_port host:(NSString*)_host {
	if (self = [super init]) {
		cls = _cls;
		port = _port;
		LXSocket* socket = [[LXSocket alloc] init];
		host = [_host retain];
		@try {
			if ([socket connect: [socket resolveHostName: host] port: port] == YES) {
				[socket sendInt: 1];
				[socket sendString: NSStringFromClass(cls)];
				key = [[socket readObject] retain];
				leaseTimer = [NSTimer scheduledTimerWithTimeInterval: LEASETIME / 2 target: self selector: @selector(renewLease) userInfo: nil repeats: NO];
			} else {
				[EXRemoteInvocationException raise: @"EXRemoteInvocationException" format: @"Cannot connect to the server"];
			}
		} @finally {
			[socket release];
		}
	}
	return self;
}

- (void)renewLease {
	leaseTimer = nil;
	NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];
	LXSocket* socket = [[LXSocket alloc] init];
	@try {
		if ([socket connect: [socket resolveHostName: host] port: port] == YES) {
			[socket sendInt: 4];
			[socket sendObject: key];
			if ([socket readInt] == 0) [EXRemoteInvocationException raise: @"EXRemoteInvocationException" format: @"No remote object any more"];
			leaseTimer = [NSTimer scheduledTimerWithTimeInterval: LEASETIME / 2 target: self selector: @selector(renewLease) userInfo: nil repeats: NO];
		} else {
			[EXRemoteInvocationException raise: @"EXRemoteInvocationException" format: @"Cannot connect to the server"];
		}
	} @finally {
		[socket release];
	}
	[pool release];
}

- (NSMethodSignature*)methodSignatureForSelector:(SEL)selector {
	NSMethodSignature* signature = [super methodSignatureForSelector: selector];
	if (signature != nil) return signature;
	return [cls instanceMethodSignatureForSelector: selector];
}

- (void)forwardInvocation:(NSInvocation*)invocation {
	LXSocket* socket = [[LXSocket alloc] init];
	@try {
		if ([socket connect: [socket resolveHostName: host] port: port] == YES) {
			[socket sendInt: 2];
			[socket sendObject: key];
			if ([socket readInt] == 0) [EXRemoteInvocationException raise: @"EXRemoteInvocationException" format: @"No remote object any more"];
			[socket sendString: NSStringFromSelector([invocation selector])];
			[socket sendInt: [[invocation methodSignature] numberOfArguments]];
			id argument;
			for (int i = 2; i < [[invocation methodSignature] numberOfArguments]; i++) {
				[invocation getArgument: &argument atIndex: i];
				[socket sendObject: argument];
			}
			if ([socket readInt] == 1) {
				id result = [socket readObject];
				[invocation setReturnValue: &result];
			}
		} else {
			[EXRemoteInvocationException raise: @"EXRemoteInvocationException" format: @"Cannot connect to the server"];
		}
	} @finally {
		[socket release];
	}
}

- (void)release {
	if ([self retainCount] == 1) {
		[leaseTimer invalidate];
		LXSocket* socket = [[LXSocket alloc] init];
		@try {
			if ([socket connect: [socket resolveHostName: host] port: port] == YES) {
				[socket sendInt: 3];
				[socket sendObject: key];
				if ([socket readInt] == 0) [EXRemoteInvocationException raise: @"EXRemoteInvocationException" format: @"No remote object any more"];
			} else {
				[EXRemoteInvocationException raise: @"EXRemoteInvocationException" format: @"Cannot connect to the server"];
			}
		} @finally {
			[socket release];
		}
	}
	[super release];
}

- (void)dealloc {
	//NSLog(@"Object proxy - being dealloced");
	[key release];
	[host release];
	[super dealloc];
}

@end
