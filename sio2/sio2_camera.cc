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


SIO2camera *sio2CameraInit( char *_name )
{
	SIO2camera *_SIO2camera = ( SIO2camera * ) calloc( 1, sizeof( SIO2camera ) );

	sio2StringCpy( _SIO2camera->name, _name );

	_SIO2camera->_SIO2transform = sio2TransformInit();

	_SIO2camera->fov = 45.0f;
	
	_SIO2camera->cstart = 0.1f;
	_SIO2camera->cend = 100.0f;

	_SIO2camera->mat_modelview  = ( float * ) malloc( 64 );
	_SIO2camera->mat_projection = ( float * ) malloc( 64 );

	sio2ResourceAdd( sio2->_SIO2resource,
					 SIO2_CAMERA,
					 ( void * )_SIO2camera );

	return _SIO2camera;
}


SIO2camera *sio2CameraFree( SIO2camera *_SIO2camera )
{
	_SIO2camera->_SIO2transform = sio2TransformFree( _SIO2camera->_SIO2transform );

	free( _SIO2camera->mat_modelview  );
	free( _SIO2camera->mat_projection );
	
	_SIO2camera->mat_modelview  =
	_SIO2camera->mat_projection = NULL;
	
	sio2ResourceDel( sio2->_SIO2resource,
					 SIO2_CAMERA,
					 (void *)_SIO2camera );	
	
	free( _SIO2camera );
	
	return NULL;
}


unsigned char sio2CameraLoad( char *_root,
							  char *_tok,
							  char *_val )
{
	unsigned int i = 0;
	
	static const unsigned int n_token = 7;

	static char *token[ n_token ] = { "l", "r", "d", "f", "cs", "ce", "ip" };


	if( !*_tok )
	{
		char name[ SIO2_MAX_CHAR ] = {""};
		sio2StringScanf( _val, "%s", name );
		sio2->_SIO2camera = sio2CameraInit( name );
		
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
			sio2StringScanf( _val, "%f%f%f", &sio2->_SIO2camera->_SIO2transform->loc->x,
											 &sio2->_SIO2camera->_SIO2transform->loc->y,
											 &sio2->_SIO2camera->_SIO2transform->loc->z );
			return 1;
		}
		
		case 1:
		{
			sio2StringScanf( _val, "%f%f%f", &sio2->_SIO2camera->_SIO2transform->rot->x,
											 &sio2->_SIO2camera->_SIO2transform->rot->y,
											 &sio2->_SIO2camera->_SIO2transform->rot->z );		
			return 1;	
		}
		
		case 2:
		{
			sio2StringScanf( _val, "%f%f%f", &sio2->_SIO2camera->_SIO2transform->dir->x,
											 &sio2->_SIO2camera->_SIO2transform->dir->y,
											 &sio2->_SIO2camera->_SIO2transform->dir->z );		
			return 1;	
		}

		case 3:
		{
			sio2StringScanf( _val, "%f", &sio2->_SIO2camera->fov );
			return 1;		
		}
		
		case 4:
		{
			sio2StringScanf( _val, "%f", &sio2->_SIO2camera->cstart );
			return 1;		
		}

		case 5:
		{
			sio2StringScanf( _val, "%f", &sio2->_SIO2camera->cend );
			return 1;		
		}

		case 6:
		{
			sio2StringScanf( _val, "%s", sio2->_SIO2camera->iponame );		
			return 1;		
		}
	}
	
	return 0;
}


void sio2CameraUpdateFrustum( SIO2camera *_SIO2camera )
{
	float c[ 16 ],
		  t;
	
	c[ 0 ] = _SIO2camera->mat_modelview[ 0 ] * _SIO2camera->mat_projection[ 0  ] +
			 _SIO2camera->mat_modelview[ 1 ] * _SIO2camera->mat_projection[ 4  ] + 
			 _SIO2camera->mat_modelview[ 2 ] * _SIO2camera->mat_projection[ 8  ] + 
			 _SIO2camera->mat_modelview[ 3 ] * _SIO2camera->mat_projection[ 12 ];

	c[ 1 ] = _SIO2camera->mat_modelview[ 0 ] * _SIO2camera->mat_projection[ 1  ] +
			 _SIO2camera->mat_modelview[ 1 ] * _SIO2camera->mat_projection[ 5  ] +
			 _SIO2camera->mat_modelview[ 2 ] * _SIO2camera->mat_projection[ 9  ] +
			 _SIO2camera->mat_modelview[ 3 ] * _SIO2camera->mat_projection[ 13 ];
	
	c[ 2 ] = _SIO2camera->mat_modelview[ 0 ] * _SIO2camera->mat_projection[ 2  ] +
			 _SIO2camera->mat_modelview[ 1 ] * _SIO2camera->mat_projection[ 6  ] +
			 _SIO2camera->mat_modelview[ 2 ] * _SIO2camera->mat_projection[ 10 ] +
			 _SIO2camera->mat_modelview[ 3 ] * _SIO2camera->mat_projection[ 14 ];

	c[ 3 ] = _SIO2camera->mat_modelview[ 0 ] * _SIO2camera->mat_projection[ 3  ] +
			 _SIO2camera->mat_modelview[ 1 ] * _SIO2camera->mat_projection[ 7  ] + 
			 _SIO2camera->mat_modelview[ 2 ] * _SIO2camera->mat_projection[ 11 ] + 
			 _SIO2camera->mat_modelview[ 3 ] * _SIO2camera->mat_projection[ 15 ];

	c[ 4 ] = _SIO2camera->mat_modelview[ 4 ] * _SIO2camera->mat_projection[ 0  ] + 
			 _SIO2camera->mat_modelview[ 5 ] * _SIO2camera->mat_projection[ 4  ] + 
			 _SIO2camera->mat_modelview[ 6 ] * _SIO2camera->mat_projection[ 8  ] +
			 _SIO2camera->mat_modelview[ 7 ] * _SIO2camera->mat_projection[ 12 ];
			
	c[ 5 ] = _SIO2camera->mat_modelview[ 4 ] * _SIO2camera->mat_projection[ 1  ] + 
			 _SIO2camera->mat_modelview[ 5 ] * _SIO2camera->mat_projection[ 5  ] +
			 _SIO2camera->mat_modelview[ 6 ] * _SIO2camera->mat_projection[ 9  ] +
			 _SIO2camera->mat_modelview[ 7 ] * _SIO2camera->mat_projection[ 13 ];
			
	c[ 6 ] = _SIO2camera->mat_modelview[ 4 ] * _SIO2camera->mat_projection[ 2  ] +
			 _SIO2camera->mat_modelview[ 5 ] * _SIO2camera->mat_projection[ 6  ] +
			 _SIO2camera->mat_modelview[ 6 ] * _SIO2camera->mat_projection[ 10 ] +
			 _SIO2camera->mat_modelview[ 7 ] * _SIO2camera->mat_projection[ 14 ];
			
	c[ 7 ] = _SIO2camera->mat_modelview[ 4 ] * _SIO2camera->mat_projection[ 3  ] +
			 _SIO2camera->mat_modelview[ 5 ] * _SIO2camera->mat_projection[ 7  ] +
			 _SIO2camera->mat_modelview[ 6 ] * _SIO2camera->mat_projection[ 11 ] +
			 _SIO2camera->mat_modelview[ 7 ] * _SIO2camera->mat_projection[ 15 ];
 
	c[ 8 ] = _SIO2camera->mat_modelview[ 8  ] * _SIO2camera->mat_projection[ 0  ] +
			 _SIO2camera->mat_modelview[ 9  ] * _SIO2camera->mat_projection[ 4  ] +
			 _SIO2camera->mat_modelview[ 10 ] * _SIO2camera->mat_projection[ 8  ] + 
			 _SIO2camera->mat_modelview[ 11 ] * _SIO2camera->mat_projection[ 12 ];
			
	c[ 9 ] = _SIO2camera->mat_modelview[ 8  ] * _SIO2camera->mat_projection[ 1  ] +
			 _SIO2camera->mat_modelview[ 9  ] * _SIO2camera->mat_projection[ 5  ] +
			 _SIO2camera->mat_modelview[ 10 ] * _SIO2camera->mat_projection[ 9  ] +
			 _SIO2camera->mat_modelview[ 11 ] * _SIO2camera->mat_projection[ 13 ];
			
	c[ 10 ] = _SIO2camera->mat_modelview[ 8  ] * _SIO2camera->mat_projection[ 2  ] +
			  _SIO2camera->mat_modelview[ 9  ] * _SIO2camera->mat_projection[ 6  ] +
			  _SIO2camera->mat_modelview[ 10 ] * _SIO2camera->mat_projection[ 10 ] +
			  _SIO2camera->mat_modelview[ 11 ] * _SIO2camera->mat_projection[ 14 ];
			
	c[ 11 ] = _SIO2camera->mat_modelview[ 8  ] * _SIO2camera->mat_projection[ 3  ] +
			  _SIO2camera->mat_modelview[ 9  ] * _SIO2camera->mat_projection[ 7  ] +
			  _SIO2camera->mat_modelview[ 10 ] * _SIO2camera->mat_projection[ 11 ] +
			  _SIO2camera->mat_modelview[ 11 ] * _SIO2camera->mat_projection[ 15 ];
 
	c[ 12 ] = _SIO2camera->mat_modelview[ 12 ] * _SIO2camera->mat_projection[ 0  ] +
			  _SIO2camera->mat_modelview[ 13 ] * _SIO2camera->mat_projection[ 4  ] +
			  _SIO2camera->mat_modelview[ 14 ] * _SIO2camera->mat_projection[ 8  ] +
			  _SIO2camera->mat_modelview[ 15 ] * _SIO2camera->mat_projection[ 12 ];
			
	c[ 13 ] = _SIO2camera->mat_modelview[ 12 ] * _SIO2camera->mat_projection[ 1  ] +
			  _SIO2camera->mat_modelview[ 13 ] * _SIO2camera->mat_projection[ 5  ] +
			  _SIO2camera->mat_modelview[ 14 ] * _SIO2camera->mat_projection[ 9  ] +
			  _SIO2camera->mat_modelview[ 15 ] * _SIO2camera->mat_projection[ 13 ];
			
	c[ 14 ] = _SIO2camera->mat_modelview[ 12 ] * _SIO2camera->mat_projection[ 2  ] +
			  _SIO2camera->mat_modelview[ 13 ] * _SIO2camera->mat_projection[ 6  ] +
			  _SIO2camera->mat_modelview[ 14 ] * _SIO2camera->mat_projection[ 10 ] +
			  _SIO2camera->mat_modelview[ 15 ] * _SIO2camera->mat_projection[ 14 ];
			
	c[ 15 ] = _SIO2camera->mat_modelview[ 12 ] * _SIO2camera->mat_projection[ 3  ] +
			  _SIO2camera->mat_modelview[ 13 ] * _SIO2camera->mat_projection[ 7  ] +
			  _SIO2camera->mat_modelview[ 14 ] * _SIO2camera->mat_projection[ 11 ] +
			  _SIO2camera->mat_modelview[ 15 ] * _SIO2camera->mat_projection[ 15 ];
 
 
	_SIO2camera->frustum[ 0 ][ 0 ] = c[ 3  ] - c[ 0  ];
	_SIO2camera->frustum[ 0 ][ 1 ] = c[ 7  ] - c[ 4  ];
	_SIO2camera->frustum[ 0 ][ 2 ] = c[ 11 ] - c[ 8  ];
	_SIO2camera->frustum[ 0 ][ 3 ] = c[ 15 ] - c[ 12 ];
 
	t = 1.0f / sqrtf( _SIO2camera->frustum[ 0 ][ 0 ] * _SIO2camera->frustum[ 0 ][ 0 ] +
					  _SIO2camera->frustum[ 0 ][ 1 ] * _SIO2camera->frustum[ 0 ][ 1 ] +
					  _SIO2camera->frustum[ 0 ][ 2 ] * _SIO2camera->frustum[ 0 ][ 2 ] );

	_SIO2camera->frustum[ 0 ][ 0 ] *= t;
	_SIO2camera->frustum[ 0 ][ 1 ] *= t;
	_SIO2camera->frustum[ 0 ][ 2 ] *= t;
	_SIO2camera->frustum[ 0 ][ 3 ] *= t;
 

	_SIO2camera->frustum[ 1 ][ 0 ] = c[ 3  ] + c[ 0  ];
	_SIO2camera->frustum[ 1 ][ 1 ] = c[ 7  ] + c[ 4  ];
	_SIO2camera->frustum[ 1 ][ 2 ] = c[ 11 ] + c[ 8  ];
	_SIO2camera->frustum[ 1 ][ 3 ] = c[ 15 ] + c[ 12 ];
 
	t = 1.0f / sqrtf( _SIO2camera->frustum[ 1 ][ 0 ] * _SIO2camera->frustum[ 1 ][ 0 ] +
					  _SIO2camera->frustum[ 1 ][ 1 ] * _SIO2camera->frustum[ 1 ][ 1 ] +
					  _SIO2camera->frustum[ 1 ][ 2 ] * _SIO2camera->frustum[ 1 ][ 2 ] );

	_SIO2camera->frustum[ 1 ][ 0 ] *= t;
	_SIO2camera->frustum[ 1 ][ 1 ] *= t;
	_SIO2camera->frustum[ 1 ][ 2 ] *= t;
	_SIO2camera->frustum[ 1 ][ 3 ] *= t;

 
	_SIO2camera->frustum[ 2 ][ 0 ] = c[ 3  ] + c[ 1  ];
	_SIO2camera->frustum[ 2 ][ 1 ] = c[ 7  ] + c[ 5  ];
	_SIO2camera->frustum[ 2 ][ 2 ] = c[ 11 ] + c[ 9  ];
	_SIO2camera->frustum[ 2 ][ 3 ] = c[ 15 ] + c[ 13 ];
 
	t = 1.0f / sqrtf( _SIO2camera->frustum[ 2 ][ 0 ] * _SIO2camera->frustum[ 2 ][ 0 ] +
					  _SIO2camera->frustum[ 2 ][ 1 ] * _SIO2camera->frustum[ 2 ][ 1 ] +
					  _SIO2camera->frustum[ 2 ][ 2 ] * _SIO2camera->frustum[ 2 ][ 2 ] );

	_SIO2camera->frustum[ 2 ][ 0 ] *= t;
	_SIO2camera->frustum[ 2 ][ 1 ] *= t;
	_SIO2camera->frustum[ 2 ][ 2 ] *= t;
	_SIO2camera->frustum[ 2 ][ 3 ] *= t;

 
	_SIO2camera->frustum[ 3 ][ 0 ] = c[ 3  ] - c[ 1  ];
	_SIO2camera->frustum[ 3 ][ 1 ] = c[ 7  ] - c[ 5  ];
	_SIO2camera->frustum[ 3 ][ 2 ] = c[ 11 ] - c[ 9  ];
	_SIO2camera->frustum[ 3 ][ 3 ] = c[ 15 ] - c[ 13 ];
 
	t = 1.0f / sqrtf( _SIO2camera->frustum[ 3 ][ 0 ] * _SIO2camera->frustum[ 3 ][ 0 ] +
					  _SIO2camera->frustum[ 3 ][ 1 ] * _SIO2camera->frustum[ 3 ][ 1 ] +
					  _SIO2camera->frustum[ 3 ][ 2 ] * _SIO2camera->frustum[ 3 ][ 2 ] );

	_SIO2camera->frustum[ 3 ][ 0 ] *= t;
	_SIO2camera->frustum[ 3 ][ 1 ] *= t;
	_SIO2camera->frustum[ 3 ][ 2 ] *= t;
	_SIO2camera->frustum[ 3 ][ 3 ] *= t;
 

	_SIO2camera->frustum[ 4 ][ 0 ] = c[ 3  ] - c[ 2  ];
	_SIO2camera->frustum[ 4 ][ 1 ] = c[ 7  ] - c[ 6  ];
	_SIO2camera->frustum[ 4 ][ 2 ] = c[ 11 ] - c[ 10 ];
	_SIO2camera->frustum[ 4 ][ 3 ] = c[ 15 ] - c[ 14 ];
 
	t = 1.0f / sqrtf( _SIO2camera->frustum[ 4 ][ 0 ] * _SIO2camera->frustum[ 4 ][ 0 ] +
					  _SIO2camera->frustum[ 4 ][ 1 ] * _SIO2camera->frustum[ 4 ][ 1 ] +
					  _SIO2camera->frustum[ 4 ][ 2 ] * _SIO2camera->frustum[ 4 ][ 2 ] );

	_SIO2camera->frustum[ 4 ][ 0 ] *= t;
	_SIO2camera->frustum[ 4 ][ 1 ] *= t;
	_SIO2camera->frustum[ 4 ][ 2 ] *= t;
	_SIO2camera->frustum[ 4 ][ 3 ] *= t;


	#if SIO2_CLIP_PLANE == 6 

		_SIO2camera->frustum[ 5 ][ 0 ] = c[ 3  ] + c[ 2  ];
		_SIO2camera->frustum[ 5 ][ 1 ] = c[ 7  ] + c[ 6  ];
		_SIO2camera->frustum[ 5 ][ 2 ] = c[ 11 ] + c[ 10 ];
		_SIO2camera->frustum[ 5 ][ 3 ] = c[ 15 ] + c[ 14 ];
	 

		t = 1.0f / sqrtf( _SIO2camera->frustum[ 5 ][ 0 ] * _SIO2camera->frustum[ 5 ][ 0 ] +
						  _SIO2camera->frustum[ 5 ][ 1 ] * _SIO2camera->frustum[ 5 ][ 1 ] +
						  _SIO2camera->frustum[ 5 ][ 2 ] * _SIO2camera->frustum[ 5 ][ 2 ] );

		_SIO2camera->frustum[ 5 ][ 0 ] *= t;
		_SIO2camera->frustum[ 5 ][ 1 ] *= t;
		_SIO2camera->frustum[ 5 ][ 2 ] *= t;
		_SIO2camera->frustum[ 5 ][ 3 ] *= t;
	#endif
}


void sio2CameraGetProjectionMatrix( SIO2camera *_SIO2camera )
{
	glGetFloatv( GL_PROJECTION_MATRIX, &_SIO2camera->mat_projection[ 0 ] ); 
}


void sio2CameraGetModelviewMatrix( SIO2camera *_SIO2camera )
{
	glGetFloatv( GL_MODELVIEW_MATRIX, &_SIO2camera->mat_modelview[ 0 ] );
}


void sio2CameraRender( SIO2camera *_SIO2camera )
{
	vec3 v;

	if( _SIO2camera->_SIO2ipo && _SIO2camera->_SIO2ipo->state == SIO2_PLAY )
	{
		sio2TransformSetLoc( _SIO2camera->_SIO2transform,
							 _SIO2camera->_SIO2ipo->_SIO2transform->loc );

		sio2TransformSetRot( _SIO2camera->_SIO2transform,
							 _SIO2camera->_SIO2ipo->_SIO2transform->rot );
		
		sio2Rotate3D( _SIO2camera->_SIO2transform->loc,
				      90.0f - _SIO2camera->_SIO2ipo->_SIO2transform->rot->x,
				      _SIO2camera->_SIO2ipo->_SIO2transform->rot->z,
				      -1.0f,
				      &v );
		
		sio2Vec3Diff( &v,
					  _SIO2camera->_SIO2transform->loc,
					  _SIO2camera->_SIO2transform->dir );
	}

	else if( _SIO2camera->_btRigidBody )
	{
		btTransform _btTransform;
		
		_SIO2camera->_btRigidBody->getWorldTransform().getOpenGLMatrix( _SIO2camera->_SIO2transform->mat );

		sio2TransformGetLocFromMatrix( _SIO2camera->_SIO2transform );
		
		sio2TransformGetRotFromMatrix( _SIO2camera->_SIO2transform );
				
		_SIO2camera->_SIO2transform->mat[ 12 ] =
		_SIO2camera->_SIO2transform->mat[ 13 ] =
		_SIO2camera->_SIO2transform->mat[ 14 ] = 0.0f;						
	}

	v.x =
	v.y = 0.0f;
	v.z = 1.0f;
	
	_SIO2camera->_SIO2transform->mat[ 0  ] = ( _SIO2camera->_SIO2transform->dir->y * v.z ) - ( _SIO2camera->_SIO2transform->dir->z * v.y );
	_SIO2camera->_SIO2transform->mat[ 4  ] = ( _SIO2camera->_SIO2transform->dir->z * v.x ) - ( _SIO2camera->_SIO2transform->dir->x * v.z );
	_SIO2camera->_SIO2transform->mat[ 8  ] = ( _SIO2camera->_SIO2transform->dir->x * v.y ) - ( _SIO2camera->_SIO2transform->dir->y * v.x );

	_SIO2camera->_SIO2transform->mat[ 1  ] = ( _SIO2camera->_SIO2transform->mat[ 4 ] * _SIO2camera->_SIO2transform->dir->z ) -
											 ( _SIO2camera->_SIO2transform->mat[ 8 ] * _SIO2camera->_SIO2transform->dir->y );
											
	_SIO2camera->_SIO2transform->mat[ 5  ] = ( _SIO2camera->_SIO2transform->mat[ 8 ] * _SIO2camera->_SIO2transform->dir->x ) - 
											 ( _SIO2camera->_SIO2transform->mat[ 0 ] * _SIO2camera->_SIO2transform->dir->z );
											
	_SIO2camera->_SIO2transform->mat[ 9  ] = ( _SIO2camera->_SIO2transform->mat[ 0 ] * _SIO2camera->_SIO2transform->dir->y ) -
											 ( _SIO2camera->_SIO2transform->mat[ 4 ] * _SIO2camera->_SIO2transform->dir->x );

	_SIO2camera->_SIO2transform->mat[ 2  ] = -_SIO2camera->_SIO2transform->dir->x;
	_SIO2camera->_SIO2transform->mat[ 6  ] = -_SIO2camera->_SIO2transform->dir->y;
	_SIO2camera->_SIO2transform->mat[ 10 ] = -_SIO2camera->_SIO2transform->dir->z;

	_SIO2camera->_SIO2transform->mat[ 15 ] = 1.0f;

	sio2TransformRender( _SIO2camera->_SIO2transform );
	
	glTranslatef( -_SIO2camera->_SIO2transform->loc->x,
				  -_SIO2camera->_SIO2transform->loc->y,
				  -_SIO2camera->_SIO2transform->loc->z );
}


float sio2CameraSphereDistInFrustum( SIO2camera *_SIO2camera,
								 	 vec3		*_v,
									 float	     _r )
{
	unsigned int i = 0;
	
	float d = 0.0f;

	_r *= 1.25f;
	while( i != SIO2_CLIP_PLANE )
	{
		d = _SIO2camera->frustum[ i ][ 0 ] * _v->x + 
			_SIO2camera->frustum[ i ][ 1 ] * _v->y + 
			_SIO2camera->frustum[ i ][ 2 ] * _v->z + 
			_SIO2camera->frustum[ i ][ 3 ];
		
		if( d < -_r )
		{ return 0.0f; }
		
		++i;
	}
	
	return d + _r;
}


unsigned char sio2CameraPointInFrustum( SIO2camera *_SIO2camera,
										vec3	   *_v )
{
	unsigned int i = 0;
	
	while( i != SIO2_CLIP_PLANE )
	{
		if( _SIO2camera->frustum[ i ][ 0 ] * _v->x +
			_SIO2camera->frustum[ i ][ 1 ] * _v->y +
			_SIO2camera->frustum[ i ][ 2 ] * _v->z +
			_SIO2camera->frustum[ i ][ 3 ] < 0.0f )
		{ return 0; }
		
		++i;
	}
	
	return 1;
}


unsigned char sio2CameraSphereInFrustum( SIO2camera *_SIO2camera,
										 vec3		*_v,
										 float		 _rad )
{
	unsigned int i = 0;
	
	while( i != SIO2_CLIP_PLANE )
	{
		if( _SIO2camera->frustum[ i ][ 0 ] * _v->x +
			_SIO2camera->frustum[ i ][ 1 ] * _v->y +
			_SIO2camera->frustum[ i ][ 2 ] * _v->z +
			_SIO2camera->frustum[ i ][ 3 ] < -_rad )
		{ return 0; }
		
		++i;
	}

	return 1;
}


unsigned char sio2CameraCubeInFrustum( SIO2camera *_SIO2camera,
									   vec3	      *_v,
									   vec3		  *_dim )
{
	unsigned int i = 0;
	
	while( i != SIO2_CLIP_PLANE )
	{
		if( _SIO2camera->frustum[ i ][ 0 ] * ( _v->x - _dim->x ) +
			_SIO2camera->frustum[ i ][ 1 ] * ( _v->y - _dim->y ) +
			_SIO2camera->frustum[ i ][ 2 ] * ( _v->z - _dim->z ) +
			_SIO2camera->frustum[ i ][ 3 ] > 0.0f )
		{
			++i;
			continue;
		}
		
		
		if( _SIO2camera->frustum[ i ][ 0 ] * ( _v->x + _dim->x ) +
			_SIO2camera->frustum[ i ][ 1 ] * ( _v->y - _dim->y ) +
			_SIO2camera->frustum[ i ][ 2 ] * ( _v->z - _dim->z ) +
			_SIO2camera->frustum[ i ][ 3 ] > 0.0f )
		{
			++i;
			continue;
		}
		
		
		if( _SIO2camera->frustum[ i ][ 0 ] * ( _v->x - _dim->x ) +
			_SIO2camera->frustum[ i ][ 1 ] * ( _v->y + _dim->y ) +
			_SIO2camera->frustum[ i ][ 2 ] * ( _v->z - _dim->z ) +
			_SIO2camera->frustum[ i ][ 3 ] > 0.0f )
		{
			++i;
			continue;
		}
		
		
		if( _SIO2camera->frustum[ i ][ 0 ] * ( _v->x + _dim->x ) +
			_SIO2camera->frustum[ i ][ 1 ] * ( _v->y + _dim->y ) +
			_SIO2camera->frustum[ i ][ 2 ] * ( _v->z - _dim->z ) +
			_SIO2camera->frustum[ i ][ 3 ] > 0.0f )
		{
			++i;
			continue;
		}
		
		
		if( _SIO2camera->frustum[ i ][ 0 ] * ( _v->x - _dim->x ) +
			_SIO2camera->frustum[ i ][ 1 ] * ( _v->y - _dim->y ) +
			_SIO2camera->frustum[ i ][ 2 ] * ( _v->z + _dim->z ) +
			_SIO2camera->frustum[ i ][ 3 ] > 0.0f )
		{
			++i;
			continue;
		}
		
		
		if( _SIO2camera->frustum[ i ][ 0 ] * ( _v->x + _dim->x ) +
			_SIO2camera->frustum[ i ][ 1 ] * ( _v->y + _dim->y ) +
			_SIO2camera->frustum[ i ][ 2 ] * ( _v->z + _dim->z ) +
			_SIO2camera->frustum[ i ][ 3 ] > 0.0f )
		{
			++i;
			continue;
		}
		
		
		if( _SIO2camera->frustum[ i ][ 0 ] * ( _v->x - _dim->x ) +
			_SIO2camera->frustum[ i ][ 1 ] * ( _v->y + _dim->y ) +
			_SIO2camera->frustum[ i ][ 2 ] * ( _v->z + _dim->z ) +
			_SIO2camera->frustum[ i ][ 3 ] > 0.0f )
		{
			++i;
			continue;
		}
		
		
		if( _SIO2camera->frustum[ i ][ 0 ] * ( _v->x + _dim->x ) +
			_SIO2camera->frustum[ i ][ 1 ] * ( _v->y + _dim->y ) +
			_SIO2camera->frustum[ i ][ 2 ] * ( _v->z + _dim->z ) +
			_SIO2camera->frustum[ i ][ 3 ] > 0.0f )
		{
			++i;
			continue;
		}
			
		return 0;
	}
	
	return 1;
}


// 0 - Outside
// 1 - Intersect
// 2 - Inside
unsigned char sio2CameraCubeIntersectFrustum( SIO2camera *_SIO2camera,
											  vec3	     *_v,
											  vec3		 *_dim )
{
	unsigned int i = 0;
	
	unsigned char c1,
				  c2 = 0;

	while( i != SIO2_CLIP_PLANE )
	{
		c1 = 0;
		
		if( _SIO2camera->frustum[ i ][ 0 ] * ( _v->x - _dim->x ) + 
			_SIO2camera->frustum[ i ][ 1 ] * ( _v->y - _dim->y ) +
			_SIO2camera->frustum[ i ][ 2 ] * ( _v->z - _dim->z ) +
			_SIO2camera->frustum[ i ][ 3 ] > 0 )
		{ ++c1; }
		
		
		if( _SIO2camera->frustum[ i ][ 0 ] * ( _v->x + _dim->x ) +
			_SIO2camera->frustum[ i ][ 1 ] * ( _v->y - _dim->y ) +
			_SIO2camera->frustum[ i ][ 2 ] * ( _v->z - _dim->z ) +
			_SIO2camera->frustum[ i ][ 3 ] > 0 )
		{ ++c1; }
		
		
		if( _SIO2camera->frustum[ i ][ 0 ] * ( _v->x - _dim->x ) +
			_SIO2camera->frustum[ i ][ 1 ] * ( _v->y + _dim->y ) +
			_SIO2camera->frustum[ i ][ 2 ] * ( _v->z - _dim->z ) +
			_SIO2camera->frustum[ i ][ 3 ] > 0 )
		{ ++c1; }
		
		
		if( _SIO2camera->frustum[ i ][ 0 ] * ( _v->x + _dim->x ) +
			_SIO2camera->frustum[ i ][ 1 ] * ( _v->y + _dim->y ) +
			_SIO2camera->frustum[ i ][ 2 ] * ( _v->z - _dim->z ) +
			_SIO2camera->frustum[ i ][ 3 ] > 0 )
		{ ++c1; }
		
		
		if( _SIO2camera->frustum[ i ][ 0 ] * ( _v->x - _dim->x ) +
			_SIO2camera->frustum[ i ][ 1 ] * ( _v->y - _dim->y ) +
			_SIO2camera->frustum[ i ][ 2 ] * ( _v->z + _dim->z ) +
			_SIO2camera->frustum[ i ][ 3 ] > 0 )
		{ ++c1; }
		
		
		if( _SIO2camera->frustum[ i ][ 0 ] * ( _v->x + _dim->x ) +
			_SIO2camera->frustum[ i ][ 1 ] * ( _v->y - _dim->y ) +
			_SIO2camera->frustum[ i ][ 2 ] * ( _v->z + _dim->z ) +
			_SIO2camera->frustum[ i ][ 3 ] > 0 )
		{ ++c1; }
		
		
		if( _SIO2camera->frustum[ i ][ 0 ] * ( _v->x - _dim->x ) +
			_SIO2camera->frustum[ i ][ 1 ] * ( _v->y + _dim->y ) +
			_SIO2camera->frustum[ i ][ 2 ] * ( _v->z + _dim->z ) +
			_SIO2camera->frustum[ i ][ 3 ] > 0 )
		{ ++c1; }
		
		
		if( _SIO2camera->frustum[ i ][ 0 ] * ( _v->x + _dim->x ) +
			_SIO2camera->frustum[ i ][ 1 ] * ( _v->y + _dim->y ) +
			_SIO2camera->frustum[ i ][ 2 ] * ( _v->z + _dim->z ) +
			_SIO2camera->frustum[ i ][ 3 ] > 0 )
		{ ++c1; }
		
		
		if( !c1 )
		{ return 0; }
		
		if( c1 == 8 )
		{ ++c2; }
	
		++i;
	}

	return ( c2 == SIO2_CLIP_PLANE ) ? 2 : 1;
}


// 0 - Outside
// 1 - Intersect
// 2 - Inside
unsigned char sio2CameraSphereIntersectFrustum( SIO2camera *_SIO2camera,
												vec3	   *_v,
												float		_rad )
{
	unsigned int i = 0;

	unsigned char c = 0;

	while( i != SIO2_CLIP_PLANE )
	{
		float dd = _SIO2camera->frustum[ i ][ 0 ] * _v->x +
				   _SIO2camera->frustum[ i ][ 1 ] * _v->y +
				   _SIO2camera->frustum[ i ][ 2 ] * _v->z +
				   _SIO2camera->frustum[ i ][ 3 ];

		if( dd <= -_rad )
		{ return 0; }
		else if( dd > _rad )
		{ ++c; }
		
		++i;
	}

	return ( c == SIO2_CLIP_PLANE ) ? 2: 1;
}


unsigned char sio2CameraGeometryInFrustum( SIO2camera	*_SIO2camera,
										   unsigned int  _nvert,
										   float		*_vert )
{
	unsigned int i = 0,
				 j;

	while( i != SIO2_CLIP_PLANE )
	{
		j = 0;
		while( j != _nvert )
		{
			if( ( _SIO2camera->frustum[ i ][ 0 ] * _vert[ j 	] + 
				  _SIO2camera->frustum[ i ][ 1 ] * _vert[ j + 1 ] + 
				  _SIO2camera->frustum[ i ][ 2 ] * _vert[ j + 2 ] + 
				  _SIO2camera->frustum[ i ][ 3 ] ) > 0 )
			{ break; }
			
			j += 3;
		}
	
		if( j == _nvert )
		{ return 0; }
	
		++i;
	}
	
	return 1;
}


void sio2CameraUpdateListener( SIO2camera *_SIO2camera )
{
	static float o[ 6 ] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,  1.0f };

	memcpy( &o[ 0 ], _SIO2camera->_SIO2transform->dir, 12 );
	
	alListener3f( AL_POSITION,
				  _SIO2camera->_SIO2transform->loc->x,
				  _SIO2camera->_SIO2transform->loc->y,
				  _SIO2camera->_SIO2transform->loc->z );
		
	alListenerfv( AL_ORIENTATION, o );
	
	#ifdef SIO2_DEBUG_AL

		sio2ErrorAL( __FILE__, __FUNCTION__, __LINE__ );
	#endif	
}
