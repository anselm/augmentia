
#import "OAuthTwitterDemoViewController.h"
#import "SA_OAuthTwitterEngine.h"

// you need to make your own secrets file that contains these ( go to twitter to get them )
// #define kOAuthConsumerKey			@""		//REPLACE ME
// #define kOAuthConsumerSecret			@""		//REPLACE ME

#import "secrets.h"

@implementation OAuthTwitterDemoViewController

//=============================================================================================================================

- (void) storeCachedTwitterOAuthData: (NSString *) data forUsername: (NSString *) username {
	NSUserDefaults	*defaults = [NSUserDefaults standardUserDefaults];
	[defaults setObject: data forKey: @"authData"];
	[defaults synchronize];
}

- (NSString *) cachedTwitterOAuthDataForUsername: (NSString *) username {
	return [[NSUserDefaults standardUserDefaults] objectForKey: @"authData"];
}

//=============================================================================================================================

- (void) OAuthTwitterController: (SA_OAuthTwitterController *) controller authenticatedWithUsername: (NSString *) username {
	NSLog(@"Authentication succeeded for %@", username);
}

- (void) OAuthTwitterControllerFailed: (SA_OAuthTwitterController *) controller {
	NSLog(@"Authentication Failed!");
}

- (void) OAuthTwitterControllerCanceled: (SA_OAuthTwitterController *) controller {
	NSLog(@"Authentication Canceled.");
}

//=============================================================================================================================

- (void) requestSucceeded: (NSString *) requestIdentifier {
	NSLog(@"Request %@ succeeded", requestIdentifier);
}

- (void) requestFailed: (NSString *) requestIdentifier withError: (NSError *) error {
	NSLog(@"Request %@ failed with error: %@", requestIdentifier, error);
}

//=============================================================================================================================

- (void)dealloc {
	[_engine release];
    [super dealloc];
}

//=============================================================================================================================

- (void) viewDidAppear: (BOOL)animated {
	if (_engine) return;
	_engine = [[SA_OAuthTwitterEngine alloc] initOAuthWithDelegate: self];
	_engine.consumerKey = kOAuthConsumerKey;
	_engine.consumerSecret = kOAuthConsumerSecret;
	UIViewController *controller = [SA_OAuthTwitterController controllerToEnterCredentialsWithTwitterEngine: _engine delegate: self];
	if (controller) 
		[self presentModalViewController: controller animated: YES];
	else {
		[_engine sendUpdate: [NSString stringWithFormat: @"Testing... %@", [NSDate date]]];
	}

}


@end
