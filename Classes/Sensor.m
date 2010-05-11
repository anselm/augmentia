//
//  Sensor.m
//  augmentia
//
//  Created by Anselm Hook on 4/15/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import "Sensor.h"

@implementation Sensor

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

@end
