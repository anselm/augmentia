
#include "ARView.h"
#include "ARViewController.h"
#include "sio2.h"


// Transform values for full screen support:
#define CAMERA_TRANSFORM_X 1
#define CAMERA_TRANSFORM_Y 1.12412

// iPhone screen dimensions:
#define SCREEN_WIDTH  320
#define SCREEN_HEIGTH 480


@implementation ARViewController

@synthesize arview;
@synthesize latitudeTextField;
@synthesize longitudeTextField;
@synthesize accuracyTextField;

//
// Visible to C code - TODO improve - maybe move c code to objective c later
//
float first_latitude = 0.0;
float first_longitude = 0.0;
float latitude = 0.0;
float longitude = 0.0;
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

//
// Accelerometer event handler
//
- (void)accelerometer:(UIAccelerometer *)accelerometer didAccelerate:(UIAcceleration *)acceleration {
	sio2->_SIO2window->accel->x = acceleration.x * ( 1.0f - sio2->_SIO2window->accel_smooth ) + sio2->_SIO2window->accel->x * sio2->_SIO2window->accel_smooth;
	sio2->_SIO2window->accel->y = acceleration.y * ( 1.0f - sio2->_SIO2window->accel_smooth ) + sio2->_SIO2window->accel->y * sio2->_SIO2window->accel_smooth;
	sio2->_SIO2window->accel->z = acceleration.z * ( 1.0f - sio2->_SIO2window->accel_smooth ) + sio2->_SIO2window->accel->z * sio2->_SIO2window->accel_smooth;
	sio2->_SIO2window->accel->x = ( int )( sio2->_SIO2window->accel->x * 100.0f );
	sio2->_SIO2window->accel->x *= 0.01f;
	sio2->_SIO2window->accel->y = ( int )( sio2->_SIO2window->accel->y * 100.0f );
	sio2->_SIO2window->accel->y *= 0.01f;
	sio2ResourceDispatchEvents( sio2->_SIO2resource, sio2->_SIO2window, SIO2_WINDOW_ACCELEROMETER, SIO2_WINDOW_TAP_NONE );
}

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

- (void)loadView {
	if(arview == NULL) {
		CGRect frame = [[UIScreen mainScreen] applicationFrame];
		arview = [[ARView alloc] initWithFrame:frame];
		arview.animationInterval = 1.0 / 60.0;
		self.view = arview;
		[arview release];
		[arview startAnimation];
		NSLog(@"ARViewController: initialization complete!");
	} else {
		NSLog(@"ARViewController: trying to initialize more than once!? Why?");
	}	
}


- (void) viewDidAppear:(BOOL)animated { 

	// CAMERA OVERLAY
	UIImagePickerController *picker = [[UIImagePickerController alloc] init];
	picker.sourceType = UIImagePickerControllerSourceTypeCamera;
	picker.showsCameraControls = NO;
	picker.navigationBarHidden = YES;
	picker.wantsFullScreenLayout = YES;
	picker.cameraViewTransform = CGAffineTransformScale(picker.cameraViewTransform, CAMERA_TRANSFORM_X, CAMERA_TRANSFORM_Y);
	picker.cameraOverlayView = arview;
	[self presentModalViewController:picker animated:YES];	
	[picker release];

	// KICK OFF VIEW
	arview.animationInterval = 1.0 / 60.0;
	[arview startAnimation];

	// KICK OFF SENSORS
	[[UIApplication sharedApplication] setIdleTimerDisabled:NO];
	[[UIAccelerometer sharedAccelerometer] setUpdateInterval:( 1.0f / 30.0f )];
	[[UIAccelerometer sharedAccelerometer] setDelegate:self];
	lm = [[CLLocationManager alloc] init];
	if ([lm locationServicesEnabled]) {
		lm.delegate = self;
		lm.desiredAccuracy = kCLLocationAccuracyBest;
		lm.distanceFilter = 1000.0f;
		[lm startUpdatingLocation];
		[lm startUpdatingHeading];
	}

    [super viewDidAppear:YES];
}

- (void)applicationWillResignActive:(UIApplication *)application {
	arview.animationInterval = 1.0 / 5.0;
}

- (void)applicationDidBecomeActive:(UIApplication *)application {
	arview.animationInterval = 1.0 / 60.0;
}

- (void)dealloc {
	[arview release];
	[lm release];
	[latitudeTextField release];
	[longitudeTextField release];
	[accuracyTextField release];
	[super dealloc];
}

- (ARViewController *) init {
	NSLog(@"ARViewController: init called");
	self.title = @"ARViewController";
	return self;
}


@end

