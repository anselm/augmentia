#import <MapKit/MapKit.h>
@interface MapController : UIViewController <MKMapViewDelegate> {
	MKMapView *mapview;
}
@property (nonatomic, retain) MKMapView *mapview;
- (void)setPositionLatitude:(float)latitude withLongitude:(float)longitude;
@end
