//
//  EXProxy.h
//  Entropy
//  (C) 2007-2009 Codesign
//  Licensed under LGPL (v3)
//

#import <Foundation/Foundation.h>
#import "EXContainer.h"

@interface EXProxy : NSObject {
	int objectID;
	EXContainer* container;
	NSMutableDictionary* loadedObjects;
	id object;
}

- (id)initWithObjectID:(int)oid container:(EXContainer*)_container loadedObjects:(NSMutableDictionary*)_loadedObjects;
- (BOOL)__isUnused;
- (id)__object;

@end
