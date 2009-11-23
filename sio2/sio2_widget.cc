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

SIO2widget *sio2WidgetInit( char *_name )
{
	SIO2widget *_SIO2widget = ( SIO2widget * ) calloc( 1, sizeof( SIO2widget ) );

	sio2StringCpy( _SIO2widget->name, _name );

	_SIO2widget->_SIO2transform = sio2TransformInit();
	
	_SIO2widget->area = sio2Vec2Init(); 
	_SIO2widget->bl   = sio2Vec2Init();
	_SIO2widget->tr   = sio2Vec2Init();

	sio2ResourceAdd( sio2->_SIO2resource,
					 SIO2_WIDGET,
					 ( void * )_SIO2widget );
					 
	sio2EnableState( &_SIO2widget->flags, SIO2_WIDGET_VISIBLE );

	return _SIO2widget;
}


SIO2widget *sio2WidgetFree( SIO2widget *_SIO2widget )
{
	_SIO2widget->_SIO2transform = sio2TransformFree( _SIO2widget->_SIO2transform );
	
	_SIO2widget->area = sio2Vec2Free( _SIO2widget->area ); 
	_SIO2widget->bl   = sio2Vec2Free( _SIO2widget->bl   );
	_SIO2widget->tr   = sio2Vec2Free( _SIO2widget->tr   );
	
	sio2ResourceDel( sio2->_SIO2resource,
					 SIO2_WIDGET,
					 ( void * )_SIO2widget );

	free( _SIO2widget );

	return NULL;
}


unsigned char sio2WidgetRender( SIO2widget    *_SIO2widget,
								SIO2window    *_SIO2window,
								unsigned char  _usematrix )
{
	if( sio2IsStateEnabled( _SIO2widget->flags, SIO2_WIDGET_VISIBLE ) )
	{
		if( _SIO2widget->_SIO2material )
		{ sio2MaterialRender( _SIO2widget->_SIO2material ); }

		glPushMatrix();
		{
			unsigned char h =  sio2IsStateEnabled( _SIO2widget->flags, SIO2_WIDGET_ALIGNH ),
						  v =  sio2IsStateEnabled( _SIO2widget->flags, SIO2_WIDGET_ALIGNV );
			
			if( h || v )
			{
				vec2 abs;
				
				abs.x = h ? _SIO2window->scl->x * _SIO2widget->_SIO2transform->loc->x : 0.0f;
				abs.y = v ? _SIO2window->scl->y * _SIO2widget->_SIO2transform->loc->y : 0.0f;
				
				glTranslatef( abs.x, abs.y, 0.0f );
			}
			

			switch( _usematrix )
			{
				case SIO2_TRANSFORM_MATRIX_APPLY:
				{ sio2TransformApply( _SIO2widget->_SIO2transform ); break; }

				case SIO2_TRANSFORM_MATRIX_BIND:
				{ sio2TransformRender( _SIO2widget->_SIO2transform ); break; }
			}

			if( sio2IsStateEnabled( _SIO2widget->flags, SIO2_WIDGET_CENTERED ) )
			{ glBindBuffer( GL_ARRAY_BUFFER, sio2->wid[ 1 ] ); }
			else
			{ glBindBuffer( GL_ARRAY_BUFFER, sio2->wid[ 0 ] ); }
									
			glVertexPointer( 2, GL_FLOAT, 0, (void *)NULL );
			
			sio2StateEnable( sio2->_SIO2state, SIO2_TEXTURE_COORD_ARRAY0 );

			glTexCoordPointer( 2, GL_FLOAT, 0, SIO2_BUFFER_OFFSET( 32 ) );
			
			glDrawArrays( GL_TRIANGLE_FAN, 0, 4 );
		}
		glPopMatrix();	
		
		return 1;
	}
	
	return 0;
}


unsigned char sio2WidgetUpdateBoundary( SIO2widget *_SIO2widget,
										SIO2window *_SIO2window )
{
	float h_size_x = _SIO2widget->area->x * 0.5f,
		  h_size_y = _SIO2widget->area->y * 0.5f;

	if( !sio2IsStateEnabled( _SIO2widget->flags, SIO2_WIDGET_VISIBLE ) || 
		!sio2IsStateEnabled( _SIO2widget->flags, SIO2_WIDGET_ENABLED ) )
	{ return 0; }
	
	
	if( sio2IsStateEnabled( _SIO2widget->flags, SIO2_WIDGET_ALIGNH ) )
	{
		_SIO2widget->bl->x = ( _SIO2window->scl->x * _SIO2widget->_SIO2transform->loc->x ) - h_size_x;
		_SIO2widget->tr->x = ( _SIO2window->scl->x * _SIO2widget->_SIO2transform->loc->x ) + h_size_x;
	}
	else
	{ 
		_SIO2widget->bl->x = !sio2IsStateEnabled( _SIO2widget->flags, SIO2_WIDGET_CENTERED ) ? 
							 _SIO2widget->_SIO2transform->loc->x :
							 _SIO2widget->_SIO2transform->loc->x - h_size_x;
		
		_SIO2widget->tr->x = !sio2IsStateEnabled( _SIO2widget->flags, SIO2_WIDGET_CENTERED ) ? 
							 _SIO2widget->_SIO2transform->loc->x + _SIO2widget->area->x :
							 _SIO2widget->_SIO2transform->loc->x + h_size_x;
	}
	
	
	if( sio2IsStateEnabled( _SIO2widget->flags, SIO2_WIDGET_ALIGNV ) )
	{ 
		_SIO2widget->bl->y = ( _SIO2window->scl->y * _SIO2widget->_SIO2transform->loc->y ) - h_size_y;
		_SIO2widget->tr->y = ( _SIO2window->scl->y * _SIO2widget->_SIO2transform->loc->y ) + h_size_y;
	}
	else
	{
		_SIO2widget->bl->y = !sio2IsStateEnabled( _SIO2widget->flags, SIO2_WIDGET_CENTERED ) ?
							 _SIO2widget->_SIO2transform->loc->y :
							 _SIO2widget->_SIO2transform->loc->y - h_size_y;
		
		_SIO2widget->tr->y = !sio2IsStateEnabled( _SIO2widget->flags, SIO2_WIDGET_CENTERED ) ?
							 _SIO2widget->_SIO2transform->loc->y + _SIO2widget->area->y :
							 _SIO2widget->_SIO2transform->loc->y + h_size_y;
	}
	
	return 1;
}


void sio2WidgetDebug( SIO2widget *_SIO2widget )
{
	static vec4 col = { 1.0f, 0.0f, 0.0f, 1.0f };
	
	float tmp[ 10 ] = { _SIO2widget->bl->x, _SIO2widget->bl->y,
					    _SIO2widget->tr->x, _SIO2widget->bl->y,
						_SIO2widget->tr->x, _SIO2widget->tr->y,
						_SIO2widget->bl->x, _SIO2widget->tr->y,
						_SIO2widget->bl->x, _SIO2widget->bl->y };

	sio2StateSetColor( sio2->_SIO2state, &col );
	
	glVertexPointer( 2,
					 GL_FLOAT,
					 0,
					 &tmp );

	glDrawArrays( GL_LINE_STRIP, 0, 5 );	
}


void sio2WidgetReset( void )
{
	glBindBuffer( GL_ARRAY_BUFFER, 0 );
}

