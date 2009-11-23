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


SIO2lamp *sio2LampInit( char *_name )
{
	SIO2lamp *_SIO2lamp = ( SIO2lamp * ) calloc( 1, sizeof( SIO2lamp ) );
	
	sio2StringCpy( _SIO2lamp->name, _name );
	
	_SIO2lamp->_SIO2transform = sio2TransformInit();
	
	_SIO2lamp->col = sio2Vec4Init();
	_SIO2lamp->col->w = 1.0f;
	
	_SIO2lamp->vis = 1;
	
	sio2ResourceAdd( sio2->_SIO2resource,
					 SIO2_LAMP,
					 ( void * )_SIO2lamp );	
	
	return _SIO2lamp;
}


SIO2lamp *sio2LampFree( SIO2lamp *_SIO2lamp )
{
	_SIO2lamp->_SIO2transform = sio2TransformFree( _SIO2lamp->_SIO2transform );
	_SIO2lamp->col = sio2Vec4Free( _SIO2lamp->col );

	sio2ResourceDel( sio2->_SIO2resource,
					 SIO2_LAMP,
					 (void *)_SIO2lamp );	

	free( _SIO2lamp );
	
	return NULL;
}


unsigned char sio2LampLoad( char *_root,
							char *_tok,
							char *_val )
{
	unsigned int i = 0;
	
	static const unsigned int n_token = 12;

	static char *token[ n_token ] = { "t" , "fl", "l" , "d"  , "c"  , "n",
									  "ds", "f" , "sb", "at1", "at2", "ip" }; 

	if( !*_tok )
	{
		char name[ SIO2_MAX_CHAR ] = {""};
		sio2StringScanf( _val, "%s", name );
		sio2->_SIO2lamp = sio2LampInit( name );
		
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
			sio2StringScanf( _val, "%c", &sio2->_SIO2lamp->type );
			return 1;
		}

		case 1:
		{
			sio2StringScanf( _val, "%d", &sio2->_SIO2lamp->flags );
			return 1;
		}
		
		case 2:
		{
			sio2StringScanf( _val, "%f%f%f", &sio2->_SIO2lamp->_SIO2transform->loc->x,
											 &sio2->_SIO2lamp->_SIO2transform->loc->y,
											 &sio2->_SIO2lamp->_SIO2transform->loc->z );
			return 1;
		}
		
		case 3:
		{
			sio2StringScanf( _val, "%f%f%f", &sio2->_SIO2lamp->_SIO2transform->dir->x,
											 &sio2->_SIO2lamp->_SIO2transform->dir->y,
											 &sio2->_SIO2lamp->_SIO2transform->dir->z );
			return 1;
		}
		
		case 4:
		{
			sio2StringScanf( _val, "%f%f%f", &sio2->_SIO2lamp->col->x,
											 &sio2->_SIO2lamp->col->y,
											 &sio2->_SIO2lamp->col->z );
			return 1;
		}
		
		case 5:
		{
			sio2StringScanf( _val, "%f", &sio2->_SIO2lamp->nrg );
			return 1;
		}
		
		case 6:
		{
			sio2StringScanf( _val, "%f", &sio2->_SIO2lamp->dst );
			return 1;
		}
		
		case 7:
		{
			sio2StringScanf( _val, "%f", &sio2->_SIO2lamp->fov );
			return 1;
		}
		
		case 8:
		{
			sio2StringScanf( _val, "%f", &sio2->_SIO2lamp->sblend );
			return 1;
		}
		
		case 9:
		{
			sio2StringScanf( _val, "%f", &sio2->_SIO2lamp->att1 );
			return 1;
		}
		
		case 10:
		{
			sio2StringScanf( _val, "%f", &sio2->_SIO2lamp->att2 );
			return 1;
		}
		
		case 11:
		{
			sio2StringScanf( _val, "%s", sio2->_SIO2lamp->iponame );		
			return 1;		
		}		
	}

	return 0;
}


unsigned char sio2LampRender( SIO2lamp	   *_SIO2lamp,
							 unsigned char  _index )
{
	static const float black[ 4 ] = { 0.0f, 0.0f, 0.0f, 1.0f };

	float c[ 4 ],
		  l[ 4 ],
		  d[ 4 ];

	_SIO2lamp->index = GL_LIGHT0 + _index;

	if( _SIO2lamp->_SIO2ipo && _SIO2lamp->_SIO2ipo->state == SIO2_PLAY )
	{
		vec3 v;
		
		memcpy( _SIO2lamp->_SIO2transform->loc,
				_SIO2lamp->_SIO2ipo->_SIO2transform->loc, 12 );
				
		sio2Rotate3D( _SIO2lamp->_SIO2transform->loc,
					  90.0f - _SIO2lamp->_SIO2ipo->_SIO2transform->rot->x,
					  _SIO2lamp->_SIO2ipo->_SIO2transform->rot->z,
					  -1.0f,
				      &v );

		sio2Vec3Diff( &v,
					  ( vec3 *)_SIO2lamp->_SIO2transform->loc,
					  ( vec3 *)_SIO2lamp->_SIO2transform->dir );
	}

	
	if( !_SIO2lamp->vis )
	{ return 0; }


	if( !glIsEnabled( _SIO2lamp->index ) )
	{ glEnable( _SIO2lamp->index ); }
	

	if( sio2->_SIO2lamp != _SIO2lamp )
	{ sio2->_SIO2lamp = _SIO2lamp; }
	else
	{ return 1; }

	memcpy( &d[ 0 ], _SIO2lamp->_SIO2transform->dir, 12 );
	d[ 3 ] = 0.0f;
	
	if( _SIO2lamp->type == SIO2_LAMP_SUN )	
	{ glLightfv( _SIO2lamp->index, GL_POSITION, &d[ 0 ] ); }
	else
	{
		memcpy( &l[ 0 ], _SIO2lamp->_SIO2transform->loc, 12 );
		l[ 3 ] = 1.0f;
		
		glLightfv( _SIO2lamp->index, GL_POSITION, &l[ 0 ] );
		
		if( _SIO2lamp->type == SIO2_LAMP_SPOT )
		{
			glLightfv( _SIO2lamp->index, GL_SPOT_DIRECTION, &d[ 0 ] );
			glLightf ( _SIO2lamp->index, GL_SPOT_CUTOFF, _SIO2lamp->fov * 0.5f );
			glLightf ( _SIO2lamp->index, GL_SPOT_EXPONENT, 128.0f * _SIO2lamp->sblend );
		}
		else
		{ glLightf( _SIO2lamp->index, GL_SPOT_CUTOFF, 180.0f ); }
	}


	glLightf( _SIO2lamp->index, GL_CONSTANT_ATTENUATION, 1.0f );
	glLightf( _SIO2lamp->index, GL_LINEAR_ATTENUATION, _SIO2lamp->att1 / _SIO2lamp->dst );
	glLightf( _SIO2lamp->index, GL_QUADRATIC_ATTENUATION, _SIO2lamp->att2 / ( _SIO2lamp->dst * _SIO2lamp->dst ) );


	c[ 0 ] = _SIO2lamp->col->x * _SIO2lamp->nrg;
	c[ 1 ] = _SIO2lamp->col->y * _SIO2lamp->nrg;
	c[ 2 ] = _SIO2lamp->col->z * _SIO2lamp->nrg;
	c[ 3 ] = 1.0f;
	
	
	if( sio2IsStateEnabled( _SIO2lamp->flags, SIO2_LAMP_NO_DIFFUSE ) )
	{ glLightfv( _SIO2lamp->index, GL_DIFFUSE, &black[ 0 ] ); }
	else
	{ glLightfv( _SIO2lamp->index, GL_DIFFUSE, &c[ 0 ] ); }
	

	if( sio2IsStateEnabled( _SIO2lamp->flags, SIO2_LAMP_NO_SPECULAR ) )
	{ glLightfv( _SIO2lamp->index, GL_SPECULAR, &black[ 0 ] ); }
	else
	{ glLightfv( _SIO2lamp->index, GL_SPECULAR, &c[ 0 ] ); }
	
	return 1;
}


void sio2LampReset( void )
{
	int i = ( SIO2_LAMP_MAX - 1 );

	while( i > -1 )
	{
		if( glIsEnabled( GL_LIGHT0 + i ) )
		{ glDisable( GL_LIGHT0 + i ); }
	
		--i;
	}
	
	sio2->_SIO2lamp = NULL;
}


void sio2LampSetAmbient( vec4 *_col )
{
	glLightModelfv( GL_LIGHT_MODEL_AMBIENT, ( float * )_col );
	glLightModelf ( GL_LIGHT_MODEL_TWO_SIDE, 1.0f );
}


void sio2LampEnableLight( void )
{
	sio2StateEnable( sio2->_SIO2state, SIO2_LIGHTING );
	sio2StateEnable( sio2->_SIO2state, SIO2_COLOR_MATERIAL );
	sio2StateEnable( sio2->_SIO2state, SIO2_NORMALIZE );
}


void sio2LampResetLight( void )
{
	sio2StateDisable( sio2->_SIO2state, SIO2_LIGHTING );
	sio2StateDisable( sio2->_SIO2state, SIO2_COLOR_MATERIAL );
	sio2StateDisable( sio2->_SIO2state, SIO2_NORMALIZE );
}


