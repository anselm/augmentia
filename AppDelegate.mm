
#import "AppDelegate.h"
#import "ARViewController.h"
#import "ARView.h"

@implementation AppDelegate

@synthesize window;
@synthesize control;

- (void)applicationDidFinishLaunching:(UIApplication *)application {

	// application.statusBarHidden = YES;
	// application.statusBarStyle = UIStatusBarStyleBlackOpaque;

	window = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
	window.backgroundColor = [UIColor redColor];
	
	control = [[ARViewController alloc] init];
	[window addSubview:control.view];
	
	[window makeKeyAndVisible];
}


- (void)dealloc {
	[window release];
	[super dealloc];
}

@end
