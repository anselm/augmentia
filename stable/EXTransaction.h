//
//  EXTransaction.h
//  Entropy
//  (C) 2007-2009 Codesign
//  Licensed under LGPL (v3)
//

#import <Foundation/Foundation.h>

@class EXContainer;

@interface EXTransaction : NSObject {
	EXContainer* container;
	NSMutableDictionary* storedObjects;
	NSTimer* timer;
	BOOL invalidated;
	BOOL timeoutExceptionRaised;
}

- (id)initWithContainer:(EXContainer*)_container timeout:(NSTimeInterval)timeout;
- (void)commit;
- (void)rollback;
- (int)storeObject:(id)object;
- (BOOL)removeObject:(id)object;
- (NSTimer*)timer;

@end
