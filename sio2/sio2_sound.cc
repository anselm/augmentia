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


SIO2sound *sio2SoundInit( char *_name )
{
	SIO2sound *_SIO2sound = ( SIO2sound * ) calloc( 1, sizeof( SIO2sound ) );
	
	sio2StringCpy( _SIO2sound->name, _name );

	sio2ResourceAdd( sio2->_SIO2resource,
					 SIO2_SOUND,
					 ( void * )_SIO2sound );

	return _SIO2sound;
}


SIO2sound *sio2SoundFree( SIO2sound *_SIO2sound )
{
	//sio2SoundStop( _SIO2sound );

	alSourcei( _SIO2sound->sid, AL_BUFFER, 0 );
	
	alDeleteSources( 1, &_SIO2sound->sid );

	sio2ResourceDel( sio2->_SIO2resource,
					 SIO2_SOUND,
					 (void *)_SIO2sound );	

	free( _SIO2sound );
	
	
	#ifdef SIO2_DEBUG_AL

		sio2ErrorAL( __FILE__, __FUNCTION__, __LINE__ );
	#endif	
	
	return NULL;
}


void sio2SoundGenId( SIO2sound		  *_SIO2sound,
					  SIO2soundbuffer *_SIO2soundbuffer,
					  unsigned int	   _flags )
{
	_SIO2sound->flags = _flags;
	_SIO2sound->_SIO2soundbuffer = _SIO2soundbuffer;

	alGenSources( 1, &_SIO2sound->sid );
	
	sio2SoundSetDefault( _SIO2sound );
	
	if( sio2IsStateEnabled( _SIO2sound->flags, SIO2_SOUND_STREAM ) )
	{	
		alSourceQueueBuffers( _SIO2sound->sid,
							  SIO2_SOUND_BUFFER,
							  _SIO2soundbuffer->bid );
	}
	else
	{ alSourcei( _SIO2sound->sid, AL_BUFFER, _SIO2soundbuffer->bid[ 0 ] ); }
	
	#ifdef SIO2_DEBUG_AL

		sio2ErrorAL( __FILE__, __FUNCTION__, __LINE__ );
	#endif		
}


void sio2SoundSetAmbient( SIO2sound *_SIO2sound )
{
	if( sio2IsStateEnabled( _SIO2sound->flags, SIO2_SOUND_FX ) )
	{ sio2DisableState( &_SIO2sound->flags, SIO2_SOUND_FX ); }
	
	sio2EnableState( &_SIO2sound->flags, SIO2_SOUND_AMBIENT ); 

	sio2SoundSetDefault( _SIO2sound );
}


void sio2SoundSetFx( SIO2sound *_SIO2sound,
					 vec3	   *_pos,
					 float		_rad )
{
	if( sio2IsStateEnabled( _SIO2sound->flags, SIO2_SOUND_AMBIENT ) )
	{ sio2DisableState( &_SIO2sound->flags, SIO2_SOUND_AMBIENT ); }
	
	sio2EnableState( &_SIO2sound->flags, SIO2_SOUND_FX );

    alSourcei( _SIO2sound->sid, AL_SOURCE_RELATIVE, AL_FALSE );
	alSourcef( _SIO2sound->sid, AL_REFERENCE_DISTANCE, _rad );
	
	alSource3f( _SIO2sound->sid,
				AL_POSITION,
				_pos->x,
				_pos->y,
				_pos->z );
				
	#ifdef SIO2_DEBUG_AL

		sio2ErrorAL( __FILE__, __FUNCTION__, __LINE__ );
	#endif	
}


void sio2SoundSetDefault( SIO2sound *_SIO2sound )
{
	static ALfloat d[ 3 ] = { 0.0f, 0.0f, 0.0f };

    alSource3f( _SIO2sound->sid, AL_POSITION, d[ 0 ], d[ 1 ], d[ 2 ] );

    alSource3f( _SIO2sound->sid, AL_VELOCITY, d[ 0 ], d[ 1 ], d[ 2 ] );
	
    alSource3f( _SIO2sound->sid, AL_DIRECTION, d[ 0 ], d[ 1 ], d[ 2 ] );
	
    alSourcef( _SIO2sound->sid, AL_ROLLOFF_FACTOR, 1.0f );
	
    alSourcei( _SIO2sound->sid, AL_SOURCE_RELATIVE, AL_TRUE );
	
	alSourcef( _SIO2sound->sid, AL_GAIN, 0.0f );
	
	alSourcef( _SIO2sound->sid, AL_PITCH, 1.0f ); 
	
	#ifdef SIO2_DEBUG_AL

		sio2ErrorAL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}


void sio2SoundPlay( SIO2sound *_SIO2sound )
{
	unsigned char loop =  sio2IsStateEnabled( _SIO2sound->flags, SIO2_SOUND_LOOP ) &&
						 !sio2IsStateEnabled( _SIO2sound->flags, SIO2_SOUND_STREAM ) ? 1 : 0;

	_SIO2sound->state = SIO2_PLAY;
	
	alSourcei( _SIO2sound->sid, AL_LOOPING, loop );
	
	alSourcePlay( _SIO2sound->sid );
	
	#ifdef SIO2_DEBUG_AL

		sio2ErrorAL( __FILE__, __FUNCTION__, __LINE__ );
	#endif	
}


void sio2SoundPause( SIO2sound *_SIO2sound )
{
	_SIO2sound->state = SIO2_PAUSE;
	
	alSourcePause( _SIO2sound->sid ); 
	
	#ifdef SIO2_DEBUG_AL

		sio2ErrorAL( __FILE__, __FUNCTION__, __LINE__ );
	#endif		
}


void sio2SoundStop( SIO2sound *_SIO2sound )
{
	_SIO2sound->state = SIO2_STOP;
	
	alSourceStop( _SIO2sound->sid );

	#ifdef SIO2_DEBUG_AL

		sio2ErrorAL( __FILE__, __FUNCTION__, __LINE__ );
	#endif		
}


void sio2SoundSetSpeed( SIO2sound *_SIO2sound,
						float	   _speed )
{
	alSourcef( _SIO2sound->sid, AL_PITCH, _speed ); 

	#ifdef SIO2_DEBUG_AL

		sio2ErrorAL( __FILE__, __FUNCTION__, __LINE__ );
	#endif	
}


void sio2SoundSetVolume( SIO2sound *_SIO2sound,
						 float		_volume )
{
	alSourcef( _SIO2sound->sid, AL_GAIN, _volume );

	#ifdef SIO2_DEBUG_AL

		sio2ErrorAL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}


void sio2SoundRewind( SIO2sound *_SIO2sound )
{
	alSourceRewind( _SIO2sound->sid );

	#ifdef SIO2_DEBUG_AL

		sio2ErrorAL( __FILE__, __FUNCTION__, __LINE__ );
	#endif	
}


void sio2SoundUpdateState( SIO2sound *_SIO2sound )
{
	int state = 0;
	
	if( sio2IsStateEnabled( _SIO2sound->flags, SIO2_SOUND_STREAM ) )
	{ return; }
	
	alGetSourcei( _SIO2sound->sid, AL_SOURCE_STATE, &state );

	switch( state )
	{
		case AL_PLAYING:
		{ _SIO2sound->state = SIO2_PLAY; break; }

		case AL_PAUSED:
		{ _SIO2sound->state = SIO2_PAUSE; break; }
		
		case AL_STOPPED:
		{ _SIO2sound->state = SIO2_STOP; break; }
	}

	#ifdef SIO2_DEBUG_AL

		sio2ErrorAL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}


void sio2SoundUpdateStream( SIO2sound *_SIO2sound )
{
	int p = 0,
		q = 0;

	if( _SIO2sound->state != SIO2_PLAY || !sio2IsStateEnabled( _SIO2sound->flags, SIO2_SOUND_STREAM ) )
	{ return; }


    alGetSourcei( _SIO2sound->sid, AL_BUFFERS_PROCESSED, &p );
	alGetSourcei( _SIO2sound->sid, AL_BUFFERS_QUEUED   , &q );
	
	
	while( p-- )
    {
        alSourceUnqueueBuffers( _SIO2sound->sid,
								1,
								&_SIO2sound->_SIO2soundbuffer->curr );

		if( sio2SoundBufferStream( _SIO2sound->_SIO2soundbuffer,
								   _SIO2sound->_SIO2soundbuffer->curr ) )
		{
			alSourceQueueBuffers( _SIO2sound->sid,
								  1,
								  &_SIO2sound->_SIO2soundbuffer->curr );
		}
    }

	
	if( !q )
	{
		unsigned int i = 0,
					 j = 0;
		
		_SIO2sound->_SIO2soundbuffer->_SIO2stream->pos = 0;

		while( i != SIO2_SOUND_BUFFER )
		{
			if( _SIO2sound->_SIO2soundbuffer->curr == _SIO2sound->_SIO2soundbuffer->bid[ i ] )
			{
				sio2SoundBufferStream( _SIO2sound->_SIO2soundbuffer, _SIO2sound->_SIO2soundbuffer->bid[ i ] );
				alSourceQueueBuffers( _SIO2sound->sid, 1, &_SIO2sound->_SIO2soundbuffer->bid[ i ] );
				
				while( j != SIO2_SOUND_BUFFER )
				{
					if( j != i )
					{
						sio2SoundBufferStream( _SIO2sound->_SIO2soundbuffer, _SIO2sound->_SIO2soundbuffer->bid[ j ] );
						alSourceQueueBuffers( _SIO2sound->sid, 1, &_SIO2sound->_SIO2soundbuffer->bid[ j ] );
					}
					
					++j;
				}
				
				break;
			}

			++i;
		}

		if( !sio2IsStateEnabled( _SIO2sound->flags, SIO2_SOUND_LOOP ) )
		{ sio2SoundStop( _SIO2sound ); }
		else
		{ sio2SoundPlay( _SIO2sound ); }
	}
	
	
	#ifdef SIO2_DEBUG_AL

		sio2ErrorAL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}
