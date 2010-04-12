
#import "EXContainer.h"
#import "EXPredicateEqualText.h"
#import <sqlite3.h>

#import "Note.h"
#import "DB.h"
#import "CJSONDeserializer.h"

static DB *db = nil;

@implementation DB

//////////////////////////////////////////////////////////////////////////////////////////////////////////
// boilerplate for singletons
//////////////////////////////////////////////////////////////////////////////////////////////////////////

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

//////////////////////////////////////////////////////////////////////////////////////////////////////////
// init
//////////////////////////////////////////////////////////////////////////////////////////////////////////

EXFile* file;
EXContainer* container;

-(id) init {
	if(!self) {
		[super init];
	}
	NSArray* paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
	NSString* documentsDirectory = [paths objectAtIndex: 0];
	NSString* dbFileName = [documentsDirectory stringByAppendingFormat: @"/db3.db"];
	file = [EXFile fileWithName: dbFileName];
	container = [[EXContainer alloc] initWithFile: file];
	db = self;
	return self;
}

- (void) dealloc {
	if(container) {
		[container release];
	}
	db = nil;
	[super dealloc];
}

-(NSArray*) getNotes:(NSString*)kind {
	if(container!=nil && kind!=nil) {
		EXPredicate* predicate = [[[EXPredicateEqualText alloc] initWithFieldName: @"kind" value: kind] autorelease];
		NSArray* resultSet = [container queryWithClass: [Note class] predicate: predicate];
		[resultSet retain]; // TODO I seem to be losing these... paranoia... examine.
		return resultSet;
	}
	return nil;
}

-(Note*) getNote:(NSString *)kind Title:(NSString *)title {
	if(container != nil && title != nil) {
		EXPredicate* predicate = [[[EXPredicateEqualText alloc] initWithFieldName: @"kind" value: kind] autorelease];
		NSArray* resultSet = [container queryWithClass: [Note class] predicate: predicate];
		for(Note* key in resultSet) {
			if([key->title isEqualToString: title]) {
				return key;
			}
		}
	}
	return nil;
}

-(void) updateNote:(NSString *)k Title:(NSString *)t Description:(NSString *)d Image:(NSString*)i {
	if(container != nil && t!=nil) {
		Note *note = [[Note alloc] init:k title:t description:d image:i];
		[container storeObject: note];
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
// unused
//////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 -(Note*) getNote:(NSString *)kind Title:(NSString *)title {

	Note* note = nil;
 
	sqlite3 *database;
	if(sqlite3_open([databasePath UTF8String], &database) == SQLITE_OK) {
		const char *sqlStatement = "SELECT title,description,image FROM note WHERE kind = TODO and title = TODO limit 1;";
		sqlite3_stmt *compiledStatement;
		if(sqlite3_prepare_v2(database, sqlStatement, -1, &compiledStatement, NULL) == SQLITE_OK) {
			while(sqlite3_step(compiledStatement) == SQLITE_ROW) {
				@try {
					NSString *t = [NSString stringWithUTF8String:(char *)sqlite3_column_text(compiledStatement, 0)];
					NSString *d = [NSString stringWithUTF8String:(char *)sqlite3_column_text(compiledStatement, 1)];
					NSString *i = [NSString stringWithUTF8String:(char *)sqlite3_column_text(compiledStatement, 2)];
					note = [[Note alloc] init:t description:d image:i];
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

	return note;
}

-(void) updateNote:(NSString *)kind Title:(NSString *)title Description:(NSString *)description {

	BOOL update = false;

	// Look in cache for a note similar to the one wish to have exist and make it if not found
	Note* note = [self getNote:kind Title:title];
	if( note != nil ) {
		note.description = description;
		update = true;

//		id customObject = [[CustomObject alloc] init];
//		[container storeObject: customObject];
//		[customObject release];

		// Write through to the database persistently
		sqlite3 *database;
		if(sqlite3_open([databasePath UTF8String], &database) == SQLITE_OK) {
			const char *sqlStatement = "UPDATE note SET description = ? WHERE kind = ? AND title = ?;";
			sqlite3_stmt *compiledStatement;
			if(sqlite3_prepare_v2(database, sqlStatement, -1, &compiledStatement, NULL) == SQLITE_OK) {
				// if we found a statement matching the update then
				// update note set description = ? where id = x
				// else
				// insert into note (title,description) values ( ?, ? ) ", title, description
			}
			//printf( "any errors? yes no?: %s\n", sqlite3_errmsg(database) ); 
			sqlite3_finalize(compiledStatement);
		}
		sqlite3_close(database);
		
		
	} else {
		note = [[Note alloc] init:title description:description image:nil];
//		[notes addObject:note];
		[note release];

		// Write through to the database persistently
		sqlite3 *database;
		if(sqlite3_open([databasePath UTF8String], &database) == SQLITE_OK) {
			const char *sqlStatement = "select title,description,image from note;";
			sqlite3_stmt *compiledStatement;
			if(sqlite3_prepare_v2(database, sqlStatement, -1, &compiledStatement, NULL) == SQLITE_OK) {
				// if we found a statement matching the update then
				// update note set description = ? where id = x
				// else
				// insert into note (title,description) values ( ?, ? ) ", title, description
			}
			//printf( "any errors? yes no?: %s\n", sqlite3_errmsg(database) ); 
			sqlite3_finalize(compiledStatement);
		}
		sqlite3_close(database);
		
		
	}

}

-(void) readDB {
	 sqlite3 *database;
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

-(void) setupDB {
	 BOOL success;
	 self.notes = [[NSMutableArray alloc] init];
	 NSArray *documentPaths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
	 NSString *documentsDir = [documentPaths objectAtIndex:0];
	 databaseName = @"db.sql";
	 databasePath = [documentsDir stringByAppendingPathComponent:databaseName];
	 NSFileManager *fileManager = [NSFileManager defaultManager];
	 success = [fileManager fileExistsAtPath:databasePath];
	 if(!success) {
	 // TODO must deal with errors
	 NSString *databasePathFromApp = [[[NSBundle mainBundle] resourcePath] stringByAppendingPathComponent:databaseName];
	 //printf("old database path is %s\n",[databasePathFromApp cString]);
	 //printf("new database path is %s\n",[databasePath cString]);
	 [fileManager copyItemAtPath:databasePathFromApp toPath:databasePath error:nil];	
	 [fileManager release];
	 }
}
*/

@end
