#import <UIKit/UIKit.h>
#import <CoreLocation/CoreLocation.h>
@class EAGLView;
@interface augmentiaAppDelegate : NSObject <UIAccelerometerDelegate,CLLocationManagerDelegate> {
	IBOutlet UIWindow *window;
	IBOutlet EAGLView *glView;
	CLLocationManager *lm;
}
@property (nonatomic, retain) UIWindow *window;
@property (nonatomic, retain) EAGLView *glView;
@end
