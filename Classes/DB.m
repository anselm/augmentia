//
// Database - implemented as a singleton class
//
// Also will shroud network access to make everything appear local and to cache it
//
// http://iphone.galloway.me.uk/iphone-sdktutorials/singleton-classes/
// http://www.mulle-kybernetik.com/artikel/Optimization/opti-2.html
//

#import <sqlite3.h>

#import "Note.h"
#import "DB.h"
#import "CJSONDeserializer.h"

static DB *db = nil;

@implementation DB
@synthesize notes;
@synthesize cursor;

+ (id)sharedDB {
	@synchronized(self) {
		if(db == nil) {
			[[self alloc] init];
		}
	}
	return db;
}

+ (id)allocWithZone:(NSZone *)zone {
	@synchronized(self) {
		if(db == nil)  {
			db = [super allocWithZone:zone];
			return db;
		}
	}
	return nil;
}

- (id)copyWithZone:(NSZone *)zone {
	return self;
}

- (id)retain {
	return self;
}

- (unsigned)retainCount {
	return UINT_MAX; //denotes an object that cannot be released
}

- (void)release {
	// never release
}

- (id)autorelease {
	return self;
}


-(void) setupDB {
	BOOL success;
	NSArray *documentPaths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
	NSString *documentsDir = [documentPaths objectAtIndex:0];
	databaseName = @"db.sql";
	databasePath = [documentsDir stringByAppendingPathComponent:databaseName];
	NSFileManager *fileManager = [NSFileManager defaultManager];
	success = [fileManager fileExistsAtPath:databasePath];
	if(success) return;
	NSString *databasePathFromApp = [[[NSBundle mainBundle] resourcePath] stringByAppendingPathComponent:databaseName];
	//printf("old database path is %s\n",[databasePathFromApp cString]);
	//printf("new database path is %s\n",[databasePath cString]);
	[fileManager copyItemAtPath:databasePathFromApp toPath:databasePath error:nil];	
	[fileManager release];
}

-(void) readDB {
	sqlite3 *database;
	self.notes = [[NSMutableArray alloc] init];
	if(sqlite3_open([databasePath UTF8String], &database) == SQLITE_OK) {
		const char *sqlStatement = "select title,description,image from note;";
		sqlite3_stmt *compiledStatement;
		if(sqlite3_prepare_v2(database, sqlStatement, -1, &compiledStatement, NULL) == SQLITE_OK) {
			while(sqlite3_step(compiledStatement) == SQLITE_ROW) {
				@try {
					NSString *t = [NSString stringWithUTF8String:(char *)sqlite3_column_text(compiledStatement, 0)];
					NSString *d = [NSString stringWithUTF8String:(char *)sqlite3_column_text(compiledStatement, 1)];
					NSString *i = [NSString stringWithUTF8String:(char *)sqlite3_column_text(compiledStatement, 2)];
					Note *note = [[Note alloc] init:t description:d image:i];
					[notes addObject:note];
					[note release];
				}
				@catch(id e) {
					printf("oops");
				}
			}
		}
		//printf( "any errors? yes no?: %s\n", sqlite3_errmsg(database) ); 
		sqlite3_finalize(compiledStatement);
	}
	sqlite3_close(database);
}

//
// A first pass on a json based loader
// We may turf this in favor of a packed blob
//
- (void)jsonLoad {
	
	NSError *error = NULL;
	NSURL *path = [NSURL URLWithString:@"http://twitter.com/users/anselm.json"];
	//NSData *data = [NSData dataWithContentsOfURL:[NSURL URLWithString:path]];
	//NSString *json = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
	NSString *json = [[NSString alloc] initWithContentsOfURL:path encoding:NSUTF8StringEncoding error:&error];
	if (json == nil) {
		NSLog(@"Error reading file at %@\n%@", path, [error localizedFailureReason]);
		return;
	}
	
	NSData *json_as_data = [json dataUsingEncoding:NSUTF32BigEndianStringEncoding];
	NSDictionary *dictionary = [[CJSONDeserializer deserializer] deserializeAsDictionary:json_as_data error:nil];

	
	NSLog(@"Error: %@", error);
}

-(void) getFriends {

	NSError *error = NULL;
	NSURL *path = [NSURL URLWithString:@"http://wayfaring.makerlab.org/users/anselm.json"];
	//NSData *data = [NSData dataWithContentsOfURL:[NSURL URLWithString:path]];
	//NSString *json = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
	NSString *json = [[NSString alloc] initWithContentsOfURL:path encoding:NSUTF8StringEncoding error:&error];
	if (json == nil) {
		NSLog(@"Error reading file at %@\n%@", path, [error localizedFailureReason]);
		return;
	}

	NSData *json_as_data = [json dataUsingEncoding:NSUTF32BigEndianStringEncoding];
	NSDictionary *dictionary = [[CJSONDeserializer deserializer] deserializeAsDictionary:json_as_data error:nil];

	NSString *key;
	for (key in dictionary) {
		NSString *value = [dictionary valueForKey:key];
		NSLog(@"Name1: %@, Value: %@", key, value);
	}

	NSLog(@"showing statuses");
	NSDictionary *status = [dictionary objectForKey:@"status"];
	for (key in status) {
		NSString *value = [dictionary valueForKey:key];
		NSLog(@"Name2: %@, Value: %@", key, value);		
	}

}

-(id) init {
	[self setupDB];
	[self readDB];
	return self;
}

@end
