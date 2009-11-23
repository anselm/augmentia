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


SIO2emitter *sio2EmitterInit( char *_name )
{
	SIO2emitter *_SIO2emitter = ( SIO2emitter * ) calloc( 1, sizeof( SIO2emitter ) );

	sio2StringCpy( _SIO2emitter->name, _name );

	_SIO2emitter->att = sio2Vec3Init();
	
	_SIO2emitter->dst = 1.0f;
	
	_SIO2emitter->_SIO2transform = sio2TransformInit();
	
	sio2ResourceAdd( sio2->_SIO2resource,
					 SIO2_EMITTER,
					 ( void * )_SIO2emitter );
	
	return _SIO2emitter;
}


SIO2emitter *sio2EmitterFree( SIO2emitter *_SIO2emitter )
{
	_SIO2emitter->att = sio2Vec3Free( _SIO2emitter->att );
	
	_SIO2emitter->_SIO2transform = sio2TransformFree( _SIO2emitter->_SIO2transform );
	
	sio2EmitterResetParticles( _SIO2emitter );
	
	sio2ResourceDel( sio2->_SIO2resource,
					 SIO2_EMITTER,
					 (void *)_SIO2emitter );
		
	free( _SIO2emitter );
	
	return NULL;
}


void sio2EmitterCreate( SIO2emitter			 *_SIO2emitter,
						SIO2material		 *_SIO2material,
						SIO2particlecreation *_SIO2particlecreation,
						SIO2particlerender	 *_SIO2particlerender,
						vec3				 *_loc,
						vec3				 *_dir,
						vec3				 *_att,
						unsigned int		  _maxp,
						float				  _pps,
						float				  _rad )

{
	_SIO2emitter->_SIO2material			= _SIO2material;
	_SIO2emitter->_SIO2particlecreation = _SIO2particlecreation;
	_SIO2emitter->_SIO2particlerender   = _SIO2particlerender;

	memcpy( _SIO2emitter->_SIO2transform->loc, _loc, 12 );
	memcpy( _SIO2emitter->_SIO2transform->dir, _dir, 12 );
	memcpy( _SIO2emitter->att, _att, 12 );

	_SIO2emitter->maxp = _maxp;
	_SIO2emitter->pps  = _pps;
	_SIO2emitter->rad  = _rad;
		
	sio2EmitterSetupParticles( _SIO2emitter );
	
	sio2TransformBindMatrix( _SIO2emitter->_SIO2transform );
	
	glPointParameterfv( GL_POINT_DISTANCE_ATTENUATION, ( float * )_SIO2emitter->att );
}


void sio2EmitterSetupParticles( SIO2emitter *_SIO2emitter )
{
	unsigned int i = 0;
	
	_SIO2emitter->_SIO2particle = ( SIO2particle ** ) malloc( _SIO2emitter->maxp * sizeof( SIO2particle ) );
	
	while( i != _SIO2emitter->maxp )
	{
		_SIO2emitter->_SIO2particle[ i ] = sio2ParticleInit();
		++i;
	}
}


void sio2EmitterResetParticles( SIO2emitter *_SIO2emitter )
{
	unsigned int i = 0;
	
	while( i != _SIO2emitter->maxp )
	{
		_SIO2emitter->_SIO2particle[ i ] = sio2ParticleFree( _SIO2emitter->_SIO2particle[ i ] );
		++i;
	}
	
	free( _SIO2emitter->_SIO2particle );
	_SIO2emitter->_SIO2particle = NULL;
}


void sio2EmitterRender( SIO2emitter	  *_SIO2emitter,
						SIO2window    *_SIO2window,
						unsigned char  _usematrix )
{
	unsigned int i = 0,
				 j = 0,
				 n_particle;

	if( _SIO2emitter->dst < 0.0f )
	{ return; }


	if( _SIO2emitter->state == SIO2_PLAY )
	{
		_SIO2emitter->sync_time += _SIO2window->d_time;
		
		if( _SIO2emitter->sync_time >= _SIO2emitter->pps )
		{
			n_particle = ( unsigned int )( _SIO2emitter->sync_time / _SIO2emitter->pps );

			_SIO2emitter->sync_time = 0.0f;

			if( _SIO2emitter->n_particle != _SIO2emitter->maxp )
			{			
				while( i != n_particle )
				{
					while( j != _SIO2emitter->maxp )
					{
						if( !_SIO2emitter->_SIO2particle[ j ]->lifetime )
						{
							if( _SIO2emitter->_SIO2particlecreation )
							{ _SIO2emitter->_SIO2particlecreation( _SIO2emitter, _SIO2emitter->_SIO2particle[ j ] ); }
						
							++_SIO2emitter->n_particle;
							
							break;
						}
						
						++j;
					}
					
					++i;
				}
			}
		}
	}

	glDepthMask( GL_FALSE );

	
	sio2StateEnable( sio2->_SIO2state, SIO2_VERTEX_ARRAY	 );
	sio2StateEnable( sio2->_SIO2state, SIO2_POINT_SPRITE	 );
	sio2StateEnable( sio2->_SIO2state, SIO2_COLOR_ARRAY		 );
	sio2StateEnable( sio2->_SIO2state, SIO2_POINT_SIZE_ARRAY );

	sio2MaterialRender( _SIO2emitter->_SIO2material );


	if( _SIO2emitter->_SIO2ipo && _SIO2emitter->_SIO2ipo->state == SIO2_PLAY )
	{
		sio2TransformSetLoc( _SIO2emitter->_SIO2transform,
							 _SIO2emitter->_SIO2ipo->_SIO2transform->loc );

		sio2TransformSetRot( _SIO2emitter->_SIO2transform,
							 _SIO2emitter->_SIO2ipo->_SIO2transform->rot );

		sio2TransformSetScl( _SIO2emitter->_SIO2transform,
							 _SIO2emitter->_SIO2ipo->_SIO2transform->scl );
							 
		sio2TransformSetMatrix( _SIO2emitter->_SIO2transform,
							    _SIO2emitter->_SIO2ipo->_SIO2transform->mat );
	}


	glPushMatrix();
	{
		switch( _usematrix )
		{
			case SIO2_TRANSFORM_MATRIX_APPLY:
			{ sio2TransformApply( _SIO2emitter->_SIO2transform ); break; }

			case SIO2_TRANSFORM_MATRIX_BIND:
			{ sio2TransformRender( _SIO2emitter->_SIO2transform ); break; }
		}


		i = 0;
		while( i != _SIO2emitter->maxp )
		{
			if( _SIO2emitter->_SIO2particle[ i ]->lifetime )
			{
				if( _SIO2emitter->state == SIO2_PLAY )
				{
					_SIO2emitter->_SIO2particle[ i ]->lifetime -= _SIO2window->d_time;

					if( _SIO2emitter->_SIO2particle[ i ]->lifetime < 0.0f )
					{
						_SIO2emitter->_SIO2particle[ i ]->lifetime = 0.0f;
						
						--_SIO2emitter->n_particle;
						
						++i;
						continue;
					}
					
					if( _SIO2emitter->_SIO2particlerender )
					{ _SIO2emitter->_SIO2particlerender( _SIO2emitter, _SIO2emitter->_SIO2particle[ i ] ); }
				}

				glVertexPointer( 3, GL_FLOAT, 0, _SIO2emitter->_SIO2particle[ i ]->loc );
				
				glColorPointer ( 4, GL_FLOAT, 0, _SIO2emitter->_SIO2particle[ i ]->col );
				
				glPointSizePointerOES( GL_FLOAT, 0, &_SIO2emitter->_SIO2particle[ i ]->size );
				
				glDrawArrays( GL_POINTS, 0, 1 );
			}
			
			++i;
		}
		glPopMatrix();
	}
}


void sio2EmitterReset( void )
{
	glBindBuffer( GL_ARRAY_BUFFER, 0 );

	sio2StateDisable( sio2->_SIO2state, SIO2_COLOR_ARRAY );
	sio2StateDisable( sio2->_SIO2state, SIO2_POINT_SIZE_ARRAY );
	sio2StateDisable( sio2->_SIO2state, SIO2_POINT_SPRITE );
	
	glDepthMask( GL_TRUE );
}


void sio2EmitterPlay( SIO2emitter *_SIO2emitter )
{ _SIO2emitter->state = SIO2_PLAY; }


void sio2EmitterPause( SIO2emitter *_SIO2emitter )
{ _SIO2emitter->state = SIO2_PAUSE; }


void sio2EmitterStop( SIO2emitter *_SIO2emitter ) 
{ _SIO2emitter->state = SIO2_STOP; }
