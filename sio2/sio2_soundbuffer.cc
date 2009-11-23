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


SIO2soundbuffer *sio2SoundBufferInit( char *_name )
{
	SIO2soundbuffer *_SIO2soundbuffer = ( SIO2soundbuffer * ) calloc( 1, sizeof( SIO2soundbuffer ) );
	
	sio2StringCpy( _SIO2soundbuffer->name, _name );

	sio2ResourceAdd( sio2->_SIO2resource,
					 SIO2_SOUNDBUFFER,
					 ( void * )_SIO2soundbuffer );

	return _SIO2soundbuffer;
}


SIO2soundbuffer *sio2SoundBufferFree( SIO2soundbuffer *_SIO2soundbuffer )
{
	if( !_SIO2soundbuffer->_SIO2stream )
	{ alDeleteBuffers( 1, &_SIO2soundbuffer->bid[ 0 ] ); }
	else
	{
		_SIO2soundbuffer->_SIO2stream = sio2StreamClose( _SIO2soundbuffer->_SIO2stream );
		
		alDeleteBuffers( SIO2_SOUND_BUFFER, &_SIO2soundbuffer->bid[ 0 ] );
		
		sio2OggClose( _SIO2soundbuffer->_SIO2stream );
		
		ov_clear( &_SIO2soundbuffer->_OggVorbis_File );
	}
	
	sio2ResourceDel( sio2->_SIO2resource,
					 SIO2_SOUNDBUFFER,
					 ( void * )_SIO2soundbuffer );	

	free( _SIO2soundbuffer );
	
	
	#ifdef SIO2_DEBUG_AL

		sio2ErrorAL( __FILE__, __FUNCTION__, __LINE__ );
	#endif	
	
	return NULL;
}


void sio2SoundBufferLoad( SIO2soundbuffer *_SIO2soundbuffer,
						  SIO2stream	  *_SIO2stream )
{ _SIO2soundbuffer->_SIO2stream = _SIO2stream; }


SIO2stream *sio2SoundBufferGenId( SIO2soundbuffer *_SIO2soundbuffer,
								  unsigned char	   _streamed )
{
	vorbis_info *_vorbis_info;

	ov_open_callbacks( _SIO2soundbuffer->_SIO2stream,
					   &_SIO2soundbuffer->_OggVorbis_File,
					   NULL,
					   0,
					   sio2->_ov_callbacks );

	_vorbis_info = ov_info( &_SIO2soundbuffer->_OggVorbis_File, -1 );
	
	if( _vorbis_info->channels == 1 )
	{ _SIO2soundbuffer->format = AL_FORMAT_MONO16; }
	else
	{ _SIO2soundbuffer->format = AL_FORMAT_STEREO16; }
	
	_SIO2soundbuffer->size = ( ( unsigned int )ov_pcm_total( &_SIO2soundbuffer->_OggVorbis_File, -1 ) * _vorbis_info->channels << 1 );
	_SIO2soundbuffer->rate = _vorbis_info->rate;
	
	if( !_streamed )
	{
		int cnt,
			bit;
		
		char *ptr = ( char * ) malloc( _SIO2soundbuffer->size );

		_SIO2soundbuffer->data = ptr;
		
		while( ( cnt = ov_read( &_SIO2soundbuffer->_OggVorbis_File,
								ptr,
								SIO2_SOUND_BUFFER_SIZE,
								0, 2, 1,
								&bit ) ) > 0 )
		{ ptr += cnt; }

		alGenBuffers( 1, &_SIO2soundbuffer->bid[ 0 ] );

		alBufferData( _SIO2soundbuffer->bid[ 0 ],
					  _SIO2soundbuffer->format,
					  _SIO2soundbuffer->data,
					  _SIO2soundbuffer->size,
					  _SIO2soundbuffer->rate );

		free( _SIO2soundbuffer->data );
		_SIO2soundbuffer->data = NULL;

		sio2OggClose( _SIO2soundbuffer->_SIO2stream ); 
		
		ov_clear( &_SIO2soundbuffer->_OggVorbis_File );
		
		_SIO2soundbuffer->_SIO2stream = sio2StreamClose( _SIO2soundbuffer->_SIO2stream );
	}
	else
	{
		unsigned int i = 0;
		
		alGenBuffers( SIO2_SOUND_BUFFER, _SIO2soundbuffer->bid );
		
		while( i != SIO2_SOUND_BUFFER )
		{
			sio2SoundBufferStream( _SIO2soundbuffer, _SIO2soundbuffer->bid[ i ] );
			++i;
		}	
	}
	
	
	#ifdef SIO2_DEBUG_AL

		sio2ErrorAL( __FILE__, __FUNCTION__, __LINE__ );
	#endif	
	
	return _SIO2soundbuffer->_SIO2stream;
}


unsigned char sio2SoundBufferStream( SIO2soundbuffer *_SIO2soundbuffer,
									 unsigned int	  _buffer )
{
	char pcm[ SIO2_SOUND_BUFFER_SIZE ] = {""};

	int  size = 0,
		 bit;

	while( size < SIO2_SOUND_BUFFER_SIZE )
	{
		int r = ov_read( &_SIO2soundbuffer->_OggVorbis_File,
						 pcm + size,
						 SIO2_SOUND_BUFFER_SIZE - size,
						 0, 2, 1,
						 &bit );
		if( r > 0 )
		{ size += r; }
		else
		{ break; }
	}


	if( !size )
	{ return 0; }

	alBufferData( _buffer, 
				  _SIO2soundbuffer->format,
				  pcm,
				  size,
				  _SIO2soundbuffer->rate );

	#ifdef SIO2_DEBUG_AL

		sio2ErrorAL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
				  
	return 1;
}
