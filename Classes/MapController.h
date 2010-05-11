#import <MapKit/MapKit.h>
@class Note;
@interface MapController : UIViewController <MKMapViewDelegate, CLLocationManagerDelegate, UIAccelerometerDelegate> {
	MKMapView *mapview;
	CLLocationManager *lm;
	Note* profile;
}
@property (nonatomic, retain) MKMapView *mapview;
@property (nonatomic, retain) Note* profile;
- (id)initWithProfile:(Note*)profileParam;

@end
