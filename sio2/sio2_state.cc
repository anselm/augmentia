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

SIO2state *sio2StateInit( void )
{
	SIO2state *_SIO2state = ( SIO2state * ) calloc( 1, sizeof( SIO2state ) );

	return _SIO2state;
}


SIO2state *sio2StateFree( SIO2state *_SIO2state )
{
	free( _SIO2state );

	return _SIO2state;
}


unsigned char sio2StateEnable( SIO2state    *_SIO2state,
							   unsigned int  _mask )
{
	switch( _mask )
	{
		case SIO2_FOG:
		{
			if( !sio2IsStateEnabled( _SIO2state->flags, _mask ) )
			{
				sio2EnableState( &_SIO2state->flags, _mask );
				glEnable( GL_FOG );
				
				return 1;
			}
		
			return 0;
		}
		
		case SIO2_BLEND:
		{
			if( !sio2IsStateEnabled( _SIO2state->flags, _mask ) )
			{
				sio2EnableState( &_SIO2state->flags, _mask );
				glEnable( GL_BLEND );

				return 1;				
			}
		
			return 0;
		}
		
		case SIO2_ALPHA_TEST:
		{
			if( !sio2IsStateEnabled( _SIO2state->flags, _mask ) )
			{
				sio2EnableState( &_SIO2state->flags, _mask );
				glEnable( GL_ALPHA_TEST );

				return 1;				
			}
		
			return 0;
		}
		
		case SIO2_TEXTURE_2D0:
		{
			sio2StateSetActiveTexture( _SIO2state, GL_TEXTURE0 );
		
			if( !sio2IsStateEnabled( _SIO2state->flags, _mask ) )
			{
				sio2EnableState( &_SIO2state->flags, _mask );

				glEnable( GL_TEXTURE_2D );
				
				return 1;				
			}
					
			return 0;
		}
		
		case SIO2_TEXTURE_2D1:
		{
			sio2StateSetActiveTexture( _SIO2state, GL_TEXTURE1 );
			
			if( !sio2IsStateEnabled( _SIO2state->flags, _mask ) )
			{
				sio2EnableState( &_SIO2state->flags, _mask );

				glEnable( GL_TEXTURE_2D );

				return 1;				
			}
					
			return 0;
		}
		
		case SIO2_COLOR_MATERIAL:
		{
			if( !sio2IsStateEnabled( _SIO2state->flags, _mask ) )
			{
				sio2EnableState( &_SIO2state->flags, _mask );
				
				glEnable( GL_COLOR_MATERIAL );
				
				return 1;				
			}
		
			return 0;
		}
		
		case SIO2_LIGHTING:
		{
			if( !sio2IsStateEnabled( _SIO2state->flags, _mask ) )
			{
				sio2EnableState( &_SIO2state->flags, _mask );
				
				glEnable( GL_LIGHTING );
				
				return 1;				
			}
		
			return 0;
		}

		case SIO2_NORMALIZE:
		{
			if( !sio2IsStateEnabled( _SIO2state->flags, _mask ) )
			{
				sio2EnableState( &_SIO2state->flags, _mask );
				
				glEnable( GL_NORMALIZE );
				
				return 1;				
			}
		
			return 0;
		}
		
		case SIO2_POINT_SPRITE:
		{
			if( !sio2IsStateEnabled( _SIO2state->flags, _mask ) )
			{
				sio2EnableState( &_SIO2state->flags, _mask );
				
				glEnable( GL_POINT_SPRITE_OES );
				
				return 1;			
			}
		
			return 0;
		}
		
		case SIO2_POINT_SIZE_ARRAY:
		{
			if( !sio2IsStateEnabled( _SIO2state->flags, _mask ) )
			{
				sio2EnableState( &_SIO2state->flags, _mask );
				
				glEnableClientState( GL_POINT_SIZE_ARRAY_OES );

				return 1;
			}
		
			return 0;
		}
		
		case SIO2_VERTEX_ARRAY:
		{
			if( !sio2IsStateEnabled( _SIO2state->flags, _mask ) )
			{
				sio2EnableState( &_SIO2state->flags, _mask );
				
				glEnableClientState( GL_VERTEX_ARRAY );

				return 1;
			}
		
			return 0;
		}
		
		case SIO2_COLOR_ARRAY:
		{
			if( !sio2IsStateEnabled( _SIO2state->flags, _mask ) )
			{
				sio2EnableState( &_SIO2state->flags, _mask );
				
				glEnableClientState( GL_COLOR_ARRAY );

				return 1;
			}
		
			return 0;
		}
		
		case SIO2_NORMAL_ARRAY:
		{
			if( !sio2IsStateEnabled( _SIO2state->flags, _mask ) )
			{
				sio2EnableState( &_SIO2state->flags, _mask );
				
				glEnableClientState( GL_NORMAL_ARRAY );

				return 1;
			}
		
			return 0;
		}
		
		case SIO2_TEXTURE_COORD_ARRAY0:
		{
			sio2StateSetClientActiveTexture( _SIO2state, GL_TEXTURE0 );
					
			if( !sio2IsStateEnabled( _SIO2state->flags, _mask ) )
			{
				sio2EnableState( &_SIO2state->flags, _mask );

				glEnableClientState( GL_TEXTURE_COORD_ARRAY );

				return 1;
			}
					
			return 0;
		}
		
		case SIO2_TEXTURE_COORD_ARRAY1:
		{
			sio2StateSetClientActiveTexture( _SIO2state, GL_TEXTURE1 );
			
			if( !sio2IsStateEnabled( _SIO2state->flags, _mask ) )
			{
				sio2EnableState( &_SIO2state->flags, _mask );

				glEnableClientState( GL_TEXTURE_COORD_ARRAY );

				return 1;
			}
		
			return 0;
		}
		
		case SIO2_DEPTH_TEST:
		{
			if( !sio2IsStateEnabled( _SIO2state->flags, _mask ) )
			{
				sio2EnableState( &_SIO2state->flags, _mask );
				
				glEnable( GL_DEPTH_TEST );
				glDepthMask( GL_TRUE );

				return 1;
			}
					
			return 0;
		}
		
		case SIO2_CULL_FACE:
		{
			if( !sio2IsStateEnabled( _SIO2state->flags, _mask ) )
			{
				sio2EnableState( &_SIO2state->flags, _mask );
				
				glEnable( GL_CULL_FACE );

				return 1;
			}
					
			return 0;
		}		
	}
	
	return 0;
}


unsigned char sio2StateDisable( SIO2state	*_SIO2state,
								unsigned int _mask )
{
	switch( _mask )
	{
		case SIO2_FOG:
		{
			if( sio2IsStateEnabled( _SIO2state->flags, _mask ) )
			{
				sio2DisableState( &_SIO2state->flags, _mask );
				glDisable( GL_FOG );
				
				return 1;				
			}
		
			return 0;
		}
		
		case SIO2_BLEND:
		{
			if( sio2IsStateEnabled( _SIO2state->flags, _mask ) )
			{
				sio2DisableState( &_SIO2state->flags, _mask );
				
				glDisable( GL_BLEND );
				
				return 1;				
			}
		
			return 0;
		}
		
		case SIO2_ALPHA_TEST:
		{
			if( sio2IsStateEnabled( _SIO2state->flags, _mask ) )
			{
				sio2DisableState( &_SIO2state->flags, _mask );
				
				glDisable( GL_ALPHA_TEST );
				
				return 1;				
			}
		
			return 0;
		}
		
		case SIO2_TEXTURE_2D0:
		{
			if( sio2IsStateEnabled( _SIO2state->flags, _mask ) )
			{
				sio2DisableState( &_SIO2state->flags, _mask );

				sio2StateSetActiveTexture( _SIO2state, GL_TEXTURE0 );
				
				glDisable( GL_TEXTURE_2D );

				return 1;				
			}
					
			return 0;
		}
		
		case SIO2_TEXTURE_2D1:
		{
			if( sio2IsStateEnabled( _SIO2state->flags, _mask ) )
			{
				sio2DisableState( &_SIO2state->flags, _mask );

				sio2StateSetActiveTexture( _SIO2state, GL_TEXTURE1 );
				
				glDisable( GL_TEXTURE_2D );
				
				return 1;				
			}
					
			return 0;
		}
		
		case SIO2_COLOR_MATERIAL:
		{
			if( sio2IsStateEnabled( _SIO2state->flags, _mask ) )
			{
				sio2DisableState( &_SIO2state->flags, _mask );
				
				glDisable( GL_COLOR_MATERIAL );
				
				return 1;				
			}
		
			return 0;
		}
		
		case SIO2_LIGHTING:
		{
			if( sio2IsStateEnabled( _SIO2state->flags, _mask ) )
			{
				sio2DisableState( &_SIO2state->flags, _mask );
				
				glDisable( GL_LIGHTING );
				
				return 1;				
			}
		
			return 0;
		}
		
		case SIO2_NORMALIZE:
		{
			if( sio2IsStateEnabled( _SIO2state->flags, _mask ) )
			{
				sio2DisableState( &_SIO2state->flags, _mask );
				
				glDisable( GL_NORMALIZE );

				return 1;				
			}
		
			return 0;
		}
		
		case SIO2_POINT_SPRITE:
		{
			if( sio2IsStateEnabled( _SIO2state->flags, _mask ) )
			{
				sio2DisableState( &_SIO2state->flags, _mask );
				
				glDisable( GL_POINT_SPRITE_OES );
				
				return 1;				
			}
		
			return 0;
		}
		
		case SIO2_POINT_SIZE_ARRAY:
		{
			if( sio2IsStateEnabled( _SIO2state->flags, _mask ) )
			{
				sio2DisableState( &_SIO2state->flags, _mask );
				
				glDisableClientState( GL_POINT_SIZE_ARRAY_OES );
				
				return 1;				
			}
		
			return 0;
		}
		
		case SIO2_VERTEX_ARRAY:
		{
			if( sio2IsStateEnabled( _SIO2state->flags, _mask ) )
			{
				sio2DisableState( &_SIO2state->flags, _mask );
				
				glDisableClientState( GL_VERTEX_ARRAY );
				
				return 1;				
			}
		
			return 0;
		}
		
		case SIO2_COLOR_ARRAY:
		{
			if( sio2IsStateEnabled( _SIO2state->flags, _mask ) )
			{
				sio2DisableState( &_SIO2state->flags, _mask );
				
				glDisableClientState( GL_COLOR_ARRAY );
				
				return 1;				
			}
		
			return 0;
		}
		
		case SIO2_NORMAL_ARRAY:
		{
			if( sio2IsStateEnabled( _SIO2state->flags, _mask ) )
			{
				sio2DisableState( &_SIO2state->flags, _mask );
				
				glDisableClientState( GL_NORMAL_ARRAY );
				
				return 1;				
			}
		
			return 0;
		}
		
		case SIO2_TEXTURE_COORD_ARRAY0:
		{
			if( sio2IsStateEnabled( _SIO2state->flags, _mask ) )
			{
				sio2DisableState( &_SIO2state->flags, _mask );

				sio2StateSetClientActiveTexture( _SIO2state, GL_TEXTURE0 );
				
				glDisableClientState( GL_TEXTURE_COORD_ARRAY );
				
				return 1;				
			}
					
			return 0;
		}
		
		case SIO2_TEXTURE_COORD_ARRAY1:
		{
			if( sio2IsStateEnabled( _SIO2state->flags, _mask ) )
			{
				sio2DisableState( &_SIO2state->flags, _mask );

				sio2StateSetClientActiveTexture( _SIO2state, GL_TEXTURE1 );

				glDisableClientState( GL_TEXTURE_COORD_ARRAY );
				
				return 1;
			}
		
			return 0;
		}
		
		case SIO2_DEPTH_TEST:
		{
			if( sio2IsStateEnabled( _SIO2state->flags, _mask ) )
			{
				sio2DisableState( &_SIO2state->flags, _mask );

				glDisable( GL_DEPTH_TEST );
				glDepthMask( GL_FALSE );
				
				return 1;				
			}
					
			return 0;
		}
		
		case SIO2_CULL_FACE:
		{
			if( sio2IsStateEnabled( _SIO2state->flags, _mask ) )
			{
				sio2DisableState( &_SIO2state->flags, _mask );

				glDisable( GL_CULL_FACE );

				return 1;				
			}
					
			return 0;
		}		
	}
	
	return 0;	
}


unsigned char sio2StateSetActiveTexture( SIO2state *_SIO2state,
										 int		_texture )
{
	if( _SIO2state->a_texture != _texture )
	{
		_SIO2state->a_texture = _texture;
		
		glActiveTexture( _texture );
		
		return 1;
	}
		
	return 0;
}


unsigned char sio2StateSetClientActiveTexture( SIO2state *_SIO2state,
											   int		  _texture )
{
	if( _SIO2state->c_texture != _texture )
	{
		_SIO2state->c_texture = _texture;
		
		glClientActiveTexture( _texture );
		
		return 1;
	}

	return 0;
}


void sio2StateSetBlendMode( SIO2state	  *_SIO2state,
							unsigned char  _blend )
{
	if( _SIO2state->blend != _blend )
	{
		_SIO2state->blend = _blend;
		
		switch( _blend )
		{
			case SIO2_MATERIAL_COLOR:
			{
				glBlendEquationOES( GL_FUNC_ADD_OES );
				glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
				
				break;
			}
			
			case SIO2_MATERIAL_MULTIPLY:
			{
				glBlendEquationOES( GL_FUNC_ADD_OES );
				glBlendFunc( GL_DST_COLOR, GL_ZERO );
				
				break;
			}
			
			case SIO2_MATERIAL_ADD:
			{
				glBlendEquationOES( GL_FUNC_ADD_OES );
				glBlendFunc( GL_SRC_ALPHA, GL_ONE );
				
				break;
			}
			
			case SIO2_MATERIAL_SUBTRACT:
			{
				glBlendEquationOES( GL_FUNC_SUBTRACT_OES );
				glBlendFunc( GL_SRC_ALPHA, GL_ONE );
				
				break; 
			}
				
			case SIO2_MATERIAL_DIVIDE:
			{
				glBlendEquationOES( GL_FUNC_ADD_OES );
				glBlendFunc( GL_ONE, GL_ONE );
				
				break; 
			}

			case SIO2_MATERIAL_DIFFERENCE:
			{ 
				glBlendEquationOES( GL_FUNC_SUBTRACT_OES );
				glBlendFunc( GL_ONE, GL_ONE );
				
				break; 
			}
						
			case SIO2_MATERIAL_SCREEN:
			{
				glBlendEquationOES( GL_FUNC_ADD_OES );
				glBlendFunc( GL_SRC_COLOR, GL_DST_COLOR );
				
				break; 
			}
		}
	}
}


void sio2StateSetAlphaFunc( SIO2state *_SIO2state,
							float	   _v )
{
	if( _SIO2state->alpha_value != _v )
	{
		_SIO2state->alpha_value = _v;
		glAlphaFunc( GL_GREATER, _v );
	}
}


void sio2StateSetColor( SIO2state *_SIO2state,
						vec4      *_color )
{
	if( memcmp( &_SIO2state->color, _color, sizeof( vec4 ) ) )
	{
		memcpy( &_SIO2state->color, _color, sizeof( vec4 ) );
	
		glColor4f( _color->x,
				   _color->y,
				   _color->z,
				   _color->w );
	}
}
