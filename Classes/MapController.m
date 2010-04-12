#import "MapController.h"
#import "PostController.h"
#import "CJSONDeserializer.h"
#import "Note.h"

@implementation MapController

@synthesize mapview;
@synthesize profile;
@synthesize notes;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SERVER GATEWAY
// TODO move to a separate file
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

- (void)serverQuery:(NSString*)query withLatitude:(float)latitude withLongitude:(float)longitude {
	
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

	// TODO rather than having actual dirty nodes we could just keep a copy of the dictionary and mark that up.
	//		the benefit of doing that is that then we can be multi-threaded over other uses of the dirty queue.
	//		arguably however arguably nobody else except for map is going to use this here in this way so not crucial.

	// Mark all dirty. We are going to Mark and Sweep on new insertions to prevent duplication and minimize memory thrashing
	NSEnumerator *enumerator = [notes keyEnumerator];
	id xkey;
	while((xkey = [enumerator nextObject])) { // TODO remove - can't figure out wtf is up with iterators in objective c
		Note* note = [notes objectForKey:xkey];
		note->dirty = true;
	}

	// Add newly found or mark existing as clean ( ie they have survived ).
	for (NSDictionary* key in [dictionary objectForKey:@"results"]) {
		
		NSDictionary *element = [key valueForKey:@"note"];
		NSString *zkey = [element valueForKey:@"id"];
		if(key == nil) {
			continue;
		}
		
		// If we already have this object then just mark as clean
		Note* note = [notes objectForKey:zkey];
		if(note) {
			note->dirty = false;
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
		note->dirty = false;
		note.title = t;
		note.subtitle = d;
		[notes setValue:note forKey:zkey];
		
		// Add to the map also
		MKCoordinateRegion aRegion = { {0.0, 0.0 }, { 0.0, 0.0 } };
		aRegion.center.latitude = [lat floatValue];
		aRegion.center.longitude = [lon floatValue];
		aRegion.span.longitudeDelta = 0.01f;
		aRegion.span.latitudeDelta = 0.01f;
		note.coordinate = aRegion.center;
		[mapview addAnnotation:note];
		
		// [ann release];
	}
	
	enumerator = [notes keyEnumerator];
	while((xkey = [enumerator nextObject])) { // TODO remove - can't figure out wtf is up with iterators in objective c
		Note* note = [notes objectForKey:xkey];
		if(note->dirty) {
			[mapview removeAnnotation:note];
			[notes removeObjectForKey:note->uuid];
			[note dealloc];
		}
	}
	
	// TODO rather than deleting the allocated RAM it might be nice to just have a fixed size buffer that we recycle
}

/*
 
 //////////////////////////////////////////////////////////////////////////////////////////////////////////
 // Scrap code to fetch things from twitter directly - unused
 // TODO we probably don't want to talk to twitter ( we are not any more )
 // TODO and if we did anyway there is another twitter library that seems to be part of the oauth built in
 //////////////////////////////////////////////////////////////////////////////////////////////////////////
 
 // Given a user account and password fetch their recent activity
 - (void)twitterGetActivity {
 NSURL *path = [NSURL URLWithString:@"http://twitter.com/users/anselm.json"];
 }
 
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
 NSURL *path = [NSURL URLWithString:@"http://angel.makerlab.org/users/anselm.json"];
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
 
 */



//////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// SENSOR CODE - GPS AND ACCELEROMETER
//
// Also these variables are visible to the C code. TODO is that best way we can expose this?
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////

float first_latitude = 0.0;
float first_longitude = 0.0;
float latitude = 45.312245099708516; // Portland Oregon
float longitude = -122.407906007766724;
float accuracy = 0.0;
float first_heading = 0.0;
float heading = 0.0;
int attempt = 5;
int attempts = 0;
BOOL locationChanged = NO;
BOOL goodLocation = NO;
BOOL goodHeading = NO;
float distanceMoved = 0.0;
float currentSpeed = 0.0;
float distanceTimeDelta = 0.0;
float kFilteringFactor = 0.3;
float kAccelerometerFrequency = 30.0;
float xfilter = 0;
float yfilter = 0;
float zfilter = 0;

/*
 The meaning of X, Y, Z by Erica Sadun (with modification for the range from -1.0 to 1.0 for firmware 2.0)
 X = Roll X corresponds to roll, or rotation around the axis that runs from your home button to your earpiece.
 Values vary from 1.0 (rolled all the way to the left) to -1.0 (rolled all the way to the right).
 
 Y = Pitch. Place your iPhone on the table and mentally draw a horizontal line about half-way down the screen.
 That's the axis around which the Y value rotates.
 Values go from 1.0 (the headphone jack straight down) to -1.0 (the headphone jack straight up).
 
 Z = Face up/face down. I expected the Z value to correspond to yaw. And it does not.
 It refers to whether your iPhone is face up (-1.0) or face down (1.0).
 When placed on it side, either the side with the volume controls and ringer switch, or the side directly opposite
 , the Z value equates to 0.0.
 
 http://iphonesdkdev.blogspot.com/2009/04/opengl-es-for-iphone-part-3-with.html
 
 TODO replace this crappy low-pass filter with something that uses inertia so it doesn't jiggle like crazy so much.
 
 */

- (void)accelerometer:(UIAccelerometer *)accelerometer didAccelerate:(UIAcceleration *)acceleration {
	
	//#ifndef TARGET_IPHONE_SIMULATOR 
	float xx = acceleration.x;
	float yy = acceleration.y;
	float zz = acceleration.z;
	float angle = atan2(xx, yy) + M_PI / 2.0;
	
	// low pass filter
	xfilter = acceleration.x * kFilteringFactor + xfilter * (1.0 - kFilteringFactor);
	yfilter = acceleration.y * kFilteringFactor + yfilter * (1.0 - kFilteringFactor);
	yfilter = acceleration.z * kFilteringFactor + zfilter * (1.0 - kFilteringFactor);
	
	/*
	 // Create Status feedback string
	 NSString *xstring = [NSString stringWithFormat:
	 @"X (roll, %4.1f%%): %f\tY (pitch %4.1f%%): %f\tZ (%4.1f%%) : %f - \tangle %f",
	 100.0 - (xx + 1.0) * 100.0, xx,
	 100.0 - (yy + 1.0) * 100.0, yy,
	 100.0 - (zz + 1.0) * 100.0, zz, angle
	 ];
	 
	 // stuff
	 NSLog(xstring);
	 //#endif
	 */
}

//
// Accelerometer event handler for SIO2 - unused for now
//
//- (void)accelerometer:(UIAccelerometer *)accelerometer didAccelerate:(UIAcceleration *)acceleration {
/*
 sio2->_SIO2window->accel->x = acceleration.x * ( 1.0f - sio2->_SIO2window->accel_smooth ) + sio2->_SIO2window->accel->x * sio2->_SIO2window->accel_smooth;
 sio2->_SIO2window->accel->y = acceleration.y * ( 1.0f - sio2->_SIO2window->accel_smooth ) + sio2->_SIO2window->accel->y * sio2->_SIO2window->accel_smooth;
 sio2->_SIO2window->accel->z = acceleration.z * ( 1.0f - sio2->_SIO2window->accel_smooth ) + sio2->_SIO2window->accel->z * sio2->_SIO2window->accel_smooth;
 sio2->_SIO2window->accel->x = ( int )( sio2->_SIO2window->accel->x * 100.0f );
 sio2->_SIO2window->accel->x *= 0.01f;
 sio2->_SIO2window->accel->y = ( int )( sio2->_SIO2window->accel->y * 100.0f );
 sio2->_SIO2window->accel->y *= 0.01f;
 sio2ResourceDispatchEvents( sio2->_SIO2resource, sio2->_SIO2window, SIO2_WINDOW_ACCELEROMETER, SIO2_WINDOW_TAP_NONE );
 */
//}

//
// Location event handler - See:
// http://stackoverflow.com/questions/1081219/optimizing-cllocationmanager-corelocation-to-retrieve-data-points-faster-on-the-i
//
- (void) locationManager: (CLLocationManager *) manager didUpdateToLocation: (CLLocation *) newLocation fromLocation: (CLLocation *) oldLocation {
	
	latitude = newLocation.coordinate.latitude;
	longitude = newLocation.coordinate.longitude;
	accuracy = newLocation.horizontalAccuracy;
	
	NSDate* eventDate = newLocation.timestamp;
	NSTimeInterval howRecent = abs([eventDate timeIntervalSinceNow]);
	attempts++;    
	
	if((newLocation.coordinate.latitude != oldLocation.coordinate.latitude) && (newLocation.coordinate.longitude != oldLocation.coordinate.longitude)) {
		locationChanged = YES;
	} else {
		locationChanged = NO;
	}
	
	// TODO this whole thing is super inaccurate...  not even down to a city block.
	
	// Here's the theory of operation
	// If the value is recent AND
	// If the new location has slightly better accuracy take the new location OR
	// If the new location has an accuracy < 50 meters take the new location OR
	// If the attempts is maxed (3 -5) AND the accuracy < 150 AND the location has changed, then this must be a new location and the device moved
	// so take this new value even though it's accuracy might be worse
	if (howRecent < 5.0) {
#ifndef __i386__
		//Do this only if not simulator since location always returns Cupertino
		if ( (newLocation.horizontalAccuracy < (oldLocation.horizontalAccuracy - 10.0)) || (newLocation.horizontalAccuracy < 50.0)
			|| ((attempts >= attempt) && (newLocation.horizontalAccuracy <= 150.0) && locationChanged) )
#endif
		{
			attempts = 0;
			latitude = newLocation.coordinate.latitude;
			longitude = newLocation.coordinate.longitude;
			if(!goodLocation) {
				first_latitude = latitude;
				first_longitude = longitude;
			}
			NSLog(@"updater setPositionLatitude! %u x %u", latitude, longitude);
			//[currentLocation release];
			//currentLocation = [newLocation retain];
			// [[NSNotificationCenter defaultCenter] postNotificationName: @"UpdateLocationNotification" object: nil];
			if (oldLocation != nil) {
				distanceMoved = [newLocation getDistanceFrom:oldLocation];
				currentSpeed = newLocation.speed;
				distanceTimeDelta = [newLocation.timestamp timeIntervalSinceDate:oldLocation.timestamp];
			}
			goodLocation = YES;
		}
	}
	// Send the update to our delegate (why?) TODO STUDY
	//[self.delegate newLocationUpdate:currentLocation];
}

- (void)locationManager:(CLLocationManager *)manager didUpdateHeading:(CLHeading *)newHeading {
	if (newHeading.headingAccuracy > 0) {
		// [newHeading retain];
		heading = newHeading.trueHeading >= 0 ? newHeading.trueHeading : newHeading.magneticHeading;
		if(!goodHeading) {
			first_heading = heading;
		}
		goodHeading = YES;
    }
}

- (void) locationManager: (CLLocationManager *) manager didFailWithError: (NSError *) error {
    NSString *msg = [[NSString alloc] initWithString:@"Error obtaining location"];
    UIAlertView *alert = [[UIAlertView alloc]
                          initWithTitle:@"Error" 
                          message:msg 
                          delegate:nil 
                          cancelButtonTitle: @"Done"
                          otherButtonTitles:nil];
    [alert show];    
    [msg release];
    [alert release];
}

- (void) sensorStart {
	// Start Sensors
	[[UIApplication sharedApplication] setIdleTimerDisabled:NO];
	[[UIAccelerometer sharedAccelerometer] setUpdateInterval:( 1.0f / kAccelerometerFrequency )];
	[[UIAccelerometer sharedAccelerometer] setDelegate:self];
	lm = [[CLLocationManager alloc] init];
	if ([lm locationServicesEnabled]) {
		lm.delegate = self;
		lm.desiredAccuracy = kCLLocationAccuracyBest;
		lm.distanceFilter = 1000.0f;
		[lm startUpdatingLocation];
		[lm startUpdatingHeading];
	}
}

- (void) sensorStop {
	[lm release];
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MAP LOGIC
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

- (id)initWithProfile:(Note*)profileParam {

	if(self = [super init ]) {
		self.title = @"";
	}

	self.notes = [NSMutableDictionary init]; // TODO remove either this or the one below - wtf is up with dictionaries in objective c?

	NSMutableDictionary *dictionary = [NSMutableDictionary dictionaryWithObjectsAndKeys: nil ];
	self.notes = dictionary;

	self.profile = profileParam;
	[self sensorStart];
	return self;
}

- (void)dealloc {
	[self sensorStop];
	if(mapview) {
		[mapview release];
		mapview = nil;
	}
	[notes dealloc];
	[super dealloc];
}

- (void)viewDidUnload {
	self.mapview = nil; // TODO WHY? TODO what is diff between viewunload and viewwilldissapear? WHY SELF?
}

- (void)loadView {
	[super loadView];
	if(mapview == NULL ) {
		CGRect frame = [[UIScreen mainScreen] applicationFrame];
		mapview = [ [ MKMapView alloc ] initWithFrame: frame ];
		self.view = mapview;
		[mapview release];
	}
}

-(void) viewDidLoad {
	[super viewDidLoad];

	// Add Map
	[mapview setMapType:MKMapTypeStandard];
	[mapview setZoomEnabled:YES];
	[mapview setScrollEnabled:YES];
	MKCoordinateRegion region = { {0.0, 0.0 }, { 0.0, 0.0 } };
	region.center.latitude = latitude;
	region.center.longitude = longitude;
	region.span.longitudeDelta = 0.01f;
	region.span.latitudeDelta = 0.01f;
	[mapview setRegion:region animated:YES];
	[mapview setShowsUserLocation:YES];
	[mapview setDelegate:self];

	// Add controls to the nav bar
	
	//NSArray *segmentTextContent = [NSArray arrayWithObjects:[UIImage imageNamed:@"arrow-dice.png"], [UIImage imageNamed:@"arrow-up.png"], [UIImage imageNamed:@"arrow-down.png"], nil];
	NSArray *items = [NSArray arrayWithObjects: @"C", @"U", @"+", nil];
	UISegmentedControl *segments = [[UISegmentedControl alloc] initWithItems:items];
	//segments.frame = CGRectMake(145, 5, 150, 35);
	//segments.selectedSegmentIndex = 1;
	segments.tag = 0;
	segments.momentary = YES;
	segments.segmentedControlStyle = UISegmentedControlStyleBar;
	[segments addTarget:self action:@selector(segmentAction:) forControlEvents:UIControlEventValueChanged];

	// UIBarButtonItem* addButton = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItem target:self action:@selector(addAction:)];
	UIBarButtonItem *segment = [[UIBarButtonItem alloc] initWithCustomView:segments];
	//[segments release];

	// self.navigationItem.rightBarButtonItem = segment;
	//self.navigationItem.rightBarButtonItem.title = @"x";
	//self.navigationItem.rightBarButtonItem.customView.hidden = NO;

	self.parentViewController.navigationItem.rightBarButtonItem = segment;
	self.title = @"";
	self.parentViewController.title = @"w";
	
	//[actionControl release];

}

- (void)segmentAction:(UISegmentedControl*)sender {
	switch ([sender selectedSegmentIndex]) {
		case 0:
		{
			// Move map to where user is - TODO make async
			NSLog(@"setPositionLatitude! %u x %u", latitude, longitude);
			MKCoordinateRegion region = { {0.0, 0.0 }, { 0.0, 0.0 } };
			region.center.latitude = latitude;
			region.center.longitude = longitude;
			region.span.longitudeDelta = 0.1f;
			region.span.latitudeDelta = 0.1f;
			[mapview setRegion:region animated:YES];
			[mapview setShowsUserLocation:YES];
			// Get data where user is - TODO make async - TODO block duplicate requests or throw away the old one
			[self serverQuery:profile.title withLatitude:latitude withLongitude:longitude];			
			break;
		}
		case 1:
		{
			// Get where map is
			MKCoordinateRegion current = mapview.region;
			// Get data where user is - TODO make async - TODO block duplicate requests or throw away the old one
			[self serverQuery:profile.title withLatitude:current.center.latitude withLongitude:current.center.longitude];			
			break;
		}
		case 2:
		{
			// Bring up a view for making a new post
			PostController* post = [[PostController alloc] init];
			[self.navigationController pushViewController:post animated:true];
			[post release];
			break;
		}
		default:
			break;
	}
}

//
// Google Maps provided callback triggered on picking an element
//
- (MKAnnotationView *)mapView:(MKMapView *)mV viewForAnnotation:(id )annotation {
	MKPinAnnotationView *pinView = nil;
	if(annotation != mapview.userLocation) {
		static NSString *defaultPinID = @"com.makerlab";
		pinView = (MKPinAnnotationView *)[mapview dequeueReusableAnnotationViewWithIdentifier:defaultPinID];
		if ( pinView == nil ) {
			pinView = [[[MKPinAnnotationView alloc] initWithAnnotation:annotation reuseIdentifier:defaultPinID] autorelease];
		}
		pinView.pinColor = MKPinAnnotationColorPurple;
		pinView.canShowCallout = YES;
		pinView.animatesDrop = YES;
	}
	else {
		[mapview.userLocation setTitle:@"I am here"];
	}
	return pinView;
}

@end
