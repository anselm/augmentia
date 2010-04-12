//
//  EXDecomposer.h
//  Entropy
//  (C) 2007-2009 Codesign
//  Licensed under LGPL (v3)
//

#import <Foundation/Foundation.h>
#import "sqlite3.h"

@class EXContainer;

@interface EXDecomposer : NSObject {
	sqlite3* db;
	EXContainer* container;
}

- (id)initWithDatabase:(sqlite3*)_db container:(EXContainer*)_container;
- (NSNumber*)decomposeObject:(id)object withObjectID:(NSNumber*)objectID storedObjects:(NSMutableDictionary*)storedObjects processedObjects:(NSMutableSet*)processedObjects;
- (NSNumber*)decomposeObject:(id)object withObjectID:(NSNumber*)objectID storedObjects:(NSMutableDictionary*)storedObjects processedObjects:(NSMutableSet*)processedObjects asNew:(BOOL)asNew;
- (void)composeObject:(id)object withObjectID:(NSNumber*)objectID versionID:(int)versionID retrievedObjects:(NSMutableDictionary*)retrievedObjects lazyLoading:(BOOL)lazyLoading;
- (void)processArrayElement:(id)element elements:(NSMutableArray*)elements storedObjects:(NSMutableDictionary*)storedObjects processedObjects:(NSMutableSet*)processedObjects;
- (void)processArrayElement:(id)element elements:(NSMutableArray*)elements retrievedObjects:(NSMutableDictionary*)retrievedObjects lazyLoading:(BOOL)lazyLoading;
+ (BOOL)shouldBeSerialized:(id)object;

@end
