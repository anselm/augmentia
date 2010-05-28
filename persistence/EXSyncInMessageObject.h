//
//  EXSyncInMessageObject.h
//  Entropy
//  (C) 2007-2009 Codesign
//  Licensed under LGPL (v3)
//

#import <Foundation/Foundation.h>

@interface EXSyncInMessageObject : NSObject {
	NSTimeInterval lastSync;
	NSString* containerIdentifier;
}

- (id)initWithLastSyncedUpdate:(NSTimeInterval)_lastSync containerIdentifier:(NSString*)_containerIdentifier;
- (NSTimeInterval)lastSync;
- (NSString*)containerIdentifier;

@end
