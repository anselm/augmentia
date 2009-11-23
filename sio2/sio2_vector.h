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

#ifndef SIO2_VECTOR_H
#define SIO2_VECTOR_H


typedef struct
{
	float x;
	float y;

} vec2;


typedef struct
{
	float x;
	float y;
	float z;

} vec3;


typedef struct
{
	float x;
	float y;
	float z;
	float w;

} vec4;


typedef struct
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
 
} col4;


typedef struct
{
	unsigned short x;
	unsigned short y;
	unsigned short z;
	
} ind3;


typedef struct
{
	float	hdl1;
	vec2	knot;
	float	hdl2;
	
} bez3;


vec2 *sio2Vec2Init( void );

vec2 *sio2Vec2Free( vec2 * );

vec3 *sio2Vec3Init( void );

vec3 *sio2Vec3Free( vec3 * );

vec4 *sio2Vec4Init( void );

vec4 *sio2Vec4Free( vec4 * );

col4 *sio2Col4Init( void );

col4 *sio2Col4Free( col4 * );


static inline void sio2Vec2Diff( vec2 *_v1, vec2 *_v2, vec2 *_v3 )
{
	_v3->x = _v1->x - _v2->x;
	_v3->y = _v1->y - _v2->y;
}


static inline void sio2Vec3Add( vec3 *_v1, vec3 *_v2, vec3 *_v3 )
{
	_v3->x = _v1->x + _v2->x;
	_v3->y = _v1->y + _v2->y;
	_v3->z = _v1->z + _v2->z;
}


static inline void sio2Vec3Diff( vec3 *_v1, vec3 *_v2, vec3 *_v3 )
{
	_v3->x = _v1->x - _v2->x;
	_v3->y = _v1->y - _v2->y;
	_v3->z = _v1->z - _v2->z;
}


static inline float sio2Magnitude( vec3 *_v1 )
{
	return sqrtf( ( _v1->x * _v1->x ) +
				  ( _v1->y * _v1->y ) +
				  ( _v1->z * _v1->z ) );
}


static inline float sio2Distance( vec3 *_v1, vec3 *_v2 )
{
	vec3 v3;
	
	sio2Vec3Diff( _v1, _v2, &v3 );

	return sio2Magnitude( &v3 );
}


static inline float sio2Normalize( vec3 *_v1, vec3 *_v2 )
{
	float len = sio2Magnitude( _v1 ),
		  mag;
		  
	if( !len )
	{ return 0.0f; }
	
	mag = 1.0f / len;

	_v2->x = _v1->x * mag;
	_v2->y = _v1->y * mag;
	_v2->z = _v1->z * mag;
	
	return len;
}


static inline float sio2DotProduct( vec3 *_v1, vec3 *_v2 )
{
	return ( _v1->x * _v2->x ) +
		   ( _v1->y * _v2->y ) +
		   ( _v1->z * _v2->z );
}


static inline float sio2DotProductToDeg( vec3 *_v1, vec3 *_v2 )
{
	float dp = sio2DotProduct( _v1, _v2 );

	if( dp > 0.999f )
	{ return 0.0f; }

	return acosf( dp ) * SIO2_RAD_TO_DEG;
}


static inline void sio2CrossProduct( vec3 *_v1, vec3 *_v2, vec3 *_v3 )
{
	_v3->x = ( _v1->y * _v2->z ) - ( _v2->y * _v1->z );
	_v3->y = ( _v1->z * _v2->x ) - ( _v2->z * _v1->x );
	_v3->z = ( _v1->x * _v2->y ) - ( _v2->x * _v1->y );
}

#endif
