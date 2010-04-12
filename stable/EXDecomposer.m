//
//  EXDecomposer.m
//  Entropy
//  (C) 2007-2009 Codesign
//  Licensed under LGPL (v3)
//

#import "EXDecomposer.h"
#import "EXContainer.h"
#import "EXReferringElement.h"
#import "EXProxy.h"
#import <objc/runtime.h>
#import "NSObject_iPhone_cat.h"

@implementation EXDecomposer

- (id)initWithDatabase:(sqlite3*)_db container:(EXContainer*)_container {
	if (self = [super init]) {
		db = _db;
		container = _container;
	}
	return self;
}

- (void)composeObject:(id)object withObjectID:(NSNumber*)objectID versionID:(int)versionID retrievedObjects:(NSMutableDictionary*)retrievedObjects lazyLoading:(BOOL)lazyLoading {
	sqlite3_stmt* stmt; int rc;
	rc = sqlite3_prepare_v2(db, "SELECT name, type FROM propertytypes WHERE vid = ? AND oid = ?", -1, &stmt, 0);
	sqlite3_bind_int(stmt, 1, versionID);
	sqlite3_bind_int(stmt, 2, [objectID intValue]);
	NSMutableDictionary* properties = [NSMutableDictionary dictionary];
	while (sqlite3_step(stmt) == SQLITE_ROW) {
		NSString* name = [NSString stringWithUTF8String: (char*) sqlite3_column_text(stmt, 0)];
		NSString* type = [NSString stringWithUTF8String: (char*) sqlite3_column_text(stmt, 1)];
		[properties setObject: type forKey: name];
	}
	sqlite3_finalize(stmt);
	for (NSString* name in [properties allKeys]) {
		NSString* type = [properties objectForKey: name];
		void* _value;
		Ivar ivar = object_getInstanceVariable(object, [name UTF8String], &_value);
		if ([type isEqual: @"i"]) {
			rc = sqlite3_prepare_v2(db, "SELECT value FROM propertyvalues_integer WHERE vid = ? AND name = ? AND oid = ?", -1, &stmt, 0);
			sqlite3_bind_int(stmt, 1, versionID);
			sqlite3_bind_text(stmt, 2, [name UTF8String], -1, SQLITE_STATIC);
			sqlite3_bind_int(stmt, 3, [objectID intValue]);
			sqlite3_step(stmt);
			int value = sqlite3_column_int(stmt, 0);
			sqlite3_finalize(stmt);
			*(int*)((void*)object + ivar_getOffset(ivar)) = value;
		} else if ([type isEqual: @"I"]) {
			rc = sqlite3_prepare_v2(db, "SELECT value FROM propertyvalues_integer WHERE vid = ? AND name = ? AND oid = ?", -1, &stmt, 0);
			sqlite3_bind_int(stmt, 1, versionID);
			sqlite3_bind_text(stmt, 2, [name UTF8String], -1, SQLITE_STATIC);
			sqlite3_bind_int(stmt, 3, [objectID intValue]);
			sqlite3_step(stmt);
			unsigned int value = sqlite3_column_int(stmt, 0);
			sqlite3_finalize(stmt);
			*(unsigned int*)((void*)object + ivar_getOffset(ivar)) = value;
		} else if ([type isEqual: @"l"]) {
			rc = sqlite3_prepare_v2(db, "SELECT value FROM propertyvalues_integer WHERE vid = ? AND name = ? AND oid = ?", -1, &stmt, 0);
			sqlite3_bind_int(stmt, 1, versionID);
			sqlite3_bind_text(stmt, 2, [name UTF8String], -1, SQLITE_STATIC);
			sqlite3_bind_int(stmt, 3, [objectID intValue]);
			sqlite3_step(stmt);
			long value = sqlite3_column_int(stmt, 0);
			sqlite3_finalize(stmt);
			*(long*)((void*)object + ivar_getOffset(ivar)) = value;
		} else if ([type isEqual: @"L"]) {
			rc = sqlite3_prepare_v2(db, "SELECT value FROM propertyvalues_integer WHERE vid = ? AND name = ? AND oid = ?", -1, &stmt, 0);
			sqlite3_bind_int(stmt, 1, versionID);
			sqlite3_bind_text(stmt, 2, [name UTF8String], -1, SQLITE_STATIC);
			sqlite3_bind_int(stmt, 3, [objectID intValue]);
			sqlite3_step(stmt);
			unsigned long value = sqlite3_column_int(stmt, 0);
			sqlite3_finalize(stmt);
			*(unsigned long*)((void*)object + ivar_getOffset(ivar)) = value;
		} else if ([type isEqual: @"c"]) {
			rc = sqlite3_prepare_v2(db, "SELECT value FROM propertyvalues_integer WHERE vid = ? AND name = ? AND oid = ?", -1, &stmt, 0);
			sqlite3_bind_int(stmt, 1, versionID);
			sqlite3_bind_text(stmt, 2, [name UTF8String], -1, SQLITE_STATIC);
			sqlite3_bind_int(stmt, 3, [objectID intValue]);
			sqlite3_step(stmt);
			signed char value = sqlite3_column_int(stmt, 0);
			sqlite3_finalize(stmt);
			*(signed char*)((void*)object + ivar_getOffset(ivar)) = value;
		} else if ([type isEqual: @"C"]) {
			rc = sqlite3_prepare_v2(db, "SELECT value FROM propertyvalues_integer WHERE vid = ? AND name = ? AND oid = ?", -1, &stmt, 0);
			sqlite3_bind_int(stmt, 1, versionID);
			sqlite3_bind_text(stmt, 2, [name UTF8String], -1, SQLITE_STATIC);
			sqlite3_bind_int(stmt, 3, [objectID intValue]);
			sqlite3_step(stmt);
			unsigned char value = sqlite3_column_int(stmt, 0);
			sqlite3_finalize(stmt);
			*(unsigned char*)((void*)object + ivar_getOffset(ivar)) = value;
		} else if ([type isEqual: @"s"]) {
			rc = sqlite3_prepare_v2(db, "SELECT value FROM propertyvalues_integer WHERE vid = ? AND name = ? AND oid = ?", -1, &stmt, 0);
			sqlite3_bind_int(stmt, 1, versionID);
			sqlite3_bind_text(stmt, 2, [name UTF8String], -1, SQLITE_STATIC);
			sqlite3_bind_int(stmt, 3, [objectID intValue]);
			sqlite3_step(stmt);
			short value = sqlite3_column_int(stmt, 0);
			sqlite3_finalize(stmt);
			*(short*)((void*)object + ivar_getOffset(ivar)) = value;
		} else if ([type isEqual: @"S"]) {
			rc = sqlite3_prepare_v2(db, "SELECT value FROM propertyvalues_integer WHERE vid = ? AND name = ? AND oid = ?", -1, &stmt, 0);
			sqlite3_bind_int(stmt, 1, versionID);
			sqlite3_bind_text(stmt, 2, [name UTF8String], -1, SQLITE_STATIC);
			sqlite3_bind_int(stmt, 3, [objectID intValue]);
			sqlite3_step(stmt);
			unsigned short value = sqlite3_column_int(stmt, 0);
			sqlite3_finalize(stmt);
			*(unsigned short*)((void*)object + ivar_getOffset(ivar)) = value;
		} else if ([type isEqual: @"q"]) {
			rc = sqlite3_prepare_v2(db, "SELECT value FROM propertyvalues_integer WHERE vid = ? AND name = ? AND oid = ?", -1, &stmt, 0);
			sqlite3_bind_int(stmt, 1, versionID);
			sqlite3_bind_text(stmt, 2, [name UTF8String], -1, SQLITE_STATIC);
			sqlite3_bind_int(stmt, 3, [objectID intValue]);
			sqlite3_step(stmt);
			long long value = sqlite3_column_int64(stmt, 0);
			sqlite3_finalize(stmt);
			//NSLog(@"##### OK %d", ivar_getOffset(ivar));
			*(long long*)((void*)object + ivar_getOffset(ivar)) = value;
		} else if ([type isEqual: @"Q"]) {
			rc = sqlite3_prepare_v2(db, "SELECT value FROM propertyvalues_integer WHERE vid = ? AND name = ? AND oid = ?", -1, &stmt, 0);
			sqlite3_bind_int(stmt, 1, versionID);
			sqlite3_bind_text(stmt, 2, [name UTF8String], -1, SQLITE_STATIC);
			sqlite3_bind_int(stmt, 3, [objectID intValue]);
			sqlite3_step(stmt);
			unsigned long long value = sqlite3_column_int64(stmt, 0);
			sqlite3_finalize(stmt);
			//NSLog(@"##### OK %d", ivar_getOffset(ivar));
			*(unsigned long long*)((void*)object + ivar_getOffset(ivar)) = value;
		} else if ([type isEqual: @"f"]) {
			rc = sqlite3_prepare_v2(db, "SELECT value FROM propertyvalues_integer WHERE vid = ? AND name = ? AND oid = ?", -1, &stmt, 0);
			sqlite3_bind_int(stmt, 1, versionID);
			sqlite3_bind_text(stmt, 2, [name UTF8String], -1, SQLITE_STATIC);
			sqlite3_bind_int(stmt, 3, [objectID intValue]);
			sqlite3_step(stmt);
			float value = sqlite3_column_double(stmt, 0);
			sqlite3_finalize(stmt);
			*(float*)((void*)object + ivar_getOffset(ivar)) = value;
		} else if ([type isEqual: @"d"]) {
			rc = sqlite3_prepare_v2(db, "SELECT value FROM propertyvalues_integer WHERE vid = ? AND name = ? AND oid = ?", -1, &stmt, 0);
			sqlite3_bind_int(stmt, 1, versionID);
			sqlite3_bind_text(stmt, 2, [name UTF8String], -1, SQLITE_STATIC);
			sqlite3_bind_int(stmt, 3, [objectID intValue]);
			sqlite3_step(stmt);
			double value = sqlite3_column_double(stmt, 0);
			sqlite3_finalize(stmt);
			*(double*)((void*)object + ivar_getOffset(ivar)) = value;
		} else if ([type isEqual: @"_NIL"]) {
			object_setIvar(object, ivar, nil);
		} else if ([type isEqual: @"_TEXT"]) {
			rc = sqlite3_prepare_v2(db, "SELECT value FROM propertyvalues_text WHERE vid = ? AND name = ? AND oid = ?", -1, &stmt, 0);
			sqlite3_bind_int(stmt, 1, versionID);
			sqlite3_bind_text(stmt, 2, [name UTF8String], -1, SQLITE_STATIC);
			sqlite3_bind_int(stmt, 3, [objectID intValue]);
			sqlite3_step(stmt);
			NSString* value = [NSString stringWithUTF8String: (char*) sqlite3_column_text(stmt, 0)];
			sqlite3_finalize(stmt);
			object_setIvar(object, ivar, [value retain]);
		} else if ([type isEqual: @"_BINARY"]) {
			rc = sqlite3_prepare_v2(db, "SELECT value FROM propertyvalues_binary WHERE vid = ? AND name = ? AND oid = ?", -1, &stmt, 0);
			sqlite3_bind_int(stmt, 1, versionID);
			sqlite3_bind_text(stmt, 2, [name UTF8String], -1, SQLITE_STATIC);
			sqlite3_bind_int(stmt, 3, [objectID intValue]);
			sqlite3_step(stmt);
			NSData* data = [[NSData alloc] initWithBytes: sqlite3_column_blob(stmt, 0) length: sqlite3_column_bytes(stmt, 0)];
			NSKeyedUnarchiver* unarchiver = [[NSKeyedUnarchiver alloc] initForReadingWithData: data];
			id value = [unarchiver decodeObjectForKey: @"root"];
			sqlite3_finalize(stmt);
			if ([value isKindOfClass: [NSArray class]]) {
				NSMutableArray* elements = [[NSMutableArray alloc] init];
				for (id element in value) {
					[self processArrayElement: element elements: elements retrievedObjects: retrievedObjects lazyLoading: lazyLoading];
				}
				object_setIvar(object, ivar, elements);
			} else if ([value isKindOfClass: [NSSet class]]) {
				NSMutableArray* elements = [[NSMutableArray alloc] init];
				for (id element in value) {
					[self processArrayElement: element elements: elements retrievedObjects: retrievedObjects lazyLoading: lazyLoading];
				}
				NSMutableSet* set = [[NSMutableSet alloc] initWithArray: elements];
				object_setIvar(object, ivar, set);
				[elements release];
			} else if ([value isKindOfClass: [NSDictionary class]]) {
				NSMutableArray* line = [[NSMutableArray alloc] init];
				for (id key in [value allKeys]) {
					[line addObject: key];
					[line addObject: [value objectForKey: key]];
				}
				NSMutableArray* elements = [[NSMutableArray alloc] init];
				for (id element in line) {
					[self processArrayElement: element elements: elements retrievedObjects: retrievedObjects lazyLoading: lazyLoading];
				}
				NSMutableDictionary* dict = [[NSMutableDictionary alloc] init];
				NSEnumerator* enumerator = [elements objectEnumerator];
				id key;
				while (key = [enumerator nextObject]) {
					id valueForKey = [enumerator nextObject];
					[dict setObject: valueForKey forKey: key];
				}
				object_setIvar(object, ivar, dict);
				[elements release];
				[line release];
			} else {
				object_setIvar(object, ivar, [value retain]);
			}
			[unarchiver release];
			[data release];
		} else if ([type isEqual: @"_REFERENCE"]) {
			rc = sqlite3_prepare_v2(db, "SELECT value FROM propertyvalues_reference WHERE vid = ? AND name = ? AND oid = ?", -1, &stmt, 0);
			sqlite3_bind_int(stmt, 1, versionID);
			sqlite3_bind_text(stmt, 2, [name UTF8String], -1, SQLITE_STATIC);
			sqlite3_bind_int(stmt, 3, [objectID intValue]);
			sqlite3_step(stmt);
			NSNumber* valueID = [NSNumber numberWithInt: sqlite3_column_int(stmt, 0)];
			sqlite3_finalize(stmt);
			id value = [retrievedObjects objectForKey: valueID];
			if (value == nil) {
				// we'll use a proxy for lazy loading
				if (lazyLoading == YES)
					value = [[[EXProxy alloc] initWithObjectID: [valueID intValue] container: container loadedObjects: retrievedObjects] autorelease];
				else
					value = [container queryWithID: [valueID intValue] atomically: NO retrievedObjects: retrievedObjects lazyLoading: lazyLoading];
				[retrievedObjects setObject: value forKey: valueID];
			}
			object_setIvar(object, ivar, [value retain]);
		} else NSLog(@"? %@", type);
	}
}

// always runs within a transaction
- (NSNumber*)decomposeObject:(id)object withObjectID:(NSNumber*)objectID storedObjects:(NSMutableDictionary*)storedObjects processedObjects:(NSMutableSet*)processedObjects {
	return [self decomposeObject: object withObjectID: objectID storedObjects: storedObjects processedObjects: processedObjects asNew: NO];
}

- (NSNumber*)decomposeObject:(id)object withObjectID:(NSNumber*)objectID storedObjects:(NSMutableDictionary*)storedObjects processedObjects:(NSMutableSet*)processedObjects asNew:(BOOL)asNew {
	//NSLog(@"Decomposing: %@", object);
	if (asNew == YES) objectID = nil;
	sqlite3_stmt* stmt; int rc; int versionID;
	if (objectID == nil) {
		rc = sqlite3_prepare_v2(db, "SELECT MAX(oid) FROM objects", -1, &stmt, 0);
		sqlite3_step(stmt);
		int maxObjectID = sqlite3_column_int(stmt, 0);
		objectID = [NSNumber numberWithInt: maxObjectID + 1];
		sqlite3_finalize(stmt);
		versionID = 1;
	} else {
		rc = sqlite3_prepare_v2(db, "SELECT vid FROM objects WHERE oid = ? AND published = 1", -1, &stmt, 0);
		sqlite3_bind_int(stmt, 1, [objectID intValue]);
		sqlite3_step(stmt);
		versionID = sqlite3_column_int(stmt, 0) + 1;
		sqlite3_finalize(stmt);
		[EXContainer executeSQL: [NSString stringWithFormat: @"UPDATE objects SET published = 0 WHERE oid = %@", objectID] database: db];
	}
	[EXContainer executeSQL: [NSString stringWithFormat: @"INSERT INTO objects (oid, vid, classname, published, timestamp) VALUES (%@, %d, '%@', 1, %f)", objectID, versionID, [object className], [[NSDate date] timeIntervalSinceReferenceDate]] database: db];
	
	Class cls = [object class];
	while (cls != [NSObject class]) {
		unsigned count, i;
		Ivar* firstIvar = class_copyIvarList(cls, &count);
		for (i = 0; i < count; i++) {
		Ivar* ivar = firstIvar + i;
		NSString* name = [NSString stringWithUTF8String: ivar_getName(*ivar)];
		NSString* type = [NSString stringWithUTF8String: ivar_getTypeEncoding(*ivar)];
		if ([type isEqual: @"i"]) {
			int value = *(int*)((void*)object + ivar_getOffset(*ivar));
			rc = sqlite3_prepare_v2(db, "INSERT INTO propertytypes (vid, name, type, oid) VALUES (?, ?, 'i', ?)", -1, &stmt, 0);
			sqlite3_bind_int(stmt, 1, versionID);
			sqlite3_bind_text(stmt, 2, [name UTF8String], -1, SQLITE_STATIC);
			sqlite3_bind_int(stmt, 3, [objectID intValue]);
			sqlite3_step(stmt);
			sqlite3_finalize(stmt);
			rc = sqlite3_prepare_v2(db, "INSERT INTO propertyvalues_integer (vid, name, value, oid) VALUES (?, ?, ?, ?)", -1, &stmt, 0);
			sqlite3_bind_int(stmt, 1, versionID);
			sqlite3_bind_text(stmt, 2, [name UTF8String], -1, SQLITE_STATIC);
			sqlite3_bind_int(stmt, 3, value);
			sqlite3_bind_int(stmt, 4, [objectID intValue]);
			sqlite3_step(stmt);
			sqlite3_finalize(stmt);
		} else if ([type isEqual: @"I"]) {
			unsigned int value = *(unsigned int*)((void*)object + ivar_getOffset(*ivar));
			rc = sqlite3_prepare_v2(db, "INSERT INTO propertytypes (vid, name, type, oid) VALUES (?, ?, 'i', ?)", -1, &stmt, 0);
			sqlite3_bind_int(stmt, 1, versionID);
			sqlite3_bind_text(stmt, 2, [name UTF8String], -1, SQLITE_STATIC);
			sqlite3_bind_int(stmt, 3, [objectID intValue]);
			sqlite3_step(stmt);
			sqlite3_finalize(stmt);
			rc = sqlite3_prepare_v2(db, "INSERT INTO propertyvalues_integer (vid, name, value, oid) VALUES (?, ?, ?, ?)", -1, &stmt, 0);
			sqlite3_bind_int(stmt, 1, versionID);
			sqlite3_bind_text(stmt, 2, [name UTF8String], -1, SQLITE_STATIC);
			sqlite3_bind_int(stmt, 3, value);
			sqlite3_bind_int(stmt, 4, [objectID intValue]);
			sqlite3_step(stmt);
			sqlite3_finalize(stmt);
		} else if ([type isEqual: @"l"]) {
			long value = *(long*)((void*)object + ivar_getOffset(*ivar));
			rc = sqlite3_prepare_v2(db, "INSERT INTO propertytypes (vid, name, type, oid) VALUES (?, ?, 'l', ?)", -1, &stmt, 0);
			sqlite3_bind_int(stmt, 1, versionID);
			sqlite3_bind_text(stmt, 2, [name UTF8String], -1, SQLITE_STATIC);
			sqlite3_bind_int(stmt, 3, [objectID intValue]);
			sqlite3_step(stmt);
			sqlite3_finalize(stmt);
			rc = sqlite3_prepare_v2(db, "INSERT INTO propertyvalues_integer (vid, name, value, oid) VALUES (?, ?, ?, ?)", -1, &stmt, 0);
			sqlite3_bind_int(stmt, 1, versionID);
			sqlite3_bind_text(stmt, 2, [name UTF8String], -1, SQLITE_STATIC);
			sqlite3_bind_int(stmt, 3, value);
			sqlite3_bind_int(stmt, 4, [objectID intValue]);
			sqlite3_step(stmt);
			sqlite3_finalize(stmt);
		} else if ([type isEqual: @"L"]) {
			unsigned long value = *(unsigned long*)((void*)object + ivar_getOffset(*ivar));
			rc = sqlite3_prepare_v2(db, "INSERT INTO propertytypes (vid, name, type, oid) VALUES (?, ?, 'l', ?)", -1, &stmt, 0);
			sqlite3_bind_int(stmt, 1, versionID);
			sqlite3_bind_text(stmt, 2, [name UTF8String], -1, SQLITE_STATIC);
			sqlite3_bind_int(stmt, 3, [objectID intValue]);
			sqlite3_step(stmt);
			sqlite3_finalize(stmt);
			rc = sqlite3_prepare_v2(db, "INSERT INTO propertyvalues_integer (vid, name, value, oid) VALUES (?, ?, ?, ?)", -1, &stmt, 0);
			sqlite3_bind_int(stmt, 1, versionID);
			sqlite3_bind_text(stmt, 2, [name UTF8String], -1, SQLITE_STATIC);
			sqlite3_bind_int(stmt, 3, value);
			sqlite3_bind_int(stmt, 4, [objectID intValue]);
			sqlite3_step(stmt);
			sqlite3_finalize(stmt);
		} else if ([type isEqual: @"c"]) {
			signed char value = *(signed char*)((void*)object + ivar_getOffset(*ivar));
			rc = sqlite3_prepare_v2(db, "INSERT INTO propertytypes (vid, name, type, oid) VALUES (?, ?, 'c', ?)", -1, &stmt, 0);
			sqlite3_bind_int(stmt, 1, versionID);
			sqlite3_bind_text(stmt, 2, [name UTF8String], -1, SQLITE_STATIC);
			sqlite3_bind_int(stmt, 3, [objectID intValue]);
			sqlite3_step(stmt);
			sqlite3_finalize(stmt);
			rc = sqlite3_prepare_v2(db, "INSERT INTO propertyvalues_integer (vid, name, value, oid) VALUES (?, ?, ?, ?)", -1, &stmt, 0);
			sqlite3_bind_int(stmt, 1, versionID);
			sqlite3_bind_text(stmt, 2, [name UTF8String], -1, SQLITE_STATIC);
			sqlite3_bind_int(stmt, 3, value);
			sqlite3_bind_int(stmt, 4, [objectID intValue]);
			sqlite3_step(stmt);
			sqlite3_finalize(stmt);
		} else if ([type isEqual: @"C"]) {
			unsigned char value = *(unsigned char*)((void*)object + ivar_getOffset(*ivar));
			rc = sqlite3_prepare_v2(db, "INSERT INTO propertytypes (vid, name, type, oid) VALUES (?, ?, 'c', ?)", -1, &stmt, 0);
			sqlite3_bind_int(stmt, 1, versionID);
			sqlite3_bind_text(stmt, 2, [name UTF8String], -1, SQLITE_STATIC);
			sqlite3_bind_int(stmt, 3, [objectID intValue]);
			sqlite3_step(stmt);
			sqlite3_finalize(stmt);
			rc = sqlite3_prepare_v2(db, "INSERT INTO propertyvalues_integer (vid, name, value, oid) VALUES (?, ?, ?, ?)", -1, &stmt, 0);
			sqlite3_bind_int(stmt, 1, versionID);
			sqlite3_bind_text(stmt, 2, [name UTF8String], -1, SQLITE_STATIC);
			sqlite3_bind_int(stmt, 3, value);
			sqlite3_bind_int(stmt, 4, [objectID intValue]);
			sqlite3_step(stmt);
			sqlite3_finalize(stmt);
		} else if ([type isEqual: @"s"]) {
			short value = *(short*)((void*)object + ivar_getOffset(*ivar));
			rc = sqlite3_prepare_v2(db, "INSERT INTO propertytypes (vid, name, type, oid) VALUES (?, ?, 's', ?)", -1, &stmt, 0);
			sqlite3_bind_int(stmt, 1, versionID);
			sqlite3_bind_text(stmt, 2, [name UTF8String], -1, SQLITE_STATIC);
			sqlite3_bind_int(stmt, 3, [objectID intValue]);
			sqlite3_step(stmt);
			sqlite3_finalize(stmt);
			rc = sqlite3_prepare_v2(db, "INSERT INTO propertyvalues_integer (vid, name, value, oid) VALUES (?, ?, ?, ?)", -1, &stmt, 0);
			sqlite3_bind_int(stmt, 1, versionID);
			sqlite3_bind_text(stmt, 2, [name UTF8String], -1, SQLITE_STATIC);
			sqlite3_bind_int(stmt, 3, value);
			sqlite3_bind_int(stmt, 4, [objectID intValue]);
			sqlite3_step(stmt);
			sqlite3_finalize(stmt);
		} else if ([type isEqual: @"S"]) {
			unsigned short value = *(unsigned short*)((void*)object + ivar_getOffset(*ivar));
			rc = sqlite3_prepare_v2(db, "INSERT INTO propertytypes (vid, name, type, oid) VALUES (?, ?, 's', ?)", -1, &stmt, 0);
			sqlite3_bind_int(stmt, 1, versionID);
			sqlite3_bind_text(stmt, 2, [name UTF8String], -1, SQLITE_STATIC);
			sqlite3_bind_int(stmt, 3, [objectID intValue]);
			sqlite3_step(stmt);
			sqlite3_finalize(stmt);
			rc = sqlite3_prepare_v2(db, "INSERT INTO propertyvalues_integer (vid, name, value, oid) VALUES (?, ?, ?, ?)", -1, &stmt, 0);
			sqlite3_bind_int(stmt, 1, versionID);
			sqlite3_bind_text(stmt, 2, [name UTF8String], -1, SQLITE_STATIC);
			sqlite3_bind_int(stmt, 3, value);
			sqlite3_bind_int(stmt, 4, [objectID intValue]);
			sqlite3_step(stmt);
			sqlite3_finalize(stmt);
		} else if ([type isEqual: @"q"]) {
			long long value = *(long long*)((void*)object + ivar_getOffset(*ivar));
			rc = sqlite3_prepare_v2(db, "INSERT INTO propertytypes (vid, name, type, oid) VALUES (?, ?, 'q', ?)", -1, &stmt, 0);
			sqlite3_bind_int(stmt, 1, versionID);
			sqlite3_bind_text(stmt, 2, [name UTF8String], -1, SQLITE_STATIC);
			sqlite3_bind_int(stmt, 3, [objectID intValue]);
			sqlite3_step(stmt);
			sqlite3_finalize(stmt);
			rc = sqlite3_prepare_v2(db, "INSERT INTO propertyvalues_integer (vid, name, value, oid) VALUES (?, ?, ?, ?)", -1, &stmt, 0);
			sqlite3_bind_int(stmt, 1, versionID);
			sqlite3_bind_text(stmt, 2, [name UTF8String], -1, SQLITE_STATIC);
			sqlite3_bind_int64(stmt, 3, value);
			sqlite3_bind_int(stmt, 4, [objectID intValue]);
			sqlite3_step(stmt);
			sqlite3_finalize(stmt);
		} else if ([type isEqual: @"Q"]) {
			unsigned long long value = *(unsigned long long*)((void*)object + ivar_getOffset(*ivar));
			rc = sqlite3_prepare_v2(db, "INSERT INTO propertytypes (vid, name, type, oid) VALUES (?, ?, 'q', ?)", -1, &stmt, 0);
			sqlite3_bind_int(stmt, 1, versionID);
			sqlite3_bind_text(stmt, 2, [name UTF8String], -1, SQLITE_STATIC);
			sqlite3_bind_int(stmt, 3, [objectID intValue]);
			sqlite3_step(stmt);
			sqlite3_finalize(stmt);
			rc = sqlite3_prepare_v2(db, "INSERT INTO propertyvalues_integer (vid, name, value, oid) VALUES (?, ?, ?, ?)", -1, &stmt, 0);
			sqlite3_bind_int(stmt, 1, versionID);
			sqlite3_bind_text(stmt, 2, [name UTF8String], -1, SQLITE_STATIC);
			sqlite3_bind_int64(stmt, 3, value);
			sqlite3_bind_int(stmt, 4, [objectID intValue]);
			sqlite3_step(stmt);
			sqlite3_finalize(stmt);
		} else if ([type isEqual: @"f"]) {
			float value = *(float*)((void*)object + ivar_getOffset(*ivar));
			rc = sqlite3_prepare_v2(db, "INSERT INTO propertytypes (vid, name, type, oid) VALUES (?, ?, 'f', ?)", -1, &stmt, 0);
			sqlite3_bind_int(stmt, 1, versionID);
			sqlite3_bind_text(stmt, 2, [name UTF8String], -1, SQLITE_STATIC);
			sqlite3_bind_int(stmt, 3, [objectID intValue]);
			sqlite3_step(stmt);
			sqlite3_finalize(stmt);
			rc = sqlite3_prepare_v2(db, "INSERT INTO propertyvalues_integer (vid, name, value, oid) VALUES (?, ?, ?, ?)", -1, &stmt, 0);
			sqlite3_bind_int(stmt, 1, versionID);
			sqlite3_bind_text(stmt, 2, [name UTF8String], -1, SQLITE_STATIC);
			sqlite3_bind_double(stmt, 3, value);
			sqlite3_bind_int(stmt, 4, [objectID intValue]);
			sqlite3_step(stmt);
			sqlite3_finalize(stmt);
		} else if ([type isEqual: @"d"]) {
			double value = *(double*)((void*)object + ivar_getOffset(*ivar));
			rc = sqlite3_prepare_v2(db, "INSERT INTO propertytypes (vid, name, type, oid) VALUES (?, ?, 'd', ?)", -1, &stmt, 0);
			sqlite3_bind_int(stmt, 1, versionID);
			sqlite3_bind_text(stmt, 2, [name UTF8String], -1, SQLITE_STATIC);
			sqlite3_bind_int(stmt, 3, [objectID intValue]);
			sqlite3_step(stmt);
			sqlite3_finalize(stmt);
			rc = sqlite3_prepare_v2(db, "INSERT INTO propertyvalues_integer (vid, name, value, oid) VALUES (?, ?, ?, ?)", -1, &stmt, 0);
			sqlite3_bind_int(stmt, 1, versionID);
			sqlite3_bind_text(stmt, 2, [name UTF8String], -1, SQLITE_STATIC);
			sqlite3_bind_double(stmt, 3, value);
			sqlite3_bind_int(stmt, 4, [objectID intValue]);
			sqlite3_step(stmt);
			sqlite3_finalize(stmt);
		} else if ([type characterAtIndex: 0] == '@') {
			id value = object_getIvar(object, *ivar);
			if (value == nil) {
				rc = sqlite3_prepare_v2(db, "INSERT INTO propertytypes (vid, name, type, oid) VALUES (?, ?, '_NIL', ?)", -1, &stmt, 0);
				sqlite3_bind_int(stmt, 1, versionID);
				sqlite3_bind_text(stmt, 2, [name UTF8String], -1, SQLITE_STATIC);
				sqlite3_bind_int(stmt, 3, [objectID intValue]);
				sqlite3_step(stmt);
				sqlite3_finalize(stmt);
			} else if ([value isKindOfClass: [EXContainer class]]) {
				// instances of EXContainer will be ignored
			} else if ([value isKindOfClass: [NSString class]]) {
				rc = sqlite3_prepare_v2(db, "INSERT INTO propertytypes (vid, name, type, oid) VALUES (?, ?, '_TEXT', ?)", -1, &stmt, 0);
				sqlite3_bind_int(stmt, 1, versionID);
				sqlite3_bind_text(stmt, 2, [name UTF8String], -1, SQLITE_STATIC);
				sqlite3_bind_int(stmt, 3, [objectID intValue]);
				sqlite3_step(stmt);
				sqlite3_finalize(stmt);
				rc = sqlite3_prepare_v2(db, "INSERT INTO propertyvalues_text (vid, name, value, oid) VALUES (?, ?, ?, ?)", -1, &stmt, 0);
				sqlite3_bind_int(stmt, 1, versionID);
				sqlite3_bind_text(stmt, 2, [name UTF8String], -1, SQLITE_STATIC);
				sqlite3_bind_text(stmt, 3, [value UTF8String], -1, SQLITE_STATIC);
				sqlite3_bind_int(stmt, 4, [objectID intValue]);
				sqlite3_step(stmt);
				sqlite3_finalize(stmt);
			} else if ([EXDecomposer shouldBeSerialized: value]) {
				rc = sqlite3_prepare_v2(db, "INSERT INTO propertytypes (vid, name, type, oid) VALUES (?, ?, '_BINARY', ?)", -1, &stmt, 0);
				sqlite3_bind_int(stmt, 1, versionID);
				sqlite3_bind_text(stmt, 2, [name UTF8String], -1, SQLITE_STATIC);
				sqlite3_bind_int(stmt, 3, [objectID intValue]);
				sqlite3_step(stmt);
				sqlite3_finalize(stmt);
				rc = sqlite3_prepare_v2(db, "INSERT INTO propertyvalues_binary (vid, name, value, oid) VALUES (?, ?, ?, ?)", -1, &stmt, 0);
				sqlite3_bind_int(stmt, 1, versionID);
				sqlite3_bind_text(stmt, 2, [name UTF8String], -1, SQLITE_STATIC);
				NSMutableData* data = [[NSMutableData alloc] init];
				NSKeyedArchiver* archiver = [[NSKeyedArchiver alloc] initForWritingWithMutableData: data];
				[archiver encodeObject: value forKey: @"root"];
				[archiver finishEncoding];
				sqlite3_bind_text(stmt, 3, [data bytes], [data length], SQLITE_STATIC);
				sqlite3_bind_int(stmt, 4, [objectID intValue]);
				sqlite3_step(stmt);
				sqlite3_finalize(stmt);
				[archiver release];
				[data release];
			} else if ([value isKindOfClass: [NSArray class]]) {
				NSMutableArray* elements = [[NSMutableArray alloc] init];
				for (id element in value) {
					[self processArrayElement: element elements: elements storedObjects: storedObjects processedObjects: processedObjects];
				}
				rc = sqlite3_prepare_v2(db, "INSERT INTO propertytypes (vid, name, type, oid) VALUES (?, ?, '_BINARY', ?)", -1, &stmt, 0);
				sqlite3_bind_int(stmt, 1, versionID);
				sqlite3_bind_text(stmt, 2, [name UTF8String], -1, SQLITE_STATIC);
				sqlite3_bind_int(stmt, 3, [objectID intValue]);
				sqlite3_step(stmt);
				sqlite3_finalize(stmt);
				rc = sqlite3_prepare_v2(db, "INSERT INTO propertyvalues_binary (vid, name, value, oid) VALUES (?, ?, ?, ?)", -1, &stmt, 0);
				sqlite3_bind_int(stmt, 1, versionID);
				sqlite3_bind_text(stmt, 2, [name UTF8String], -1, SQLITE_STATIC);
				NSMutableData* data = [[NSMutableData alloc] init];
				NSKeyedArchiver* archiver = [[NSKeyedArchiver alloc] initForWritingWithMutableData: data];
				[archiver encodeObject: elements forKey: @"root"];
				[archiver finishEncoding];
				sqlite3_bind_text(stmt, 3, [data bytes], [data length], SQLITE_STATIC);
				sqlite3_bind_int(stmt, 4, [objectID intValue]);
				sqlite3_step(stmt);
				sqlite3_finalize(stmt);
				[archiver release];
				[data release];
				[elements release];
			} else if ([value isKindOfClass: [NSSet class]]) {
				NSMutableArray* elements = [[NSMutableArray alloc] init];
				for (id element in value) {
					[self processArrayElement: element elements: elements storedObjects: storedObjects processedObjects: processedObjects];
				}
				rc = sqlite3_prepare_v2(db, "INSERT INTO propertytypes (vid, name, type, oid) VALUES (?, ?, '_BINARY', ?)", -1, &stmt, 0);
				sqlite3_bind_int(stmt, 1, versionID);
				sqlite3_bind_text(stmt, 2, [name UTF8String], -1, SQLITE_STATIC);
				sqlite3_bind_int(stmt, 3, [objectID intValue]);
				sqlite3_step(stmt);
				sqlite3_finalize(stmt);
				rc = sqlite3_prepare_v2(db, "INSERT INTO propertyvalues_binary (vid, name, value, oid) VALUES (?, ?, ?, ?)", -1, &stmt, 0);
				sqlite3_bind_int(stmt, 1, versionID);
				sqlite3_bind_text(stmt, 2, [name UTF8String], -1, SQLITE_STATIC);
				NSMutableData* data = [[NSMutableData alloc] init];
				NSKeyedArchiver* archiver = [[NSKeyedArchiver alloc] initForWritingWithMutableData: data];
				NSSet* set = [[NSSet alloc] initWithArray: elements];
				[archiver encodeObject: set forKey: @"root"];
				[archiver finishEncoding];
				sqlite3_bind_text(stmt, 3, [data bytes], [data length], SQLITE_STATIC);
				sqlite3_bind_int(stmt, 4, [objectID intValue]);
				sqlite3_step(stmt);
				sqlite3_finalize(stmt);
				[archiver release];
				[data release];
				[set release];
				[elements release];
			} else if ([value isKindOfClass: [NSDictionary class]]) {
				NSMutableArray* elements = [[NSMutableArray alloc] init];
				for (id element in [value allKeys]) {
					[self processArrayElement: element elements: elements storedObjects: storedObjects processedObjects: processedObjects];
					[self processArrayElement: [value objectForKey: element] elements: elements storedObjects: storedObjects processedObjects: processedObjects];
				}
				rc = sqlite3_prepare_v2(db, "INSERT INTO propertytypes (vid, name, type, oid) VALUES (?, ?, '_BINARY', ?)", -1, &stmt, 0);
				sqlite3_bind_int(stmt, 1, versionID);
				sqlite3_bind_text(stmt, 2, [name UTF8String], -1, SQLITE_STATIC);
				sqlite3_bind_int(stmt, 3, [objectID intValue]);
				sqlite3_step(stmt);
				sqlite3_finalize(stmt);
				rc = sqlite3_prepare_v2(db, "INSERT INTO propertyvalues_binary (vid, name, value, oid) VALUES (?, ?, ?, ?)", -1, &stmt, 0);
				sqlite3_bind_int(stmt, 1, versionID);
				sqlite3_bind_text(stmt, 2, [name UTF8String], -1, SQLITE_STATIC);
				NSMutableData* data = [[NSMutableData alloc] init];
				NSKeyedArchiver* archiver = [[NSKeyedArchiver alloc] initForWritingWithMutableData: data];
				NSMutableDictionary* dict = [[NSMutableDictionary alloc] init];
				NSEnumerator* enumerator = [elements objectEnumerator];
				id key;
				while (key = [enumerator nextObject]) {
					id valueForKey = [enumerator nextObject];
					[dict setObject: valueForKey forKey: key];
				}
				[archiver encodeObject: dict forKey: @"root"];
				[archiver finishEncoding];
				//NSLog(@"dictionary archived: %@", dict);
				sqlite3_bind_text(stmt, 3, [data bytes], [data length], SQLITE_STATIC);
				sqlite3_bind_int(stmt, 4, [objectID intValue]);
				sqlite3_step(stmt);
				sqlite3_finalize(stmt);
				[archiver release];
				[data release];
				[dict release];
				[elements release];
			} else {
				NSValue* key = [NSValue valueWithPointer: value];
				NSNumber* valueID = [storedObjects objectForKey: key];
				if (valueID == nil) {
					// we should check whether the object is a proxy
					if ([value respondsToSelector: @selector(__isUnused)]) {
						if ([value __isUnused] == NO)
							valueID = [NSNumber numberWithInt: [container store: [value __object] atomically: NO storedObjects: storedObjects locally: YES processedObjects: processedObjects]];
					} else {
						valueID = [NSNumber numberWithInt: [container store: value atomically: NO storedObjects: storedObjects locally: YES processedObjects: processedObjects]];
					}
					[storedObjects setObject: valueID forKey: key];
				}
				rc = sqlite3_prepare_v2(db, "INSERT INTO propertytypes (vid, name, type, oid) VALUES (?, ?, '_REFERENCE', ?)", -1, &stmt, 0);
				sqlite3_bind_int(stmt, 1, versionID);
				sqlite3_bind_text(stmt, 2, [name UTF8String], -1, SQLITE_STATIC);
				sqlite3_bind_int(stmt, 3, [objectID intValue]);
				sqlite3_step(stmt);
				sqlite3_finalize(stmt);
				rc = sqlite3_prepare_v2(db, "INSERT INTO propertyvalues_reference (vid, name, value, oid) VALUES (?, ?, ?, ?)", -1, &stmt, 0);
				sqlite3_bind_int(stmt, 1, versionID);
				sqlite3_bind_text(stmt, 2, [name UTF8String], -1, SQLITE_STATIC);
				sqlite3_bind_int(stmt, 3, [valueID intValue]);
				sqlite3_bind_int(stmt, 4, [objectID intValue]);
				sqlite3_step(stmt);
				sqlite3_finalize(stmt);
			}
		} else NSLog(@"won't process ivar %@ of type %@", name, type);
		}
		free(firstIvar);
		cls = [cls superclass];
	}
	return objectID;
}

- (void)processArrayElement:(id)element elements:(NSMutableArray*)elements storedObjects:(NSMutableDictionary*)storedObjects processedObjects:(NSMutableSet*)processedObjects {
	if ([EXDecomposer shouldBeSerialized: element]) {
		[elements addObject: element];
	} else if ([element isKindOfClass: [NSArray class]]) {
		NSMutableArray* elements2 = [[NSMutableArray alloc] init];
		for (id element2 in element) {
			[self processArrayElement: element2 elements: elements2 storedObjects: storedObjects processedObjects: processedObjects];
		}
		[elements addObject: elements2];
		[elements2 release];
	} else if ([element isKindOfClass: [NSSet class]]) {
		NSMutableArray* elements2 = [[NSMutableArray alloc] init];
		for (id element2 in element) {
			[self processArrayElement: element2 elements: elements2 storedObjects: storedObjects processedObjects: processedObjects];
		}
		NSSet* set = [[NSSet alloc] initWithArray: elements2];
		[elements addObject: set];
		[set release];
		[elements2 release];
	} else if ([element isKindOfClass: [NSDictionary class]]) {
		NSMutableArray* elements2 = [[NSMutableArray alloc] init];
		for (id element2 in [element allKeys]) {
			[self processArrayElement: element2 elements: elements2 storedObjects: storedObjects processedObjects: processedObjects];
			[self processArrayElement: [element objectForKey: element2] elements: elements2 storedObjects: storedObjects processedObjects: processedObjects];
		}
		NSMutableDictionary* dict = [[NSMutableDictionary alloc] init];
		NSEnumerator* enumerator = [elements2 objectEnumerator];
		id key;
		while (key = [enumerator nextObject]) {
			id valueForKey = [enumerator nextObject];
			[dict setObject: valueForKey forKey: key];
		}
		[elements addObject: dict];
		[dict release];
		[elements2 release];
	} else {
		NSValue* key = [NSValue valueWithPointer: element];
		NSNumber* valueID = [storedObjects objectForKey: key];
		if (valueID == nil) {
			valueID = [NSNumber numberWithInt: [container store: element atomically: NO storedObjects: storedObjects locally: YES processedObjects: processedObjects]];
			[storedObjects setObject: valueID forKey: key];
		}
		EXReferringElement* referringElement =  [[EXReferringElement alloc] initWithID: [valueID intValue]];
		[elements addObject: referringElement];
		[referringElement release];
	}
}

- (void)processArrayElement:(id)element elements:(NSMutableArray*)elements retrievedObjects:(NSMutableDictionary*)retrievedObjects lazyLoading:(BOOL)lazyLoading {
	if ([element isKindOfClass: [NSArray class]]) {
		NSMutableArray* elements2 = [[NSMutableArray alloc] init];
		for (id element2 in element) {
			[self processArrayElement: element2 elements: elements2 retrievedObjects: retrievedObjects lazyLoading: lazyLoading];
		}
		[elements addObject: elements2];
		[elements2 release];
	} else if ([element isKindOfClass: [EXReferringElement class]]) {
		NSNumber* key = [NSNumber numberWithInt: [(EXReferringElement*) element objectID]];
		id value = [retrievedObjects objectForKey: key];
		if (value == nil) {
			value = [container queryWithID: [(EXReferringElement*) element objectID] atomically: NO retrievedObjects: retrievedObjects lazyLoading: lazyLoading];
			[retrievedObjects setObject: value forKey: key];
		}
		[elements addObject: value];
	} else {
		[elements addObject: element];
	}
}

+ (BOOL)shouldBeSerialized:(id)object {
	return [object isKindOfClass: [NSString class]] || [object isKindOfClass: [NSValue class]]
	|| [object isKindOfClass: [NSNull class]] || [object isKindOfClass: [NSData class]]
	|| [object isKindOfClass: [NSDate class]];
}

@end
