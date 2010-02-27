
#import <UIKit/UIKit.h>
#import "AppDelegate.h"

#import "DB.h"

#import "ARController.h"
#import "MapController.h"
#import "GlobeController.h"
#import "DetailController.h"
#import "ProfileController.h"
#import "ProfilesController.h"
#import "ProfileNewController.h"
#import "OAuthTwitterDemoViewController.h"

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
ProfileNewController *profilenew;
OAuthTwitterDemoViewController *oauth;

- (void)setActiveViewController:(NSString *)name {

	if(window == nil) {

//		ar = [[ARController alloc] init];
//		map = [[MapController alloc] init];
//		detail = [[DetailController alloc] init];
//		globe = [[GlobeController alloc] init];
//		profile = [[ProfileController alloc] init];
		profiles = [[ProfilesController alloc] init];
		profilenew = [[ProfileNewController alloc] init];
		nav = [[UINavigationController alloc] initWithRootViewController:profiles];

		// application.statusBarHidden = YES;
		// application.statusBarStyle = UIStatusBarStyleBlackOpaque;
		window = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
		window.backgroundColor = [UIColor redColor];

		[window addSubview:nav.view];
		[window makeKeyAndVisible];

	} else if([name isEqualToString:@"ProfileNew"]) {
		[nav pushViewController:profilenew animated:YES];
	} else if([name isEqualToString:@"TwitterAuth"]) {
		if(!oauth) {
			oauth = [[OAuthTwitterDemoViewController alloc] init];
		}
		[nav pushViewController:oauth animated:YES];
	} else if([name isEqualToString:@"profiles_from_profile_new"]) {
		[nav popViewControllerAnimated:YES];
//		[[(UITableViewController *)[nav topViewController] tableView] reloadData];
		[profiles.tableView reloadData];
	}
}

- (void)applicationDidFinishLaunching:(UIApplication *)application {
	
	// Initialize our database first
	db = [DB sharedDB];
	
	// Make one of the controllers take over
	[self setActiveViewController:@"Profiles"];

}

- (void)dealloc {
	[window release];
	[super dealloc];
}

@end
