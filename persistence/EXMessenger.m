//
//  EXMessanger.m
//  CRo
//  Entropy
//  (C) 2007-2009 Codesign
//  Licensed under LGPL (v3)
//

#import "EXMessenger.h"
#import "LXSocket.h"

@implementation EXMessenger

- (id)initWithFile:(NSString*)fileName {
	EXContainer* _container = [[EXContainer alloc] initWithFile: [EXFile fileWithName: fileName]];
	id result = [self initWithContainer: _container];
	[_container release];
	return result;
}

- (id)initWithContainer:(EXContainer*)_container {
	if (self = [super init]) {
		container = [_container retain];
	}
	return self;
}

- (EXContainer*)container {
	return container;
}

- (BOOL)postMessage:(EXPersistentMessage*)message {
	return [self postMessage: message storage: container];
}

- (BOOL)postMessage:(EXPersistentMessage*)message storage:(id)storage {
	@try {
		[message setPosted: [NSDate date]];
		[storage storeObject: message];
		return YES;
	} @catch (NSException* exception) {
		NSLog(@"Cannot post message: %@", exception);
	}
	return NO;
}

- (BOOL)transmitToHost:(NSString*)host port:(unsigned)port {
	LXSocket* socket = [[LXSocket alloc] init];
	@try {
		if ([socket connect: host port: port] == YES) {
			[socket sendInt: 1];
			NSArray* messages = [container queryWithClass: [EXPersistentMessage class]];
			for (EXPersistentMessage* message in messages) {
				[socket sendInt: 1];
				[socket sendObject: message];
				if ([socket readInt] == 1) [container removeObject: message];
			}
			[socket sendInt: 0];
			return YES;
		}
	} @finally {
		[socket release];
	}
	return NO;
}

- (BOOL)receiveFromHost:(NSString*)host port:(unsigned)port owner:(NSString*)owner {
	LXSocket* socket = [[LXSocket alloc] init];
	@try {
		if ([socket connect: host port: port] == YES) {
			[socket sendInt: 2];
			[socket sendString: owner];
			while ([socket readInt] == 1) {
				EXPersistentMessage* message = [socket readObject];
				[message setDelivered: [NSDate date]];
				if ([delegate respondsToSelector: @selector(messenger:message:)]) {
					if ([delegate performSelector: @selector(messenger:message:)
									withObject: self
									   withObject: message]) [socket sendInt: 1];
					else  [socket sendInt: 0];
				} else  [socket sendInt: 0];
			}
			return YES;
		}
	} @finally {
		[socket release];
	}
	return NO;
}

- (void)setDelegate:(id)_delegate {
	if (delegate != _delegate) {
		[delegate release];
		delegate = [_delegate retain];
	}
}

- (void)dealloc {
	[container release];
	[delegate release];
	[super dealloc];
}

@end
