
/************************************************************************************************************************/

#import <UIKit/UIKit.h>
#import <OpenGLES/EAGL.h>
#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>

#import <CoreLocation/CoreLocation.h>
#import "Texture2D.h"


/************************************************************************************************************************/

#ifdef DEBUGON
#define DEBUGLOG if (DEBUGON) NSLog
#else
#define DEBUGLOG
#endif

/************************************************************************************************************************/

@protocol GLTriangleViewDelegate;

typedef struct {
	float latitude;
	float longitude;
	float orientation;
	BOOL rotstop; // stop self rotation
	BOOL touchInside; // finger tap inside of the object ?
	BOOL scalestart; // start to scale the obejct ?
	CGPoint pos; // position of the object on the screen
	CGPoint startTouchPosition; // Start Touch Position
	CGPoint currentTouchPosition; // Current Touch Position
	GLfloat pinchDistance; // distance between two fingers pinch
	GLfloat pinchDistanceShown; // distance that have shown on screen
	GLfloat scale; // OpenGL scale factor of the object
	GLfloat rotation; // OpenGL rotation factor of the object
	GLfloat rotspeed; // control rotation speed of the object
	Texture2D *texture;
} ObjectData;

/************************************************************************************************************************/

@interface HUDView:

UIView {
@private
	GLint backingWidth;
	GLint backingHeight;
	EAGLContext *context;
	GLuint viewRenderbuffer, viewFramebuffer;
	GLuint depthRenderbuffer;
	NSTimer *animationTimer;
	NSTimeInterval animationInterval;
	id<GLTriangleViewDelegate> delegate;
	BOOL delegateSetup;
@public
    ObjectData squareData;
    ObjectData ellipseData;
	ObjectData markers[128];
	int marker_count;
    GLfloat ellipseVertices[720];
    CGFloat initialDistance;
	float latitude;
	float longitude;
	float orientation;
}

@property NSTimeInterval animationInterval;
@property (nonatomic) ObjectData squareData;
@property (nonatomic) ObjectData ellipseData;
@property CGFloat initialDistance;

@property(nonatomic, assign) id<GLTriangleViewDelegate> delegate;
	- (void)startAnimation;
	- (void)stopAnimation;
	- (void)drawView;
	- (void)setupView;
@end

@protocol GLTriangleViewDelegate<NSObject>
	@required -(void)drawView:(HUDView*)view;
	@optional -(void)setupView:(HUDView*)view;
@end

/************************************************************************************************************************/

@interface HUDController:
	UIViewController <CLLocationManagerDelegate> {
		HUDView *hudview;
		UITextField *latitudeTextField;
		UITextField *longitudeTextField;
		UITextField *accuracyTextField;
		CLLocationManager *lm;
	}
	@property (retain, nonatomic) HUDView *hudview;
	@property (retain, nonatomic) UITextField *latitudeTextField;
	@property (retain, nonatomic) UITextField *longitudeTextField;
	@property (retain, nonatomic) UITextField *accuracyTextField;
	- (void)save_all;
@end
