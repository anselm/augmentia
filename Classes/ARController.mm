
#include "ARView.h"
#include "ARController.h"

@implementation ARController

// Transform values for full screen support:
#define CAMERA_TRANSFORM_X 1
#define CAMERA_TRANSFORM_Y 1.12412

@synthesize arview;

- (ARController *) init {
	[super init];
	self.title = @"AR View";
	return self;
}

- (void)dealloc {
	[arview release];
	[super dealloc];
}

- (void)loadView {
	if(arview == NULL) {
		CGRect frame = [[UIScreen mainScreen] applicationFrame];
		arview = [[ARView alloc] initWithFrame:frame];
		arview.animationInterval = 1.0 / 60.0;
		self.view = arview;
		[arview release];
		[arview startAnimation];
		NSLog(@"ARViewController: initialization complete!");
	} else {
		NSLog(@"ARViewController: trying to initialize more than once!? Why?");
	}	
}


- (void) viewDidAppear:(BOOL)animated { 

#ifndef __i386__
	// Show a camera overlay if on real hardware (not on a simulator)
	UIImagePickerController *picker = [[UIImagePickerController alloc] init];
	picker.sourceType = UIImagePickerControllerSourceTypeCamera;
	picker.showsCameraControls = NO;
	picker.navigationBarHidden = YES;
	picker.wantsFullScreenLayout = YES;
	picker.cameraViewTransform = CGAffineTransformScale(picker.cameraViewTransform, CAMERA_TRANSFORM_X, CAMERA_TRANSFORM_Y);
	picker.cameraOverlayView = arview;
	[self presentModalViewController:picker animated:YES];	
	[picker release];
#endif

	arview.animationInterval = 1.0 / 60.0;
	[arview startAnimation];

    [super viewDidAppear:YES];
}

- (void)applicationWillResignActive:(UIApplication *)application {
	arview.animationInterval = 1.0 / 5.0;
}

- (void)applicationDidBecomeActive:(UIApplication *)application {
	arview.animationInterval = 1.0 / 60.0;
}

@end

