
#import <UIKit/UIKit.h>
#import <CoreLocation/CoreLocation.h>

@class ARView;

@interface ARController: UIViewController <UIAccelerometerDelegate,CLLocationManagerDelegate> {
	ARView *arview;
	UITextField *latitudeTextField;
	UITextField *longitudeTextField;
	UITextField *accuracyTextField;
	CLLocationManager *lm;
}
@property (retain, nonatomic) ARView *arview;
@property (retain, nonatomic) UITextField *latitudeTextField;
@property (retain, nonatomic) UITextField *longitudeTextField;
@property (retain, nonatomic) UITextField *accuracyTextField;
@end
