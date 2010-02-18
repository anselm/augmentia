
#import <MapKit/MapKit.h>

@interface Note : NSObject <MKAnnotation> {
	int id;
	NSString *kind;
	NSString *title;
    NSString *subtitle;
	NSString *description;
	NSString *image;
	NSString *secret;
	float lat;
	float lon;
	int favorite;
	NSString *owner;
	NSString *uuid;
	CLLocationCoordinate2D coordinate;
}
@property (nonatomic, retain) NSString *title;
@property (nonatomic, retain) NSString *subtitle;
@property (nonatomic, retain) NSString *description;
@property (nonatomic, retain) NSString *image;
@property (nonatomic, assign) CLLocationCoordinate2D coordinate;
-(id)init:(NSString *)t description:(NSString *)d image:(NSString *)i;
@end
