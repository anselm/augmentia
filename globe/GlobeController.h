
#import <UIKit/UIKit.h>
#import <OpenGLES/EAGL.h>
#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>

#ifdef DEBUGON
#define DEBUGLOG if (DEBUGON) NSLog
#else
#define DEBUGLOG
#endif

@interface GlobeView:
	UIView {
		@private
			GLint backingWidth;
			GLint backingHeight;
			EAGLContext *context;
			GLuint viewRenderbuffer, viewFramebuffer;
			GLuint depthRenderbuffer;
			NSTimer *animationTimer;
			NSTimeInterval animationInterval;
	}
	@property NSTimeInterval animationInterval;
	- (void)startAnimation;
	- (void)stopAnimation;
	- (void)drawView;
	- (void)setupView;
@end

@interface GlobeController:
	UIViewController {
		GlobeView *globeview;
	}
	@property (nonatomic, retain) GlobeView *globeview;
@end