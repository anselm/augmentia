
#import "Note.h"
#import "Sensor.h"
#import "MapController.h"

@implementation MapController

extern Sensor* sensor;

@synthesize mapview;
@synthesize profile;

- (id)initWithProfile:(Note*)profileParam {
	self = [super init ];
	self.title = @"world";
	self.profile = profileParam;
	return self;
}

- (void)dealloc {
	[mapview release];
	mapview = nil;
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
	float latitude = [sensor sensor_latitude];
	float longitude = [sensor sensor_longitude];

	// Add Map
	[mapview setMapType:MKMapTypeStandard];
	[mapview setZoomEnabled:YES];
	[mapview setScrollEnabled:YES];
	MKCoordinateRegion region = { {0.0, 0.0 }, { 0.0, 0.0 } };
	region.center.latitude = latitude;
	region.center.longitude = longitude;
	region.span.longitudeDelta = 10.0f;
	region.span.latitudeDelta = 10.0f;
	[mapview setRegion:region animated:YES];
	[mapview setShowsUserLocation:YES];
	[mapview setDelegate:self];

	// Add controls to the nav bar

	// UIBarButtonItem* addButton = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItem target:self action:@selector(addAction:)];

	//NSArray *segmentTextContent = [NSArray arrayWithObjects:[UIImage imageNamed:@"arrow-dice.png"], [UIImage imageNamed:@"arrow-up.png"], [UIImage imageNamed:@"arrow-down.png"], nil];
	NSArray *items = [NSArray arrayWithObjects: @"Center", @"Update",nil];
	UISegmentedControl *segments = [[UISegmentedControl alloc] initWithItems:items];
	//segments.frame = CGRectMake(145, 5, 150, 35);
	//segments.selectedSegmentIndex = 1;
	segments.tag = 0;
	segments.momentary = YES;
	segments.segmentedControlStyle = UISegmentedControlStyleBar;
	[segments addTarget:self action:@selector(segmentAction:) forControlEvents:UIControlEventValueChanged];
	UIBarButtonItem *segment = [[UIBarButtonItem alloc] initWithCustomView:segments];
	self.parentViewController.navigationItem.rightBarButtonItem = segment;
	//[segments release];

	self.title = @"world";
	self.parentViewController.title = @"world";

}

- (void)segmentAction:(UISegmentedControl*)sender {
	float latitude = [sensor sensor_latitude];
	float longitude = [sensor sensor_longitude];
	switch ([sender selectedSegmentIndex]) {
		case 0:
		{
			// RECENTER
			MKCoordinateRegion region = { {0.0, 0.0 }, { 0.0, 0.0 } };
			region.center.latitude = latitude;
			region.center.longitude = longitude;
			region.span.longitudeDelta = 0.1f;
			region.span.latitudeDelta = 0.1f;
			[mapview setRegion:region animated:YES];
			[mapview setShowsUserLocation:YES];
			// FALL THROUGH
		}
		case 1:
		{
			// LOAD DATA HERE
			MKCoordinateRegion current = mapview.region;
			// Get data where user is - TODO make async - TODO block duplicate requests or throw away the old one
	//		[self serverQuery:profile.title withLatitude:current.center.latitude withLongitude:current.center.longitude];			
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
