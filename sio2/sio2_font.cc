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


SIO2font *sio2FontInit( const char *_name )
{
	SIO2font *_SIO2font = ( SIO2font * ) calloc( 1, sizeof( SIO2font ) );
	
	sio2StringCpy( _SIO2font->name, _name );
	
	_SIO2font->_SIO2transform = sio2TransformInit();

	sio2ResourceAdd( sio2->_SIO2resource,
					 SIO2_FONT,
					 ( void * )_SIO2font );	
	
	return _SIO2font;
}


SIO2font *sio2FontFree( SIO2font *_SIO2font )
{
	_SIO2font->_SIO2transform = sio2TransformFree( _SIO2font->_SIO2transform );
	
	glDeleteBuffers( 1, &_SIO2font->vbo );

	sio2ResourceDel( sio2->_SIO2resource,
					 SIO2_FONT,
					 (void *)_SIO2font );


	free( _SIO2font );

	return NULL;
}


void sio2FontCreate( SIO2font	   *_SIO2font,
					 SIO2material  *_SIO2material,
					 unsigned char  _n_char,
					 unsigned char  _c_offset,
					 float		    _size, 
					 float		    _space )
{
	_SIO2font->n_char   = _n_char;
	_SIO2font->c_offset = _c_offset;
	_SIO2font->size		= _size;
	_SIO2font->space	= _space;

	_SIO2font->_SIO2material = _SIO2material;

	sio2FontBuild( _SIO2font );
}


void sio2FontBuild( SIO2font *_SIO2font )
{
	unsigned int i = 0,
				 boffset;
	
	unsigned short size = ( _SIO2font->_SIO2material->_SIO2image[ SIO2_MATERIAL_CHANNEL0 ]->width  / _SIO2font->n_char ) * 
						  ( _SIO2font->_SIO2material->_SIO2image[ SIO2_MATERIAL_CHANNEL0 ]->height / _SIO2font->n_char );
	
	float *buf		   = ( float * ) malloc( size << 6 ),
		  ratiox	   = _SIO2font->size / _SIO2font->_SIO2material->_SIO2image[ SIO2_MATERIAL_CHANNEL0 ]->width,	
		  ratioy	   = _SIO2font->size / _SIO2font->_SIO2material->_SIO2image[ SIO2_MATERIAL_CHANNEL0 ]->height,
		  ratiowx	   = _SIO2font->_SIO2material->_SIO2image[ SIO2_MATERIAL_CHANNEL0 ]->width / _SIO2font->size,
		  ratiohy	   = _SIO2font->_SIO2material->_SIO2image[ SIO2_MATERIAL_CHANNEL0 ]->height / _SIO2font->size,
		  hsize		   = _SIO2font->size * 0.5f,

		  v_coord[ 8 ] = { -hsize, -hsize,
						    hsize, -hsize,
						    hsize,  hsize,
						   -hsize,  hsize };
			  	  
	boffset = size << 3;
	_SIO2font->boffset = size << 5;

	while( i != size )
	{
		float cx = ( float )( i % _SIO2font->n_char ) / ratiowx,
			  cy = ( float )( i / _SIO2font->n_char ) / ratiohy,
			  t_coord[ 8 ];

		t_coord[ 0 ] = cx		  ; t_coord[ 1 ] = 1.0f + ( cy + ratioy );
		t_coord[ 2 ] = cx + ratiox; t_coord[ 3 ] = 1.0f + ( cy + ratioy );
		t_coord[ 4 ] = cx + ratiox; t_coord[ 5 ] = 1.0f + cy;
		t_coord[ 6 ] = cx		  ; t_coord[ 7 ] = 1.0f + cy;

		memcpy( &buf[   i << 3 	           ], &v_coord[ 0 ], 32 );
		memcpy( &buf[ ( i << 3 ) + boffset ], &t_coord[ 0 ], 32 );
	
		++i;
	}
	

	glGenBuffers( 1, &_SIO2font->vbo );
	
	glBindBuffer( GL_ARRAY_BUFFER, _SIO2font->vbo );
	
	glBufferData( GL_ARRAY_BUFFER,
				  size << 6,
				  &buf[ 0 ],
				  GL_STATIC_DRAW );

	free( buf );
	
	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif	
	
	sio2FontReset();
}


unsigned char sio2FontPrint( SIO2font	   *_SIO2font,
							 unsigned char  _usematrix,
							 const char	   *_fmt,
							 ... )
{
	unsigned char n_lines = 1;
	
	char *str = ( char * ) calloc( sio2StringLen( _fmt ) + SIO2_MAX_CHAR, sizeof( char ) );

	unsigned int i = 0,
				 slen;	
	
	va_list	ap;


	va_start( ap, _fmt );
	{ 
	    vsprintf( str, _fmt, ap );
	}
	va_end( ap );	
	
	slen = sio2StringLen( str );

	sio2MaterialRender( _SIO2font->_SIO2material );

	
	if( sio2->_SIO2font != _SIO2font )
	{
		sio2->_SIO2font = _SIO2font;
		
		glBindBuffer( GL_ARRAY_BUFFER,
					  _SIO2font->vbo );
		
		glVertexPointer( 2,
						 GL_FLOAT,
						 0,
						 ( void * )NULL );
		
		sio2StateEnable( sio2->_SIO2state, SIO2_TEXTURE_COORD_ARRAY0 );

		glTexCoordPointer( 2,
						   GL_FLOAT,
						   0,
						   SIO2_BUFFER_OFFSET( _SIO2font->boffset ) );

		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
	}


	glPushMatrix();
	{	
		float space = 0.0f;
		
		switch( _usematrix )
		{
			case SIO2_TRANSFORM_MATRIX_APPLY:
			{ sio2TransformApply( _SIO2font->_SIO2transform ); break; }

			case SIO2_TRANSFORM_MATRIX_BIND:
			{ sio2TransformRender( _SIO2font->_SIO2transform ); break; }
		}

		
		while( i != slen )
		{
			glDrawArrays( GL_TRIANGLE_FAN,
						  ( str[ i ] - _SIO2font->c_offset ) << 2, 4 );
		
			if( str[ i ] == 10 )
			{
				glTranslatef( -space, -( _SIO2font->size + _SIO2font->line ), 0.0f );
				
				space = 0.0f;
				++n_lines;
			}
			else
			{
				space += _SIO2font->space;
				
				glTranslatef( _SIO2font->space, 0.0f, 0.0f );
			}
			
			
			++i;
		}
	}
	glPopMatrix();

	free( str );

	return n_lines;
}


void sio2FontReset( void )
{
	sio2->_SIO2font = NULL;
	
	glBindBuffer( GL_ARRAY_BUFFER, 0 );
}
