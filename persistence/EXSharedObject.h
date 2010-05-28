//
//  EXSharedObject.h
//  Entropy
//  (C) 2007-2009 Codesign
//  Licensed under LGPL (v3)
//

#import <Foundation/Foundation.h>
#import "EXPersistentObject.h"

@interface EXSharedObject : EXPersistentObject <NSCoding> {
	long long __uniqueID;
	NSString* containerIdentifier;
}

- (long long)__uniqueID;
- (NSString*)containerIdentifier;
- (void)setContainerIdentifier:(NSString*)_containerIdentifier;

@end
