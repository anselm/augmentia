
#import <UIKit/UIKit.h>
#import <CoreLocation/CoreLocation.h>

@class DB;
@class UIWindow;
@interface AppDelegate : NSObject <UIApplicationDelegate,UIAccelerometerDelegate,CLLocationManagerDelegate> {
	DB *db;
	UIWindow *window;
	UINavigationController *nav;
}
@property (nonatomic, retain) DB *db;
@property (nonatomic, retain) UIWindow *window;
@property (nonatomic, retain) UINavigationController *nav;
@end
