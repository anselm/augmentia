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

*/


#ifndef SIO2_OBJECT_H
#define SIO2_OBJECT_H


typedef enum
{
	SIO2_OBJECT_SOLID			= ( 1 << 0 ),
	SIO2_OBJECT_TRANSPARENT		= ( 1 << 1 ),
	SIO2_OBJECT_ALPHA_TESTED	= ( 1 << 2 )

} SIO2_OBJECT_TYPE;


typedef enum
{
	SIO2_OBJECT_ACTOR		 = ( 1 << 0  ),
	SIO2_OBJECT_GHOST		 = ( 1 << 1  ),	
	SIO2_OBJECT_DYNAMIC		 = ( 1 << 2  ),
	SIO2_OBJECT_RIGIDBODY	 = ( 1 << 3  ),
	SIO2_OBJECT_SOFTBODY	 = ( 1 << 4  ),
	SIO2_OBJECT_BILLBOARD	 = ( 1 << 5  ),
	SIO2_OBJECT_HALO		 = ( 1 << 6  ),
	SIO2_OBJECT_TWOSIDE		 = ( 1 << 7  ),
	SIO2_OBJECT_NOSLEEPING	 = ( 1 << 8  ),
	SIO2_OBJECT_SHADOW		 = ( 1 << 9  ),
	SIO2_OBJECT_DYNAMIC_DRAW = ( 1 << 10 ),
	SIO2_OBJECT_INVISIBLE	 = ( 1 << 11 )
	
} SIO2_OBJECT_FLAGS;


typedef enum
{
	SIO2_OBJECT_SIZE = 0,
	SIO2_OBJECT_NORMALS,
	SIO2_OBJECT_VCOLOR,	
	SIO2_OBJECT_TEXUV0,
	SIO2_OBJECT_TEXUV1,
	
	SIO2_OBJECT_NVBO_OFFSET
	
} SIO2_OBJECT_VBO_OFFSET;


typedef void( SIO2objectactionCallback( void * ) );


typedef struct
{
	unsigned char		bounds;
	
	float				mass;
	float				damp;
	float				rotdamp;
	float				margin;
	
	float				linstiff;
	float				shapematch;
	
	unsigned char		citeration;
	unsigned char		piteration;
	
	btTriangleMesh		*_btTriangleMesh;
	
	btConvexHullShape	*_btConvexHullShape;
	
	btRigidBody			*_btRigidBody;

	btSoftBody			*_btSoftBody;

} SIO2objectphysic;


typedef struct
{
	unsigned char				loop;
	
	unsigned char				next_action;
	
	float						t_ratio;
	float						d_time;
	float						interp;
	float						fps;
	
	SIO2action					*_SIO2action;
	SIO2frame					*_SIO2frame1;
	SIO2frame					*_SIO2frame2;

	unsigned int				curr_frame;
	unsigned int				next_frame;

	unsigned char				state;
	
	SIO2objectactionCallback	*_SIO2objectactionCallback;
	
} SIO2objectanimation;


typedef struct
{
	char				name[ SIO2_MAX_CHAR ];

	col4				*col;

	float				rad;
	float				dst;

	unsigned int		vbo;
	unsigned char		*buf;
		
	unsigned int		vbo_offset[ SIO2_OBJECT_NVBO_OFFSET ];
	
	unsigned int		flags;
	unsigned int		type;	

	vec3				*dim;

	char				iponame[ SIO2_MAX_CHAR ];
	SIO2ipo				*_SIO2ipo;

	char				instname[ SIO2_MAX_CHAR ];
	void				*_SIO2instance;
	
	unsigned int		n_vgroup;
	SIO2vertexgroup		**_SIO2vertexgroup;

	unsigned int		n_sound;
	SIO2sound			**_SIO2sound;
	
	SIO2transform		*_SIO2transform;

	SIO2objectphysic	*_SIO2objectphysic;
	
	SIO2objectanimation *_SIO2objectanimation;
	
	void				*userdata;

} SIO2object;


SIO2object *sio2ObjectInit( char * );

SIO2object *sio2ObjectFree( SIO2object * );

unsigned char sio2ObjectLoad( char *, char *, char * );

void sio2ObjectGenId( SIO2object * );

void sio2ObjectBindSound( SIO2object * );

unsigned char sio2ObjectRender( SIO2object *, SIO2window *, SIO2camera *, unsigned char, unsigned char );

void sio2ObjectBindVBO( SIO2object *, unsigned char );

void sio2ObjectReset( void );

void sio2ObjectBillboard( SIO2object *, vec3 * );

unsigned int sio2ObjectGetNumVert( SIO2object * );

SIO2object *sio2ObjectSoftCopy( SIO2object *, char * );

SIO2object *sio2ObjectHardCopy( SIO2object *, char * );

void sio2ObjectEnableObjectCollisionCallback( SIO2object * );

void sio2ObjectDisableObjectCollisionCallback( SIO2object * );

void sio2ObjectUpdateType( SIO2object * );

void sio2ObjectPlay( SIO2object *, unsigned char );

void sio2ObjectPause( SIO2object * );

void sio2ObjectStop( SIO2object * );

unsigned char sio2ObjectSetAction( SIO2object *, SIO2action *, float, float );

unsigned char sio2ObjectNextAction( SIO2object *, SIO2action *, float, float );

void sio2ObjectUpdateTimeRatio( SIO2object * );

void sio2ObjectRenderAction( SIO2object *, SIO2window * );

unsigned char sio2ObjectSetFrame( SIO2object *, unsigned int );

void sio2ObjectInitPhysicAttributes( SIO2object * );

void sio2ObjectCopyPhysicAttributes( SIO2object *, SIO2object * );

void sio2ObjectInitAnimationAttributes( SIO2object * );

#endif
