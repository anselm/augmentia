//
// Application kick off point
//
// Globals are registered here for convenience
//
//

@class DB;
@class UIWindow;
@interface AppDelegate : NSObject  <UIApplicationDelegate> {
	DB *db;
	UIWindow *window;
}
@property (nonatomic, retain) DB *db;
@property (nonatomic, retain) UIWindow *window;
- (void)setActiveViewController:(NSString *)name;
@end
