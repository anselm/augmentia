#import <UIKit/UIKit.h>
#import <CoreLocation/CoreLocation.h>

@interface Sensor : NSObject <CLLocationManagerDelegate, UIAccelerometerDelegate> {
	CLLocationManager *lm;
}
- (float)latitude;	
- (float)longitude;
@end
