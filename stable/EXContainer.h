//
//  EXContainer.h
//  Entropy
//  (C) 2007-2009 Codesign
//  Licensed under LGPL (v3)
//

#import <Foundation/Foundation.h>
#import "EXFile.h"
#import "EXDecomposer.h"
#import "EXPredicate.h"
#import "EXDrainer.h"
#import "EXTransaction.h"
#import "EXMessage.h"
#import "EXSyncInfo.h"
#import "EXGlobalSyncInfo.h"
#import "sqlite3.h"

@interface EXContainer : NSObject {
	sqlite3* db;
	EXDecomposer* decomposer;
	NSMutableDictionary* objectIDs;
	NSMutableArray* objects;
	EXDrainer* drainer;
	NSLock* transactionLock;
	NSString* uniqueIdentifier;
	id delegate;
	NSTimer* drainTimer;
	BOOL transactionInProgress;
}

// public methods

- (id)initWithFile:(EXFile*)file;
- (id)initWithDocumentFile:(NSString*)file;
- (int)storeObject:(id)object;
- (int)storeObject:(id)object asNew:(BOOL)asNew;
- (NSArray*)queryWithClass:(Class)cls;
- (NSArray*)queryWithClass:(Class)cls lazyLoading:(BOOL)lazyLoading;
- (id)queryForSingletonWithClass:(Class)cls allocAndInitIfNotExists:(BOOL)allocAndInitIfNotExists;
- (NSArray*)queryWithClass:(Class)cls predicate:(EXPredicate*)predicate;
#ifdef __BLOCKS__
- (NSArray*)queryWithClass:(Class)cls condition:(BOOL(^)(id))block;
#endif
- (NSArray*)queryWithClass:(Class)cls predicate:(EXPredicate*)predicate lazyLoading:(BOOL)lazyLoading;
- (id)queryWithID:(int)_objectID;
- (id)queryWithID:(int)_objectID lazyLoading:(BOOL)lazyLoading;
- (BOOL)removeObject:(id)object;
- (EXTransaction*)transaction;
- (EXTransaction*)transactionWithTimeout:(NSTimeInterval)timeout;
- (void)allowMessagingOnPort:(int)port;
- (void)synchronizeWithPort:(int)port host:(NSString*)host;
- (id)delegate;
- (void)setDelegate:(id)_delegate;
- (BOOL)isTransactionInProgress;
												 
// private methods

- (void)postMessage:(EXMessage*)message toHost:(NSString*)host port:(int)port;
- (BOOL)sendMessages;
- (EXGlobalSyncInfo*)globalSyncInfo;
- (NSString*)uniqueIdentifier;
- (id)messageReceived:(id)messageObject;
- (BOOL)messageDelivered:(EXMessage*)message withReply:(id)reply;
- (EXSyncInfo*)syncInfoForObjectID:(int)objectID objectUniqueID:(long long)_objectUniqueID action:(EXSyncInfoAction)action className:(NSString*)className containerIdentifier:(NSString*)containerIdentifier;
- (int)storeLocally:(id)object;
- (BOOL)removeObject:(id)object atomically:(BOOL)atomically locally:(BOOL)locally;
- (void)bindObject:(id)object toID:(int)objectID;
- (int)IDOfObject:(id)object;
- (int)store:(id)object atomically:(BOOL)atomically storedObjects:(NSMutableDictionary*)storedObjects locally:(BOOL)locally processedObjects:(NSMutableSet*)processedObjects;
- (int)store:(id)object atomically:(BOOL)atomically storedObjects:(NSMutableDictionary*)storedObjects locally:(BOOL)locally processedObjects:(NSMutableSet*)processedObjects asNew:(BOOL)asNew;
- (id)queryWithID:(int)_objectID atomically:(BOOL)atomically retrievedObjects:(NSMutableDictionary*)retrievedObjects lazyLoading:(BOOL)lazyLoading;
- (NSArray*)queryWithClass:(Class)cls predicate:(EXPredicate*)predicate atomically:(BOOL)atomically retrievedObjects:(NSMutableDictionary*)retrievedObjects lazyLoading:(BOOL)lazyLoading;
- (void)drain;
- (void)createDrainer;
- (void)autoreleaseDrainer;
- (BOOL)executeSQL:(NSString*)command;
- (BOOL)executeSQL:(NSString*)command raiseExceptionOnFailure:(BOOL)raiseExceptionOnFailure;
+ (BOOL)executeSQL:(NSString*)command database:(sqlite3*)db;
+ (BOOL)executeSQL:(NSString*)command database:(sqlite3*)db raiseExceptionOnFailure:(BOOL)raiseExceptionOnFailure;
+ (long long)uniqueID;
- (sqlite3*)database;
+ (BOOL)isCollection:(id)object;
- (void)lockForTransaction;
- (void)unlockForTransaction;
- (NSSet*)subclassesOfClass:(Class)cls;
- (NSString*)listOfSubclassesOfClass:(Class)cls;

@end
