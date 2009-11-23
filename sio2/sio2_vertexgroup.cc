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

SIO2vertexgroup *sio2VertexGroupInit( char *_name )
{
	SIO2vertexgroup *_SIO2vertexgroup = ( SIO2vertexgroup * ) calloc( 1, sizeof( SIO2vertexgroup ) );
	
	sio2StringCpy( _SIO2vertexgroup->name, _name );
	
	_SIO2vertexgroup->mode = GL_TRIANGLES;
	
	return _SIO2vertexgroup;
}


SIO2vertexgroup *sio2VertexGroupFree( SIO2vertexgroup *_SIO2vertexgroup )
{
	glDeleteBuffers( 1, &_SIO2vertexgroup->vbo );
	
	if( _SIO2vertexgroup->ind )
	{
		free( _SIO2vertexgroup->ind );
		_SIO2vertexgroup->ind = NULL;
	}
	
	free( _SIO2vertexgroup );

	return NULL;
}


void sio2VertexGroupLoad( SIO2vertexgroup *_SIO2vertexgroup,
						  SIO2stream	  *_SIO2stream )
{
	sio2StreamRead( _SIO2stream, &_SIO2vertexgroup->mname[ 0 ], SIO2_MAX_CHAR );
	
	sio2StreamRead( _SIO2stream,
					&_SIO2vertexgroup->n_ind, 4 );

	if( _SIO2vertexgroup->n_ind )
	{
		_SIO2vertexgroup->ind = (unsigned short *) malloc( _SIO2vertexgroup->n_ind );
		sio2StreamRead( _SIO2stream, &_SIO2vertexgroup->ind[ 0 ], _SIO2vertexgroup->n_ind ); 
	}
}


void sio2VertexGroupGenId( SIO2vertexgroup *_SIO2vertexgroup )
{
	if( _SIO2vertexgroup->n_ind )
	{
		glGenBuffers( 1, &_SIO2vertexgroup->vbo );
		
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER,
					  _SIO2vertexgroup->vbo );
		
		glBufferData( GL_ELEMENT_ARRAY_BUFFER,
					  _SIO2vertexgroup->n_ind << 1,
					  &_SIO2vertexgroup->ind[ 0 ],
					  GL_STATIC_DRAW );

		if(  _SIO2vertexgroup->_SIO2material &&
			!_SIO2vertexgroup->_SIO2material->_SIO2vertexshader )
		{
			free( _SIO2vertexgroup->ind );
			_SIO2vertexgroup->ind = NULL;
		}
	}
}


void sio2VertexGroupRender( SIO2vertexgroup *_SIO2vertexgroup,
							unsigned char	 _usematerial )
{
	if( _usematerial )
	{
		if( _SIO2vertexgroup->_SIO2material )
		{
			if( _SIO2vertexgroup->_SIO2material->_SIO2vertexshader )
			{
				unsigned int i = 0;

				vec3 ver,
					 nor = { 0.0f, 0.0f, 0.0f };
					 
				col4 col = { 0, 0, 0, 0 };
				
				vec2 uv0 = { 0.0f, 0.0f },
					 uv1 = { 0.0f, 0.0f };

				unsigned char *buf = ( unsigned char * )sio2MapBuffer( sio2->_SIO2object->vbo, GL_ARRAY_BUFFER );
				
				while( i != _SIO2vertexgroup->n_ind )
				{
					memcpy( &ver, &sio2->_SIO2object->buf[ _SIO2vertexgroup->ind[ i ] * 12 ], 12 );
					
					if( sio2->_SIO2object->vbo_offset[ SIO2_OBJECT_NORMALS ] )
					{ memcpy( &nor, &sio2->_SIO2object->buf[ sio2->_SIO2object->vbo_offset[ SIO2_OBJECT_NORMALS ] + ( _SIO2vertexgroup->ind[ i ] * 12 ) ], 12 ); }
					
					if( sio2->_SIO2object->vbo_offset[ SIO2_OBJECT_VCOLOR ] )
					{ memcpy( &col, &sio2->_SIO2object->buf[ sio2->_SIO2object->vbo_offset[ SIO2_OBJECT_VCOLOR ] + ( _SIO2vertexgroup->ind[ i ] << 2 ) ], 4 ); }
					
					if( sio2->_SIO2object->vbo_offset[ SIO2_OBJECT_TEXUV0 ] )
					{ memcpy( &uv0, &sio2->_SIO2object->buf[ sio2->_SIO2object->vbo_offset[ SIO2_OBJECT_TEXUV0 ] + ( _SIO2vertexgroup->ind[ i ] << 3 ) ], 8 ); }

					if( sio2->_SIO2object->vbo_offset[ SIO2_OBJECT_TEXUV1 ] )
					{ memcpy( &uv1, &sio2->_SIO2object->buf[ sio2->_SIO2object->vbo_offset[ SIO2_OBJECT_TEXUV1 ] + ( _SIO2vertexgroup->ind[ i ] << 3 ) ], 8 ); }
					
					
					_SIO2vertexgroup->_SIO2material->_SIO2vertexshader( &ver, &nor, &col, &uv0, &uv1, _SIO2vertexgroup->_SIO2material );


					memcpy( &buf[ _SIO2vertexgroup->ind[ i ] * 12 ], &ver, 12 );
					
					if( sio2->_SIO2object->vbo_offset[ SIO2_OBJECT_NORMALS ] )
					{ memcpy( &buf[ sio2->_SIO2object->vbo_offset[ SIO2_OBJECT_NORMALS ] + ( _SIO2vertexgroup->ind[ i ] * 12 ) ], &nor, 12 ); }
					
					if( sio2->_SIO2object->vbo_offset[ SIO2_OBJECT_VCOLOR ] )
					{ memcpy( &buf[ sio2->_SIO2object->vbo_offset[ SIO2_OBJECT_VCOLOR ] + ( _SIO2vertexgroup->ind[ i ] << 2 ) ], &col, 4 ); }

					if( sio2->_SIO2object->vbo_offset[ SIO2_OBJECT_TEXUV0 ] )
					{ memcpy( &buf[ sio2->_SIO2object->vbo_offset[ SIO2_OBJECT_TEXUV0 ] + ( _SIO2vertexgroup->ind[ i ] << 3 ) ], &uv0, 8 ); }

					if( sio2->_SIO2object->vbo_offset[ SIO2_OBJECT_TEXUV1 ] )
					{ memcpy( &buf[ sio2->_SIO2object->vbo_offset[ SIO2_OBJECT_TEXUV1 ] + ( _SIO2vertexgroup->ind[ i ] << 3 ) ], &uv1, 8 ); }					
					
					++i;
				}
				
				buf = ( unsigned char * )sio2UnmapBuffer( sio2->_SIO2object->vbo, GL_ARRAY_BUFFER );
			}
			
			sio2MaterialRender( _SIO2vertexgroup->_SIO2material );
		}
		
		else if( sio2->_SIO2material )
		{ sio2MaterialReset(); }
	}
	

	if( sio2->_SIO2vertexgroup != _SIO2vertexgroup )
	{
		sio2->_SIO2vertexgroup = _SIO2vertexgroup;

		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER,
					  _SIO2vertexgroup->vbo );
	}
	
	glDrawElements( _SIO2vertexgroup->mode,
					_SIO2vertexgroup->n_ind,
					GL_UNSIGNED_SHORT,
					(void *)NULL );	
}
