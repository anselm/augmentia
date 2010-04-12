//
//  EXContainer.m
//  Entropy
//  (C) 2007-2009 Codesign
//  Licensed under LGPL (v3)
//

#import "EXContainer.h"
#import "EXException.h"
#import "EXSharedObject.h"
#import "EXPredicateEqualInt64.h"
#import "EXPredicateEqualInt.h"
#import "EXPredicateEqualText.h"
#import "EXSyncOutMessageObject.h"
#import "EXContainerUniqueIdentifier.h"
#import "EXUpdateRequestReply.h"
#import "EXSyncInMessageObject.h"
#import "EXPersistentObject.h"
#import "LXSocket.h"
#import "NSObject_iPhone_cat.h"

#define EXActionSendingMessage	1

#define EXReplySuccess			1
#define EXReplyFailure			2
#define EXReplyConfirmation		3

#define DRAIN_INTERVAL 60

@implementation EXContainer

+ (void)initialize {
	srandomdev();
}

- (id)initWithDocumentFile:(NSString*)file {
    NSArray* paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    NSString* documentsDirectory = [paths objectAtIndex: 0];
	file = [@"/" stringByAppendingString: file];
	NSString* fileName = [documentsDirectory stringByAppendingString: file];
	return [[EXContainer alloc] initWithFile: [EXFile fileWithName: fileName]];
}

- (id)initWithFile:(EXFile*)file {
	if (self = [super init]) {
		int rc = sqlite3_open([[file fileName] UTF8String], &db);
		if (rc) {
			NSLog(@"Can't open database: %s\n", sqlite3_errmsg(db));
		} else {
			NSArray* commands = [NSArray arrayWithObjects:
								 @"CREATE TABLE IF NOT EXISTS objects (oid INTEGER, vid INTEGER, classname TEXT, published INTEGER, timestamp REAL)",
								 @"CREATE TABLE IF NOT EXISTS propertytypes (oid INTEGER, vid INTEGER, name TEXT, type TEXT)",
								 @"CREATE TABLE IF NOT EXISTS propertyvalues_integer (oid INTEGER, vid INTEGER, name TEXT, value INTEGER)",
								 @"CREATE TABLE IF NOT EXISTS propertyvalues_real (oid INTEGER, vid INTEGER, name TEXT, value REAL)",
								 @"CREATE TABLE IF NOT EXISTS propertyvalues_text (oid INTEGER, vid INTEGER, name TEXT, value TEXT)",
								 @"CREATE TABLE IF NOT EXISTS propertyvalues_reference (oid INTEGER, vid INTEGER, name TEXT, value INTEGER)",
								 @"CREATE TABLE IF NOT EXISTS propertyvalues_binary (oid INTEGER, vid INTEGER, name TEXT, value BLOB)",
								 
								 @"CREATE INDEX IF NOT EXISTS idx_objects ON objects (oid, classname, published, timestamp)",
								 @"CREATE INDEX IF NOT EXISTS idx_propertytypes ON propertytypes (oid, vid, name)",
								 @"CREATE INDEX IF NOT EXISTS idx_propertyvalues_integer ON propertyvalues_integer (oid, vid, name, value)",
								 @"CREATE INDEX IF NOT EXISTS idx_propertyvalues_real ON propertyvalues_real (oid, vid, name, value)",
								 @"CREATE INDEX IF NOT EXISTS idx_propertyvalues_text ON propertyvalues_text (oid, vid, name, value)",
								 @"CREATE INDEX IF NOT EXISTS idx_propertyvalues_reference ON propertyvalues_reference (oid, vid, name, value)",
								 @"CREATE INDEX IF NOT EXISTS idx_propertyvalues_binary ON propertyvalues_binary (oid, vid, name)",
								 nil];
			for (NSString* command in commands) {
				if ([self executeSQL: command] == NO) [EXException raise: @"EXException" format: @"Cannot initialize database"];
			}
		}
		decomposer = [[EXDecomposer alloc] initWithDatabase: db container: self];
		objectIDs = [[NSMutableDictionary alloc] init];
		objects = [[NSMutableArray alloc] init];
		transactionLock = [[NSLock alloc] init];
		drainTimer = [NSTimer scheduledTimerWithTimeInterval: DRAIN_INTERVAL target: self selector: @selector(drain:) userInfo: nil repeats: YES];
		[self createDrainer];
		NSArray* resultSet = [self queryWithClass: [EXContainerUniqueIdentifier class]];
		if ([resultSet count] > 0) uniqueIdentifier = [[[resultSet objectAtIndex: 0] uniqueIdentifier] retain];
		else {
			EXContainerUniqueIdentifier* containerUniqueIdentifier = [[EXContainerUniqueIdentifier alloc] init];
			[self storeObject: containerUniqueIdentifier];
			uniqueIdentifier = [[containerUniqueIdentifier uniqueIdentifier] retain];
			[containerUniqueIdentifier release];
		}
	}
	return self;
}

- (EXTransaction*)transaction {
	return [self transactionWithTimeout: 0];
}

- (EXTransaction*)transactionWithTimeout:(NSTimeInterval)timeout {
	[self autoreleaseDrainer];
	return [[[EXTransaction alloc] initWithContainer: self timeout: timeout] autorelease];
}

- (BOOL)isTransactionInProgress {
	return transactionInProgress;
}

- (int)storeObject:(id)object {
	return [self storeObject: object asNew: NO];
}

- (int)storeObject:(id)object asNew:(BOOL)asNew {
	if ([EXContainer isCollection: object]) {
		[EXException raise: @"EXException" format: @"A collection object cannot be stored directly"];
		return -1;
	}
	NSMutableDictionary* storedObjects = [[NSMutableDictionary alloc] init];
	NSMutableSet* processedObjects = [[NSMutableSet alloc] init];
	int objectID = [self store: object atomically: YES storedObjects: storedObjects locally: NO processedObjects: processedObjects asNew: asNew];
	[processedObjects release];
	[storedObjects release];
	return objectID;
}

- (int)storeLocally:(id)object {
	NSMutableDictionary* storedObjects = [[NSMutableDictionary alloc] init];
	NSMutableSet* processedObjects = [[NSMutableSet alloc] init];
	int objectID = [self store: object atomically: YES storedObjects: storedObjects locally: YES processedObjects: processedObjects];
	[processedObjects release];
	[storedObjects release];
	return objectID;
}

- (int)store:(id)object atomically:(BOOL)atomically storedObjects:(NSMutableDictionary*)storedObjects locally:(BOOL)locally processedObjects:(NSMutableSet*)processedObjects {
	return [self store: object atomically: atomically storedObjects: storedObjects locally: locally processedObjects: processedObjects asNew: NO];
}

- (int)store:(id)object atomically:(BOOL)atomically storedObjects:(NSMutableDictionary*)storedObjects locally:(BOOL)locally processedObjects:(NSMutableSet*)processedObjects asNew:(BOOL)asNew {
	NSValue* key = [NSValue valueWithPointer: object];
	if ([processedObjects containsObject: key]) {
		[EXException raise: @"EXException" format: @"Object hierarchy to be stored not acyclic: %@", [object className]];
		return -1;
	}
	[processedObjects addObject: key];
	if (atomically == YES) {
		[self autoreleaseDrainer];
		[self lockForTransaction];
		[self executeSQL: @"BEGIN EXCLUSIVE TRANSACTION" raiseExceptionOnFailure: YES];
	}
	@try {
		if ([object isKindOfClass: [EXSharedObject class]]) {
			if (!locally || [object containerIdentifier] == nil) {
				[object setContainerIdentifier: [self uniqueIdentifier]];
			}
		}
		NSNumber* objectID = [objectIDs objectForKey: key];
		NSNumber* assignedObjectID = [decomposer decomposeObject: object withObjectID: objectID storedObjects: storedObjects processedObjects: processedObjects asNew: asNew];
		if (objectID == nil) {
			[objectIDs setObject: assignedObjectID forKey: key];
			[objects addObject: object];
		}
		if ([object isKindOfClass: [EXSharedObject class]]) {
			EXSyncInfo* syncInfo = [self syncInfoForObjectID: [assignedObjectID intValue] objectUniqueID: [object __uniqueID] action: EXSyncInfoActionUpdate className: [object className] containerIdentifier: [object containerIdentifier]];
			[syncInfo setSyncedOut: locally];
			[syncInfo setTimeStampToNow];
			[self store: syncInfo atomically: NO storedObjects: storedObjects locally: YES processedObjects: processedObjects];
		}
		if (atomically == YES) {
			[self executeSQL: @"COMMIT" raiseExceptionOnFailure: YES];
			[self unlockForTransaction];
		}
		return [assignedObjectID intValue];
	} @catch (NSException* exception) {
		if (atomically == YES) {
			[self executeSQL: @"ROLLBACK" raiseExceptionOnFailure: YES];
			[self unlockForTransaction];
		}
		NSLog(@"Nested exception: %@", exception);
		[EXException raise: @"EXException" format: @"Cannot store object"];
	}
	return -1;
}

- (EXSyncInfo*)syncInfoForObjectID:(int)objectID objectUniqueID:(long long)_objectUniqueID action:(EXSyncInfoAction)action className:(NSString*)className containerIdentifier:(NSString*)containerIdentifier {
	NSMutableDictionary* retrievedObjects = [[NSMutableDictionary alloc] init];
	EXPredicate* predicate = [[[EXPredicateEqualInt alloc] initWithFieldName: @"objectID" intValue: objectID] autorelease];
	NSArray* resultSet = [self queryWithClass: [EXSyncInfo class] predicate: predicate atomically: NO retrievedObjects: retrievedObjects lazyLoading: NO];
	[retrievedObjects autorelease];
	if ([resultSet count] > 0) {
		EXSyncInfo* result = [resultSet objectAtIndex: 0];
		[result setObjectAction: action];
		return result;
	} else {
		EXSyncInfo* syncInfo = [[[EXSyncInfo alloc] initWithObjectID: objectID objectUniqueID: _objectUniqueID action: action className: className containerIdentifier: containerIdentifier] autorelease];
		return syncInfo;
	}
}

- (EXGlobalSyncInfo*)globalSyncInfo {
	NSArray* resultSet = [self queryWithClass: [EXGlobalSyncInfo class]];
	if ([resultSet count] > 0) {
		return [resultSet objectAtIndex: 0];
	} else {
		EXGlobalSyncInfo* globalSyncInfo = [[[EXGlobalSyncInfo alloc] initWithContainerIdentifier: [self uniqueIdentifier]] autorelease];
		[self storeObject: globalSyncInfo];
		return globalSyncInfo;
	}
}

- (BOOL)removeObject:(id)object {
	return [self removeObject: object atomically: YES locally: NO];
}

- (BOOL)removeObject:(id)object atomically:(BOOL)atomically locally:(BOOL)locally {
	NSValue* key = [NSValue valueWithPointer: object];
	NSNumber* objectID = [objectIDs objectForKey: key];
	if (objectID != nil) {
		if (atomically == YES) {
			[self autoreleaseDrainer];
			[self lockForTransaction];
			[self executeSQL: @"BEGIN EXCLUSIVE TRANSACTION" raiseExceptionOnFailure: YES];
		}
		@try {
			[self executeSQL: [NSString stringWithFormat: @"UPDATE objects SET published = 0 WHERE oid = %@", objectID] raiseExceptionOnFailure: YES];
			if ([object isKindOfClass: [EXSharedObject class]]) {
				if (!locally || [object containerIdentifier] == nil) {
					[object setContainerIdentifier: [self uniqueIdentifier]];
				}
				EXSyncInfo* syncInfo = [self syncInfoForObjectID: [objectID intValue] objectUniqueID: [object __uniqueID] action: EXSyncInfoActionDeletion className: [object className] containerIdentifier: [object containerIdentifier]];
				[syncInfo setSyncedOut: locally];
				[syncInfo setTimeStampToNow];
				NSMutableDictionary* storedObjects = [[NSMutableDictionary alloc] init];
				NSMutableSet* processedObjects = [[NSMutableSet alloc] init];
				[self store: syncInfo atomically: NO storedObjects: storedObjects locally: YES processedObjects: processedObjects];
				[storedObjects release];
				[processedObjects release];
			}
			if (atomically == YES) {
				[self executeSQL: @"COMMIT" raiseExceptionOnFailure: YES];
				[self unlockForTransaction];
			}
			return YES;
		} @catch (NSException* exception) {
			if (atomically == YES) {
				[self executeSQL: @"ROLLBACK" raiseExceptionOnFailure: YES];
				[self unlockForTransaction];
			}
			NSLog(@"%@", exception);
			[EXException raise: @"EXException" format: @"Cannot delete object"];
		}
	}
	return NO;
}

- (void)bindObject:(id)object toID:(int)objectID {
	NSValue* key = [NSValue valueWithPointer: object];
	[objectIDs setObject: [NSNumber numberWithInt: objectID] forKey: key];
	[objects addObject: object];
}

- (void)postMessage:(EXMessage*)message toHost:(NSString*)host port:(int)port {
	[message setHost: host port: port];
	[self storeObject: message];
}

- (BOOL)sendMessages {
	EXPredicate* predicate = [[[EXPredicateEqualInt alloc] initWithFieldName: @"status" intValue: EXMessageStatusPending] autorelease];
	NSArray* resultSet = [self queryWithClass: [EXMessage class] predicate: predicate];
	resultSet = [resultSet sortedArrayUsingSelector: @selector(compare:)];
	//NSLog(@"CLIENT: pending messages: %u", [resultSet count]);
	NSString* host = nil; int port; LXSocket* socket = nil;
	for (EXMessage* message in resultSet) {
		if (host == nil || ![host isEqual: [message host]] || port != [message port]) {
			[socket release];
			socket = [[LXSocket alloc] init];
			if (![socket connect: [message host] port: [message port]]) {
				[socket release];
				socket = nil;
				continue;
			}
		}
		[socket sendInt: EXActionSendingMessage];
		[socket sendObject: [message object]];
		if ([socket readInt] == EXReplySuccess) {
			id reply = [socket readObject];
			if ([self messageDelivered: message withReply: reply] == YES) {
				[message setStatusToProcessed];
				[self storeObject: message];
				[socket sendInt: EXReplyConfirmation];
			} else [socket sendInt: EXReplyFailure];
		}
	}
	[socket release];
	return YES;
}

- (void)allowMessagingOnPort:(int)port {
	LXSocket* serverSocket = [[LXSocket alloc] init];
	[serverSocket bindToPort: port];
	[serverSocket listen: 1000];
	[NSThread detachNewThreadSelector: @selector(serverListener:) toTarget: self withObject: serverSocket];
}

- (void)serverListener:(LXSocket*)serverSocket {
	while (YES) {
		NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];
		LXSocket* socket = [[serverSocket accept] autorelease];
		switch ([socket readInt]) {
			case EXActionSendingMessage:;
				id object = [socket readObject];
				id reply = [self messageReceived: object];
				if (reply != nil) {
					[socket sendInt: EXReplySuccess];
					[socket sendObject: reply];
					if ([socket readInt] == EXReplyConfirmation) {
					}
				} else [socket sendInt: EXReplyFailure];
				break;
		}
		[pool release];
	}
}

- (id)messageReceived:(id)messageObject {
	if ([messageObject isKindOfClass: [EXSyncOutMessageObject class]]) {
		id genericObject = [messageObject object];
		EXSharedObject* sharedObject = [genericObject isKindOfClass: [EXSharedObject class]] ? genericObject : nil;
		NSString* className = [genericObject isKindOfClass: [EXSharedObject class]] ? [genericObject className] : genericObject;
		EXPredicate* predicate = [[[EXPredicateEqualInt64 alloc] initWithFieldName: @"__uniqueID" int64Value: [messageObject objectUniqueID]] autorelease];
		NSArray* resultSet = [self queryWithClass: NSClassFromString(className) predicate: predicate];
		if ([resultSet count] > 0) {
			id object = [resultSet objectAtIndex: 0];
			if ([messageObject objectAction] == EXSyncInfoActionUpdate) {
				[self bindObject: sharedObject toID: [self IDOfObject: object]];
				[self storeLocally: sharedObject];
			} else if ([messageObject objectAction] == EXSyncInfoActionDeletion) {
				[self removeObject: object atomically: YES locally: YES];
			}
		} else {
			if ([messageObject objectAction] == EXSyncInfoActionUpdate) [self storeLocally: sharedObject];
		}
		return @"1";
	} else if ([messageObject isKindOfClass: [EXSyncInMessageObject class]]) {
		NSArray* resultSet = [self queryWithClass: [EXSyncInfo class]];
		resultSet = [resultSet sortedArrayUsingSelector: @selector(compare:)];
		NSMutableArray* updates = [[NSMutableArray alloc] init];
		NSTimeInterval lastUpdate = 0;
		for (EXSyncInfo* syncInfo in resultSet) {
			if ([syncInfo timeStamp] > [messageObject lastSync]) {
				if (![[syncInfo containerIdentifier] isEqual: [messageObject containerIdentifier]]) {
					if ([syncInfo objectAction] == EXSyncInfoActionUpdate) {
						EXSharedObject* object = [self queryWithID: [syncInfo objectID]];
						if (object != nil) {
							[updates addObject: [NSArray arrayWithObjects: [NSNumber numberWithInt: [syncInfo objectAction]], object, nil]];
						}
					} else {
						[updates addObject: [NSArray arrayWithObjects: [NSNumber numberWithInt: [syncInfo objectAction]], [NSNumber numberWithLongLong: [syncInfo objectUniqueID]], [syncInfo objectClassName], nil]];
					}
					lastUpdate = [syncInfo timeStamp];
				}
			}
		}
		EXUpdateRequestReply* reply = [[[EXUpdateRequestReply alloc] initWithLastSyncedUpdate: lastUpdate updates: updates] autorelease];
		[updates release];
		return reply;
	} else NSLog(@"SERVER DELEGATE: processing received message - %@", messageObject);
	return nil;
}

- (BOOL)messageDelivered:(EXMessage*)message withReply:(id)reply {
	if ([reply isKindOfClass: [EXUpdateRequestReply class]]) {
		NSArray* updates = [reply updates];
		NSLog(@"should process %u update(s)", [updates count]);
		for (NSArray* update in updates) {
			EXSyncInfoAction action = [[update objectAtIndex: 0] intValue];
			if (action == EXSyncInfoActionDeletion) {
				long long uniqueID = [[update objectAtIndex: 1] longLongValue];
				NSString* className = [update objectAtIndex: 2];
				EXPredicate* predicate = [[[EXPredicateEqualInt64 alloc] initWithFieldName: @"__uniqueID" int64Value: uniqueID] autorelease];
				NSArray* resultSet = [self queryWithClass: NSClassFromString(className) predicate: predicate];
				BOOL existing = [resultSet count] > 0;
				if (existing) {
					id object = [resultSet objectAtIndex: 0];
					[self removeObject: object atomically: YES locally: YES];
					if (delegate != nil && [delegate respondsToSelector: @selector(didReceiveDeletion:)])
						[delegate performSelector: @selector(didReceiveDeletion:) withObject: object];
				}
			} else {
				EXSharedObject* sharedObject = [update objectAtIndex: 1];
				EXPredicate* predicate = [[[EXPredicateEqualInt64 alloc] initWithFieldName: @"__uniqueID" int64Value: [sharedObject __uniqueID]] autorelease];
				NSArray* resultSet = [self queryWithClass: [sharedObject class] predicate: predicate];
				BOOL existing = [resultSet count] > 0;
				if (existing) {
					id object = [resultSet objectAtIndex: 0];
					[self bindObject: sharedObject toID: [self IDOfObject: object]];
				}
				[self storeLocally: sharedObject];
				if (delegate != nil && [delegate respondsToSelector: @selector(didReceiveUpdate:)])
					[delegate performSelector: @selector(didReceiveUpdate:) withObject: sharedObject];
			}
		}
		NSTimeInterval lastSyncedUpdate = [reply lastSyncedUpdate];
		if (lastSyncedUpdate > 0) {
			EXGlobalSyncInfo* globalSyncInfo = [self globalSyncInfo];
			[globalSyncInfo setLastIncomingSync: lastSyncedUpdate];
			[self storeObject: globalSyncInfo];
		}
	} else NSLog(@"CLIENT DELEGATE: message delivered - %@ (%@)", reply, [reply className]);
	return YES;
}

- (void)synchronizeWithPort:(int)port host:(NSString*)host {
	LXSocket* socket = [[LXSocket alloc] init];
	BOOL canConnect = [socket connect: host port: port];
	[socket release];
	if (canConnect == NO) { NSLog(@"no connection, won't sync"); return; }

	EXPredicate* predicate = [[[EXPredicateEqualInt alloc] initWithFieldName: @"syncedOut" intValue: NO] autorelease];
	NSArray* resultSet = [self queryWithClass: [EXSyncInfo class] predicate: predicate];
	resultSet = [resultSet sortedArrayUsingSelector: @selector(compare:)];
	NSLog(@"%u objects should be synced out", [resultSet count]);
	for (EXSyncInfo* syncInfo in resultSet) {
		if ([syncInfo objectAction] == EXSyncInfoActionDeletion) {
			EXSyncOutMessageObject* messageObject = [[EXSyncOutMessageObject alloc] initWithObject: [syncInfo objectClassName] objectUniqueID: [syncInfo objectUniqueID] action: [syncInfo objectAction]];
			EXMessage* message = [[EXMessage alloc] initWithObject: messageObject];
			[messageObject release];
			[self postMessage: message toHost: host port: port];
			[message release];
			[syncInfo setSyncedOut: YES];
			[self storeObject: syncInfo];
		} else {
			EXSharedObject* object = [self queryWithID: [syncInfo objectID]];
			if (object == nil) [self removeObject: syncInfo];
			else {
				EXSyncOutMessageObject* messageObject = [[EXSyncOutMessageObject alloc] initWithObject: object action: [syncInfo objectAction]];
				EXMessage* message = [[EXMessage alloc] initWithObject: messageObject];
				[messageObject release];
				[self postMessage: message toHost: host port: port];
				[message release];
				[syncInfo setSyncedOut: YES];
				[self storeObject: syncInfo];
			}
		}
	}
	EXGlobalSyncInfo* globalSyncInfo = [self globalSyncInfo];
	EXMessage* message = [[EXMessage alloc] initWithObject: [[[EXSyncInMessageObject alloc] initWithLastSyncedUpdate: [globalSyncInfo lastIncomingSync] containerIdentifier: [self uniqueIdentifier]] autorelease]];
	[self postMessage: message toHost: host port: port];
	[message release];
	[self sendMessages];
}

- (NSSet*)subclassesOfClass:(Class)cls {
	NSMutableSet* subclasses = [[NSMutableSet alloc] init];
	sqlite3_stmt* stmt; int rc;
	rc = sqlite3_prepare_v2(db, "SELECT DISTINCT classname FROM objects WHERE published = 1", -1, &stmt, 0);
	if (rc != SQLITE_OK) [EXException raise: @"EXException" format: @"Cannot prepare SQL query or bind variable"];
	while (sqlite3_step(stmt) == SQLITE_ROW) {
		char* _className = (char*) sqlite3_column_text(stmt, 0);
		NSString* className = [[NSString alloc] initWithUTF8String: _className];
		if ([NSClassFromString(className) isSubclassOfClass: cls]) [subclasses addObject: className];
		[className release];
	}
	sqlite3_finalize(stmt);
	return subclasses;
}

- (NSString*)listOfSubclassesOfClass:(Class)cls {
	NSSet* subclasses = [self subclassesOfClass: cls];
	NSMutableString* listOfSubclasses = [[NSMutableString alloc] initWithString: @"("];
	BOOL first = YES;
	for (NSString* subclass in subclasses) {
		if (first == YES) first = NO; else [listOfSubclasses appendString: @", "];
		[listOfSubclasses appendString: @"'"];
		[listOfSubclasses appendString: subclass];
		[listOfSubclasses appendString: @"'"];
	}
	[listOfSubclasses appendString: @")"];
	[subclasses release];
	return listOfSubclasses;
}

- (NSArray*)queryWithClass:(Class)cls {
	return [self queryWithClass: cls lazyLoading: NO];
}

- (NSArray*)queryWithClass:(Class)cls lazyLoading:(BOOL)lazyLoading {
	[self autoreleaseDrainer];
	[self lockForTransaction];
	[self executeSQL: @"BEGIN EXCLUSIVE TRANSACTION" raiseExceptionOnFailure: YES];
	NSMutableDictionary* retrievedObjects = [[NSMutableDictionary alloc] init];
	@try {
		NSMutableArray* resultSet = [NSMutableArray array];
		sqlite3_stmt* stmt; int rc;
		NSString* listOfSubclasses = [self listOfSubclassesOfClass: cls];
		rc = sqlite3_prepare_v2(db,
								[[NSString stringWithFormat: @"SELECT oid, vid, classname FROM objects WHERE published = 1 AND classname IN %@", listOfSubclasses] UTF8String],
								-1, &stmt, 0);
		[listOfSubclasses release];
		//NSString* className = NSStringFromClass(cls);
		//rc = sqlite3_prepare_v2(db, "SELECT oid, vid FROM objects WHERE published = 1 AND classname = ?", -1, &stmt, 0);
		//if (rc == SQLITE_OK) rc = sqlite3_bind_text(stmt, 1, [className UTF8String], -1, SQLITE_STATIC);
		if (rc != SQLITE_OK) [EXException raise: @"EXException" format: @"Cannot prepare SQL query or bind variable"];
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			NSNumber* objectID = [NSNumber numberWithInt: sqlite3_column_int(stmt, 0)];
			int versionID = sqlite3_column_int(stmt, 1);
			char* _className = (char*) sqlite3_column_text(stmt, 2);
			NSString* className = [[NSString alloc] initWithUTF8String: _className];
			id object = [[NSClassFromString(className) alloc] autorelease];
			[decomposer composeObject: object withObjectID: objectID versionID: versionID retrievedObjects: retrievedObjects lazyLoading: lazyLoading];
			NSValue* key = [NSValue valueWithPointer: object];
			[objectIDs setObject: objectID forKey: key];
			[objects addObject: object];
			[resultSet addObject: object];
			if ([object isKindOfClass: [EXPersistentObject class]]) [object setContainer: self];
		}
		sqlite3_finalize(stmt);
		[self executeSQL: @"COMMIT" raiseExceptionOnFailure: YES];
		[self unlockForTransaction];
		return resultSet;
	} @catch (NSException* exception) {
		[self executeSQL: @"ROLLBACK" raiseExceptionOnFailure: YES];
		[self unlockForTransaction];
		NSLog(@"%@", exception);
		[EXException raise: @"EXException" format: @"Cannot query objects"];
	} @finally {
		[retrievedObjects autorelease];
	}
	return nil;
}

- (id)queryForSingletonWithClass:(Class)cls allocAndInitIfNotExists:(BOOL)allocAndInitIfNotExists {
	NSArray* records = [self queryWithClass: cls];
	if ([records count] != 0) return [records objectAtIndex: 0];
	else return allocAndInitIfNotExists ? [[[cls alloc] init] autorelease] : nil;
}

- (NSArray*)queryWithClass:(Class)cls predicate:(EXPredicate*)predicate {
	return [self queryWithClass: cls predicate: predicate lazyLoading: NO];
}

#ifdef __BLOCKS__
- (NSArray*)queryWithClass:(Class)cls condition:(BOOL(^)(id))block {
	NSMutableArray* filteredObjects = [NSMutableArray array];
	NSArray* _objects = [self queryWithClass: cls];
	for (id obj in _objects) {
		if (block(obj) == YES) [filteredObjects addObject: obj];
	}
	return filteredObjects;
}
#endif

- (NSArray*)queryWithClass:(Class)cls predicate:(EXPredicate*)predicate lazyLoading:(BOOL)lazyLoading {
	NSMutableDictionary* retrievedObjects = [[NSMutableDictionary alloc] init];
	NSArray* result = [self queryWithClass: cls predicate: predicate atomically: YES retrievedObjects: retrievedObjects lazyLoading: lazyLoading];
	[retrievedObjects autorelease];
	return result;
}

- (NSArray*)queryWithClass:(Class)cls predicate:(EXPredicate*)predicate atomically:(BOOL)atomically retrievedObjects:(NSMutableDictionary*)retrievedObjects lazyLoading:(BOOL)lazyLoading {
	if (atomically) {
		[self autoreleaseDrainer];
		[self lockForTransaction];
		[self executeSQL: @"BEGIN EXCLUSIVE TRANSACTION" raiseExceptionOnFailure: YES];
	}
	@try {
		//NSString* className = NSStringFromClass(cls);
		NSMutableArray* resultSet = [NSMutableArray array];
		sqlite3_stmt* stmt; int rc;
		NSString* listOfSubclasses = [self listOfSubclassesOfClass: cls];
		// ****************************
		// optimized query for integers
		// ****************************
		if ([predicate isKindOfClass: [EXPredicateEqualInt class]]) {
			//NSString* sql = @"SELECT oid, vid FROM objects WHERE published = 1 AND classname = ? AND oid IN (SELECT DISTINCT propertyvalues_integer.oid FROM propertyvalues_integer, objects WHERE published = 1 AND objects.oid = propertyvalues_integer.oid AND objects.vid = propertyvalues_integer.vid AND name = ? AND value = ?)";
			NSString* sql = [NSString stringWithFormat: @"SELECT oid, vid, classname FROM objects WHERE published = 1 AND classname IN %@ AND oid IN (SELECT DISTINCT propertyvalues_integer.oid FROM propertyvalues_integer, objects WHERE published = 1 AND objects.oid = propertyvalues_integer.oid AND objects.vid = propertyvalues_integer.vid AND name = ? AND value = ?)", listOfSubclasses];
			rc = sqlite3_prepare_v2(db, [sql UTF8String], -1, &stmt, 0);
			//if (rc == SQLITE_OK) rc = sqlite3_bind_text(stmt, 1, [className UTF8String], -1, SQLITE_STATIC);
			if (rc == SQLITE_OK) rc = sqlite3_bind_text(stmt, 1, [[predicate fieldName] UTF8String], -1, SQLITE_STATIC);
			if (rc == SQLITE_OK) rc = sqlite3_bind_int(stmt, 2, [(EXPredicateEqualInt*) predicate intValue]);
			if (rc != SQLITE_OK) [EXException raise: @"EXException" format: @"Cannot prepare SQL query or bind variable"];
			//int i = 0;
			while (sqlite3_step(stmt) == SQLITE_ROW) {
				NSNumber* objectID = [NSNumber numberWithInt: sqlite3_column_int(stmt, 0)];
				int versionID = sqlite3_column_int(stmt, 1);
				char* _className = (char*) sqlite3_column_text(stmt, 2);
				NSString* className = [[NSString alloc] initWithUTF8String: _className];
				id object = [[NSClassFromString(className) alloc] autorelease];
				[decomposer composeObject: object withObjectID: objectID versionID: versionID retrievedObjects: retrievedObjects lazyLoading: lazyLoading];
				NSValue* key = [NSValue valueWithPointer: object];
				[objectIDs setObject: objectID forKey: key];
				[objects addObject: object];
				[resultSet addObject: object];
				if ([object isKindOfClass: [EXPersistentObject class]]) [object setContainer: self];
			}
		} else
			// *************************
			// optimized query for texts
			// *************************
			if ([predicate isKindOfClass: [EXPredicateEqualText class]]) {
			//NSString* sql = @"SELECT oid, vid FROM objects WHERE published = 1 AND classname = ? AND oid IN (SELECT DISTINCT propertyvalues_text.oid FROM propertyvalues_text, objects WHERE published = 1 AND objects.oid = propertyvalues_text.oid AND objects.vid = propertyvalues_text.vid AND name = ? AND value = ?)";
			NSString* sql = [NSString stringWithFormat: @"SELECT oid, vid, classname FROM objects WHERE published = 1 AND classname IN %@ AND oid IN (SELECT DISTINCT propertyvalues_text.oid FROM propertyvalues_text, objects WHERE published = 1 AND objects.oid = propertyvalues_text.oid AND objects.vid = propertyvalues_text.vid AND name = ? AND value = ?)", listOfSubclasses];
			rc = sqlite3_prepare_v2(db, [sql UTF8String], -1, &stmt, 0);
			//if (rc == SQLITE_OK) rc = sqlite3_bind_text(stmt, 1, [className UTF8String], -1, SQLITE_STATIC);
			if (rc == SQLITE_OK) rc = sqlite3_bind_text(stmt, 1, [[predicate fieldName] UTF8String], -1, SQLITE_STATIC);
			if (rc == SQLITE_OK) rc = sqlite3_bind_text(stmt, 2, [[(EXPredicateEqualText*) predicate textValue] UTF8String], -1, SQLITE_STATIC);
			if (rc != SQLITE_OK) [EXException raise: @"EXException" format: @"Cannot prepare SQL query or bind variable"];
			//int i = 0;
			while (sqlite3_step(stmt) == SQLITE_ROW) {
				NSNumber* objectID = [NSNumber numberWithInt: sqlite3_column_int(stmt, 0)];
				int versionID = sqlite3_column_int(stmt, 1);
				char* _className = (char*) sqlite3_column_text(stmt, 2);
				NSString* className = [[NSString alloc] initWithUTF8String: _className];
				id object = [[NSClassFromString(className) alloc] autorelease];
				[decomposer composeObject: object withObjectID: objectID versionID: versionID retrievedObjects: retrievedObjects lazyLoading: lazyLoading];
				NSValue* key = [NSValue valueWithPointer: object];
				[objectIDs setObject: objectID forKey: key];
				[objects addObject: object];
				[resultSet addObject: object];
				if ([object isKindOfClass: [EXPersistentObject class]]) [object setContainer: self];
			}
		} else {
			// *****************
			// unoptimized query
			// *****************
			rc = sqlite3_prepare_v2(db,
									[[NSString stringWithFormat: @"SELECT oid, vid, classname FROM objects WHERE published = 1 AND classname IN %@", listOfSubclasses] UTF8String],
									-1, &stmt, 0);
			//rc = sqlite3_prepare_v2(db, "SELECT oid, vid FROM objects WHERE published = 1 AND classname = ?", -1, &stmt, 0);
			//if (rc == SQLITE_OK) rc = sqlite3_bind_text(stmt, 1, [className UTF8String], -1, SQLITE_STATIC);
			if (rc != SQLITE_OK) [EXException raise: @"EXException" format: @"Cannot prepare SQL query or bind variable"];
			while (sqlite3_step(stmt) == SQLITE_ROW) {
				NSNumber* objectID = [NSNumber numberWithInt: sqlite3_column_int(stmt, 0)];
				int versionID = sqlite3_column_int(stmt, 1);
				char* _className = (char*) sqlite3_column_text(stmt, 2);
				NSString* className = [[NSString alloc] initWithUTF8String: _className];
				id object = [NSClassFromString(className) alloc];
				[decomposer composeObject: object withObjectID: objectID versionID: versionID retrievedObjects: retrievedObjects lazyLoading: lazyLoading];
				if ([predicate evaluateWithObject: object] == YES) {
					NSValue* key = [NSValue valueWithPointer: object];
					[objectIDs setObject: objectID forKey: key];
					[objects addObject: object];
					[resultSet addObject: object];
					if ([object isKindOfClass: [EXPersistentObject class]]) [object setContainer: self];
					[object autorelease];
				} else {
					[object release];
				}
			}
		}
		[listOfSubclasses release];
		sqlite3_finalize(stmt);
		if (atomically == YES) {
			[self executeSQL: @"COMMIT" raiseExceptionOnFailure: YES];
			[self unlockForTransaction];
		}
		EXSorting* sorting = [predicate sorting];
		if (sorting != nil)
			return [resultSet sortedArrayUsingFunction: EXSortingFunction context: sorting];
		else return resultSet;
	} @catch (NSException* exception) {
		if (atomically == YES) {
			[self executeSQL: @"ROLLBACK" raiseExceptionOnFailure: YES];
			[self unlockForTransaction];
		}
		NSLog(@"%@", exception);
		[EXException raise: @"EXException" format: @"Cannot query objects"];
	} @finally {
	}
	return nil;
}

- (id)queryWithID:(int)_objectID {
	return [self queryWithID: _objectID lazyLoading: NO];
}

- (id)queryWithID:(int)_objectID lazyLoading:(BOOL)lazyLoading {
	NSMutableDictionary* retrievedObjects = [[NSMutableDictionary alloc] init];
	id object = [self queryWithID: _objectID atomically: YES retrievedObjects: retrievedObjects lazyLoading: lazyLoading];
	[retrievedObjects autorelease];
	return object;
}

- (id)queryWithID:(int)_objectID atomically:(BOOL)atomically retrievedObjects:(NSMutableDictionary*)retrievedObjects lazyLoading:(BOOL)lazyLoading {
	if (atomically == YES) {
		[self autoreleaseDrainer];
		[self lockForTransaction];
		[self executeSQL: @"BEGIN EXCLUSIVE TRANSACTION" raiseExceptionOnFailure: YES];
	}
	@try {
		id object = nil;
		sqlite3_stmt* stmt; int rc;
		rc = sqlite3_prepare_v2(db, "SELECT vid, classname FROM objects WHERE published = 1 AND oid = ?", -1, &stmt, 0);
		if (rc == SQLITE_OK) rc = sqlite3_bind_int(stmt, 1, _objectID);
		if (rc != SQLITE_OK) [EXException raise: @"EXException" format: @"Cannot prepare SQL query or bind variable"];
		if (sqlite3_step(stmt) == SQLITE_ROW) {
			NSNumber* objectID = [NSNumber numberWithInt: _objectID];
			int versionID = sqlite3_column_int(stmt, 0);
			char* _className = (char*) sqlite3_column_text(stmt, 1);
			NSString* className = [NSString stringWithUTF8String: _className];
			Class cls = NSClassFromString(className);
			object = [[cls alloc] autorelease];
			[decomposer composeObject: object withObjectID: objectID versionID: versionID retrievedObjects: retrievedObjects lazyLoading: lazyLoading];
			NSValue* key = [NSValue valueWithPointer: object];
			[objectIDs setObject: objectID forKey: key];
			[objects addObject: object];
			if ([object isKindOfClass: [EXPersistentObject class]]) [object setContainer: self];
		}
		sqlite3_finalize(stmt);
		if (atomically == YES) {
			[self executeSQL: @"COMMIT" raiseExceptionOnFailure: YES];
			[self unlockForTransaction];
		}
		return object;
	} @catch (NSException* exception) {
		if (atomically == YES) {
			[self executeSQL: @"ROLLBACK" raiseExceptionOnFailure: YES];
			[self unlockForTransaction];
		}
		NSLog(@"%@", exception);
		[EXException raise: @"EXException" format: @"Cannot query objects"];
	}
	return nil;
}

- (int)IDOfObject:(id)object {
	NSValue* key = [NSValue valueWithPointer: object];
	return [[objectIDs objectForKey: key] intValue];
}

- (BOOL)executeSQL:(NSString*)command {
	return [EXContainer executeSQL: command database: db];
}

- (BOOL)executeSQL:(NSString*)command raiseExceptionOnFailure:(BOOL)raiseExceptionOnFailure {
	return [EXContainer executeSQL: command database: db raiseExceptionOnFailure: raiseExceptionOnFailure];
}

+ (BOOL)executeSQL:(NSString*)command database:(sqlite3*)db {
	return [self executeSQL: command database: db raiseExceptionOnFailure: NO];
}

+ (BOOL)executeSQL:(NSString*)command database:(sqlite3*)db raiseExceptionOnFailure:(BOOL)raiseExceptionOnFailure {
	char* zErrMsg = NULL;
	int rc = sqlite3_exec(db, [command UTF8String], NULL, NULL, &zErrMsg);
	if (rc != SQLITE_OK) {
		NSLog(@"SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
		if (raiseExceptionOnFailure == YES) [EXException raise: @"EXException" format: @"Cannot execute SQL statement"];
		return NO;
	} else {
		return YES;
	}
}

- (void)drain:(NSTimer*)timer {
	[self drain];
}

- (void)drain {
	//NSLog(@"draining");
	[transactionLock lock];
	for (int i = 0; i < [objects count]; i++) {
		id object = [objects objectAtIndex: i];
		if ([object retainCount] == 1) {
			//NSLog(@"draining object %d (%@)", (int) object, [object className]);
			NSValue* key = [NSValue valueWithPointer: object];
			[objectIDs removeObjectForKey: key];
			[objects removeObjectAtIndex: i];
			i--;
		}
	}
	[transactionLock unlock];
}

- (void)createDrainer {
	[transactionLock lock];
	drainer = [[EXDrainer alloc] initWithContainer: self];
	[transactionLock unlock];
}

- (void)autoreleaseDrainer {
	[transactionLock lock];
	if (![drainer isAutoreleased]) {
		[drainer autorelease];
	}
	[transactionLock unlock];
}

+ (long long)uniqueID {
	return (((long long) random()) << 32) |
		((long long) ([[NSDate date] timeIntervalSinceReferenceDate] * 1000));
}

- (NSString*)uniqueIdentifier {
	return uniqueIdentifier;
}

- (sqlite3*)database {
	return db;
}

+ (BOOL)isCollection:(id)object {
	return [object isKindOfClass: [NSArray class]] || [object isKindOfClass: [NSSet class]]
		|| [object isKindOfClass: [NSDictionary class]];
}

- (id)delegate {
	return delegate;
}

- (void)setDelegate:(id)_delegate {
	if (delegate != _delegate) {
		[delegate release];
		delegate = [_delegate retain];
	}
}

- (void)lockForTransaction {
	[transactionLock lock];
	transactionInProgress = YES;
}

- (void)unlockForTransaction {
	transactionInProgress = NO;
	[transactionLock unlock];
}

- (void)dealloc {
	[drainTimer invalidate];
	sqlite3_close(db);
	[decomposer release];
	[objectIDs release];
	[objects release];
	[drainer deactivate];
	if (![drainer isAutoreleased]) [drainer release];
	[transactionLock release];
	[uniqueIdentifier release];
	[delegate release];
	[super dealloc];
}

@end
