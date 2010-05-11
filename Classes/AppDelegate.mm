
#import <UIKit/UIKit.h>
#import "AppDelegate.h"

#import "DB.h"
#import "ProfilesController.h"

@implementation AppDelegate

@synthesize db;
@synthesize nav;
@synthesize window;

- (void)applicationDidFinishLaunching:(UIApplication *)application {

	// Start DB
	db = [DB sharedDB];

	// Window preferences
	application.statusBarHidden = NO;
	application.statusBarStyle = UIStatusBarStyleBlackOpaque;
	window = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
	window.backgroundColor = [UIColor redColor];	

	// Start off with a profiles picker
	ProfilesController *profiles = [[ProfilesController alloc] init];

	// And a navigation bar
	nav = [[UINavigationController alloc] initWithRootViewController:profiles];

	// Show the profiles now
	[window addSubview:nav.view];
	[window makeKeyAndVisible];
}

- (void)dealloc {
	[window release];
	[super dealloc];
}

@end
