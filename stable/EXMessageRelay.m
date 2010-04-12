//
//  EXMessageRelay.m
//  Entropy
//  (C) 2007-2009 Codesign
//  Licensed under LGPL (v3)
//

#import "EXMessageRelay.h"
#import "LXSocket.h"
#import "EXPersistentMessage.h"
#import "EXPredicateEqualText.h"
@implementation EXMessageRelay

+ (id)relay {
	return  [[[self alloc] init] autorelease];
}

- (id)init {
	if (self = [super init]) {
		container = [[EXContainer alloc] initWithFile: [EXFile fileWithName: @"relay.db"]];
	}
	return self;
}

- (void)runInThread {
	[self retain];
	[NSThread detachNewThreadSelector: @selector(run) toTarget: self withObject: nil];
}

- (void)run {
	LXSocket* serverSocket = [[LXSocket alloc] init];
	if ([serverSocket bindToPort: 8009]) {
		if ([serverSocket listen: 10]) {
			while (YES) {
				NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];
				@try {
					LXSocket* socket = [serverSocket accept];
					int action = [socket readInt];
					switch (action) {
						case 1:
							while ([socket readInt] == 1) {
								@try {
									EXPersistentMessage* message = [socket readObject];
									[message setSent: [NSDate date]];
									if ([[message to] isKindOfClass: [NSArray class]]) {
										NSArray* receivers = [message to];
										for (id to in receivers) {
											EXPersistentMessage* copyOfMessage = [message mutableCopy];
											[copyOfMessage setTo: to];
											[container storeObject: copyOfMessage];
											[copyOfMessage release];
											NSLog(@"Split message (for %@) stored in relay", to);
										}
									} else {
										[container storeObject: message];
										NSLog(@"Message stored in relay");
									}
									[socket sendInt: 1];
								} @catch (NSException* exception) {
									NSLog(@"Cannot receive & store message in relay");
									[socket sendInt: 0];
								}
							}
							break;
						case 2:;
							NSString* owner = [socket readString];
							EXPredicate* predicate = [[[EXPredicateEqualText alloc] initWithFieldName: @"to" value: owner] autorelease];
							NSArray* messages = [container queryWithClass: [EXPersistentMessage class] predicate: predicate];
							messages = [messages sortedArrayUsingSelector: @selector(compare:)];
							for (EXPersistentMessage* message in messages) {
								[socket sendInt: 1];
								[socket sendObject: message];
								if ([socket readInt] == 1) {
									NSLog(@"Removing message from relay");
									[container removeObject: message];
								} else NSLog(@"Won't remove message from relay");
							}
							[socket sendInt: 0];
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
	[self release];
}

- (void)dealloc {
	[container release];
	[super dealloc];
}

@end
