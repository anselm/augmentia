/*

[ EULA: Revision date: 2009/03/22 ]

SIO2 Engine 3D Game for iPhone & iPod Touch :: Free Edition

Copyright (C) 2009 SIO2 Interactive http://sio2interactive.com

This software is provided 'as-is', without any express or implied warranty.

In no event will the authors be held liable for any damages arising from the use
of this software.

Permission is granted to anyone to use this software for any purpose, including
free or commercial applications, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not claim
that you wrote the original software. 

If you are using the "Free Edition" of this software in a product (either free
or commercial), you are required to display a full-screen "Powered by SIO2 engine"
splash screen logo in the start up sequence of any product created and released
with the SIO2 Engine.

This screen shall be visible for no less than two (2) seconds, using one (1) of
the two (2) files provided with the SIO2 SDK:

(a) "/SIO2_SDK/src/poweredby_p.jpg" for portrait

(b) "/SIO2_SDK/src/poweredby_l.jpg" for landscape.

2. Altered source versions must be plainly marked as such (even for internal use),
and must not be misrepresented as being the original software. You are also invited
to post any modifications done to the SIO2 source, at the following email
address: sio2interactive@gmail.com, for review and possible addition to the SIO2
source tree to make them available to the community and to make SIO2 a better
software. But it is not required to do so.

3. This notice may not be removed or altered from any source distribution.

4. If your product using SIO2 Engine "Free Edition" is made available to the
public ( either in a free or commercial form ) you are required to let us know
by email (sio2interactive@gmail.com) the following information:

- The title of your product

- A short description of your product

- A valid URL and screenshot(s) of the product in order for us to put it on our
website (http://sio2interactive.com/GAMES.html) in order to help you promote
your creation(s) as well as promoting the SIO2 project.

If you have any questions or want more information concerning this agreement
please send us an email at: sio2interactive@gmail.com

SIO2 Engine is using other external library and source packages and their
respective license(s), as well as this one, can be found in the 
"/SIO2_SDK/src/LICENSE/" directory, please review all the licenses before
making your product available.




[ EULA: Revision date: 2009/03/23 ]

SIO2 Engine 3D Game for iPhone & iPod Touch :: Indie Edition

Copyright (C) 2009 SIO2 Interactive http://sio2interactive.com

This software is provided 'as-is', without any express or implied warranty.

In no event will the authors be held liable for any damages arising from the use
of this software.

Permission is granted to anyone to use this software for free or commercial applications,
subject to the following restrictions:

1. By using the "SIO2 Indie Edition" you are required to use and include the "sio2.cert"
certificate within your application on a game basis. The certificate will be send to you to
the email that you provide within the purchase form in the next two (2) working days. Certificate
is restricted on a per application basis, you CANNOT reuse the certificate for multiple game
production.

2. By using the "SIO2 Indie Edition" you are entitled of a life time free upgrade to any
subsequent SIO2 versions on a game basis prior to the initial purchase date. Every time
a new version is made available you will receive notification by email within two (2) 
working days after its official release.

3. You must use an independent certificate for every game that you release, either free or
commercial.

4. By using the "SIO2 Indie Edition" you are NOT required to use any splash screen, or
mention of any kind of SIO2 Engine or SIO2 Interactive within your application.

5. By using the "SIO2 Indie Edition" you are entitled to receive customer support and
customer service within working hours (either on IM or by email at sio2interactive@gmail.com).
Every requests will be answered within 48 hours or two (2) working days.

6. You are required to NOT clear the console output and do not override the system log in
order to display at any time on the console prompt the information that your "sio2.cert"
hold, such as your "Game Studio" and "Game Title" as well as your unique certificate key
bundle within your ".app".

7. If your product using SIO2 Engine "Indie Edition" is made available to the public
( either in a free or commercial form ) you are invited to let us know by email
(sio2interactive@gmail.com) the following information:

- The title of your product

- A short description of your product

- A valid URL and screenshot(s) of the product in order for us to put it on our
website (http://sio2interactive.com/GAMES.html) in order to help you promote
your creation(s) as well as promoting the SIO2 project.

But it is NOT required to do so.

If you have any questions or want more information concerning this agreement
please send us an email at: sio2interactive@gmail.com

SIO2 Engine is using other external library and source packages and their
respective license(s), as well as this one, can be found in the 
"/SIO2_SDK/src/LICENSE/" directory, please review all the licenses before
making your product available.


[ v1.3.1 ]

- Improved particle system + tutorial
- Particle system demo
- New tutorial04 with planar Shadow
- More flexible render function
- New Theora Lib integrated
- Better OGV color handling + Optimization
- Better OGG loading time + Optimization
- Improved events system with true multi touch support
- Physic & Culling in another thread (tutorial06_2)
- IPO on object, lamp, camera, particle
- SIO2timer
- Bullet 2.73
- Full Soft Body Physic support
- New built in debugging mechanism for OpenGL / OpenAL / Memory
- Faster Loading / Decompression improvements ( Sounds & Texture )
- General Optimization, bug & memory leaks fixes etc... 
- Fix btTriangleMesh leak problem (ugly fix but work...)


[ v1.3.2 ]

- Unified transformation mechanism (SIO2transform)
- Improved IPO support
- Consistency Improvements
- Improvement of the MapBuffer & UnMapBuffer functionalities
- Performance optimization for material / images
- Upgrade to LUA 5.1.4
- Networking functionalities via SIO2socket
- Tutorial 13_1 & 13_2 introducing Networking & Remote accelerometer debugging.
- Upgrade to the iPhone SDK 2.2
- Anisotropic Filter 1X, 2X
- Support for GL_EXT_texture_lod_bias via the filter property.
- 16 bits texture support ( GL_LUMINANCE_ALPHA )
- Full MD2 Support
- Full PCX Support ( except for 1bits & 4bits )
- Full PNG Support
- Bug Fixes
- sio2ObjectDuplicate improvements and integration in tutorial_06 (tripple click on object to duplicate)


[ v1.3.3 ]

- Exporter update image bug fixed
- PNG loader bug fix (and decompress from SIO2stream)
- New SIO2transform function sio2TransformApply
- SIO2transform parent matrix bug fix
- New powered by logo (please use that one for your apps)
- SIO2object ghost behavior modifications, now used as visible / invisible
- Exporter SIO2object actor flags bug fix
- sio2PhysicRemoveObject bug fix
- SIO2widget is now visible by default at creation time
- Add SIO2transform on SIO2widget
- Billboard optimization
- sio2DotProduct & CrossProduct independent normalization (less sqrtf)
- Improved SIO2widget events & control over multitouch & states
- No more swapping of XY touch / widgets when in landscape.
- Fix Blender camera lens conversion problem. (now same as viewport)
- Hybrid (Bone / Keyframe) animation system built in SIO2object
- Tutorial 15, introducing new animation technique + double buffer sound with a full lenght OGG
- sio2ResourceGetVRAMSize (get the size of the current resource VBO + textures)
- SIO2sound can now be streamed from memory using double buffer
- Remove SIO2memory, Leaks in Instruments work perfectly fine now.
- Fix early depth & color buffer clean up
- Improved tutorial07 introducing new widget functionalities etc...
- Vertex Color optimization (remove the A at export time, but keep the boffset at 4 bytes ~ Blender don't allow you to paint the A anyway...) 
- PCX Support removed, seems to bug in blender and who's using it anyway...
- MD2 loader have been removed from the source tree and is now exclusive to tutorial14
- Tutorial14 improvements, with IPO, skybox, clouds etc...
- New video tutorial15
- Tutorial 16 introducing soft body physic.


[ 1.3.4 ]

- sio2LookAt put back the original from MESA.
- New sio2ObjectSetVertexColorAlpha (demo in tutorial03).
- Add return value on sio2ResourceOpen.
- Add sio2Error for tracking generic C/C++ error.
- Accelerometer smooth factor in SIO2window (default 0.9f)
- Add new frustum test for bounding box sio2CameraCubeIntersectFrustum
- Modification of sio2CameraSphereDistInFrustum now return neg. distance, now all dst test are < 0.0f
- Added default damping and rotation damping factor to SIO2object
- Multi touch system improvement (independent finger events)
- Add widget validate lock tag (for continous press/release event)
- Add matrix type to render object render function & widget
- General optimization
- Add password protection support to .sio2 + SIO2resource modifications
- SIO2sound flexibility improvements.
- All known bugs in 1.3.3 fix
- Major optimization (up to 25%)


[ 1.3.5 ]

- Add userdata to sio2Window
- Modification in sio2LookAt
- sio2ResourceBindAllSounds sio2->_SIO2resource pointer bug fixed when using external SIO2resource
- Fix empty resource * crash when dispatch events
- More convenient way to handle the sio2->_SIO2resource (now automatic)
- Fix bug with object duplicate
- sio2PhysicRender modification to take the substep of the d_time
- sio2LuaInit print loaded LUA modules list.
- Fix sio2ImageSetAlpha (to create mask) offset (now work for every type of stream)


[ 1.3.6 ]

- Exporter now export emptymesh
- Emitter culling bug fix
- SIO2frame support normals
- Add sio2ResetListener function
- Sound stream improvements & bug fix
- sio2ObjectRenderFrame optimization
- File format optimization (shorter tag faster parsing almost 50% faster but less user friendly) -> Please re-export your scenes...
- Lamp flag export bug fix
- sio2ImageBlur
- Added safety net for SIO2thread
- Video stop thread bug fix
- Video mem leak fix
- Video optimization (almost 2x)
- New action system based on Blender action strips.
- SIO2widget & SIO2object SIO2_TRANSFORM_MATRIX_NONE bug fix.
- Bullet 2.75 rc3 (need -fno-regmove compiler flag)
- sio2TransformRotateX & sio2TransformRotateZ takes now degree
- Adjustable clipping planes, default 5 ~ 16% faster
- Integration of nvtristrip (optimize up to 40% faster)
- GL_EXT_texture_lod_bias integration optimization
- Dot3 Lighting & Normalmap Tutorial (basic)
- SIO2image bind check (avoid binding image over and over)
- SIO2image bind & unbind function callbacks (ideal for combiners & texture matrices)
- Add SIO2_OBJECT_INVISIBLE that can be toggled by the face property "invisible"
- SIO2_OBJECT_GHOST act now like the one in blender.
- Exporter now use pure Python to compress zipfile (ideal for cross platform assets creation)
- Machine state software support
- Now export static mesh of any kinds.
- Frustum clipping for small or long objects bug fixed. (http://robertmarkmorley.com/2008/11/16/frustum-culling-in-opengl/)
- sio2CameraPerspective bug fix.
- Port for iPhone OS 3.0 ( -Wno-write-strings )
- Exporter: automatic quads to triangles conversion + remove double at 0.001f of threshold
- OpenGL ES trace
- SIO2video optimization and flexibility improvement
- LUA VM Reset Function
- Material SIO2vertexshader calback (in object space)
- sio2ObjectSoftCopy create an instance at 0,0,0
- sio2ObjectHardCopy create a full copy at 0,0,0
- sio2Frame callback, give the opportunity to callback a function when rendering a frame on an animation.
- Lower SIO2object memory footprint. Now init. struct for physic and animation.
- SIO2frame callback, provide callback functionalities for animation sequence
- SIO2ipo callback, provide callback functionalities for curve sequence
- General optimization, leaks & bug fix (no more known bugs)

*/


#ifndef SIO2_H
#define SIO2_H

//#define SIO2_DEBUG_GL
//#define SIO2_DEBUG_AL
//#define SIO2_DEBUG_LOG

#define	SIO2_MAX_CHAR				64
#define SIO2_MAX_PATH				256

#define SIO2_PI						3.141593f
#define SIO2_DEG_TO_RAD				0.017453f
#define SIO2_RAD_TO_DEG				57.29577f

#define SIO2_CLIP_PLANE				6
#define SIO2_ARCHIVE_TYPE			8
#define SIO2_LAMP_MAX				8

#define SIO2_SOCKET_BUFFER_SIZE		4096

#define SIO2_SOUND_BUFFER			4
#define SIO2_SOUND_BUFFER_SIZE		8092

#define SIO2_VIDEO_BUFFER			2
#define SIO2_VIDEO_BUFFER_BITS		3
#define SIO2_VIDEO_BUFFER_SIZE		8092

#define SIO2_THREAD_TIMEOUT			1

#define SIO2_BUFFER_OFFSET( i )( ( char * )NULL + ( i ) )

#define SIO2_CLAMP( x, low, high ) ( ( x > high ) ? high : ( ( x < low ) ? low : x ) )

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <unistd.h>
#include <sys/sysctl.h>
#include <sys/time.h>

#define BT_NO_PROFILE
#include "../bullet/btBulletDynamicsCommon.h"
#include "../bullet/btSoftRigidDynamicsWorld.h"
#include "../bullet/btSoftBodyRigidBodyCollisionConfiguration.h"
#include "../bullet/btSoftBody.h"


extern "C"
{
	// OpenGL ES
	#include <OpenGLES/EAGL.h>
	#include <OpenGLES/ES1/gl.h>
	#include <OpenGLES/ES1/glext.h>


	// OpenAL
	#include <OpenAL/al.h>
	#include <OpenAL/alc.h>

	/*
		The default LUA type have been replaced for float,
		as well as all arithmetic functions in order to 
		receive a float parameter instead of a double for
		speed at the cost of precision.
	*/
	#include "../lua/lua.h"
	#include "../lua/lualib.h"
	#include "../lua/lauxlib.h"	
	
	// SIO2
	#include "sio2_stream.h"
	#include "sio2_string.h"	
	#include "sio2_script.h"
	#include "sio2_vector.h"
	#include "sio2_utils.h"

	#ifdef SIO2_DEBUG_LOG
	
		#include "sio2_gl.h"
	#endif
	
	#include "sio2_state.h"
	#include "sio2_mist.h"	
	#include "sio2_image.h"
	#include "sio2_video.h"
	#include "sio2_soundbuffer.h"		
	#include "sio2_sound.h"
	#include "sio2_material.h"
	#include "sio2_transform.h"
	#include "sio2_window.h"	
	#include "sio2_widget.h"
	#include "sio2_font.h"
	#include "sio2_ipocurve.h"
	#include "sio2_ipo.h"
	#include "sio2_lamp.h"		
	#include "sio2_vertexgroup.h"
	#include "sio2_timer.h"
	#include "sio2_particle.h"
	#include "sio2_emitter.h"
	#include "sio2_frame.h"
	#include "sio2_action.h"

	#include "sio2_thread.h"
	#include "sio2_socket.h"
}

#include "sio2_camera.h"
#include "sio2_object.h"
#include "sio2_physic.h"
#include "sio2_sensor.h"
#include "sio2_resource.h"


typedef struct
{
	char				app_path[ SIO2_MAX_PATH ];
	char				app_name[ SIO2_MAX_CHAR ];

	unsigned int		i_time;
	
	unsigned int		wid[ 2 ];

	unsigned char		tfilter;
	unsigned char		afilter;
	
	int					cpu_mhz;
	int					bus_mhz;
	
	char				sys[ SIO2_MAX_CHAR ];

	ALCdevice			*device;
	ALCcontext			*context;
	
	ov_callbacks		 _ov_callbacks;

	lua_State			*_lua_State;

	SIO2state			*_SIO2state;

	SIO2window			*_SIO2window;
	SIO2camera			*_SIO2camera;
	SIO2resource		*_SIO2resource;
	SIO2physic			*_SIO2physic;
	SIO2object			*_SIO2object;
	SIO2lamp			*_SIO2lamp;
	SIO2vertexgroup		*_SIO2vertexgroup;
	SIO2material		*_SIO2material;
	SIO2image			*_SIO2image[ SIO2_MATERIAL_NCHANNEL ];
	SIO2font			*_SIO2font;
	SIO2ipo				*_SIO2ipo;
	SIO2ipocurve		*_SIO2ipocurve;
	SIO2action			*_SIO2action;
	
} SIO2;

extern SIO2 *sio2;


extern "C"
{
	#include "sio2_cert.h"
}


void sio2InitGL( void );

void sio2InitAL( void );

void sio2ShutdownAL( void );

void sio2InitLUA( void );

int sio2ExecLUA( char * );

void sio2ShutdownLUA( void );

void sio2ResetLUA( void );

void sio2InitWidget( void );

void sio2ShutdownWidget( void );

void sio2ErrorGL( const char *, const char *, unsigned int );

void sio2ErrorAL( const char *, const char *, unsigned int );

void sio2Error( const char *, const char *, unsigned int, char * );

void sio2ResetState( void );

void sio2ResetListener( void );

bool sio2PhysicCollisionCallback( btManifoldPoint &, const btCollisionObject *, int, int, const btCollisionObject *, int, int );

size_t sio2OggRead( void *, size_t, size_t, void * );

int sio2OggSeek( void *, ogg_int64_t, int );


static inline long sio2OggTell( void *_SIO2stream )
{
	SIO2stream *ptr = ( SIO2stream * )_SIO2stream;

	return ptr->pos;
}


static inline int sio2OggClose( void *_SIO2stream )
{
	if( _SIO2stream )
	{ return 1; }
	else
	{ return 0; }
}


static inline void sio2PngRead( png_structp _png_structp, png_bytep	_png_bytep, png_size_t  _png_size_t )
{
	SIO2stream *_SIO2stream = ( SIO2stream * ) png_get_io_ptr( _png_structp );

	sio2StreamRead( _SIO2stream, _png_bytep, _png_size_t );
}


#endif

