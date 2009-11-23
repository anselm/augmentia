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

#include "sio2.h"


SIO2transform *sio2TransformInit( void )
{
	SIO2transform *_SIO2transform = ( SIO2transform * ) calloc( 1, sizeof( SIO2transform ) );
	
	_SIO2transform->loc = sio2Vec3Init();
	_SIO2transform->rot = sio2Vec3Init();
	_SIO2transform->scl = sio2Vec3Init();
	_SIO2transform->dir = sio2Vec3Init();
	
	_SIO2transform->scl->x =
	_SIO2transform->scl->y = 
	_SIO2transform->scl->z = 1.0f;
	
	_SIO2transform->mat = ( float * ) calloc( 1, 64 );
	
	return _SIO2transform;
}


SIO2transform *sio2TransformFree( SIO2transform *_SIO2transform )
{
	_SIO2transform->loc = sio2Vec3Free( _SIO2transform->loc );
	_SIO2transform->rot = sio2Vec3Free( _SIO2transform->rot );
	_SIO2transform->scl = sio2Vec3Free( _SIO2transform->scl );
	_SIO2transform->dir = sio2Vec3Free( _SIO2transform->dir );

	free( _SIO2transform->mat );
	_SIO2transform->mat = NULL;
	
	free( _SIO2transform );
	
	return NULL;
}


void sio2TransformSetLoc( SIO2transform *_SIO2transform,
						  vec3			*_loc )
{ memcpy( _SIO2transform->loc, _loc, 12 ); }


void sio2TransformSetRot( SIO2transform *_SIO2transform,
						  vec3			*_rot )
{ memcpy( _SIO2transform->rot, _rot, 12 ); }


void sio2TransformSetScl( SIO2transform *_SIO2transform,
						  vec3			*_scl )
{ memcpy( _SIO2transform->scl, _scl, 12 ); }


void sio2TransformSetDir( SIO2transform *_SIO2transform,
						  vec3			*_dir )
{ memcpy( _SIO2transform->dir, _dir, 12 ); }


void sio2TransformSetMatrix( SIO2transform *_SIO2transform,
							 float		   *_mat )
{ memcpy( _SIO2transform->mat, _mat, 64 ); }


void sio2TransformBindMatrix( SIO2transform *_SIO2transform )
{
	glPushMatrix();
	{
		glLoadIdentity();
		
		glTranslatef( _SIO2transform->loc->x,
					  _SIO2transform->loc->y,
					  _SIO2transform->loc->z );
		
		glRotatef( _SIO2transform->rot->z,
				   0.0f,
				   0.0f,
				   1.0f );	
		
		glRotatef( _SIO2transform->rot->y,
				   0.0f,
				   1.0f,
				   0.0f );		
		
		glRotatef( _SIO2transform->rot->x,
				   1.0f,
				   0.0f,
				   0.0f );
		
		glScalef( _SIO2transform->scl->x,
				  _SIO2transform->scl->y,
				  _SIO2transform->scl->z );
		
		glGetFloatv( GL_MODELVIEW_MATRIX, &_SIO2transform->mat[ 0 ] );
	}
	glPopMatrix();
}


void sio2TransformRender( SIO2transform *_SIO2transform )
{
	if( _SIO2transform->_SIO2parent )
	{
		SIO2transform *ptr = ( SIO2transform * )_SIO2transform->_SIO2parent; 
		
		glMultMatrixf( &ptr->mat[ 0 ] );
		
		glMultMatrixf( &_SIO2transform->mat[ 0 ] );
	}
	else
	{ glMultMatrixf( &_SIO2transform->mat[ 0 ] ); }
}


void sio2TransformApply( SIO2transform *_SIO2transform )
{
	glTranslatef( _SIO2transform->loc->x,
				  _SIO2transform->loc->y,
				  _SIO2transform->loc->z );

	glRotatef( _SIO2transform->rot->z,
			   0.0f,
			   0.0f,
			   1.0f );	

	glRotatef( _SIO2transform->rot->y,
			   0.0f,
			   1.0f,
			   0.0f );		

	glRotatef( _SIO2transform->rot->x,
			   1.0f,
			   0.0f,
			   0.0f );

	glScalef( _SIO2transform->scl->x,
			  _SIO2transform->scl->y,
			  _SIO2transform->scl->z );
}


void sio2TransformRotateX( SIO2transform *_SIO2transform,
						   float		  _rotx )
{
	vec3 v;
	
	_rotx *= SIO2_DEG_TO_RAD;
	
	sio2Vec3Add( _SIO2transform->loc,
				 _SIO2transform->dir,
				 &v );
	
	v.z += _rotx;
	
	sio2Vec3Diff( &v,
				  _SIO2transform->loc,
				  _SIO2transform->dir );	
}


void sio2TransformRotateZ( SIO2transform *_SIO2transform,
							float		  _rotz )
{
	vec3 v;
	
	_rotz *= SIO2_DEG_TO_RAD;
	
	v.x = ( _SIO2transform->loc->x + cosf( _rotz ) *
			_SIO2transform->dir->x - sinf( _rotz ) *
			_SIO2transform->dir->y );
							
	v.y = ( _SIO2transform->loc->y + sinf( _rotz ) *
			_SIO2transform->dir->x + cosf( _rotz ) *
			_SIO2transform->dir->y );
	
	v.z = _SIO2transform->loc->z + 
		  _SIO2transform->dir->z;
	
	sio2Vec3Diff( &v,
				  _SIO2transform->loc,
				  _SIO2transform->dir );
}


void sio2TransformCopy( SIO2transform *_SIO2transform1,
						SIO2transform *_SIO2transform2 )
{
	sio2TransformSetLoc( _SIO2transform1, _SIO2transform2->loc );
	sio2TransformSetRot( _SIO2transform1, _SIO2transform2->rot );
	sio2TransformSetScl( _SIO2transform1, _SIO2transform2->scl );
}
