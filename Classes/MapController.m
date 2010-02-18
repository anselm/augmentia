#import "MapController.h"
#import "CJSONDeserializer.h"
#import "Note.h"

@implementation MapController
@synthesize mapview;

- (id) init {
	if(self = [super init ]) {
	}
	return self;
}

- (void)viewDidUnload {
    self.mapview = nil;
}

- (void)dealloc {
    [mapview release];
    [super dealloc];
}

- (void)loadView {
	[super loadView];	
	if(mapview == NULL ) {
		CGRect frame = [[UIScreen mainScreen] applicationFrame];
		mapview = [ [ MKMapView alloc ] initWithFrame: frame ];
		//[mapview release];
		self.view = mapview;
		//[self.navigationController pushViewController:d.profile animated:YES];
		//[ self addSubview: self.mapview ];
		//	[window addSubview: self.mapview ];
	}
}

-(void) viewDidLoad {
    [super viewDidLoad];
    [mapview setMapType:MKMapTypeStandard];
    [mapview setZoomEnabled:YES];
    [mapview setScrollEnabled:YES];
/*	MKCoordinateRegion region = { {0.0, 0.0 }, { 0.0, 0.0 } };
	region.center.latitude = 41.902245099708516;
	region.center.longitude = 12.457906007766724;
	region.span.longitudeDelta = 0.01f;
	region.span.latitudeDelta = 0.01f;
	[mapview setRegion:region animated:YES];
	[mapview setShowsUserLocation:YES];
*/

	[mapview setDelegate:self];
}

- (MKAnnotationView *)mapView:(MKMapView *)mV viewForAnnotation:(id )annotation {
    MKPinAnnotationView *pinView = nil;
    if(annotation != mapview.userLocation) {
		static NSString *defaultPinID = @"com.invasivecode.pin";
		pinView = (MKPinAnnotationView *)[mapview dequeueReusableAnnotationViewWithIdentifier:defaultPinID];
		if ( pinView == nil ) {
            pinView = [[[MKPinAnnotationView alloc] initWithAnnotation:annotation reuseIdentifier:defaultPinID] autorelease];
		}
        pinView.pinColor = MKPinAnnotationColorPurple;
        pinView.canShowCallout = YES;
        pinView.animatesDrop = YES;
    }
    else
        [mapview.userLocation setTitle:@"I am here"];
    return pinView;
}

- (void)setPositionLatitude:(float)latitude withLongitude:(float)longitude {

//	latitude = 37;
//	longitude = -121;
	
	NSLog(@"setPositionLatitude! %u x %u", latitude, longitude);
	MKCoordinateRegion region = { {0.0, 0.0 }, { 0.0, 0.0 } };
	region.center.latitude = latitude;
	region.center.longitude = longitude;
	region.span.longitudeDelta = 0.1f;
	region.span.latitudeDelta = 0.1f;
	[mapview setRegion:region animated:YES];
	[mapview setShowsUserLocation:YES];

	if(true) {
		NSError *error = NULL;
		NSString* url=[[NSString alloc] initWithFormat:@"http://angel.makerlab.org/json?rad=1&lat=%f&lon=%f",latitude,longitude];
		NSURL *path = [NSURL URLWithString:url];
		//NSData *data = [NSData dataWithContentsOfURL:[NSURL URLWithString:path]];
		//NSString *json = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
		NSString *json = [[NSString alloc] initWithContentsOfURL:path encoding:NSUTF8StringEncoding error:&error];
		if (json == nil) {
			NSLog(@"Error reading file at %@\n%@", path, [error localizedFailureReason]);
			return;
		}
		NSData *json_as_data = [json dataUsingEncoding:NSUTF32BigEndianStringEncoding];
		NSDictionary *dictionary = [[CJSONDeserializer deserializer] deserializeAsDictionary:json_as_data error:nil];

		//"results":[{"note": {"lon":-121.97,"lat":37.37,"rad":0.137799999999998}},	
		
		NSLog(@"showing locations");
//		NSLog(@"results of dciontary: %@", [[dictionary objectForKey:@"results"] description]);

		NSArray *status = [dictionary objectForKey:@"results"];
		NSDictionary *key;
		for (key in status) {
			NSDictionary *note = [key valueForKey:@"note"];
			NSString *lat = [note valueForKey:@"lat"];
			NSString *lon = [note valueForKey:@"lon"];
			NSLog(@"Lat, Lon: %@ x %@", lat, lon);

			Note *ann = [[Note alloc] init];
//			ann.title = @"foo";
			ann.title = [note valueForKey:@"title"];
			if ((NSNull *)ann.title == [NSNull null])
				ann.title = @"BLANK";
			//			ann.subtitle = @"SUBfoo";
			ann.subtitle = [note valueForKey:@"description"];
			if ((NSNull *)ann.subtitle == [NSNull null])
				ann.subtitle = @"Blank blank";
			MKCoordinateRegion aRegion = { {0.0, 0.0 }, { 0.0, 0.0 } };
			aRegion.center.latitude = [lat floatValue];
			aRegion.center.longitude = [lon floatValue];
			NSLog(@"Lat, Lon: %5.2f, %5.2f", aRegion.center.latitude, aRegion.center.longitude);
			aRegion.span.longitudeDelta = 0.01f;
			aRegion.span.latitudeDelta = 0.01f;
			
			ann.coordinate = aRegion.center;
			[mapview addAnnotation:ann];
			
//			[ann release];
		}
		NSLog(@"done setPositionLatitude");
		
	}
}

/*
- (void)animateToWorld:(WorldCity *)worldCity
{    
    MKCoordinateRegion current = mapView.region;
    MKCoordinateRegion zoomOut = { { (current.center.latitude + worldCity.coordinate.latitude)/2.0 , (current.center.longitude + worldCity.coordinate.longitude)/2.0 }, {90, 90} };
    [mapView setRegion:zoomOut animated:YES];
}

- (void)animateToPlace:(WorldCity *)worldCity
{
    MKCoordinateRegion region;
    region.center = worldCity.coordinate;
    MKCoordinateSpan span = {0.4, 0.4};
    region.span = span;
    [mapView setRegion:region animated:YES];
}
*/

@end
