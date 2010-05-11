#import "MapController.h"
#import "PostController.h"
#import "Sensor.h"
#import "Note.h"

@implementation MapController

@synthesize mapview;
@synthesize profile;

Sensor *sensor;

- (id)initWithProfile:(Note*)profileParam {

	if(self = [super init ]) {
		self.title = @"";
	}

	self.profile = profileParam;
	sensor = [[Sensor alloc] init];
	[sensor sensorStart];
	return self;
}

- (void)dealloc {
	[sensor sensorStop];
	if(mapview) {
		[mapview release];
		mapview = nil;
	}
	[super dealloc];
}

- (void)viewDidUnload {
	self.mapview = nil; // TODO WHY? TODO what is diff between viewunload and viewwilldissapear? WHY SELF?
}

- (void)loadView {
	[super loadView];
	if(mapview == NULL ) {
		CGRect frame = [[UIScreen mainScreen] applicationFrame];
		mapview = [ [ MKMapView alloc ] initWithFrame: frame ];
		self.view = mapview;
		[mapview release];
	}
}

-(void) viewDidLoad {
	[super viewDidLoad];
	float latitude = [sensor latitude];
	float longitude = [sensor longitude];

	// Add Map
	[mapview setMapType:MKMapTypeStandard];
	[mapview setZoomEnabled:YES];
	[mapview setScrollEnabled:YES];
	MKCoordinateRegion region = { {0.0, 0.0 }, { 0.0, 0.0 } };
	region.center.latitude = latitude;
	region.center.longitude = longitude;
	region.span.longitudeDelta = 0.01f;
	region.span.latitudeDelta = 0.01f;
	[mapview setRegion:region animated:YES];
	[mapview setShowsUserLocation:YES];
	[mapview setDelegate:self];

	// Add controls to the nav bar
	
	//NSArray *segmentTextContent = [NSArray arrayWithObjects:[UIImage imageNamed:@"arrow-dice.png"], [UIImage imageNamed:@"arrow-up.png"], [UIImage imageNamed:@"arrow-down.png"], nil];
	NSArray *items = [NSArray arrayWithObjects: @"C", @"U", @"+", nil];
	UISegmentedControl *segments = [[UISegmentedControl alloc] initWithItems:items];
	//segments.frame = CGRectMake(145, 5, 150, 35);
	//segments.selectedSegmentIndex = 1;
	segments.tag = 0;
	segments.momentary = YES;
	segments.segmentedControlStyle = UISegmentedControlStyleBar;
	[segments addTarget:self action:@selector(segmentAction:) forControlEvents:UIControlEventValueChanged];

	// UIBarButtonItem* addButton = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItem target:self action:@selector(addAction:)];
	UIBarButtonItem *segment = [[UIBarButtonItem alloc] initWithCustomView:segments];
	//[segments release];

	// self.navigationItem.rightBarButtonItem = segment;
	//self.navigationItem.rightBarButtonItem.title = @"x";
	//self.navigationItem.rightBarButtonItem.customView.hidden = NO;

	self.parentViewController.navigationItem.rightBarButtonItem = segment;
	self.title = @"";
	self.parentViewController.title = @"w";
	
	//[actionControl release];

}

- (void)segmentAction:(UISegmentedControl*)sender {
	float latitude = [sensor latitude];
	float longitude = [sensor longitude];
	switch ([sender selectedSegmentIndex]) {
		case 0:
		{
			// Move map to where user is - TODO make async
			NSLog(@"setPositionLatitude! %u x %u", latitude, longitude);
			MKCoordinateRegion region = { {0.0, 0.0 }, { 0.0, 0.0 } };
			region.center.latitude = latitude;
			region.center.longitude = longitude;
			region.span.longitudeDelta = 0.1f;
			region.span.latitudeDelta = 0.1f;
			[mapview setRegion:region animated:YES];
			[mapview setShowsUserLocation:YES];
			// Get data where user is - TODO make async - TODO block duplicate requests or throw away the old one
			[self serverQuery:profile.title withLatitude:latitude withLongitude:longitude];			
			break;
		}
		case 1:
		{
			// Get where map is
			MKCoordinateRegion current = mapview.region;
			// Get data where user is - TODO make async - TODO block duplicate requests or throw away the old one
			[self serverQuery:profile.title withLatitude:current.center.latitude withLongitude:current.center.longitude];			
			break;
		}
		case 2:
		{
			// Bring up a view for making a new post
			PostController* post = [[PostController alloc] init];
			[self.navigationController pushViewController:post animated:true];
			[post release];
			break;
		}
		default:
			break;
	}
}

//
// Google Maps provided callback triggered on picking an element
//
- (MKAnnotationView *)mapView:(MKMapView *)mV viewForAnnotation:(id )annotation {
	MKPinAnnotationView *pinView = nil;
	if(annotation != mapview.userLocation) {
		static NSString *defaultPinID = @"com.makerlab";
		pinView = (MKPinAnnotationView *)[mapview dequeueReusableAnnotationViewWithIdentifier:defaultPinID];
		if ( pinView == nil ) {
			pinView = [[[MKPinAnnotationView alloc] initWithAnnotation:annotation reuseIdentifier:defaultPinID] autorelease];
		}
		pinView.pinColor = MKPinAnnotationColorPurple;
		pinView.canShowCallout = YES;
		pinView.animatesDrop = YES;
	}
	else {
		[mapview.userLocation setTitle:@"I am here"];
	}
	return pinView;
}

@end
