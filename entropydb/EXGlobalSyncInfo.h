//
//  EXGlobalSyncInfo.h
//  Entropy
//  (C) 2007-2009 Codesign
//  Licensed under LGPL (v3)
//

#import <Foundation/Foundation.h>

@interface EXGlobalSyncInfo : NSObject {
	NSTimeInterval lastIncomingSync;
	NSString* containerIdentifier;
}

- (id)initWithContainerIdentifier:(NSString*)_containerIdentifier;
- (NSString*)containerIdentifier;
- (void)setLastIncomingSync:(NSTimeInterval)timeInterval;
- (NSTimeInterval)lastIncomingSync;

@end
