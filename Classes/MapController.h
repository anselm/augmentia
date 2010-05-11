#import <MapKit/MapKit.h>
@class Note;
@interface MapController : UIViewController <MKMapViewDelegate> {
	MKMapView *mapview;
	Note* profile;
}
@property (nonatomic, retain) MKMapView *mapview;
@property (nonatomic, retain) Note* profile;
- (id)initWithProfile:(Note*)profileParam;

@end
