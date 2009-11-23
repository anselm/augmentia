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


SIO2image *sio2ImageInit( const char *_name )
{
	SIO2image *_SIO2image = ( SIO2image * ) calloc( 1, sizeof( SIO2image ) );
	
	sio2StringCpy( _SIO2image->name, _name );
	
	sio2ResourceAdd( sio2->_SIO2resource,
					 SIO2_IMAGE,
					 ( void * )_SIO2image );
	
	return _SIO2image;
}


SIO2image *sio2ImageFree( SIO2image *_SIO2image )
{
	if( _SIO2image->tex )
	{
		free( _SIO2image->tex );
		_SIO2image->tex = NULL;
	}

	glDeleteTextures( 1, &_SIO2image->tid );

	sio2ResourceDel( sio2->_SIO2resource,
					  SIO2_IMAGE,
					  (void *)_SIO2image );	
	
	free( _SIO2image );
	
	return NULL;
}


void sio2ImageLoad( SIO2image  *_SIO2image,
				    SIO2stream *_SIO2stream )
{
	char tmp[ SIO2_MAX_PATH ] = {""};
	
	sio2StringCpy( tmp, _SIO2stream->fname );
	
	sio2StringToUpper( tmp );

	if( sio2StringTok( tmp, ( char * )".JPG"  ) ||
		sio2StringTok( tmp, ( char * )".JPEG" ) )
	{
		sio2ImageLoadJPEG( _SIO2image,
						   _SIO2stream );
	}
	
	else if( sio2StringTok( tmp, ( char * )".TGA" ) )
	{
		sio2ImageLoadTGA( _SIO2image,
						  _SIO2stream );
	}
	
	else if( sio2StringTok( tmp, ( char * )".PNG" ) )
	{
		sio2ImageLoadPNG( _SIO2image,
						  _SIO2stream );
	}
}


void sio2ImageLoadTGA( SIO2image  *_SIO2image,
					   SIO2stream *_SIO2stream )
{
	unsigned int size;
	
	unsigned char *header;

	header = ( unsigned char * )sio2StreamReadPtr( _SIO2stream, 18 );

	_SIO2image->width  = header[ 13 ] * 256 + header[ 12 ];
	_SIO2image->height = header[ 15 ] * 256 + header[ 14 ];
	_SIO2image->bits   = header[ 16 ] >> 3;
	
	size = _SIO2image->width * _SIO2image->height * _SIO2image->bits;
	
	_SIO2image->tex = ( unsigned char * ) malloc( size );


	if( header[ 2 ] == 10 || header[ 2 ] == 11 )
	{
		unsigned int i,
					 px_count = _SIO2image->width * _SIO2image->height,
					 px_index = 0,
					 by_index = 0;
		
		unsigned char chunk = 0,
					  *bgra;

		do
		{
			sio2StreamRead( _SIO2stream, &chunk, 1 );
			
			if( chunk < 128 )
			{ 
				chunk++;
				
				i = 0;
				while( i != chunk )
				{
					sio2StreamRead( _SIO2stream, &_SIO2image->tex[ by_index ], _SIO2image->bits );
					by_index += _SIO2image->bits;
					
					++i;
				}
			}
			else
			{
				chunk -= 127;

				bgra = ( unsigned char * )sio2StreamReadPtr( _SIO2stream, _SIO2image->bits );
				
				i = 0;
				while( i != chunk )
				{
					memcpy( &_SIO2image->tex[ by_index ], &bgra[ 0 ], _SIO2image->bits );
					by_index += _SIO2image->bits;
					
					++i;
				}				
			}
			px_index += chunk;
		}
		while( px_index < px_count );
	}
	else
	{ sio2StreamRead( _SIO2stream, &_SIO2image->tex[ 0 ], size ); }
	
	
	if( _SIO2image->bits == 3 )
	{
		unsigned int i = 0;
		
		while( i != size )
		{
			unsigned char tmp = _SIO2image->tex[ i ];
			
			_SIO2image->tex[ i     ] = _SIO2image->tex[ i + 2 ];
			_SIO2image->tex[ i + 2 ] = tmp;
			
			i += 3;
		}
	}
	
	if( !header[ 17 ] || header[ 17 ] == 8 )
	{ sio2ImageFlip( _SIO2image ); }
}


void sio2ImageLoadJPEG( SIO2image  *_SIO2image,
						SIO2stream *_SIO2stream )
{
	unsigned char *row;	

	unsigned int size;
	
	struct jpeg_decompress_struct cinfo;
	struct jpeg_error_mgr jerr;
	
	cinfo.err = jpeg_std_error( &jerr );
	jpeg_create_decompress( &cinfo );
	
	jpeg_stdio_src_buf( &cinfo, _SIO2stream->buf,  _SIO2stream->size );
	jpeg_read_header( &cinfo, 1 );
	
	jpeg_start_decompress( &cinfo );
	
	_SIO2image->width  = cinfo.image_width;
	_SIO2image->height = cinfo.image_height;
	_SIO2image->bits   = cinfo.output_components;	
	
	 size = _SIO2image->width * _SIO2image->height * _SIO2image->bits;

	_SIO2image->tex = ( unsigned char * ) malloc( size );
	
	row = _SIO2image->tex;
	
	while( cinfo.output_scanline < _SIO2image->height )
	{
		row = _SIO2image->tex   + 
			  _SIO2image->bits  *
			  _SIO2image->width * 
			  cinfo.output_scanline;
		
		jpeg_read_scanlines( &cinfo, &row, 1 );
	}

	jpeg_finish_decompress ( &cinfo );
	jpeg_destroy_decompress( &cinfo );
}


void sio2ImageLoadPNG( SIO2image  *_SIO2image,
					   SIO2stream *_SIO2stream )
{
	png_structp _png_structp;
	
	png_infop _png_infop;
	
	png_bytep *_png_bytep;

	int	i = 0,
		bits,
		type;

	_png_structp = png_create_read_struct( PNG_LIBPNG_VER_STRING,
										   ( png_voidp * )_SIO2stream->fname,
										   NULL, NULL );

	_png_infop = png_create_info_struct( _png_structp );
	
	png_set_read_fn( _png_structp, ( png_voidp * )_SIO2stream, sio2PngRead );
	
	png_read_info (_png_structp, _png_infop);


	bits = png_get_bit_depth ( _png_structp, _png_infop );
	type = png_get_color_type( _png_structp, _png_infop );


	if( type == PNG_COLOR_TYPE_PALETTE )
	{ png_set_palette_to_rgb( _png_structp ); }
	
	if( type == PNG_COLOR_TYPE_GRAY && bits < 8 )
	{ png_set_gray_1_2_4_to_8( _png_structp ); }

	if( png_get_valid( _png_structp, _png_infop, PNG_INFO_tRNS ) )
	{ png_set_tRNS_to_alpha (_png_structp); }
	
	
	if( bits == 16 )
	{ png_set_strip_16( _png_structp ); }
	
	else if( bits < 8 )
    { png_set_packing( _png_structp ); }

	png_read_update_info( _png_structp, _png_infop );

	png_get_IHDR( _png_structp,
				  _png_infop,
				  ( png_uint_32 * )( &_SIO2image->width  ),
				  ( png_uint_32 * )( &_SIO2image->height ),
				  &bits,
				  &type,
				  NULL, NULL, NULL );

	switch( type )
	{
		case PNG_COLOR_TYPE_GRAY:
		{
			_SIO2image->bits = 1;
			break;
		}

		case PNG_COLOR_TYPE_GRAY_ALPHA:
		{
			_SIO2image->bits = 2;
			break;
		}
				
		case PNG_COLOR_TYPE_RGB:
		{
			_SIO2image->bits = 3;
			break;
		}

		case PNG_COLOR_TYPE_RGB_ALPHA:
		{
			_SIO2image->bits = 4;
			break;
		}		
	}

	_SIO2image->tex = ( unsigned char * ) malloc( _SIO2image->width  *
												  _SIO2image->height *
												  _SIO2image->bits );

	_png_bytep = ( png_bytep * ) malloc( _SIO2image->height * sizeof( png_bytep ) );

	while( i < ( int )_SIO2image->height )
	{
		_png_bytep[ i ] = ( png_bytep )(   _SIO2image->tex    +
										 ( _SIO2image->height - ( i + 1 ) ) * 
										   _SIO2image->width  *
										   _SIO2image->bits );
		++i;
	}

	png_read_image( _png_structp,
					_png_bytep );

	png_read_end( _png_structp, NULL );

	png_destroy_read_struct( &_png_structp,
							 &_png_infop, NULL );
	free( _png_bytep );
	
	sio2ImageFlip( _SIO2image );
	
	if( _SIO2image->bits == 4 )
	{ sio2ImageRGBAtoBGRA( _SIO2image ); }
}


void sio2ImageGenId( SIO2image	  *_SIO2image,
					 unsigned int  _flags,
					 float		   _filter )
{
	int iformat,
		format;

	switch( _SIO2image->bits )
	{
		case 0:
		{ return; }
		
		case 1:
		{
			iformat = GL_LUMINANCE;
			format	= GL_LUMINANCE;
			
			break;
		}

		case 2:
		{
			iformat = GL_LUMINANCE_ALPHA;
			format	= GL_LUMINANCE_ALPHA;
			
			break;
		}
		
		case 3:
		{
			iformat = GL_RGB;
			format	= GL_RGB;
			
			break;
		}

		case 4:
		{
			iformat = GL_RGBA;
			format	= GL_BGRA;
			
			break;
		}
	}
 
 
	if( !_SIO2image->tid )
	{
		_SIO2image->flags = _flags;

		glGenTextures( 1, &_SIO2image->tid );
		
		glBindTexture( GL_TEXTURE_2D, _SIO2image->tid );
				

		if( sio2IsStateEnabled( _flags, SIO2_IMAGE_CLAMP ) )
		{
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
		}
		

		if( sio2->afilter != SIO2_IMAGE_ISOTROPIC )
		{
			glTexParameterf( GL_TEXTURE_2D,
							 GL_TEXTURE_MAX_ANISOTROPY_EXT,
							 ( float )sio2->afilter );
		}


		_SIO2image->filter = _filter;

		glTexEnvf( GL_TEXTURE_FILTER_CONTROL_EXT,
				   GL_TEXTURE_LOD_BIAS_EXT, _SIO2image->filter );		


		if( !sio2IsStateEnabled( _flags, SIO2_IMAGE_MIPMAP ) )
		{
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );	
		}
		else
		{
			if( sio2->tfilter == SIO2_IMAGE_BILINEAR )
			{
				glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
				glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST );
			}
			
			else if( sio2->tfilter == SIO2_IMAGE_TRILINEAR )
			{
				glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
				glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST );
			}
			
			else if( sio2->tfilter == SIO2_IMAGE_QUADLINEAR )
			{
				glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
				glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
			}
			
			glTexParameteri( GL_TEXTURE_2D,
							 GL_GENERATE_MIPMAP,
							 GL_TRUE );
		}
			

		glTexImage2D( GL_TEXTURE_2D,
					  0,
					  iformat,
					  _SIO2image->width,
					  _SIO2image->height,
					  0,
					  format,
					  GL_UNSIGNED_BYTE,
					  _SIO2image->tex );
	}
	else
	{
		glBindTexture( GL_TEXTURE_2D, _SIO2image->tid );

		glTexSubImage2D( GL_TEXTURE_2D,
						 0, 0, 0,
						 _SIO2image->width,
						 _SIO2image->height,						 
						 format,
						 GL_UNSIGNED_BYTE,
						 _SIO2image->tex );
	}
	
	free( _SIO2image->tex );
	_SIO2image->tex = NULL;
}


void sio2ImageScale( SIO2image	  *_SIO2image,
					 unsigned int  _width,
					 unsigned int  _height )
{
	unsigned int i = 0,
				 j,
				 offset,
				 *px = ( unsigned int * ) malloc( _width  << 3 ),
				 *py = ( unsigned int * ) malloc( _height << 3 );
	
	float t = 0.0f,
		  ratio_x = (float)_SIO2image->width  / (float)_width,
		  ratio_y = (float)_SIO2image->height / (float)_height;
	
	
	unsigned char *tex = ( unsigned char * ) malloc( _width * _height * _SIO2image->bits );
	
	while( i != _width )
	{
		px[ i ] = ( unsigned int )t;
	
		t += ratio_x;
		
		++i;
	}
	

	i = 0;
	t = 0.0f;
	while( i != _height )
	{
		py[ i ] = ( unsigned int )t;
	
		t += ratio_y;
		
		++i;
	}
		   
	
	i = 0;
	while( i != _height )
	{
		offset = py[ i ] * _SIO2image->width;

		j = 0;
		while( j != _width )
		{
			switch( _SIO2image->bits )
			{
				case 1:
				{
					tex[ ( i * _width + j ) ] = _SIO2image->tex[ ( offset + px[ j ] ) ];

					break;
				}

				case 2:
				{
					tex[ ( i * _width + j ) * _SIO2image->bits     ] = _SIO2image->tex[ ( offset + px[ j ] ) * _SIO2image->bits     ];
					tex[ ( i * _width + j ) * _SIO2image->bits + 1 ] = _SIO2image->tex[ ( offset + px[ j ] ) * _SIO2image->bits + 1 ];

					break;
				}
			
				case 3:
				{
					tex[ ( i * _width + j ) * _SIO2image->bits     ] = _SIO2image->tex[ ( offset + px[ j ] ) * _SIO2image->bits     ];
					tex[ ( i * _width + j ) * _SIO2image->bits + 1 ] = _SIO2image->tex[ ( offset + px[ j ] ) * _SIO2image->bits + 1 ];
					tex[ ( i * _width + j ) * _SIO2image->bits + 2 ] = _SIO2image->tex[ ( offset + px[ j ] ) * _SIO2image->bits + 2 ];
				
					break;
				}
			
				case 4:
				{
					tex[ ( i * _width + j ) * _SIO2image->bits     ] = _SIO2image->tex[ ( offset + px[ j ] ) * _SIO2image->bits     ];
					tex[ ( i * _width + j ) * _SIO2image->bits + 1 ] = _SIO2image->tex[ ( offset + px[ j ] ) * _SIO2image->bits + 1 ];
					tex[ ( i * _width + j ) * _SIO2image->bits + 2 ] = _SIO2image->tex[ ( offset + px[ j ] ) * _SIO2image->bits + 2 ];
					tex[ ( i * _width + j ) * _SIO2image->bits + 3 ] = _SIO2image->tex[ ( offset + px[ j ] ) * _SIO2image->bits + 3 ];
				
					break;
				}
			}
			
			++j;
		}
	
	
		++i;
	}
	
	
	free( px );
	free( py );
	
	px = 
	py = NULL;
	
	_SIO2image->width  = _width;
	_SIO2image->height = _height;
	
	free( _SIO2image->tex );
	_SIO2image->tex = tex;
}


void sio2ImageFlip( SIO2image *_SIO2image )
{
	unsigned int i    = 0,
				 size = _SIO2image->width  *
					    _SIO2image->height *
						_SIO2image->bits,
				
				 rows = _SIO2image->width * _SIO2image->bits;
						
	unsigned char *buf = ( unsigned char * ) malloc( size );

	while( i != _SIO2image->height )
	{
		memcpy( buf + ( i * rows ),
				_SIO2image->tex + ( ( ( _SIO2image->height - i ) - 1 ) * rows ),
				rows );
		++i;
	}
	
	memcpy( &_SIO2image->tex[ 0 ],
			&buf[ 0 ], size );
			
	free( buf );
	buf = NULL;
} 


void sio2ImageSetAlpha( SIO2image *_SIO2image0,
					    SIO2image *_SIO2image1 )
{
	if( _SIO2image0->bits   == 3				  &&
		_SIO2image1->bits   == 1				  &&
		_SIO2image0->width  == _SIO2image1->width && 
		_SIO2image0->height == _SIO2image1->height )
	{
		unsigned int i   = 0,
					 rgb = 0,
					 a   = 0,
					 size;
					 
		unsigned char *tex;

		_SIO2image0->bits = 4;		
		size = _SIO2image0->width * _SIO2image0->height * _SIO2image0->bits;
		
		tex = ( unsigned char * ) malloc( size );
		
		while( i != size )
		{
			tex[ i     ] = _SIO2image0->tex[ rgb + 2 ];
			tex[ i + 1 ] = _SIO2image0->tex[ rgb + 1 ];
			tex[ i + 2 ] = _SIO2image0->tex[ rgb     ];
			tex[ i + 3 ] = _SIO2image1->tex[ a 	     ];
		
			++a;
			rgb += 3;
			i   += 4;
		}
		
		free( _SIO2image0->tex );
		_SIO2image0->tex = tex;
	}
}


void sio2ImageRGBAtoBGRA( SIO2image *_SIO2image )
{
	unsigned int i = 0,
				 s = _SIO2image->width  *
					 _SIO2image->height *
					 _SIO2image->bits;
	
	unsigned char t;

	while( i != s )
	{
		t = _SIO2image->tex[ i ];
		
		_SIO2image->tex[ i ] = _SIO2image->tex[ i + 2 ];
		
		_SIO2image->tex[ i + 2 ] = t;
	
		i += _SIO2image->bits;
	}
}


void sio2ImageRender( SIO2image *_SIO2image )
{
	glBindTexture( GL_TEXTURE_2D, _SIO2image->tid );
}


void sio2ImageBlur( SIO2image *_SIO2image )
{
	unsigned int i = 1,
				 j,
				 w  = _SIO2image->width  - 1,
				 h  = _SIO2image->height - 1,
				 bw = _SIO2image->width * _SIO2image->bits;

	if( _SIO2image->bits < 3 )
	{ return; }
	
	while( i != h )
	{
		j = 1;
		while( j < w )
		{
			unsigned int jb   =   j       * _SIO2image->bits,
						 jp   = ( j + 1 ) * _SIO2image->bits,
						 jm   = ( j - 1 ) * _SIO2image->bits,
						 ib   =   i       * bw,
						 im   = ( i - 1 ) * bw,
						 ip   = ( i + 1 ) * bw,
						 ibjb = ib + jb;
						 
			unsigned char *px1 = &_SIO2image->tex[ ib + jb ],
						  *px2 = &_SIO2image->tex[ ib + jm ],
						  *px3 = &_SIO2image->tex[ ib + jp ],
						  *px4 = &_SIO2image->tex[ im + jb ],
						  *px5 = &_SIO2image->tex[ ip + jb ],
						  *px6 = &_SIO2image->tex[ im + jm ],
						  *px7 = &_SIO2image->tex[ im + jp ],
						  *px8 = &_SIO2image->tex[ ip + jm ],
						  *px9 = &_SIO2image->tex[ ip + jp ];
			
			_SIO2image->tex[ ibjb     ] = ( ( px1[ 0 ] << 2 ) +
										  ( ( px2[ 0 ] + px3[ 0 ] + px4[ 0 ] + px5[ 0 ] ) << 1 ) +
										 	  px6[ 0 ] + px7[ 0 ] + px8[ 0 ] + px9[ 0 ] ) >> 4;

			_SIO2image->tex[ ibjb + 1 ] = ( ( px1[ 1 ] << 2 ) +
										  ( ( px2[ 1 ] + px3[ 1 ] + px4[ 1 ] + px5[ 1 ] ) << 1 ) +
										      px6[ 1 ] + px7[ 1 ] + px8[ 1 ] + px9[ 1 ] ) >> 4;

			_SIO2image->tex[ ibjb + 2 ] = ( ( px1[ 2 ] << 2 ) +
										  ( ( px2[ 2 ] + px3[ 2 ] + px4[ 2 ] + px5[ 2 ] ) << 1 ) +
										      px6[ 2 ] + px7[ 2 ] + px8[ 2 ] + px9[ 2 ] ) >> 4;
			++j;
		}
		
		++i;
	}
}
