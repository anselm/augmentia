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


SIO2ipo *sio2IpoInit( char *_name )
{
	SIO2ipo *_SIO2ipo = ( SIO2ipo * )calloc( 1, sizeof( SIO2ipo ) );
	
	sio2StringCpy( _SIO2ipo->name, _name );

	_SIO2ipo->_SIO2transform = sio2TransformInit();

	sio2ResourceAdd( sio2->_SIO2resource,
					 SIO2_IPO,
					 ( void * )_SIO2ipo );	
	
	return _SIO2ipo;
}


SIO2ipo *sio2IpoFree( SIO2ipo *_SIO2ipo )
{
	if( _SIO2ipo->locx )
	{ _SIO2ipo->locx = sio2IpoCurveFree( _SIO2ipo->locx ); }
	
	if( _SIO2ipo->locy )
	{ _SIO2ipo->locy = sio2IpoCurveFree( _SIO2ipo->locy ); }
	
	if( _SIO2ipo->locz )
	{ _SIO2ipo->locz = sio2IpoCurveFree( _SIO2ipo->locz ); }
	

	if( _SIO2ipo->rotx )
	{ _SIO2ipo->rotx = sio2IpoCurveFree( _SIO2ipo->rotx ); }
	
	if( _SIO2ipo->roty )
	{ _SIO2ipo->roty = sio2IpoCurveFree( _SIO2ipo->roty ); }
	
	if( _SIO2ipo->rotz )
	{ _SIO2ipo->rotz = sio2IpoCurveFree( _SIO2ipo->rotz ); }
	
	
	if( _SIO2ipo->sclx )
	{ _SIO2ipo->sclx = sio2IpoCurveFree( _SIO2ipo->sclx ); }
	
	if( _SIO2ipo->scly )
	{ _SIO2ipo->scly = sio2IpoCurveFree( _SIO2ipo->scly ); }
	
	if( _SIO2ipo->sclz )
	{ _SIO2ipo->sclz = sio2IpoCurveFree( _SIO2ipo->sclz ); }
	
	
	_SIO2ipo->_SIO2transform = sio2TransformFree( _SIO2ipo->_SIO2transform );
	
	sio2ResourceDel( sio2->_SIO2resource,
					 SIO2_IPO,
					 (void *)_SIO2ipo );	
	
	free( _SIO2ipo );

	return NULL;
}


unsigned char sio2IpoLoad( char *_root, char *_tok, char *_val )
{
	unsigned int i = 0;
	
	static const unsigned int n_token = 11;

	static char *token[ n_token ] = { "lx" , "ly" , "lz",
									  "rx" , "ry" , "rz",
									  "sx" , "sy" , "sz",
									  "i"  , "e" }; 


	if( !*_tok )
	{
		char name[ SIO2_MAX_CHAR ] = {""};
		sio2StringScanf( _val, "%s", name );
		sio2->_SIO2ipo = sio2IpoInit( name );
		
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
			if( !sio2->_SIO2ipo->locx )
			{
				sio2->_SIO2ipo->locx = sio2IpoCurveInit();
				sio2->_SIO2ipocurve  = sio2->_SIO2ipo->locx;
			}
			
			++sio2->_SIO2ipo->locx->n_point;
			
			sio2->_SIO2ipo->locx->point = ( bez3 * ) realloc( sio2->_SIO2ipo->locx->point,
															  sio2->_SIO2ipo->locx->n_point * sizeof( bez3 ) );
			
			sio2StringScanf( _val, "%f%f%f%f", &sio2->_SIO2ipo->locx->point[ sio2->_SIO2ipo->locx->n_point - 1 ].hdl1,
											   &sio2->_SIO2ipo->locx->point[ sio2->_SIO2ipo->locx->n_point - 1 ].knot.x,
											   &sio2->_SIO2ipo->locx->point[ sio2->_SIO2ipo->locx->n_point - 1 ].knot.y,
											   &sio2->_SIO2ipo->locx->point[ sio2->_SIO2ipo->locx->n_point - 1 ].hdl2 );
			return 1;
		}
		
		case 1:
		{
			if( !sio2->_SIO2ipo->locy )
			{
				sio2->_SIO2ipo->locy = sio2IpoCurveInit();
				sio2->_SIO2ipocurve  = sio2->_SIO2ipo->locy;			
			}
			
			++sio2->_SIO2ipo->locy->n_point;
			
			sio2->_SIO2ipo->locy->point = ( bez3 * ) realloc( sio2->_SIO2ipo->locy->point,
															  sio2->_SIO2ipo->locy->n_point * sizeof( bez3 ) );
			
			sio2StringScanf( _val, "%f%f%f%f", &sio2->_SIO2ipo->locy->point[ sio2->_SIO2ipo->locy->n_point - 1 ].hdl1,
											   &sio2->_SIO2ipo->locy->point[ sio2->_SIO2ipo->locy->n_point - 1 ].knot.x,
											   &sio2->_SIO2ipo->locy->point[ sio2->_SIO2ipo->locy->n_point - 1 ].knot.y,
											   &sio2->_SIO2ipo->locy->point[ sio2->_SIO2ipo->locy->n_point - 1 ].hdl2 );
			return 1;
		}
		
		case 2:
		{
			if( !sio2->_SIO2ipo->locz )
			{
				sio2->_SIO2ipo->locz = sio2IpoCurveInit();
				sio2->_SIO2ipocurve  = sio2->_SIO2ipo->locz;			
			}
			
			++sio2->_SIO2ipo->locz->n_point;
			
			sio2->_SIO2ipo->locz->point = ( bez3 * ) realloc( sio2->_SIO2ipo->locz->point,
															  sio2->_SIO2ipo->locz->n_point * sizeof( bez3 ) );
			
			sio2StringScanf( _val, "%f%f%f%f", &sio2->_SIO2ipo->locz->point[ sio2->_SIO2ipo->locz->n_point - 1 ].hdl1,
												   &sio2->_SIO2ipo->locz->point[ sio2->_SIO2ipo->locz->n_point - 1 ].knot.x,
												   &sio2->_SIO2ipo->locz->point[ sio2->_SIO2ipo->locz->n_point - 1 ].knot.y,
												   &sio2->_SIO2ipo->locz->point[ sio2->_SIO2ipo->locz->n_point - 1 ].hdl2 );
			return 1;
		}

		case 3:
		{
			if( !sio2->_SIO2ipo->rotx )
			{
				sio2->_SIO2ipo->rotx = sio2IpoCurveInit();
				sio2->_SIO2ipocurve  = sio2->_SIO2ipo->rotx;			
			}
			
			++sio2->_SIO2ipo->rotx->n_point;
			
			sio2->_SIO2ipo->rotx->point = ( bez3 * ) realloc( sio2->_SIO2ipo->rotx->point,
															  sio2->_SIO2ipo->rotx->n_point * sizeof( bez3 ) );
			
			sio2StringScanf( _val, "%f%f%f%f", &sio2->_SIO2ipo->rotx->point[ sio2->_SIO2ipo->rotx->n_point - 1 ].hdl1,
											   &sio2->_SIO2ipo->rotx->point[ sio2->_SIO2ipo->rotx->n_point - 1 ].knot.x,
											   &sio2->_SIO2ipo->rotx->point[ sio2->_SIO2ipo->rotx->n_point - 1 ].knot.y,
											   &sio2->_SIO2ipo->rotx->point[ sio2->_SIO2ipo->rotx->n_point - 1 ].hdl2 );
			return 1;
		}
		
		case 4:
		{
			if( !sio2->_SIO2ipo->roty )
			{
				sio2->_SIO2ipo->roty = sio2IpoCurveInit();
				sio2->_SIO2ipocurve  = sio2->_SIO2ipo->roty;
			}
			
			++sio2->_SIO2ipo->roty->n_point;
			
			sio2->_SIO2ipo->roty->point = ( bez3 * ) realloc( sio2->_SIO2ipo->roty->point,
															  sio2->_SIO2ipo->roty->n_point * sizeof( bez3 ) );
			
			sio2StringScanf( _val, "%f%f%f%f", &sio2->_SIO2ipo->roty->point[ sio2->_SIO2ipo->roty->n_point - 1 ].hdl1,
											   &sio2->_SIO2ipo->roty->point[ sio2->_SIO2ipo->roty->n_point - 1 ].knot.x,
											   &sio2->_SIO2ipo->roty->point[ sio2->_SIO2ipo->roty->n_point - 1 ].knot.y,
											   &sio2->_SIO2ipo->roty->point[ sio2->_SIO2ipo->roty->n_point - 1 ].hdl2 );
			return 1;
		}
		
		case 5:
		{
			if( !sio2->_SIO2ipo->rotz )
			{
				sio2->_SIO2ipo->rotz = sio2IpoCurveInit();
				sio2->_SIO2ipocurve  = sio2->_SIO2ipo->rotz;
			}
			
			++sio2->_SIO2ipo->rotz->n_point;
			
			sio2->_SIO2ipo->rotz->point = ( bez3 * ) realloc( sio2->_SIO2ipo->rotz->point,
															  sio2->_SIO2ipo->rotz->n_point * sizeof( bez3 ) );
			
			sio2StringScanf( _val, "%f%f%f%f", &sio2->_SIO2ipo->rotz->point[ sio2->_SIO2ipo->rotz->n_point - 1 ].hdl1,
											   &sio2->_SIO2ipo->rotz->point[ sio2->_SIO2ipo->rotz->n_point - 1 ].knot.x,
											   &sio2->_SIO2ipo->rotz->point[ sio2->_SIO2ipo->rotz->n_point - 1 ].knot.y,
											   &sio2->_SIO2ipo->rotz->point[ sio2->_SIO2ipo->rotz->n_point - 1 ].hdl2 );
			return 1;
		}
		
		case 6:
		{
			if( !sio2->_SIO2ipo->sclx )
			{
				sio2->_SIO2ipo->sclx = sio2IpoCurveInit();
				sio2->_SIO2ipocurve  = sio2->_SIO2ipo->sclx;			
			}
			
			++sio2->_SIO2ipo->sclx->n_point;
			
			sio2->_SIO2ipo->sclx->point = ( bez3 * ) realloc( sio2->_SIO2ipo->sclx->point,
															  sio2->_SIO2ipo->sclx->n_point * sizeof( bez3 ) );
			
			sio2StringScanf( _val, "%f%f%f%f", &sio2->_SIO2ipo->sclx->point[ sio2->_SIO2ipo->sclx->n_point - 1 ].hdl1,
											   &sio2->_SIO2ipo->sclx->point[ sio2->_SIO2ipo->sclx->n_point - 1 ].knot.x,
											   &sio2->_SIO2ipo->sclx->point[ sio2->_SIO2ipo->sclx->n_point - 1 ].knot.y,
											   &sio2->_SIO2ipo->sclx->point[ sio2->_SIO2ipo->sclx->n_point - 1 ].hdl2 );
			return 1;
		}
		
		case 7:
		{
			if( !sio2->_SIO2ipo->scly )
			{
				sio2->_SIO2ipo->scly = sio2IpoCurveInit();
				sio2->_SIO2ipocurve  = sio2->_SIO2ipo->scly;			
			}
			
			++sio2->_SIO2ipo->scly->n_point;
			
			sio2->_SIO2ipo->scly->point = ( bez3 * ) realloc( sio2->_SIO2ipo->scly->point,
															  sio2->_SIO2ipo->scly->n_point * sizeof( bez3 ) );
			
			sio2StringScanf( _val, "%f%f%f%f", &sio2->_SIO2ipo->scly->point[ sio2->_SIO2ipo->scly->n_point - 1 ].hdl1,
											   &sio2->_SIO2ipo->scly->point[ sio2->_SIO2ipo->scly->n_point - 1 ].knot.x,
											   &sio2->_SIO2ipo->scly->point[ sio2->_SIO2ipo->scly->n_point - 1 ].knot.y,
											   &sio2->_SIO2ipo->scly->point[ sio2->_SIO2ipo->scly->n_point - 1 ].hdl2 );
			return 1;
		}
		
		case 8:
		{
			if( !sio2->_SIO2ipo->sclz )
			{
				sio2->_SIO2ipo->sclz = sio2IpoCurveInit();
				sio2->_SIO2ipocurve  = sio2->_SIO2ipo->sclz;			
			}
			
			++sio2->_SIO2ipo->sclz->n_point;
			
			sio2->_SIO2ipo->sclz->point = ( bez3 * ) realloc( sio2->_SIO2ipo->sclz->point,
															  sio2->_SIO2ipo->sclz->n_point * sizeof( bez3 ) );
			
			sio2StringScanf( _val, "%f%f%f%f", &sio2->_SIO2ipo->sclz->point[ sio2->_SIO2ipo->sclz->n_point - 1 ].hdl1,
											   &sio2->_SIO2ipo->sclz->point[ sio2->_SIO2ipo->sclz->n_point - 1 ].knot.x,
											   &sio2->_SIO2ipo->sclz->point[ sio2->_SIO2ipo->sclz->n_point - 1 ].knot.y,
											   &sio2->_SIO2ipo->sclz->point[ sio2->_SIO2ipo->sclz->n_point - 1 ].hdl2 );
			return 1;
		}
		
		case 9:
		{
			sio2StringScanf( _val, "%c", &sio2->_SIO2ipocurve->interpolation );
			return 1;
		}
		
		case 10:
		{
			sio2StringScanf( _val, "%c", &sio2->_SIO2ipocurve->extrapolation );
			return 1;
		}		
	}
	
	return 0;
}


void sio2IpoRender( SIO2ipo *_SIO2ipo, SIO2window *_SIO2window )
{
	if( _SIO2ipo->state == SIO2_PLAY )
	{
		if( _SIO2ipo->locx )
		{ _SIO2ipo->_SIO2transform->loc->x = sio2IpoCurveRender( _SIO2ipo->locx, _SIO2window ); }

		if( _SIO2ipo->locy )
		{ _SIO2ipo->_SIO2transform->loc->y = sio2IpoCurveRender( _SIO2ipo->locy, _SIO2window ); }
		
		if( _SIO2ipo->locz )
		{ _SIO2ipo->_SIO2transform->loc->z = sio2IpoCurveRender( _SIO2ipo->locz, _SIO2window ); }


		if( _SIO2ipo->rotx )
		{ _SIO2ipo->_SIO2transform->rot->x = sio2IpoCurveRender( _SIO2ipo->rotx, _SIO2window ); }

		if( _SIO2ipo->roty )
		{ _SIO2ipo->_SIO2transform->rot->y = sio2IpoCurveRender( _SIO2ipo->roty, _SIO2window ); }

		if( _SIO2ipo->rotz )
		{ _SIO2ipo->_SIO2transform->rot->z = sio2IpoCurveRender( _SIO2ipo->rotz, _SIO2window ); }


		if( _SIO2ipo->sclx )
		{ _SIO2ipo->_SIO2transform->scl->x = sio2IpoCurveRender( _SIO2ipo->sclx, _SIO2window ); }

		if( _SIO2ipo->scly )
		{ _SIO2ipo->_SIO2transform->scl->y = sio2IpoCurveRender( _SIO2ipo->scly, _SIO2window ); }

		if( _SIO2ipo->sclz )
		{ _SIO2ipo->_SIO2transform->scl->z = sio2IpoCurveRender( _SIO2ipo->sclz, _SIO2window ); }
	}
	
	sio2TransformBindMatrix( _SIO2ipo->_SIO2transform );
}


void sio2IpoPlay( SIO2ipo *_SIO2ipo )
{ _SIO2ipo->state = SIO2_PLAY; }


void sio2IpoPause( SIO2ipo *_SIO2ipo )
{ _SIO2ipo->state = SIO2_PAUSE; }


void sio2IpoStop( SIO2ipo		*_SIO2ipo,
				  SIO2transform *_SIO2transform )
{
	_SIO2ipo->state = SIO2_STOP;

	if( _SIO2transform )
	{ sio2IpoReset( _SIO2ipo, _SIO2transform ); }
}


void sio2IpoReset( SIO2ipo		 *_SIO2ipo,
				   SIO2transform *_SIO2transform )
{
	if( _SIO2ipo->locx )
	{ _SIO2ipo->_SIO2transform->loc->x = sio2IpoCurveReset( _SIO2ipo->locx ); }
	else if( _SIO2transform )
	{ _SIO2ipo->_SIO2transform->loc->x = _SIO2transform->loc->x; }
	
	if( _SIO2ipo->locy )
	{ _SIO2ipo->_SIO2transform->loc->y = sio2IpoCurveReset( _SIO2ipo->locy ); }
	else if( _SIO2transform )
	{ _SIO2ipo->_SIO2transform->loc->y = _SIO2transform->loc->y; }
	
	if( _SIO2ipo->locz )
	{ _SIO2ipo->_SIO2transform->loc->z = sio2IpoCurveReset( _SIO2ipo->locz ); }
	else if( _SIO2transform )
	{ _SIO2ipo->_SIO2transform->loc->z = _SIO2transform->loc->z; }


	if( _SIO2ipo->rotx )
	{ _SIO2ipo->_SIO2transform->rot->x = sio2IpoCurveReset( _SIO2ipo->rotx ); }
	else if( _SIO2transform )
	{ _SIO2ipo->_SIO2transform->rot->x = _SIO2transform->rot->x; }

	if( _SIO2ipo->roty )
	{ _SIO2ipo->_SIO2transform->rot->y = sio2IpoCurveReset( _SIO2ipo->roty ); }
	else if( _SIO2transform )
	{ _SIO2ipo->_SIO2transform->rot->y = _SIO2transform->rot->y; }

	if( _SIO2ipo->rotz )
	{ _SIO2ipo->_SIO2transform->rot->z = sio2IpoCurveReset( _SIO2ipo->rotz ); }
	else if( _SIO2transform )
	{ _SIO2ipo->_SIO2transform->rot->z = _SIO2transform->rot->z; }

	
	if( _SIO2ipo->sclx )
	{ _SIO2ipo->_SIO2transform->scl->x = sio2IpoCurveReset( _SIO2ipo->sclx ); }
	else if( _SIO2transform )
	{ _SIO2ipo->_SIO2transform->scl->x = _SIO2transform->scl->x; }

	if( _SIO2ipo->scly )
	{ _SIO2ipo->_SIO2transform->scl->y = sio2IpoCurveReset( _SIO2ipo->scly ); }
	else if( _SIO2transform )
	{ _SIO2ipo->_SIO2transform->scl->y = _SIO2transform->scl->y; }

	if( _SIO2ipo->sclz )
	{ _SIO2ipo->_SIO2transform->scl->z = sio2IpoCurveReset( _SIO2ipo->sclz ); }
	else if( _SIO2transform )
	{ _SIO2ipo->_SIO2transform->scl->z = _SIO2transform->scl->z; }	
}
