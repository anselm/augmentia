
#import <UIKit/UIKit.h>
#import "AppDelegate.h"

#import "ARController.h"
#import "GlobeController.h"
#import "DetailController.h"
#import "ProfileController.h"
#import "ProfilesController.h"
#import "MapController.h"
#import "DB.h"

@implementation AppDelegate
@synthesize db;
@synthesize window;

UINavigationController *nav;
ARController *ar;
MapController *map;
GlobeController *globe;
DetailController *detail;
ProfileController *profile;
ProfilesController *profiles;

- (void)setActiveViewController:(NSString *)name {

	if(window == nil) {

		ar = [[ARController alloc] init];
		map = [[MapController alloc] init];
		detail = [[DetailController alloc] init];
		profile = [[ProfileController alloc] init];
		profiles = [[ProfilesController alloc] init];
		nav = [[UINavigationController alloc] initWithRootViewController:profiles];

		// application.statusBarHidden = YES;
		// application.statusBarStyle = UIStatusBarStyleBlackOpaque;
		window = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
		window.backgroundColor = [UIColor redColor];

		[nav pushViewController:ar animated:YES];	

		[window addSubview:nav.view];
		[window makeKeyAndVisible];

	}
}

- (void)applicationDidFinishLaunching:(UIApplication *)application {
	
	// Initialize our database first
	db = [DB sharedDB];
	
	// Make one of the controllers take over
	[self setActiveViewController:@""];

}

- (void)dealloc {
	[window release];
	[super dealloc];
}

@end
