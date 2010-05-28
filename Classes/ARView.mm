
#import <QuartzCore/QuartzCore.h>
#import <OpenGLES/EAGLDrawable.h>

#import "main.h"
#import "sio2.h"

#import "ARView.h"
#import "CJSONDeserializer.h"

@interface ARView ()
	@property (nonatomic, retain) EAGLContext *context;
	@property (nonatomic, assign) NSTimer *animationTimer;
	- (BOOL) createFramebuffer;
	- (void) destroyFramebuffer;
@end

@implementation ARView

@synthesize context;
@synthesize animationTimer;
@synthesize animationInterval;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// sensors are in a separate area
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern float first_latitude;
extern float first_longitude;
extern float latitude;
extern float longitude;
extern float first_heading;
extern float heading;
extern BOOL locationChanged;
extern BOOL goodLocation;
extern BOOL goodHeading;
extern float distanceMoved;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// local state
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int screen_orientation = 0;
float scene_ready = FALSE;




////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// camera
//
// camera view in the world is a function of external sensors
// there is also a local independent swivel so you can move the view around with your finger if you don't have a 3gs
// also you can drive the view around with your finger independent of actually physically moving
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float camera_thrust = 0;
float camera_angular = 0;
float camera_rotation = 0;
float camera_orientation = 0;
float camera_first_time = 1;

vec3 world = { 0,0,0 };
vec3 offset = { 0,0,0 };
vec3 target = { 0,0,0 };

// set this to 1 to move all geometry near me so i can see it when in palo alto
#define BE_LOCAL 1

// set this scale up so that i don't get tired playtesting the game ( i only have to walk 1/100th as far)
#define TEST_SCALE_FACTOR 100

//
// Update Camera
//
// camera view in the world is a function of external sensors
// there is also a local independent swivel so you can move the view around with your finger if you don't have a 3gs
// also you can drive the view around with your finger independent of actually physically moving
//
//

extern float xfilter,yfilter,zfilter;

void augmentiaCamera() {
	
	SIO2camera *camera = sio2->_SIO2camera;
	SIO2window *window = sio2->_SIO2window;
	
	// make camera just in time if needed
	if( !camera ) {
		camera = ( SIO2camera * )sio2ResourceGet( sio2->_SIO2resource, SIO2_CAMERA, "camera/Camera" );
		if(!camera) return;
		sio2->_SIO2camera = camera;
		sio2Perspective( camera->fov, window->scl->x / window->scl->y, camera->cstart, camera->cend );
	}
	
	// Unsure if this has to be exactly here TODO examine
	if( screen_orientation ) {
		sio2WindowEnterLandscape3D();
	}
	
	float speed = window->d_time;
	float angle = atan2(xfilter, yfilter) + M_PI / 2.0;
	
	// camera apply local forces to camera and set camera heading; this snaps no ease in
	camera_rotation += camera_angular;
	camera_orientation = (heading - first_heading) + camera_rotation;
	camera->_SIO2transform->dir->x = cosf(camera_orientation*3.1459/180);
	camera->_SIO2transform->dir->y = -sinf(camera_orientation*3.1459/180);
	camera->_SIO2transform->dir->z = yfilter * 3.1459;
	
	// apply any thrust to camera along heading
	if( camera_thrust ) {
		offset.x += camera->_SIO2transform->dir->x * speed * camera_thrust;
		offset.y += camera->_SIO2transform->dir->y * speed * camera_thrust;
		offset.z = 0.0;
	}
	// camera pos dev mode or real mode
	if(BE_LOCAL) {
		target.x = (longitude - first_longitude) * TEST_SCALE_FACTOR + offset.x;
		target.y = (latitude - first_latitude) * TEST_SCALE_FACTOR + offset.y;
	} else {
		// for now i am going to magnify latitude - so it must be divided by n when saving to server - offset ignored.
		target.x = longitude * TEST_SCALE_FACTOR + offset.x;
		target.y = latitude * TEST_SCALE_FACTOR + offset.y;
	}
	// camera ease in in a nice way; except on first refresh of valid data - go to target immediately in that case
	target.z = 0.0;
	if( camera_first_time && goodHeading) {
		world.x = target.x;
		world.y = target.y;
		world.z = target.z;
		camera_first_time = 0;
	} else {
		world.x += ( target.x - world.x ) / 10.0;
		world.y += ( target.y - world.y ) / 10.0;
	}
	
	// camera do sio2 work
	camera->_SIO2transform->loc->x = world.x;
	camera->_SIO2transform->loc->y = world.y;
	camera->_SIO2transform->loc->z = world.z;
	sio2CameraRender( camera );
	sio2CameraUpdateFrustum( camera );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// render world
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const GLfloat box[] = {
	-1.0, -1.0, 0, 
	1.0, -1.0, 0, 
	1.0,  1.0, 0, 
	-1.0,  1.0, 0,
};

// Shadow matrix so that things can cast what appears to be shadows
void shadowmatrix( float *_m, vec4 *_n, vec4 *_lpos ) {
	float dp = ( _n->x * _lpos->x ) +
	( _n->y * _lpos->y ) +
	( _n->z * _lpos->z ) + 
	( _n->w * _lpos->w );
	_m[ 0  ] = dp   - ( _lpos->x * _n->x );
	_m[ 4  ] = 0.0f - ( _lpos->x * _n->y );
	_m[ 8  ] = 0.0f - ( _lpos->x * _n->z );
	_m[ 12 ] = 0.0f - ( _lpos->x * _n->w );
	_m[ 1  ] = 0.0f - ( _lpos->y * _n->x );
	_m[ 5  ] = dp   - ( _lpos->y * _n->y );
	_m[ 9  ] = 0.0f - ( _lpos->y * _n->z );
	_m[ 13 ] = 0.0f - ( _lpos->y * _n->w );
	_m[ 2  ] = 0.0f - ( _lpos->z * _n->x );
	_m[ 6  ] = 0.0f - ( _lpos->z * _n->y );
	_m[ 10 ] = dp   - ( _lpos->z * _n->z );
	_m[ 14 ] = 0.0f - ( _lpos->z * _n->w );	
	_m[ 3  ] = 0.0f - ( _lpos->w * _n->x );
	_m[ 7  ] = 0.0f - ( _lpos->w * _n->y );
	_m[ 11 ] = 0.0f - ( _lpos->w * _n->z );
	_m[ 15 ] = dp   - ( _lpos->w * _n->w );
}

//
// Draw a radar view so that we can see where stuff is in the world
//
void augmentiaRadar( void ) {
	
	// goto 2d mode
	sio2WindowEnter2D( sio2->_SIO2window, 0.0f, 1.0f );
	sio2WindowEnterLandscape2D( sio2->_SIO2window );
	
	// move to center of radar and rotate radar ( hardcoded for now )
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(32,32,0);
	glRotatef(camera_orientation+90,0,0,1);
	
	// draw me
	glDisable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glVertexPointer(3,GL_FLOAT,0,box);
	glColor4f(1.0f,0.0f,0.0f,1.0f);
	glDrawArrays(GL_LINE_LOOP,0,4);	
	//glCircle();
	
	// draw everybody else unless they are too far away
	glDisable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glVertexPointer(3,GL_FLOAT,0,box);
	glColor4f(0.0f,0.0f,0.0f,1.0f);
	for(int i = 0; i < sio2->_SIO2resource->n_object; i++ ) {
		SIO2object *obj = ( SIO2object * )sio2->_SIO2resource->_SIO2object[ i ];
		float x = obj->_SIO2transform->loc->x - world.x;
		float y = obj->_SIO2transform->loc->y - world.y;
		float z = obj->_SIO2transform->loc->z - world.z;
		if( x*x + y*y + z*z < 100*100) {
			glPushMatrix();
			glTranslatef(x,y,z);
			glDrawArrays(GL_LINE_LOOP,0,4);
			glPopMatrix();
		}
	}
	
	glPopMatrix();
	glEnable(GL_TEXTURE_2D);
	
	sio2WindowLeaveLandscape2D( sio2->_SIO2window );
	sio2WindowLeave2D();
}

//
// Shadows - off for now
//
void augmentiaShadows() {
	vec4 shadow = { 0.0f, 0.0f, 0.0f, 1.0f };
	static float m[ 16 ] = { 0.0f };
	if( !m[ 0 ] ) {
		vec4 n, lpos;
		n.x = n.y = n.w = 0.0f;
		n.z = 1.0f;
		lpos.x =  22.0f;
		lpos.y = -11.0f;
		lpos.z =  22.0f;
		lpos.w =  0.0f;
		shadowmatrix( m, &n, &lpos );
	}
	glPushMatrix();
	glMultMatrixf( &m[ 0 ] );
	sio2StateSetColor( sio2->_SIO2state, &shadow );
	glEnable( GL_POLYGON_OFFSET_FILL );
	glPolygonOffset( -10.0f, -10.0f );
	for(int i = 0; i < sio2->_SIO2resource->n_object; i++ ) {
		SIO2object *_SIO2object = ( SIO2object * )sio2->_SIO2resource->_SIO2object[ i ];
		//if( sio2IsStateEnabled( _SIO2object->flags, SIO2_OBJECT_SHADOW ) ) {
		if( _SIO2object->dst < 0.0f ) { _SIO2object->dst = 1.0f; }
		sio2ObjectRender( _SIO2object,sio2->_SIO2window,sio2->_SIO2camera,0, SIO2_TRANSFORM_MATRIX_BIND );
		//}
	}
	sio2ObjectReset();
	glDisable( GL_POLYGON_OFFSET_FILL );
	glPopMatrix();
}

//
// Render everything - including updating the camera transforms
//
void augmentiaRender( void ) {
	
	// skip out early if scene is not loaded yet
	if( !scene_ready ) {
		return;
	}
	
	// Why is this here? TODO
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	
	glClearColor(0,0,0,0) ;
	glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT );
	
	// deal with camera
	augmentiaCamera();
	
	// render objects
	sio2ResourceCull( sio2->_SIO2resource, sio2->_SIO2camera );
	sio2ResourceRender( sio2->_SIO2resource, sio2->_SIO2window, sio2->_SIO2camera, SIO2_RENDER_SOLID_OBJECT | SIO2_RENDER_ALPHA_TESTED_OBJECT );
	sio2MaterialReset();
	
	// Render shadows
	// augmentiaShadows();
	
	// render a radar view
	augmentiaRadar();
	
	if( screen_orientation ) {
		sio2WindowLeaveLandscape3D();
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// load and make objects dynamically
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//
// load the world
//
void augmentiaLoading( void ) {
	
	// load sio2 geometry
	sio2->_SIO2resource = sio2ResourceInit("world");
	sio2ResourceCreateDictionary( sio2->_SIO2resource );
	sio2ResourceOpen( sio2->_SIO2resource,"shadowland.sio2", 1 );
	for(int i = 0; i < sio2->_SIO2resource->gi.number_entry; i++ ) {
		sio2ResourceExtract( sio2->_SIO2resource, NULL );
	}
	sio2ResourceClose( sio2->_SIO2resource );
	sio2ResetState();
	sio2ResourceBindAllImages( sio2->_SIO2resource );
	sio2ResourceBindAllMaterials( sio2->_SIO2resource );
	sio2ResourceBindAllMatrix( sio2->_SIO2resource );
	sio2ResourceGenId( sio2->_SIO2resource );
	
	scene_ready = TRUE;
	
	// Allow renderer to participate now; I stalled till after geometry was loaded... kind of hacky...
	sio2->_SIO2window->_SIO2windowrender = augmentiaRender;
}

//
// Clone an object
//
SIO2object* augmentiaClone(char* original_name, float x, float y, float z, float orient) {
	
	static unsigned int unique_name_id = 0;
	char unique_name[ SIO2_MAX_CHAR ];
	SIO2object *parent = NULL;
	SIO2object *duplicate = NULL;
	
	// find object in resource list by name
	SIO2object *selection = ( SIO2object * )sio2ResourceGetObject( sio2->_SIO2resource,original_name);
	if(!selection) {
		return NULL;
	}
	
	// actually make a copy with a unique name
	parent = selection->_SIO2instance ? ( SIO2object * )selection->_SIO2instance : selection;
	sprintf( unique_name, "%s_%d", parent->name, unique_name_id );
	if( selection->_SIO2objectphysic && selection->_SIO2objectphysic->bounds == SIO2_PHYSIC_CONVEXHULL ) {
		duplicate = sio2ObjectHardCopy( parent, unique_name );
	} else {
		duplicate = sio2ObjectSoftCopy( parent, unique_name );
	}
	
	// copy the transform matrix again (may not be needed) and update its position
	sio2TransformCopy( duplicate->_SIO2transform, selection->_SIO2transform );
	duplicate->_SIO2transform->loc->x = x;
	duplicate->_SIO2transform->loc->y = y;
	duplicate->_SIO2transform->loc->z = z;
	duplicate->_SIO2transform->rot->x = 0;
	duplicate->_SIO2transform->rot->y = 0;
	duplicate->_SIO2transform->rot->z = -orient;
	
	// bind matrix basically builds an opengl model view matrix and store this into the duplicate
	sio2TransformBindMatrix( duplicate->_SIO2transform );
	
	// this does some game physics related stuff - but since i have physics off it is unclear if needed
	// sio2PhysicAddObject( sio2->_SIO2physic, duplicate );
	
	// build an ordinary opengl display list for the object
	if( selection->_SIO2objectphysic && selection->_SIO2objectphysic->bounds == SIO2_PHYSIC_CONVEXHULL ) {
		sio2ObjectGenId( duplicate );
	}
	
	unique_name_id++;
	
	return duplicate;
}

//
// Manage our own pool of objects on top of SIO2 and on top of the app
// These will represent objects in our AR
// This bit of code is a bit hacked
//

typedef struct {
	int uuid;
	float x,y,z;
	float lat;
	float lon;
	float heading;
	SIO2object *object;
} ARObject ;

#define AROBJECTMAX 128

ARObject arobjects[AROBJECTMAX];
int arobjectcursor = 0;
int arobjectsinitialized = 0;

//
// Add an object to our system
// Objects may come from a server and have a unique id
// We recycle oldest to cap our proximity to 100 objects
// TODO may want to sort these by distance (on the server or here) and use that as a basis for deletion priority
//
void augmentiaAddObject(int uuid,float lat, float lon, float heading) {
	
	// Just in time initialization once only
	if(!arobjectsinitialized) {
		for(int i = 0; i < AROBJECTMAX ; i++ ) {
			arobjects[i].uuid = 0;
			arobjects[i].object = NULL;
		}
		arobjectsinitialized = 1;
	}
	
	// Do we already have this uuid?
	for(int i=0;i<AROBJECTMAX;i++) {
		if ( arobjects[i].uuid == uuid ) return;
	}
	
	// recycle an object
	ARObject *ar = arobjects + arobjectcursor;
	arobjectcursor++;
	if(arobjectcursor>=AROBJECTMAX) arobjectcursor = 0;
	
	// populate object
	ar->uuid = uuid;
	ar->lat = lat;
	ar->lon = lon;
	ar->x = ar->lon * TEST_SCALE_FACTOR;
	ar->y = ar->lat * TEST_SCALE_FACTOR;
	ar->z = 0;
	ar->heading = heading;
	
	// make graphics for it... if it has none
	if(ar->object == NULL) {
		ar->object = augmentiaClone("object/Cube",ar->x,ar->y,ar->z,ar->heading);
	}
	
	// move it just in case
	ar->object->_SIO2transform->loc->x = ar->x;
	ar->object->_SIO2transform->loc->y = ar->y;
	ar->object->_SIO2transform->loc->z = ar->z;
	ar->object->_SIO2transform->rot->x = 0;
	ar->object->_SIO2transform->rot->y = 0;
	ar->object->_SIO2transform->rot->z = ar->heading;
	
}

//
// Invoked by local user action.
// In this example we can treat this as a creation event request.
// For networking purposes we push it up to the server and it returns new total state.
//
int ar_create_request = 0;
float ar_create_lat = 0;
float ar_create_lon = 0;
float ar_heading = 0;
char* ar_create_name = NULL;
int ar_test = 1;

void augmentiaCloneAR() {
	
	ar_create_name = "object/Cube";
	ar_create_lon = sio2->_SIO2camera->_SIO2transform->loc->x + cosf(camera_orientation*3.1459/180) * 10;
	ar_create_lat = sio2->_SIO2camera->_SIO2transform->loc->y + -sinf(camera_orientation*3.1459/180) * 10;
	ar_create_lat = ar_create_lat / TEST_SCALE_FACTOR;
	ar_create_lon = ar_create_lon / TEST_SCALE_FACTOR;
	ar_heading = camera_orientation;
	
	if(false) {
		// for real networked use creation requests would go to a server
		ar_create_request = 1;
	} else {
		// for testing purposes we can just make an object locally
		ar_test = ar_test + 1;
		augmentiaAddObject(ar_test,ar_create_lat,ar_create_lon,camera_orientation);
	}
	
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// user events
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vec2 touch;

//
// Single and double tap detect
//
void augmentiaScreenTap( void *_ptr, unsigned char _state ) {
	if( _state == SIO2_WINDOW_TAP_DOWN && sio2->_SIO2window->n_tap == 2 ) {
		augmentiaCloneAR();
	}
	if( _state == SIO2_WINDOW_TAP_DOWN ) {
		if(!screen_orientation) {
			touch.x = sio2->_SIO2window->touch[ 0 ]->x;
			touch.y = sio2->_SIO2window->touch[ 0 ]->y;
		} else {
			touch.y = sio2->_SIO2window->touch[ 0 ]->x;
			touch.x = sio2->_SIO2window->touch[ 0 ]->y;
		}
	} else if( _state == SIO2_WINDOW_TAP_UP ) {
		camera_thrust = 0;
		camera_angular = 0.0f;
	}
}

//
// Rotate the camera heading on finger drag event
//
void augmentiaScreenTouchMove( void *_ptr ) {
	vec2 d;
	if( !sio2->_SIO2camera ) {
		return;
	}
	if( !screen_orientation ) {
		d.x = sio2->_SIO2window->touch[ 0 ]->x - touch.x;
		d.y = sio2->_SIO2window->touch[ 0 ]->y - touch.y;
	} else {
		d.y = sio2->_SIO2window->touch[ 0 ]->x - touch.x;
		d.x = touch.y - sio2->_SIO2window->touch[ 0 ]->y;	
	}
	camera_thrust = - d.x / 5;
	camera_angular = d.y / 50;
}

void augmentiaScreenAccelerometer( void *_ptr ) {
}

void augmentiaShutdown( void ) {
	sio2ResourceUnloadAll( sio2->_SIO2resource );
	sio2->_SIO2window = sio2WindowInit();
	sio2->_SIO2resource = sio2ResourceFree( sio2->_SIO2resource );
	sio2 = sio2Shutdown();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// events - can we push up to controller TODO?
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// sio2 initialization - setups up a bunch of hooks into augmentia*() methods
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

+ (Class)layerClass {
	return [CAEAGLLayer class];
}

- (void)layoutSubviews {
	[EAGLContext setCurrentContext:context];
	[self destroyFramebuffer];
	[self createFramebuffer];
	[self drawView];
}

-(id)initWithFrame:(CGRect)frame {
	if((self = [super initWithFrame:frame])) {
		CAEAGLLayer *eaglLayer = (CAEAGLLayer *)self.layer;
		eaglLayer.opaque = NO;
		//eaglLayer.alpha = 1.0;
		eaglLayer.drawableProperties = [
										NSDictionary dictionaryWithObjectsAndKeys:
										[NSNumber numberWithBool:NO],
										kEAGLDrawablePropertyRetainedBacking,
										kEAGLColorFormatRGBA8,
										kEAGLDrawablePropertyColorFormat,
										nil
										];
		context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES1];
		if (!context || ![EAGLContext setCurrentContext:context] || ![self createFramebuffer] ) {
			NSLog(@"GlobeView: Initialization error" );
			[self release];
			return nil;
		}
		NSLog(@"View: Initialized 3!!" );
		animationInterval = 1.0 / 60.0;
		//[self setupView];		
	}
	return self;
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

- (void)dealloc {
	[self stopAnimation];
	if ([EAGLContext currentContext] == context) {
		[EAGLContext setCurrentContext:nil];
	}
	[context release];	
	[super dealloc];
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

- (void)drawView {
	if( sio2->_SIO2window->_SIO2windowrender ) {
		sio2->_SIO2window->_SIO2windowrender();
		sio2WindowSwapBuffers( sio2->_SIO2window );
	}
	glBindRenderbufferOES(GL_RENDERBUFFER_OES, viewRenderbuffer);
	[context presentRenderbuffer:GL_RENDERBUFFER_OES];
}


/*
 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 // network
 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 
 // this implements a poor mans queue - later it could be more fancy
 extern int ar_create_request;
 extern float ar_create_lat;
 extern float ar_create_lon;
 extern char* ar_create_name;
 void augmentiaAddObject(int uuid,float lat, float lon, float heading);
 
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
 
 */


@end
