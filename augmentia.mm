
#include "augmentia.h"
#include "sio2/sio2.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// iphone world state ( orientation, position and the like )
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
// camera
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

void augmentiaCamera() {

	SIO2camera *camera = sio2->_SIO2camera;
	SIO2window *window = sio2->_SIO2window;

	// make camera?
	if( !camera ) {
		camera = ( SIO2camera * )sio2ResourceGet( sio2->_SIO2resource, SIO2_CAMERA, "camera/Camera" );
		if(!camera) return;
		sio2->_SIO2camera = camera;
		sio2Perspective( camera->fov, window->scl->x / window->scl->y, camera->cstart, camera->cend );
	}

	// Unsure if this has to be exactly here 
	if( screen_orientation ) {
		sio2WindowEnterLandscape3D();
	}

	float speed = window->d_time;

	// camera apply local forces to camera and set camera heading; this snaps no ease in
	camera_rotation += camera_angular;
	camera_orientation = (heading - first_heading) + camera_rotation;
	camera->_SIO2transform->dir->x = cosf(camera_orientation*3.1459/180);
	camera->_SIO2transform->dir->y = -sinf(camera_orientation*3.1459/180);
	camera->_SIO2transform->dir->z = 0.0;

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

// http://sio2interactive.wikidot.com/sio2-widgets

SIO2image *NAMEOFYOURIMAGE;
SIO2stream *NAMEOFYOURSTREAM;
SIO2widget *NAMEOFYOURWIDGET;
SIO2material *NAMEOFYOURMATERIAL;

void augmentiaRadarLoad( void ) {
	sio2InitWidget();
	NAMEOFYOURSTREAM = sio2StreamOpen( "NAMEOFIMAGEFILE.tga", 1 );
	if( NAMEOFYOURSTREAM ) {
		NAMEOFYOURIMAGE = sio2ImageInit( "HUD.tga" );
		sio2ImageLoad( NAMEOFYOURIMAGE, NAMEOFYOURSTREAM );
		sio2ImageGenId( NAMEOFYOURIMAGE, NULL, 0.0f );
		NAMEOFYOURSTREAM = sio2StreamClose( NAMEOFYOURSTREAM );
		NAMEOFYOURMATERIAL = sio2MaterialInit( "HUD" );
		NAMEOFYOURMATERIAL->blend = SIO2_MATERIAL_COLOR;
		NAMEOFYOURMATERIAL->_SIO2image[ SIO2_MATERIAL_CHANNEL0 ] = NAMEOFYOURIMAGE;
		NAMEOFYOURWIDGET = sio2WidgetInit( "HUD" );        
		NAMEOFYOURWIDGET->_SIO2material = NAMEOFYOURMATERIAL;       
		NAMEOFYOURWIDGET->_SIO2transform->scl->x = 512.0f;
		NAMEOFYOURWIDGET->_SIO2transform->scl->y = 32.0f;       
		NAMEOFYOURWIDGET->_SIO2transform->loc->x  = -15.0f;
		NAMEOFYOURWIDGET->_SIO2transform->loc->y  = 283.0f;
		sio2EnableState( & NAMEOFYOURWIDGET->flags, SIO2_WIDGET_VISIBLE );
	}
}

GLfloat vertices[722];
int made_circle = 0;
void glCircle( void ) {
	if(!made_circle) {
		made_circle = 1;
		vertices[0] = 0.0;
		vertices[1] = 0.0;
		for (int i = 0; i < 720; i += 2) {
			vertices[i+2] = (cos(3.14159/180*(i/2)) * 1);
			vertices[i+3] = (sin(3.14159/180*(i/2)) * 1);
		}
		vertices[719] = 0.0;
		vertices[720] = 1.0;
	}
	glDisable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glVertexPointer(3,GL_FLOAT,0,vertices);
	glColor4f(1.0f,0.0f,0.0f,1.0f);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 361);
}

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

	// pop state
	glPopMatrix();
	
	//sio2TransformBindMatrix( NAMEOFYOURWIDGET->_SIO2transform );
	//sio2WidgetRender( NAMEOFYOURWIDGET, sio2->_SIO2window, 1 );
	//sio2WidgetReset();
	//sio2MaterialReset();
	
	glEnable(GL_TEXTURE_2D);
	sio2WindowLeaveLandscape2D( sio2->_SIO2window );
	sio2WindowLeave2D();
}

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

void augmentiaRender( void ) {

	// skip out early if scene is not loaded yet
	if( !scene_ready ) {
		return;
	}

	// Why is this here?
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	glClearColor( 1.0f, 1.0f, 1.0f, 1.0f );
	glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT );

	// deal with camera
	augmentiaCamera();

	// render objects
	sio2ResourceCull( sio2->_SIO2resource, sio2->_SIO2camera );
	sio2ResourceRender( sio2->_SIO2resource, sio2->_SIO2window, sio2->_SIO2camera, SIO2_RENDER_SOLID_OBJECT | SIO2_RENDER_ALPHA_TESTED_OBJECT );
	sio2MaterialReset();
	
	// Render shadows
	// augmentiaShadows();
	
	// Render all the alpha objects currently inside the frustum.
	if(false) {
		sio2ResourceRender( sio2->_SIO2resource, sio2->_SIO2window, sio2->_SIO2camera, SIO2_RENDER_TRANSPARENT_OBJECT );
	}

	// render a radar view
	augmentiaRadar();
	
	if( screen_orientation ) {
		sio2WindowLeaveLandscape3D();
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// manage objects geometry
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void augmentiaLoading( void ) {
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
	
	// Hack: Allow renderer to participate now.
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Manage our own pool of objects on top of SIO2
// These will represent objects in our AR
// This bit of code is a bit hacked
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

void augmentiaAddObject(int uuid,float lat, float lon, float heading) {

	// Manage a small fixed array of objects which we will track by ourselves
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
// A hack to propagate a creation request up to .m file and thence onto my server
// The server will respond with all nearby objects including the new one
// Note that the "object/Cube" name is also a hack - couldn't figure how to rename in blender
// Note need to propagate heading
// Note the lon/lat is not a proper mapping to x,y,z
//
int ar_create_request = 0;
float ar_create_lat = 0;
float ar_create_lon = 0;
char* ar_create_name = NULL;

void augmentiaCloneAR() {
	ar_create_name = "object/Cube";
	ar_create_request = 1;
	ar_create_lat = sio2->_SIO2camera->_SIO2transform->loc->x + cosf(camera_orientation*3.1459/180) * 10;
	ar_create_lon = sio2->_SIO2camera->_SIO2transform->loc->y + -sinf(camera_orientation*3.1459/180) * 10;
	ar_create_lat = ar_create_lat / TEST_SCALE_FACTOR;
	ar_create_lon = ar_create_lon / TEST_SCALE_FACTOR;
	//ar->heading = camera_orientation;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// user events
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//
// Track the starting position of user screen touch event and use it to drag the camera heading around.
// Can rotate screen on double tap but this is disabled for now.
// For now clone an object on double tap.
//

vec2 touch;
void augmentiaScreenTap( void *_ptr, unsigned char _state ) {
	if( _state == SIO2_WINDOW_TAP_DOWN && sio2->_SIO2window->n_tap == 2 ) {
		//screen_orientation = !screen_orientation;
		//if( screen_orientation )
		//	[[UIApplication sharedApplication] setStatusBarOrientation: UIInterfaceOrientationLandscapeRight animated: YES];
		//else
		//	[[UIApplication sharedApplication] setStatusBarOrientation: UIInterfaceOrientationPortrait animated: YES];
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
// Rotate the camera heading if large drag event
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
// notes
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*

 http://angel.makerlab.com

TODO REMAINING NOV 18 2009

 - improve publishing of heading and state to server and limit each client to a fixed number of objects

 - make the first time update a bit smoother; occur before presenting the avatar to the view

 - show contrails from the server of waze drivers better;

 - support pan and tilt
 
 - support camera overlay

 - let you name your critters and even publish your own account info so it is more social
 
*/


