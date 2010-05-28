//
//  EXMessanger.h
//  Entropy
//  (C) 2007-2009 Codesign
//  Licensed under LGPL (v3)
//

#import <Foundation/Foundation.h>
#import "EXPersistentMessage.h"
#import "EXContainer.h"

@interface EXMessenger : NSObject {
	EXContainer* container;
	id delegate;
}

- (id)initWithFile:(NSString*)fileName;
- (id)initWithContainer:(EXContainer*)_container;
- (BOOL)postMessage:(EXPersistentMessage*)message;
- (BOOL)postMessage:(EXPersistentMessage*)message storage:(id)storage; // storage is a container or a transaction
- (BOOL)transmitToHost:(NSString*)host port:(unsigned)port;
- (BOOL)receiveFromHost:(NSString*)host port:(unsigned)port owner:(NSString*)owner;
- (void)setDelegate:(id)_delegate;
- (EXContainer*)container;

@end
