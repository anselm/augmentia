
#import "EXContainer.h"
#import "EXPredicateEqualText.h"
#import <sqlite3.h>

#import "Note.h"
#import "DB.h"
#import "CJSONDeserializer.h"

static DB *db = nil;

@implementation DB

@synthesize notes;

EXFile* file;
EXContainer* container;

//////////////////////////////////////////////////////////////////////////////////////////////////////////
// initialization of singleton
//////////////////////////////////////////////////////////////////////////////////////////////////////////

-(id) init {
	[super init];
	NSArray* paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
	NSString* documentsDirectory = [paths objectAtIndex: 0];
	NSString* dbFileName = [documentsDirectory stringByAppendingFormat: @"/db3.db"];
	file = [EXFile fileWithName: dbFileName];
	container = [[EXContainer alloc] initWithFile: file];
	notes = [NSMutableDictionary dictionaryWithObjectsAndKeys: nil ];
	db = self;
	return self;
}

- (void) dealloc {
	[container release];
	[notes dealloc];
	[super dealloc];
}

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
	return UINT_MAX;
}

- (void)release {
}

- (id)autorelease {
	return self;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
// database wrappers
//////////////////////////////////////////////////////////////////////////////////////////////////////////

//
// Get all notes of a kind
//
-(NSArray*) getNotes:(NSString*)kind {
	if(container!=nil && kind!=nil) {
		EXPredicate* predicate = [[[EXPredicateEqualText alloc] initWithFieldName: @"kind" value: kind] autorelease];
		NSArray* resultSet = [container queryWithClass: [Note class] predicate: predicate];
		[resultSet retain]; // TODO I seem to be losing these... paranoia... examine.
		return resultSet;
	}
	NSArray* results = [NSArray arrayWithObjects: nil ];
	[results retain]; // TODO why retain this?
	return results;
}

//
// Get a note by title
//
-(Note*) getNote:(NSString *)kind Title:(NSString *)title {
	if(container != nil && title != nil) {
		// TODO why not query on both keys?
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

//
// Save a note
//
-(void) updateNote:(NSString *)k Title:(NSString *)t Description:(NSString *)d Image:(NSString*)i {
	if(container != nil && t!=nil) {
		Note *note = [[Note alloc] init:k title:t description:d image:i];
		[container storeObject: note];
		[note dealloc];
	}
}

//
// Query for notes
// May talk to cache or server
//
- (void)query:(NSString*)query withLatitude:(float)latitude withLongitude:(float)longitude {

	// TODO block multiple simultaneous requests
	// TODO make this asynchronous

	// Unused approach - TODO think about skipping ascii step below and using this later
	// NSData *data = [NSData dataWithContentsOfURL:[NSURL URLWithString:path]];
	// NSString *json = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];

	// Fetch data
	NSString* server=@"http://angel.makerlab.org/json?";
	//NSString* url=[[NSString alloc] initWithFormat:@"%@rad=1&latitude=%f&longitude=%f&q=%@",server,latitude,longitude,query];
	NSString* url=[[NSString alloc] initWithFormat:@"%@rad=1&latitude=%f&longitude=%f",server,latitude,longitude];
	NSURL *path = [NSURL URLWithString:url];
	NSError *error = NULL;
	NSString *json = [[NSString alloc] initWithContentsOfURL:path encoding:NSUTF8StringEncoding error:&error];
	[url release];

	// Bail if error
	if (json == nil) {
		NSLog(@"Error reading file at %@\n%@", path, [error localizedFailureReason]);
		return;
	}

	// Convert results to a dictionary
	NSData *json_as_data = [json dataUsingEncoding:NSUTF32BigEndianStringEncoding];
	NSDictionary *dictionary = [[CJSONDeserializer deserializer] deserializeAsDictionary:json_as_data error:nil];

	// Convert dictionary to objects - do not insert duplicates but do update their timestamp
	for (NSDictionary* key in [dictionary objectForKey:@"results"]) {

		NSDictionary *element = [key valueForKey:@"note"];
		NSString *zkey = [element valueForKey:@"id"];
		if(key == nil) {
			continue;
		}

		// If we already have this object then just mark as clean
		Note* note = [notes objectForKey:zkey];
		if(note) {
			note->flags = 0;
			continue;
		}

		// Add object
		NSString *k = [element valueForKey:@"kind"];
		NSString *t = [element valueForKey:@"title"];
		NSString *d = [element valueForKey:@"description"];
		NSString *lat = [element valueForKey:@"lat"];
		NSString *lon = [element valueForKey:@"lon"];
		note = [[Note alloc] init:k title:t description:d image:nil];
		note->key = zkey;
		note->lat = [lat floatValue];
		note->lon = [lon floatValue];
		note.title = t;
		note.subtitle = d;
		[notes setValue:note forKey:zkey];

		// Add to the map also
		// TODO obviously we don't want this here.
		MKCoordinateRegion aRegion = { {0.0, 0.0 }, { 0.0, 0.0 } };
		aRegion.center.latitude = [lat floatValue];
		aRegion.center.longitude = [lon floatValue];
		aRegion.span.longitudeDelta = 0.01f;
		aRegion.span.latitudeDelta = 0.01f;
		note.coordinate = aRegion.center;
		//		[mapview addAnnotation:note];

		// [ann release];
	}

	// TODO mark and sweep is broken
	/*
	enumerator = [notes keyEnumerator];
	while((xkey = [enumerator nextObject])) { // TODO remove - can't figure out wtf is up with iterators in objective c
		Note* note = [notes objectForKey:xkey];
		if(note->dirty) {
			//			[mapview removeAnnotation:note];
			[notes removeObjectForKey:note->uuid];
			[note dealloc];
		}
	}*/
	
	// TODO rather than deleting the allocated RAM it might be nice to just have a fixed size buffer that we recycle
}

@end
