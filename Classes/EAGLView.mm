
#import "CJSONDeserializer.h"

#import <QuartzCore/QuartzCore.h>
#import <OpenGLES/EAGLDrawable.h>
#import "EAGLView.h"
#import "main.h"
#include "augmentia.h"

@interface EAGLView ()
	@property (nonatomic, retain) EAGLContext *context;
	@property (nonatomic, assign) NSTimer *animationTimer;
	- (BOOL) createFramebuffer;
	- (void) destroyFramebuffer;
@end

@implementation EAGLView
@synthesize context;
@synthesize animationTimer;
@synthesize animationInterval;

// this implements a poor mans queue - later it could be more fancy
extern int ar_create_request;
extern float ar_create_lat;
extern float ar_create_lon;
extern char* ar_create_name;
void augmentiaAddObject(int uuid,float lat, float lon, float heading);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// network
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

- (void)handleError:(NSError *)error {
	if (error != nil) {
		UIAlertView *errorAlertView = [[UIAlertView alloc] initWithTitle:@"Error" message:[error localizedDescription] delegate:nil cancelButtonTitle:@"Close" otherButtonTitles:nil];
		[errorAlertView show];
		[errorAlertView release];
	}
}

- (void)connection:(NSURLConnection *)connection didReceiveResponse:(NSURLResponse *)response {
	[receivedData setLength:0];
}

- (void)connection:(NSURLConnection *)connection didReceiveData:(NSData *)data {
	[receivedData appendData:data];	
}

- (void)connection:(NSURLConnection *)connection didFailWithError:(NSError *)error {
	[connection release];
	[receivedData release];
	//NSLog(@"Connection failed! Error - %@ %@", [error localizedDescription], [[error userInfo] objectForKey:NSErrorFailingURLStringKey]);
}

- (void)server_update_async {
	//NSString *url = @"http://www.waze.com/rtserver/web/GeoRSS?os=60&left=-25046885.4248&right=5009377.084&bottom=-5009377.0856&top=20037508.3384&format=JSON&ma=20&mu=10&sc=55468034&types=alerts%2Cusers&pr=Mercator";
	NSString *url = @"http://makerlab.org";
	NSURLRequest *theRequest=[NSURLRequest requestWithURL:[NSURL URLWithString:url] cachePolicy:NSURLRequestUseProtocolCachePolicy timeoutInterval:60.0];
	NSURLConnection *theConnection=[[NSURLConnection alloc] initWithRequest:theRequest delegate:self];
	if (theConnection) {
		receivedData=[[NSMutableData data] retain];
	}
}

- (void)connectionDidFinishLoading:(NSURLConnection *)connection {
	//int length = [receivedData length];
	
	//NSString *data = [[NSString alloc] initWithData:receivedData encoding:NSUTF8StringEncoding];
	//NSLog(@"Almost Succeeded! Received %d bytes of data %@",length,data);
	//NSData *theData = [theSource dataUsingEncoding:NSUTF32BigEndianStringEncoding];
	
	//	NSError *error = NULL;
	//	CJSONDeserializer *jsonDeserializer = [CJSONDeserializer deserializer];
	//	NSDictionary *resultsDictionary = [jsonDeserializer deserializeAsDictionary:receivedData error:&error];
	//	NSLog(@"Error: %@", error);
	
	[connection release];
	[receivedData release];
	//[data release];
	
}

- (NSString *)readFromServer:(NSString *)urlString {
	NSURL *url = [NSURL URLWithString:urlString];
	NSMutableURLRequest *request = [[NSMutableURLRequest alloc] initWithURL:url];
	[request setHTTPMethod:@"GET"];
	NSURLResponse *response = nil;
	NSError *error = nil;
	NSData *result = [NSURLConnection sendSynchronousRequest:request returningResponse:&response error:&error];
	[request release];
	[self handleError:error];
	NSString *resultString = [[NSString alloc] initWithData:result encoding:NSUTF8StringEncoding];
	return [resultString autorelease];
}

- (void) server_update {
	
	NSString *url = [NSString stringWithFormat:@"http://locative.makerlab.org/json?rad=1&lat=37.4418834&lon=-122.1430195" ];
	NSString *str = [self readFromServer:url];
	NSData *blob = [str dataUsingEncoding:NSUTF32BigEndianStringEncoding];
	
	CJSONDeserializer *jsonDeserializer = [CJSONDeserializer deserializer];
	NSError *error = nil;
	NSDictionary *results = [jsonDeserializer deserializeAsDictionary:blob error:&error];
	if(error != nil) [self handleError:error];
	
	NSArray *array = [results objectForKey:@"results"];
	for (NSDictionary *notes in array) {
		NSDictionary *note = [notes objectForKey:@"note"];
		NSString *text = [note objectForKey:@"title"];
		NSNumber *lat = (NSNumber *)[note objectForKey:@"lat"];
		NSNumber *lon = (NSNumber *)[note objectForKey:@"lon"];
		NSNumber *uuid = (NSNumber *)[note objectForKey:@"id"];
		NSLog(@"Success: %@ and %f,%f,%d", text, [lat floatValue], [lon floatValue], [uuid intValue] );

		augmentiaAddObject([uuid intValue],[lat floatValue],[lon floatValue], 0 );

	}
	
}

//
// Making an object in a multiplayer game is a bit different from a single player game.
// The transaction has to be submitted to the server and the server will respond with any fresh state.
// Later on we can implement predictive object creation.
//
// Check if there is a flag set for creating a new object.
// If so then publish the object to the server.
// Also ask the server for all recent objects.
//
//
- (void) server_synchronize {
	if(!ar_create_request) return;
	ar_create_request = 0;
	
	// synchronously post the request
	NSString *url = [NSString stringWithFormat:@"http://locative.makerlab.org/json?rad=1&lat=37.4418834&lon=-122.1430195&title=dinosaur" ];
	[self readFromServer:url];

	// go ahead and do a server update
	[self server_update];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// opengl boilerplate
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// You must implement this [ for some mysterious reason ]
+ (Class)layerClass {
	return [CAEAGLLayer class];
}

//The GL view is stored in the nib file. When it's unarchived it's sent -initWithCoder:
- (id)initWithCoder:(NSCoder*)coder {
	if ((self = [super initWithCoder:coder])) {
		CAEAGLLayer *eaglLayer = (CAEAGLLayer *)self.layer;		
		eaglLayer.opaque = YES;
		eaglLayer.drawableProperties = [NSDictionary dictionaryWithObjectsAndKeys:
		   [NSNumber numberWithBool:NO], kEAGLDrawablePropertyRetainedBacking, kEAGLColorFormatRGBA8, kEAGLDrawablePropertyColorFormat, nil];
		context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES1];		
		if (!context || ![EAGLContext setCurrentContext:context]) {
			[self release];
			return nil;
		}
		animationInterval = 1.0 / 60.0;
	}
	return self;
}

- (void)drawView {
	if( sio2->_SIO2window->_SIO2windowrender ) {
		sio2->_SIO2window->_SIO2windowrender();
		sio2WindowSwapBuffers( sio2->_SIO2window );
	}
	glBindRenderbufferOES(GL_RENDERBUFFER_OES, viewRenderbuffer);
	[context presentRenderbuffer:GL_RENDERBUFFER_OES];
}

- (void)layoutSubviews {
	[EAGLContext setCurrentContext:context];
	[self destroyFramebuffer];
	[self createFramebuffer];
	[self drawView];
}

- (BOOL)createFramebuffer {
	glGenFramebuffersOES(1, &viewFramebuffer);
	glGenRenderbuffersOES(1, &viewRenderbuffer);
	glBindFramebufferOES(GL_FRAMEBUFFER_OES, viewFramebuffer);
	glBindRenderbufferOES(GL_RENDERBUFFER_OES, viewRenderbuffer);
	[context renderbufferStorage:GL_RENDERBUFFER_OES fromDrawable:(CAEAGLLayer*)self.layer];
	glFramebufferRenderbufferOES(GL_FRAMEBUFFER_OES, GL_COLOR_ATTACHMENT0_OES, GL_RENDERBUFFER_OES, viewRenderbuffer);
	glGetRenderbufferParameterivOES(GL_RENDERBUFFER_OES, GL_RENDERBUFFER_WIDTH_OES, &backingWidth);
	glGetRenderbufferParameterivOES(GL_RENDERBUFFER_OES, GL_RENDERBUFFER_HEIGHT_OES, &backingHeight);
	glGenRenderbuffersOES(1, &depthRenderbuffer);
	glBindRenderbufferOES(GL_RENDERBUFFER_OES, depthRenderbuffer);
	// Use a 24bits depth buffer instead of the default 16bits so that shadows don't zfight as much
	glRenderbufferStorageOES(GL_RENDERBUFFER_OES, GL_DEPTH_COMPONENT24_OES, backingWidth, backingHeight);
	glFramebufferRenderbufferOES(GL_FRAMEBUFFER_OES, GL_DEPTH_ATTACHMENT_OES, GL_RENDERBUFFER_OES, depthRenderbuffer);
	if( !sio2 ) {
		sio2Init( &tmp_argc, tmp_argv );
		sio2InitGL();
		sio2->_SIO2window = sio2WindowInit();
		sio2->_SIO2resource = sio2ResourceInit( "default" );
		sio2WindowUpdateViewport( sio2->_SIO2window, 0, 0, backingWidth, backingHeight );
		sio2->_SIO2window->_SIO2windowrender = augmentiaLoading;
		sio2WindowShutdown( sio2->_SIO2window, augmentiaShutdown );
		sio2->_SIO2window->_SIO2windowtap			= augmentiaScreenTap;
		sio2->_SIO2window->_SIO2windowtouchmove		= augmentiaScreenTouchMove;
		sio2->_SIO2window->_SIO2windowaccelerometer = augmentiaScreenAccelerometer;
	}
	return YES;
}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event {
	UITouch *touch;
	CGPoint pos;
	sio2->_SIO2window->n_touch = 0;
	for( touch in touches ) {
		pos = [ touch locationInView:self ];
		sio2->_SIO2window->touch[ sio2->_SIO2window->n_touch ]->x = pos.y;
		sio2->_SIO2window->touch[ sio2->_SIO2window->n_touch ]->y = pos.x;
		++sio2->_SIO2window->n_touch;
	}
	sio2->_SIO2window->n_tap = [ [ touches anyObject ] tapCount ];
	sio2ResourceDispatchEvents( sio2->_SIO2resource, sio2->_SIO2window, SIO2_WINDOW_TAP, SIO2_WINDOW_TAP_DOWN );
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event {
	UITouch *touch;
	CGPoint pos;
	sio2->_SIO2window->n_touch = 0;
	for( touch in touches ) {
		pos = [ touch locationInView:self ];
		sio2->_SIO2window->touch[ sio2->_SIO2window->n_touch ]->x = pos.y;
		sio2->_SIO2window->touch[ sio2->_SIO2window->n_touch ]->y = pos.x;
		++sio2->_SIO2window->n_touch;
	}
	sio2ResourceDispatchEvents( sio2->_SIO2resource, sio2->_SIO2window, SIO2_WINDOW_TOUCH_MOVE, SIO2_WINDOW_TAP_DOWN );
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event {
	UITouch *touch;
	CGPoint pos;
	sio2->_SIO2window->n_touch = 0;
	for( touch in touches ) {
		pos = [ touch locationInView:self ];
		sio2->_SIO2window->touch[ sio2->_SIO2window->n_touch ]->x = pos.y;
		sio2->_SIO2window->touch[ sio2->_SIO2window->n_touch ]->y = pos.x;
		++sio2->_SIO2window->n_touch;
	}
	sio2ResourceDispatchEvents( sio2->_SIO2resource, sio2->_SIO2window, SIO2_WINDOW_TAP, SIO2_WINDOW_TAP_UP );

	// do any updates - can move this elsewhere later
	[self server_synchronize ];
}

- (void)destroyFramebuffer {
	glDeleteFramebuffersOES(1, &viewFramebuffer);
	viewFramebuffer = 0;
	glDeleteRenderbuffersOES(1, &viewRenderbuffer);
	viewRenderbuffer = 0;
	if(depthRenderbuffer) {
		glDeleteRenderbuffersOES(1, &depthRenderbuffer);
		depthRenderbuffer = 0;
	}
}

- (void)startAnimation {
	self.animationTimer = [NSTimer scheduledTimerWithTimeInterval:animationInterval target:self selector:@selector(drawView) userInfo:nil repeats:YES];
}

- (void)stopAnimation {
	self.animationTimer = nil;
}

- (void)setAnimationTimer:(NSTimer *)newTimer {
	[animationTimer invalidate];
	animationTimer = newTimer;
}

- (void)setAnimationInterval:(NSTimeInterval)interval {	
	animationInterval = interval;
	if (animationTimer) {
		[self stopAnimation];
		[self startAnimation];
	}
}

- (void)dealloc {
	[self stopAnimation];
	if ([EAGLContext currentContext] == context) {
		[EAGLContext setCurrentContext:nil];
	}
	[context release];	
	[super dealloc];
}


@end
