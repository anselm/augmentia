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


SIO2material *sio2MaterialInit( const char *_name )
{
	SIO2material *_SIO2material = ( SIO2material * ) calloc( 1, sizeof( SIO2material ) );
	
	sio2StringCpy( _SIO2material->name, _name );
	
	_SIO2material->diffuse  = sio2Vec4Init();
	_SIO2material->specular = sio2Vec4Init();

	_SIO2material->diffuse->x =
	_SIO2material->diffuse->y =
	_SIO2material->diffuse->z =
	_SIO2material->diffuse->w = 1.0f;

	sio2ResourceAdd( sio2->_SIO2resource,
					 SIO2_MATERIAL,
					 ( void * )_SIO2material );

	return _SIO2material;
}



SIO2material *sio2MaterialFree( SIO2material *_SIO2material )
{
	_SIO2material->diffuse  = sio2Vec4Free( _SIO2material->diffuse  );
	_SIO2material->specular = sio2Vec4Free( _SIO2material->specular );


	sio2ResourceDel( sio2->_SIO2resource,
					 SIO2_MATERIAL,
					 (void *)_SIO2material );

	free( _SIO2material );

	return NULL;
}


unsigned char sio2MaterialLoad( char *_root,
							    char *_tok,
							    char *_val )
{
	unsigned int i = 0;
	
	static const unsigned int n_token = 16;

	static const char *token[ n_token ] = { "tfl0", "t0" , "tfi0", "tfl1", "t1",
											"tfi1", "sfl", "sb"  , "d"   , "sp",
											"a"   , "sh" , "fr"  , "re"  , "al",
											"b" }; 

	if( !*_tok )
	{
		char name[ SIO2_MAX_CHAR ] = {""};
		sio2StringScanf( _val, "%s", name );
		sio2->_SIO2material = sio2MaterialInit( name );
		
		return 1;
	}
	

	while( i != n_token )
	{
		if( !sio2StringCmp( _tok, token[ i ] ) )
		{ break; }
		
		++i;
	}


	switch( i )
	{
		case 0:
		{
			sio2StringScanf( _val, "%d", &sio2->_SIO2material->tflags[ SIO2_MATERIAL_CHANNEL0 ] );
			return 1;
		}
		
		case 1:
		{
			sio2StringScanf( _val, "%s", sio2->_SIO2material->tname[ SIO2_MATERIAL_CHANNEL0 ] );
			return 1;
		}

		case 2:
		{
			sio2StringScanf( _val, "%f", &sio2->_SIO2material->tfilter[ SIO2_MATERIAL_CHANNEL0 ] );
			return 1;
		}
		
		case 3:
		{
			sio2StringScanf( _val, "%d", &sio2->_SIO2material->tflags[ SIO2_MATERIAL_CHANNEL1 ] );
			return 1;
		}
		
		case 4:
		{
			sio2StringScanf( _val, "%s", sio2->_SIO2material->tname[ SIO2_MATERIAL_CHANNEL1 ] );
			return 1;
		}
		
		case 5:
		{
			sio2StringScanf( _val, "%f", &sio2->_SIO2material->tfilter[ SIO2_MATERIAL_CHANNEL1 ] );
			return 1;
		}
				
		case 6:
		{
			sio2StringScanf( _val, "%d", &sio2->_SIO2material->sflags );
			return 1;
		}
		
		case 7:
		{
			sio2StringScanf( _val, "%s", sio2->_SIO2material->sbname );
			return 1;
		}
		
		case 8:
		{
			sio2StringScanf( _val, "%f%f%f", &sio2->_SIO2material->diffuse->x,
											 &sio2->_SIO2material->diffuse->y,
											 &sio2->_SIO2material->diffuse->z );
			return 1;
		}
		
		case 9:
		{
			sio2StringScanf( _val, "%f%f%f", &sio2->_SIO2material->specular->x,
											 &sio2->_SIO2material->specular->y,
											 &sio2->_SIO2material->specular->z );
			return 1;
		}
		
		case 10:
		{
			sio2StringScanf( _val, "%f", &sio2->_SIO2material->alpha );
			
			sio2->_SIO2material->diffuse->w  = sio2->_SIO2material->alpha;
			sio2->_SIO2material->specular->w = sio2->_SIO2material->alpha;
			
			return 1;
		}
		
		case 11:
		{
			sio2StringScanf( _val, "%f", &sio2->_SIO2material->shininess );
			return 1;
		}
		
		case 12:
		{
			sio2StringScanf( _val, "%f", &sio2->_SIO2material->friction );
			return 1;
		}
		
		case 13:
		{
			sio2StringScanf( _val, "%f", &sio2->_SIO2material->restitution );
			return 1;
		}
		
		case 14:
		{
			sio2StringScanf( _val, "%f", &sio2->_SIO2material->alvl );
			return 1;
		}
		
		case 15:
		{
			sio2StringScanf( _val, "%c", &sio2->_SIO2material->blend );
			return 1;
		}	
	}

	return 0;
}


void sio2MaterialResetImages( SIO2material *_SIO2material )
{
	int i = ( SIO2_MATERIAL_NCHANNEL - 1 );
	
	while( i != -1 )
	{
		if( _SIO2material->_SIO2image[ i ] &&
			_SIO2material->_SIO2image[ i ]->_SIO2imageunbind )
		{ _SIO2material->_SIO2image[ i ]->_SIO2imageunbind( _SIO2material->_SIO2image[ i ], i ); }
		
		--i;
	}
}


void sio2MaterialRender( SIO2material *_SIO2material )
{
	int i = ( SIO2_MATERIAL_NCHANNEL - 1 );
	
	if( sio2->_SIO2material != _SIO2material )
	{
		if( sio2->_SIO2material )
		{ sio2MaterialResetImages( sio2->_SIO2material ); }
	
		sio2->_SIO2material = _SIO2material;
	}
	else
	{ return; }


	// Alpha Blending
	if( _SIO2material->blend )
	{
		sio2StateEnable( sio2->_SIO2state, SIO2_BLEND );

		sio2StateSetBlendMode( sio2->_SIO2state, _SIO2material->blend );
	}
	else
	{ sio2StateDisable( sio2->_SIO2state, SIO2_BLEND ); }	


	// Alpha test
	if( _SIO2material->alvl )
	{
		sio2StateEnable( sio2->_SIO2state, SIO2_ALPHA_TEST );
		
		sio2StateSetAlphaFunc( sio2->_SIO2state, _SIO2material->alvl );
	}
	else
	{ sio2StateDisable( sio2->_SIO2state, SIO2_ALPHA_TEST ); }
	

	// Texture
	while( i != -1 )
	{
		if( _SIO2material->_SIO2image[ i ] )
		{
			if( !i )
			{ sio2StateEnable( sio2->_SIO2state, SIO2_TEXTURE_2D0 ); }
			else
			{ sio2StateEnable( sio2->_SIO2state, SIO2_TEXTURE_2D1 ); }

		
			if( sio2->_SIO2image[ i ] == _SIO2material->_SIO2image[ i ] )
			{
				--i;
				continue;
			}

			sio2->_SIO2image[ i ] = _SIO2material->_SIO2image[ i ];

			sio2ImageRender( _SIO2material->_SIO2image[ i ] );

			if( _SIO2material->_SIO2image[ i ]->_SIO2imagebind )
			{ _SIO2material->_SIO2image[ i ]->_SIO2imagebind( _SIO2material->_SIO2image[ i ], i ); }
		}
		else
		{
			if( !i )
			{ sio2StateDisable( sio2->_SIO2state, SIO2_TEXTURE_2D0 ); }
			else
			{ sio2StateDisable( sio2->_SIO2state, SIO2_TEXTURE_2D1 ); }
		}
		
		--i;
	}	


	if( sio2IsStateEnabled( sio2->_SIO2state->flags, SIO2_COLOR_MATERIAL ) )
	{
		glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR , ( float * )_SIO2material->specular );		
		glMaterialf ( GL_FRONT_AND_BACK, GL_SHININESS, _SIO2material->shininess );
	}

	
	sio2StateSetColor( sio2->_SIO2state,
					   _SIO2material->diffuse );
}


void sio2MaterialReset( void )
{
	static vec4 blank = { 1.0f, 1.0f, 1.0f, 1.0f };
	
	sio2StateDisable( sio2->_SIO2state, SIO2_BLEND );
	
	sio2StateSetBlendMode( sio2->_SIO2state, SIO2_MATERIAL_MIX );

	sio2StateDisable( sio2->_SIO2state, SIO2_ALPHA_TEST );

	sio2StateDisable( sio2->_SIO2state, SIO2_TEXTURE_2D0 );
	sio2StateDisable( sio2->_SIO2state, SIO2_TEXTURE_COORD_ARRAY0 );

	sio2StateDisable( sio2->_SIO2state, SIO2_TEXTURE_2D1 );	
	sio2StateDisable( sio2->_SIO2state, SIO2_TEXTURE_COORD_ARRAY1 );
		
	sio2StateSetColor( sio2->_SIO2state, &blank );
	
	if( sio2->_SIO2material )
	{ sio2MaterialResetImages( sio2->_SIO2material ); }	

	sio2->_SIO2image[ 0 ] =
	sio2->_SIO2image[ 1 ] = NULL;
	
	sio2->_SIO2material = NULL;
			   
	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif			   
}
