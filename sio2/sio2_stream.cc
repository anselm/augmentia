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


SIO2stream *sio2StreamInit( const char *_fname )
{
	SIO2stream *_SIO2stream = ( SIO2stream * ) calloc( 1, sizeof( SIO2stream ) );

	sio2StringCpy( _SIO2stream->fname, _fname );

	return _SIO2stream;
}


SIO2stream *sio2StreamOpen( char		  *_fname,
							unsigned char  _rel )
{
	FILE *f;
	
	SIO2stream *_SIO2stream;
	
	if( _rel )
	{
		char fname[ SIO2_MAX_PATH ] = {""};
		sprintf( fname, "%s%s", sio2->app_path, _fname ); 
		
		f = fopen( fname, "rb" );
	}
	else
	{ f = fopen( _fname, "rb" ); }


	if( !f )
	{ return NULL; }
	
	_SIO2stream = ( SIO2stream * ) calloc( 1, sizeof( SIO2stream ) );

	sio2StringCpy( _SIO2stream->fname, _fname );


	fseek( f, 0, SEEK_END );
	_SIO2stream->size = ftell( f );
	fseek( f, 0, SEEK_SET );
	
	_SIO2stream->buf = ( unsigned char * ) malloc( _SIO2stream->size );
	fread( &_SIO2stream->buf[ 0 ], 1, _SIO2stream->size, f );
	
	_SIO2stream->cur = _SIO2stream->buf;
	
	fclose( f );

	return _SIO2stream;
}


SIO2stream *sio2StreamOpenText( char		  *_fname,
								unsigned char  _rel )
{
	SIO2stream *_SIO2stream = sio2StreamOpen( _fname, _rel );

	if( _SIO2stream )
	{
		_SIO2stream->buf = ( unsigned char * ) realloc( _SIO2stream->buf,
														_SIO2stream->size + 1 );
		_SIO2stream->buf[ _SIO2stream->size ] = 0;
	}
	
	return _SIO2stream;
}


SIO2stream *sio2StreamClose( SIO2stream *_SIO2stream )
{
	if( !_SIO2stream )
	{ return NULL; }
	
	if( _SIO2stream->buf )
	{
		free( _SIO2stream->buf );
		_SIO2stream->buf = NULL;
	}

	free( _SIO2stream );

	return NULL;
}


unsigned int sio2StreamRead( SIO2stream   *_SIO2stream,
						     void		  *_ptr,
						     unsigned int  _size_t )
{
	if( ( _SIO2stream->pos + _size_t ) > _SIO2stream->size )
	{ _size_t = _SIO2stream->size - _SIO2stream->pos; }

	memcpy( _ptr, &_SIO2stream->buf[ _SIO2stream->pos ], _size_t );
	_SIO2stream->pos += _size_t;

	return _size_t;
}


void *sio2StreamReadPtr( SIO2stream	*_SIO2stream,
						 unsigned int  _size_t )
{
	void *ptr;
	
	if( ( _SIO2stream->pos + _size_t ) > _SIO2stream->size )
	{ _size_t = _SIO2stream->size - _SIO2stream->pos; }


	ptr = &_SIO2stream->buf[ _SIO2stream->pos ];
	
	_SIO2stream->pos += _size_t;

	return ptr;
}


unsigned char sio2StreamEOF( SIO2stream *_SIO2stream )
{ return _SIO2stream->pos >= _SIO2stream->size ? 1 : 0; }


void sio2StreamParse( SIO2stream   *_SIO2stream,
					  unsigned int  _n_entry,
					  SIO2entry	   *_SIO2entry )
{
	unsigned int s;
	
	char *root	   = ( char * ) malloc( SIO2_MAX_CHAR ),
		 *tok	   = ( char * ) malloc( SIO2_MAX_CHAR ),
		 *val	   = ( char * ) malloc( SIO2_MAX_PATH ),
		 *root_ptr = root,
		 *tok_ptr  = tok;
	
	SIO2parsercallback *root_callback   = NULL,
					   *custom_callback = NULL;
	
	unsigned char *ptr = NULL,
				   state = 0;
	
	while( *_SIO2stream->cur )
	{
		if( *_SIO2stream->cur == 13 ||
			*_SIO2stream->cur == 10 ||
			*_SIO2stream->cur ==  9 ||
			*_SIO2stream->cur == 32 )
		{ goto next_char; }

		// (
		else if( *_SIO2stream->cur == 40 )
		{
			// )
			ptr = ( unsigned char * )sio2StringChr( ( char * )_SIO2stream->cur, 41 );

			s = ptr - _SIO2stream->cur;
			
			++_SIO2stream->cur;
			memcpy( val, _SIO2stream->cur, s );
			val[ s - 1 ] = 0;

			if( !state )
			{
				unsigned int i = 0;
				
				*root = 0;
				root = root_ptr;
				
				while( i != _n_entry )
				{
					if( !sio2StringCmp( root, _SIO2entry[ i ].str ) )
					{
						root_callback = _SIO2entry[ i ].root;
						custom_callback = _SIO2entry[ i ].custom;
						
						break;
					}
					++i;
				}
				
				if( i == _n_entry )
				{ goto cleanup; }
			}

			*tok = 0;
			tok  = tok_ptr;

			_SIO2stream->cur = ptr;
			
			if( !root_callback( root, tok, val ) && custom_callback )
			{ 
				if( !custom_callback( root, tok, val ) )
				{ goto cleanup; }
			}
		}
		
		// Comments /*
		else if( *_SIO2stream->cur == 47 && *( _SIO2stream->cur + 1 ) == 42 )
		{
			_SIO2stream->cur = ( unsigned char * )sio2StringTok( ( char * )_SIO2stream->cur, ( char * )"*/" );
			_SIO2stream->cur += 2;
			
			goto next_char;
		}
		
		// {
		else if( *_SIO2stream->cur == 123 )
		{ state = 1; }
		
		// }
		else if( *_SIO2stream->cur == 125 )
		{ state = 0; }

		// root
		else if( !state )
		{
			*root = *_SIO2stream->cur;
			++root;
		}
		
		// token
		else
		{
			*tok = *_SIO2stream->cur;
			++tok;
		}
		
next_char:

		++_SIO2stream->cur;
	}
	
cleanup:


	free( root_ptr );
	free( tok_ptr  );
	free( val      );
	
	root_ptr =
	tok_ptr  =
	val		 = NULL;
}