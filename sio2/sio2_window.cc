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


SIO2window *sio2WindowInit( void )
{
	unsigned int i = 0;
	
	SIO2window *_SIO2window = ( SIO2window * ) calloc( 1, sizeof( SIO2window ) );

	_SIO2window->loc   = sio2Vec2Init();
	_SIO2window->scl   = sio2Vec2Init();
	_SIO2window->accel = sio2Vec3Init();

	_SIO2window->mat_viewport = ( int * )malloc( 16 );
	
	_SIO2window->touch = ( vec2 ** ) malloc( SIO2_WINDOW_MAX_TOUCH * sizeof( vec2 * ) );
	
	while( i != SIO2_WINDOW_MAX_TOUCH )
	{
		_SIO2window->touch[ i ] = sio2Vec2Init();
		++i;
	}

	_SIO2window->curr_time = sio2->i_time;

	_SIO2window->accel_smooth = 0.9f;

	return _SIO2window;
}


SIO2window *sio2WindowFree( SIO2window *_SIO2window )
{
	unsigned int i = 0;
	
	_SIO2window->loc   = sio2Vec2Free( _SIO2window->loc   );
	_SIO2window->scl   = sio2Vec2Free( _SIO2window->scl   );
	_SIO2window->accel = sio2Vec3Free( _SIO2window->accel );	

	free( _SIO2window->mat_viewport );
	_SIO2window->mat_viewport = NULL;


	while( i != SIO2_WINDOW_MAX_TOUCH )
	{
		_SIO2window->touch[ i ] = sio2Vec2Free( _SIO2window->touch[ i ] );
		++i;
	}

	free( _SIO2window->touch );
	_SIO2window->touch = NULL;
	

	free( _SIO2window );
	
	return NULL;
}


void sio2WindowShutdown( SIO2window			*_SIO2window,
						 SIO2windowshutdown *_SIO2windowshutdown )
{
	_SIO2window->_SIO2windowshutdown = _SIO2windowshutdown;

	atexit( _SIO2windowshutdown );
}


void sio2WindowSwapBuffers( SIO2window *_SIO2window )
{
	_SIO2window->curr_time = sio2GetElapsedTime();	
	
	if( _SIO2window->last_sync )
	{
		if( _SIO2window->sync_time >= 1.0f )
		{
			_SIO2window->sync_time = 0.0f;
			_SIO2window->fps = _SIO2window->fra;
			_SIO2window->fra = 0.0f;
		}
			
		_SIO2window->d_time = SIO2_CLAMP( ( _SIO2window->curr_time - _SIO2window->last_sync ) * 0.001f, 0.0f, 1.0f );
		_SIO2window->sync_time += _SIO2window->d_time;
		
		++_SIO2window->fra;
	}
	
	_SIO2window->last_sync = _SIO2window->curr_time;
}


void sio2WindowGetViewportMatrix( SIO2window *_SIO2window )
{
	glGetIntegerv( GL_VIEWPORT, &_SIO2window->mat_viewport[ 0 ] );
}


void sio2WindowUpdateViewport( SIO2window *_SIO2window,
							   int		   _x,
							   int		   _y,
							   int		   _w,
							   int		   _h )
{
	glViewport( _x, _y, _w, _h );
	
	sio2WindowGetViewportMatrix( _SIO2window );
	
	_SIO2window->loc->x = ( float )_x;
	_SIO2window->loc->y = ( float )_y;
	
	_SIO2window->scl->x = ( float )( _SIO2window->mat_viewport[ 2 ] - _SIO2window->mat_viewport[ 0 ] );
	_SIO2window->scl->y = ( float )( _SIO2window->mat_viewport[ 3 ] - _SIO2window->mat_viewport[ 1 ] );	
}


void sio2WindowDebugTouch( SIO2window *_SIO2window )
{
	static vec4 col = { 0.0f, 0.0f, 1.0f, 1.0f };
	
	unsigned int i = 0;
	
	float tmp[ 2 ];

	glPointSize( 32.0f );
	
	sio2StateSetColor( sio2->_SIO2state, &col );

	while( i != _SIO2window->n_touch )
	{
		tmp[ 0 ] = _SIO2window->touch[ i ]->x;
		tmp[ 1 ] = _SIO2window->touch[ i ]->y;
	
		glVertexPointer( 2,
						 GL_FLOAT,
						 0,
						 &tmp );

		glDrawArrays( GL_POINTS, 0, 1 );	

		++i;
	}

	glPointSize( 1.0f );
}


void sio2WindowEnter2D( SIO2window *_SIO2window, float _cstart, float _cend )
{
	glMatrixMode( GL_PROJECTION );
	glPushMatrix();
	glLoadIdentity();
	
	glOrthof( _SIO2window->loc->x,
			  _SIO2window->scl->x,
			  _SIO2window->loc->y,
			  _SIO2window->scl->y,
			  _cstart, _cend );

	glMatrixMode( GL_MODELVIEW );
	glPushMatrix();
	glLoadIdentity();
	
	sio2StateDisable( sio2->_SIO2state, SIO2_DEPTH_TEST );
	sio2StateDisable( sio2->_SIO2state, SIO2_CULL_FACE  );
}


void sio2WindowLeave2D( void )
{
	glMatrixMode( GL_PROJECTION );
	glPopMatrix();

	glMatrixMode( GL_MODELVIEW );
	glPopMatrix();
	
	sio2StateEnable( sio2->_SIO2state, SIO2_DEPTH_TEST );
	sio2StateEnable( sio2->_SIO2state, SIO2_CULL_FACE );	
}


void sio2WindowEnterLandscape3D( void )
{
	glPushMatrix();
	glRotatef( -90.0f, 0.0f, 0.0f, 1.0f );
}


void sio2WindowLeaveLandscape3D( void )
{
	glPopMatrix();
}


void sio2WindowEnterLandscape2D( SIO2window *_SIO2window )
{
	float tmp = _SIO2window->scl->x;
	
	_SIO2window->scl->x = _SIO2window->scl->y;
	_SIO2window->scl->y = tmp;
	
	glPushMatrix();

	glRotatef(-90.0f, 0.0f, 0.0f, 1.0f );
	glTranslatef( -_SIO2window->scl->x, 0.0f, 0.0f );
}


void sio2WindowLeaveLandscape2D( SIO2window *_SIO2window )
{ 
	float tmp = _SIO2window->scl->x;
	
	_SIO2window->scl->x = _SIO2window->scl->y;
	_SIO2window->scl->y = tmp;
	
	glPopMatrix();	
}


void sio2WindowSetAccelerometerSensitivity( SIO2window *_SIO2window,
											float		_smooth )
{ _SIO2window->accel_smooth = SIO2_CLAMP( _smooth, 0.01f, 0.99f ); }
