#import <UIKit/UIKit.h>
@class ARViewController;
@interface AppDelegate : NSObject {
	UIWindow *window;
	ARViewController *control;
}
@property (nonatomic, retain) UIWindow *window;
@property (nonatomic, retain) ARViewController *control;
@end
