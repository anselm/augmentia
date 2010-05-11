#import <UIKit/UIKit.h>
#import <CoreLocation/CoreLocation.h>

@interface Sensor : NSObject <CLLocationManagerDelegate, UIAccelerometerDelegate> {
	CLLocationManager *lm;
	float sensor_latitude;
	float sensor_longitude;
}
@property (nonatomic, readwrite ) float sensor_latitude;
@property (nonatomic, readwrite ) float sensor_longitude;
- (void) sensorStart;
- (void) sensorStop;
@end
