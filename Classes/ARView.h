#import <UIKit/UIKit.h>
#import <OpenGLES/EAGL.h>
#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>

@interface ARView : UIView {
	GLint backingWidth;
	GLint backingHeight;	
	EAGLContext *context;
	GLuint viewRenderbuffer, viewFramebuffer;
	GLuint depthRenderbuffer;	
	NSTimer *animationTimer;
	NSTimeInterval animationInterval;
	NSMutableData *receivedData;
}
@property NSTimeInterval animationInterval;
- (void)startAnimation;
- (void)stopAnimation;
- (void)drawView;
@end
