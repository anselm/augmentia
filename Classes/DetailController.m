
#import "AppDelegate.h"
#import "DetailController.h"
#import "Note.h"
#import "DB.h"

@implementation DetailController

@synthesize image;

- (id) init {
	[super init];
	return self;
}

- (BOOL)shouldAutorotateToInterfaceOrientation: (UIInterfaceOrientation)interfaceOrientation {
	return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

- (void)didReceiveMemoryWarning {
	[ super didReceiveMemoryWarning ];
}

- (void)dealloc {
	[ super dealloc ];
}

- (void) loadView {
	[ super loadView ];
}

- (void) viewWillAppear:(BOOL)animated {
	UISlider *gameVolumeControl = [ [ UISlider alloc ] initWithFrame: CGRectMake(170, 0, 125, 50) ];
	gameVolumeControl.minimumValue = 0.0;
	gameVolumeControl.maximumValue = 10.0;
	gameVolumeControl.tag = 1;
	gameVolumeControl.value = 3.5;
	gameVolumeControl.continuous = YES;
	[gameVolumeControl addTarget:self action:@selector(sliderAction:) forControlEvents:UIControlEventValueChanged];
	[self.view addSubview: gameVolumeControl ];
	[ gameVolumeControl release ];
	
	AppDelegate *d = (AppDelegate *)[[UIApplication sharedApplication] delegate];
	Note* note = d.db.cursor;

	NSData *file = [NSData dataWithContentsOfURL:[NSURL URLWithString:[note image]]];
	UIImage *uiimage = [[UIImage alloc] initWithData:file];
	CGRect myImageRect = CGRectMake(0.0f, 0.0f, 64.0f, 64.0f);
	image = [[UIImageView alloc] initWithFrame:myImageRect];
	[image setImage:uiimage];
	image.opaque = YES;
	[self.view addSubview:image];
	[image release];
}

- (void)viewDidLoad {
	[super viewDidLoad];
}

- (void)sliderAction:(UISlider*)sender {
//	if ([activeTextField canResignFirstResponder])
//	[activeTextField resignFirstResponder];
	NSLog(@"sliderAction: sender = %d, value = %.1f", [sender tag], [sender value]);
}

@end

