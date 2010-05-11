
#import <MapKit/MapKit.h>

// http://cocoadevcentral.com/d/learn_objectivec/
// http://www.cocoacast.com/?q=node/103

@interface Note : NSObject <MKAnnotation> {
	@public NSString *key;
	@public NSString *kind;
	@public NSString *title;
    @public NSString *subtitle;
	@public NSString *description;
	@public NSString *image;
	@public NSString *secret;
	@public float lat;
	@public float lon;
	@public int favorite;
	@public NSString *owner;
	@public NSString *uuid;
	@public CLLocationCoordinate2D coordinate;
	@public int flags;
}

#define NOTE_DIRTY		1
#define NOTE_UNRENDERED	2
#define NOTE_OBSOLETE	4

@property (nonatomic, retain, readwrite ) NSString *kind;
@property (nonatomic, retain, readwrite ) NSString *title;
@property (nonatomic, retain, readwrite ) NSString *subtitle;
@property (nonatomic, retain, readwrite ) NSString *description;
@property (nonatomic, retain, readwrite ) NSString *image;
@property (nonatomic, assign) CLLocationCoordinate2D coordinate;
-(id)init:(NSString*)k title:(NSString *)t description:(NSString *)d image:(NSString *)i;
-(void) print;
-(void) dealloc;
@end
