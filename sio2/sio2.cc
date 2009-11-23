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

#ifndef SIO2_WRAP_C
#define SIO2_WRAP_C

	#include "../lua/sio2_wrap.c"
#endif

SIO2 *sio2 = NULL;

void sio2InitGL( void )
{
	glDepthFunc ( GL_LEQUAL );
	glCullFace  ( GL_BACK 	);
	glFrontFace ( GL_CCW 	);
	
	glShadeModel( GL_SMOOTH );
	
	glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
	glHint( GL_GENERATE_MIPMAP_HINT		  , GL_NICEST );
	glHint( GL_FOG_HINT				      , GL_NICEST );

	sio2StateEnable( sio2->_SIO2state, SIO2_DEPTH_TEST	 );
	sio2StateEnable( sio2->_SIO2state, SIO2_CULL_FACE	 );
	sio2StateEnable( sio2->_SIO2state, SIO2_VERTEX_ARRAY );
	
	glTexEnvi( GL_POINT_SPRITE_OES, GL_COORD_REPLACE_OES, GL_TRUE );
		
	printf("\nGL_VENDOR:          %s\n", ( char * )glGetString ( GL_VENDOR     ) );
	printf("GL_RENDERER:        %s\n"  , ( char * )glGetString ( GL_RENDERER   ) );
	printf("GL_VERSION:         %s\n"  , ( char * )glGetString ( GL_VERSION    ) );
	printf("GL_EXTENSIONS:      %s\n"  , ( char * )glGetString ( GL_EXTENSIONS ) );
	
	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
	
	glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT );
}


void sio2InitAL( void )
{
	sio2->device = alcOpenDevice( NULL );
	
	sio2->context = alcCreateContext( sio2->device, NULL );
    
	alcMakeContextCurrent( sio2->context );

	printf("\nAL_VENDOR:          %s\n", ( char * )alGetString ( AL_VENDOR     ) );
	printf("AL_RENDERER:        %s\n"  , ( char * )alGetString ( AL_RENDERER   ) );
	printf("AL_VERSION:         %s\n"  , ( char * )alGetString ( AL_VERSION    ) );
	printf("AL_EXTENSIONS:      %s\n"  , ( char * )alGetString ( AL_EXTENSIONS ) );	

	sio2->_ov_callbacks.read_func  = sio2OggRead;
	sio2->_ov_callbacks.seek_func  = sio2OggSeek;
	sio2->_ov_callbacks.tell_func  = sio2OggTell;
	sio2->_ov_callbacks.close_func = sio2OggClose;
	
	#ifdef SIO2_DEBUG_AL

		sio2ErrorAL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}


void sio2ErrorGL( const char   *_fname, 
				  const char   *_funct,
				  unsigned int  _line )
{
	char tmp[ SIO2_MAX_PATH ] = {""};
	
	unsigned int error;
						 					
	while( ( error = glGetError() ) != GL_NO_ERROR )	
	{											 		
		char str[ SIO2_MAX_CHAR ]={""};				
		
		switch( error )
		{			
			case GL_INVALID_ENUM:
			{
				sio2StringCpy( str, "GL_INVALID_ENUM" );
				break;
			}
													
			case GL_INVALID_VALUE:
			{
				sio2StringCpy( str, "GL_INVALID_VALUE:" );
				break;
			}
			
			case GL_INVALID_OPERATION:
			{
				sio2StringCpy( str, "GL_INVALID_OPERATION" );
				break;
			}
			
			case GL_STACK_OVERFLOW:
			{
				sio2StringCpy( str, "GL_STACK_OVERFLOW" );
				break;
			}
			
			case GL_STACK_UNDERFLOW:
			{
				sio2StringCpy( str, "GL_STACK_UNDERFLOW" );
				break;
			}			
			
			case GL_OUT_OF_MEMORY:
			{
				sio2StringCpy( str, "GL_OUT_OF_MEMORY" );
				break;
			}
		}
		
		sprintf( tmp, "GL_ERROR: %s %s(%d):%s",			
				 str, _fname, _line, _funct );						

		printf( "%s\n", tmp );
	}
}


void sio2ErrorAL( const char   *_fname, 
			 	  const char   *_funct,
				  unsigned int  _line )
{
	char tmp[ SIO2_MAX_PATH ] = {""};
	
	unsigned int error;
						 					
	while( ( error = alGetError() ) != AL_NO_ERROR )	
	{											 		
		char str[ SIO2_MAX_CHAR ]={""};				
		
		switch( error )									
		{												
			case AL_INVALID_NAME:						
			{											
				sio2StringCpy( str, "AL_INVALID_NAME" );
				break;									
			}
													
			case AL_INVALID_ENUM:						
			{											
				sio2StringCpy( str, "AL_INVALID_ENUM" );
				break;									
			}	
													
			case AL_INVALID_VALUE:
			{
				sio2StringCpy( str, "AL_INVALID_VALUE" );
				break;
			}
			
			case AL_INVALID_OPERATION:
			{											
				sio2StringCpy( str, "AL_INVALID_OPERATION" );
				break;
			}
													
			case AL_OUT_OF_MEMORY:						
			{											
				sio2StringCpy( str, "AL_OUT_OF_MEMORY" );
				break;
			}																							
		}
		
		sprintf( tmp, "AL_ERROR: %s %s(%d):%s",			
				 str, _fname, _line, _funct );						

		printf( "%s\n", tmp );
	}
}


void sio2Error( const char   *_fname, 
				const char   *_funct,
				unsigned int  _line,
				char		 *_msg )
{
	char tmp[ SIO2_MAX_PATH ] = {""};
	
	sprintf( tmp, "ERROR: %s(%d):%s [ %s ]",	
			 _fname, _line, _funct, _msg );						

	printf( "%s\n", tmp );
}


void sio2InitLUA( void )
{
	printf("\nLUA_VENDOR:         Lua.org\n" );
	printf("LUA_VERSION:        %s\n", LUA_RELEASE );
	printf("LUA_MODULE:         " );


	sio2->_lua_State = lua_open();
	luaL_Reg *lib = ( luaL_Reg * )luaL_openlibs( sio2->_lua_State );
		
	while( lib->func )
	{
		if( sio2StringLen( lib->name ) )
		{
			char tmp[ SIO2_MAX_CHAR ] = {""};
			
			sio2StringCpy( tmp, lib->name );
			sio2StringToUpper( tmp );
			printf("%s ", tmp );
		}
		else
		{ printf("DEFAULT " ); }
		
		++lib;
	}

	luaopen_SIO2( sio2->_lua_State );
	printf("%s\n", SWIG_name );
}


int sio2ExecLUA( char *_code )
{
	int err = luaL_dostring( sio2->_lua_State, _code );
	
	if( err )
	{
		printf( "[ ERROR ] %d:%s.\n-> %s\n",
				err,
				lua_tostring( sio2->_lua_State, -1 ),
				_code );
				
		lua_pop( sio2->_lua_State, 1 );
	}
	
	return err;
}


void sio2ResetState( void )
{
	unsigned int i = 0;
	
	while( i != SIO2_MATERIAL_NCHANNEL )
	{
		sio2->_SIO2image[ i ] = NULL;
		++i;
	}
	
	sio2->_SIO2camera	   = NULL;
	sio2->_SIO2object	   = NULL;
	sio2->_SIO2lamp		   = NULL;
	sio2->_SIO2vertexgroup = NULL;
	sio2->_SIO2material	   = NULL;
	sio2->_SIO2font		   = NULL;
	sio2->_SIO2ipo		   = NULL;
	sio2->_SIO2ipocurve	   = NULL;
	sio2->_SIO2action      = NULL;
}

void sio2ResetListener( void )
{
	static float o[ 6 ] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f };

	alListener3f( AL_POSITION, 0.0f, 0.0f, 0.0f );
		
	alListenerfv( AL_ORIENTATION, o );
	
	#ifdef SIO2_DEBUG_AL

		sio2ErrorAL( __FILE__, __FUNCTION__, __LINE__ );
	#endif	
}


void sio2ShutdownAL( void )
{
	alcMakeContextCurrent( NULL );

	alcDestroyContext( sio2->context );
		
	alcCloseDevice( sio2->device );
	
	#ifdef SIO2_DEBUG_AL

		sio2ErrorAL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}


void sio2ShutdownLUA( void )
{
	if( sio2->_lua_State )
	{
		lua_close( sio2->_lua_State );
		sio2->_lua_State = NULL;
	}
}


void sio2ResetLUA( void )
{
	sio2ShutdownLUA();
		
	sio2->_lua_State = lua_open();
	
	luaL_openlibs( sio2->_lua_State );

	luaopen_SIO2( sio2->_lua_State );
}


void sio2InitWidget( void )
{
	float w0[ 16 ] = { 0.0f, 0.0f,
					   1.0f, 0.0f,
					   1.0f, 1.0f,
					   0.0f, 1.0f,
					   0.0f, 1.0f,
					   1.0f, 1.0f,
					   1.0f, 0.0f,
					   0.0f, 0.0f };
								   
	float w1[ 16 ] = { -0.5f, -0.5f,
						0.5f, -0.5f,
						0.5f,  0.5f,
					   -0.5f,  0.5f,
						0.0f, 1.0f,
						1.0f, 1.0f,
						1.0f, 0.0f,
						0.0f, 0.0f };
	
	glGenBuffers( 2, &sio2->wid[ 0 ] );

	glBindBuffer( GL_ARRAY_BUFFER, sio2->wid[ 0 ] );

	glBufferData( GL_ARRAY_BUFFER,
				  64,
				  &w0[ 0 ],
				  GL_STATIC_DRAW );

	glBindBuffer( GL_ARRAY_BUFFER, sio2->wid[ 1 ] );

	glBufferData( GL_ARRAY_BUFFER,
				  64,
				  &w1[ 0 ],
				  GL_STATIC_DRAW );				  
}


void sio2ShutdownWidget( void )
{
	glDeleteBuffers( 2, &sio2->wid[ 0 ] );
}


bool sio2PhysicCollisionCallback( btManifoldPoint &cp,
								  const btCollisionObject *colObj0,int partId0, int index0, 
								  const btCollisionObject *colObj1,int partId1, int index1 )
{
	unsigned int i = 0;
	
	while( i != sio2->_SIO2resource->n_sensor )
	{
		SIO2sensor *_SIO2sensor = ( SIO2sensor * )sio2->_SIO2resource->_SIO2sensor[ i ];
	
		if( _SIO2sensor->_SIO2sensorcollision )
		{
			if( ( _SIO2sensor->_SIO2object0->_SIO2objectphysic->_btRigidBody == btRigidBody::upcast( colObj0 ) ||
				  _SIO2sensor->_SIO2object0->_SIO2objectphysic->_btRigidBody == btRigidBody::upcast( colObj1 ) )
				  &&
				( _SIO2sensor->_SIO2object1->_SIO2objectphysic->_btRigidBody == btRigidBody::upcast( colObj0 ) ||
				  _SIO2sensor->_SIO2object1->_SIO2objectphysic->_btRigidBody == btRigidBody::upcast( colObj1 ) ) )
			{ _SIO2sensor->_SIO2sensorcollision( _SIO2sensor ); }
		}
		else if( _SIO2sensor->_SIO2sensorcontact )
		{
			_SIO2sensor->_SIO2object0 = ( SIO2object * )btRigidBody::upcast( colObj0 )->getUserPointer();
			_SIO2sensor->_SIO2object1 = ( SIO2object * )btRigidBody::upcast( colObj1 )->getUserPointer();
			
			_SIO2sensor->_SIO2sensorcontact( _SIO2sensor );
			
			_SIO2sensor->_SIO2object0 = NULL;
			_SIO2sensor->_SIO2object1 = NULL;
		}
	
		++i;
	}

	return false;
}


size_t sio2OggRead( void   *_ptr,
					size_t  _size,
					size_t  _read,
					void   *_SIO2stream )
{
	unsigned int seof,
				 pos;
			
	SIO2stream *ptr = ( SIO2stream * )_SIO2stream;

	seof = ptr->size - ptr->pos;
	
	if( ( _read * _size ) < seof )
	{ pos = _read * _size; }
	else
	{ pos = seof; }

	
	if( pos )
	{
		memcpy( _ptr, ptr->buf + ptr->pos, pos );
		ptr->pos += pos;
	}

	return pos;
}


int sio2OggSeek( void		 *_SIO2stream,
				 ogg_int64_t  _offset, 
				 int		  _stride )
{
	unsigned int pos;
	
	SIO2stream *ptr = ( SIO2stream * )_SIO2stream;

	switch( _stride )
	{
		case SEEK_SET:
		{
			if( ptr->size >= _offset )
			{ pos = ( unsigned int )_offset; }
			else
			{ pos = ptr->size; }

			ptr->pos = pos;
			
			break;
		}
		
		case SEEK_CUR:
		{
			unsigned int seof = ptr->size - ptr->pos;
			
			if( _offset < seof )
			{ pos = ( unsigned int )_offset; }
			else
			{ pos = seof; }
		
			ptr->pos += pos;
			
			break;
		}

		case SEEK_END:
		{
			ptr->pos = ptr->size + 1;
			
			break;
		}
	};

	return 0;
}

