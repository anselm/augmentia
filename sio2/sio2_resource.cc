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


char *SIO2_RESOURCE_PATH[ SIO2_ARCHIVE_TYPE ] =
{
	"object/", "material/", "lamp/",
	"camera/", "image/"   , "sound/",
	"script/", "ipo/"
};


SIO2resource *sio2ResourceInit( char *_name )
{
	SIO2resource *_SIO2resource = ( SIO2resource * ) calloc( 1, sizeof( SIO2resource ) );

	sio2StringCpy( _SIO2resource->name, _name );

	return _SIO2resource;
}


SIO2resource *sio2ResourceFree( SIO2resource *_SIO2resource )
{
	if( _SIO2resource->_SIO2image )
	{
		free( _SIO2resource->_SIO2image );
		_SIO2resource->_SIO2image = NULL;
	}
	
	if( _SIO2resource->_SIO2widget )
	{
		free( _SIO2resource->_SIO2widget );
		_SIO2resource->_SIO2widget = NULL;
	}

	if( _SIO2resource->_SIO2camera )
	{
		free( _SIO2resource->_SIO2camera );
		_SIO2resource->_SIO2camera = NULL;
	}

	if( _SIO2resource->_SIO2material )
	{
		free( _SIO2resource->_SIO2material );
		_SIO2resource->_SIO2material = NULL;
	}

	if( _SIO2resource->_SIO2soundbuffer )
	{
		free( _SIO2resource->_SIO2soundbuffer );
		_SIO2resource->_SIO2soundbuffer = NULL;
	}

	if( _SIO2resource->_SIO2sound )
	{
		free( _SIO2resource->_SIO2sound );
		_SIO2resource->_SIO2sound = NULL;
	}
	
	if( _SIO2resource->_SIO2video )
	{
		free( _SIO2resource->_SIO2video );
		_SIO2resource->_SIO2video = NULL;
	}

	if( _SIO2resource->_SIO2object )
	{
		free( _SIO2resource->_SIO2object );
		_SIO2resource->_SIO2object = NULL;
	}

	if( _SIO2resource->_SIO2physic )
	{
		free( _SIO2resource->_SIO2physic );
		_SIO2resource->_SIO2physic = NULL;
	}

	if( _SIO2resource->_SIO2sensor )
	{
		free( _SIO2resource->_SIO2sensor );
		_SIO2resource->_SIO2sensor = NULL;
	}

	if( _SIO2resource->_SIO2emitter )
	{
		free( _SIO2resource->_SIO2emitter );
		_SIO2resource->_SIO2emitter = NULL;
	}

	if( _SIO2resource->_SIO2mist )
	{
		free( _SIO2resource->_SIO2mist );
		_SIO2resource->_SIO2mist = NULL;
	}

	if( _SIO2resource->_SIO2font )
	{
		free( _SIO2resource->_SIO2font );
		_SIO2resource->_SIO2font = NULL;
	}

	if( _SIO2resource->_SIO2lamp )
	{
		free( _SIO2resource->_SIO2lamp );
		_SIO2resource->_SIO2lamp = NULL;
	}

	if( _SIO2resource->_SIO2script )
	{
		free( _SIO2resource->_SIO2script );
		_SIO2resource->_SIO2script = NULL;
	}

	if( _SIO2resource->_SIO2ipo )
	{
		free( _SIO2resource->_SIO2ipo );
		_SIO2resource->_SIO2ipo = NULL;
	}
	
	if( _SIO2resource->_SIO2action )
	{
		free( _SIO2resource->_SIO2action );
		_SIO2resource->_SIO2action = NULL;
	}
	
	if( _SIO2resource->_SIO2timer )
	{
		free( _SIO2resource->_SIO2timer );
		_SIO2resource->_SIO2timer = NULL;
	}
		
	if( _SIO2resource->_SIO2entry )
	{
		free( _SIO2resource->_SIO2entry );
		_SIO2resource->_SIO2entry = NULL;
	}

	free( _SIO2resource );

	return NULL;
}


unsigned int sio2ResourceGetVRAMSize( SIO2resource *_SIO2resource )
{
	unsigned int i   = 0,
				 mem = 0;
	
	while( i != _SIO2resource->n_image )
	{
		SIO2image *_SIO2image = ( SIO2image * )_SIO2resource->_SIO2image[ i ];
	
		mem += _SIO2image->width * _SIO2image->height * _SIO2image->bits;	
	
		if( sio2IsStateEnabled( _SIO2image->flags, SIO2_IMAGE_MIPMAP ) )
		{
			unsigned int width   = _SIO2image->width,
						 height  = _SIO2image->height;
			
			while( width > 1 || height > 1 )
			{
				width  = ( unsigned int )( width  * 0.5f );
				height = ( unsigned int )( height * 0.5f );

				mem += width * height * _SIO2image->bits; 
			}
		}

		++i;
	}
	
	
	i = 0;
	while( i != _SIO2resource->n_object )
	{
		unsigned j = 0;
		
		SIO2object *_SIO2object = ( SIO2object * )_SIO2resource->_SIO2object[ i ];
		
		mem += _SIO2object->vbo_offset[ SIO2_OBJECT_SIZE ];
	
		while( j != _SIO2object->n_vgroup )
		{
			mem += _SIO2object->_SIO2vertexgroup[ j ]->n_ind << 1;
			++j;
		}
	
		++i;
	}
	

	i = 0;
	while( i != _SIO2resource->n_action )
	{
		SIO2action *_SIO2action = ( SIO2action * )_SIO2resource->_SIO2action[ i ];
		
		mem += _SIO2action->s_frame * _SIO2action->n_frame;
	
		++i;
	}
	

	return mem;
}


void sio2ResourceAdd( SIO2resource  *_SIO2resource,
					  unsigned char  _type,
					  void		    *_ptr )
{
	sio2->_SIO2resource = _SIO2resource;
	
	switch( _type )
	{
		case SIO2_IMAGE:
		{
			++_SIO2resource->n_image;
			_SIO2resource->_SIO2image = ( void ** ) realloc( _SIO2resource->_SIO2image,
															 _SIO2resource->n_image * sizeof( void * ) );
			
			_SIO2resource->_SIO2image[ _SIO2resource->n_image - 1 ] = _ptr;
			
			break;
		}
		
		case SIO2_WIDGET:
		{
			++_SIO2resource->n_widget;
			_SIO2resource->_SIO2widget = ( void ** ) realloc( _SIO2resource->_SIO2widget,
															  _SIO2resource->n_widget * sizeof( void * ) );
			
			_SIO2resource->_SIO2widget[ _SIO2resource->n_widget - 1 ] = _ptr;
			
			break;
		}
		
		case SIO2_CAMERA:
		{
			++_SIO2resource->n_camera;
			_SIO2resource->_SIO2camera = ( void ** ) realloc( _SIO2resource->_SIO2camera,
															  _SIO2resource->n_camera * sizeof( void * ) );
			
			_SIO2resource->_SIO2camera[ _SIO2resource->n_camera - 1 ] = _ptr;
			
			break;
		}		

		case SIO2_MATERIAL:
		{
			++_SIO2resource->n_material;
			_SIO2resource->_SIO2material = ( void ** ) realloc( _SIO2resource->_SIO2material,
															    _SIO2resource->n_material * sizeof( void * ) );
			
			_SIO2resource->_SIO2material[ _SIO2resource->n_material - 1 ] = _ptr;
			
			break;
		}
		
		case SIO2_SOUNDBUFFER:
		{
			++_SIO2resource->n_soundbuffer;
			_SIO2resource->_SIO2soundbuffer = ( void ** ) realloc( _SIO2resource->_SIO2soundbuffer,
																   _SIO2resource->n_soundbuffer * sizeof( void * ) );
			
			_SIO2resource->_SIO2soundbuffer[ _SIO2resource->n_soundbuffer - 1 ] = _ptr;
			
			break;
		}
		
		case SIO2_SOUND:
		{
			++_SIO2resource->n_sound;
			_SIO2resource->_SIO2sound = ( void ** ) realloc( _SIO2resource->_SIO2sound,
															 _SIO2resource->n_sound * sizeof( void * ) );
			
			_SIO2resource->_SIO2sound[ _SIO2resource->n_sound - 1 ] = _ptr;
			
			break;
		}

		case SIO2_VIDEO:
		{
			++_SIO2resource->n_video;
			_SIO2resource->_SIO2video = ( void ** ) realloc( _SIO2resource->_SIO2video,
															 _SIO2resource->n_video * sizeof( void * ) );
			
			_SIO2resource->_SIO2video[ _SIO2resource->n_video - 1 ] = _ptr;
			
			break;
		}
		
		case SIO2_OBJECT:
		{
			++_SIO2resource->n_object;
			_SIO2resource->_SIO2object = ( void ** ) realloc( _SIO2resource->_SIO2object,
															  _SIO2resource->n_object * sizeof( void * ) );
			
			_SIO2resource->_SIO2object[ _SIO2resource->n_object - 1 ] = _ptr;
			
			break;
		}
		
		case SIO2_PHYSIC:
		{
			++_SIO2resource->n_physic;
			_SIO2resource->_SIO2physic = ( void ** ) realloc( _SIO2resource->_SIO2physic,
															  _SIO2resource->n_physic * sizeof( void * ) );
			
			_SIO2resource->_SIO2physic[ _SIO2resource->n_physic - 1 ] = _ptr;
			
			break;
		}
		
		case SIO2_SENSOR:
		{
			++_SIO2resource->n_sensor;
			_SIO2resource->_SIO2sensor = ( void ** ) realloc( _SIO2resource->_SIO2sensor,
															  _SIO2resource->n_sensor * sizeof( void * ) );
			
			_SIO2resource->_SIO2sensor[ _SIO2resource->n_sensor - 1 ] = _ptr;
			
			break;
		}

		case SIO2_EMITTER:
		{
			++_SIO2resource->n_emitter;
			_SIO2resource->_SIO2emitter = ( void ** ) realloc( _SIO2resource->_SIO2emitter,
															   _SIO2resource->n_emitter * sizeof( void * ) );
			
			_SIO2resource->_SIO2emitter[ _SIO2resource->n_emitter - 1 ] = _ptr;
			
			break;
		}
		
		case SIO2_MIST:
		{
			++_SIO2resource->n_mist;
			_SIO2resource->_SIO2mist = ( void ** ) realloc( _SIO2resource->_SIO2mist,
															_SIO2resource->n_mist * sizeof( void * ) );
			
			_SIO2resource->_SIO2mist[ _SIO2resource->n_mist - 1 ] = _ptr;
			
			break;
		}
		
		case SIO2_FONT:
		{
			++_SIO2resource->n_font;
			_SIO2resource->_SIO2font = ( void ** ) realloc( _SIO2resource->_SIO2font,
															_SIO2resource->n_font * sizeof( void * ) );
			
			_SIO2resource->_SIO2font[ _SIO2resource->n_font - 1 ] = _ptr;
			
			break;
		}
		
		case SIO2_LAMP:
		{
			++_SIO2resource->n_lamp;
			_SIO2resource->_SIO2lamp = ( void ** ) realloc( _SIO2resource->_SIO2lamp,
															_SIO2resource->n_lamp * sizeof( void * ) );
			
			_SIO2resource->_SIO2lamp[ _SIO2resource->n_lamp - 1 ] = _ptr;
			
			break;
		}
		
		case SIO2_SCRIPT:
		{
			++_SIO2resource->n_script;
			_SIO2resource->_SIO2script = ( void ** ) realloc( _SIO2resource->_SIO2script,
															  _SIO2resource->n_script * sizeof( void * ) );
			
			_SIO2resource->_SIO2script[ _SIO2resource->n_script - 1 ] = _ptr;
			
			break;
		}
		
		case SIO2_IPO:
		{
			++_SIO2resource->n_ipo;
			_SIO2resource->_SIO2ipo = ( void ** ) realloc( _SIO2resource->_SIO2ipo,
														   _SIO2resource->n_ipo * sizeof( void * ) );
			
			_SIO2resource->_SIO2ipo[ _SIO2resource->n_ipo - 1 ] = _ptr;
			
			break;
		}


		case SIO2_ACTION:
		{
			++_SIO2resource->n_action;
			_SIO2resource->_SIO2action = ( void ** ) realloc( _SIO2resource->_SIO2action,
															  _SIO2resource->n_action * sizeof( void * ) );
			
			_SIO2resource->_SIO2action[ _SIO2resource->n_action - 1 ] = _ptr;
			
			break;
		}

		
		case SIO2_TIMER:
		{
			++_SIO2resource->n_timer;
			_SIO2resource->_SIO2timer = ( void ** ) realloc( _SIO2resource->_SIO2timer,
														     _SIO2resource->n_timer * sizeof( void * ) );
			
			_SIO2resource->_SIO2timer[ _SIO2resource->n_timer - 1 ] = _ptr;
			
			break;
		}		
	}
}


void sio2ResourceDel( SIO2resource  *_SIO2resource,
					  unsigned char  _type,
					  void			*_ptr )
{
	unsigned int i;

	sio2->_SIO2resource = _SIO2resource;
	
	switch( _type )
	{
		case SIO2_IMAGE:
		{
			i = 0;
			
			while( i != _SIO2resource->n_image )
			{
				if( _ptr == _SIO2resource->_SIO2image[ i ] )
				{
					--_SIO2resource->n_image;
									
					if( i < _SIO2resource->n_image )
					{
						memcpy( &_SIO2resource->_SIO2image[ i ],
								&_SIO2resource->_SIO2image[ i + 1 ],
								(_SIO2resource->n_image - i ) * sizeof( void * ) );
					}

					_SIO2resource->_SIO2image = ( void ** ) realloc( _SIO2resource->_SIO2image,
																	 _SIO2resource->n_image * sizeof( void * ) );
					break;
				}
						
				++i;
			}

			break;			
		}
		
		case SIO2_WIDGET:
		{
			i = 0;
			
			while( i != _SIO2resource->n_widget )
			{
				if( _ptr == _SIO2resource->_SIO2widget[ i ] )
				{
					--_SIO2resource->n_widget;
					
					if( i < _SIO2resource->n_widget )
					{
						memcpy( &_SIO2resource->_SIO2widget[ i ],
								&_SIO2resource->_SIO2widget[ i + 1 ],
								(_SIO2resource->n_widget - i ) * sizeof( void * ) );
					}
					
					_SIO2resource->_SIO2widget = ( void ** ) realloc( _SIO2resource->_SIO2widget,
																	  _SIO2resource->n_widget * sizeof( void * ) );
					break;
				}
						
				++i;
			}

			break;			
		}		

		case SIO2_CAMERA:
		{
			i = 0;
			
			while( i != _SIO2resource->n_camera )
			{
				if( _ptr == _SIO2resource->_SIO2camera[ i ] )
				{
					--_SIO2resource->n_camera;
					
					if( i < _SIO2resource->n_camera )
					{				
						memcpy( &_SIO2resource->_SIO2camera[ i ],
								&_SIO2resource->_SIO2camera[ i + 1 ],
								(_SIO2resource->n_camera - i ) * sizeof( void * ) );
					}
					
					_SIO2resource->_SIO2camera = ( void ** ) realloc( _SIO2resource->_SIO2camera,
																	  _SIO2resource->n_camera * sizeof( void * ) );
					break;
				}
				
				++i;
			}

			break;			
		}

		case SIO2_MATERIAL:
		{
			i = 0;
			
			while( i != _SIO2resource->n_material )
			{
				if( _ptr == _SIO2resource->_SIO2material[ i ] )
				{
					--_SIO2resource->n_material;
					
					if( i < _SIO2resource->n_material )
					{				
						memcpy( &_SIO2resource->_SIO2material[ i ],
								&_SIO2resource->_SIO2material[ i + 1 ],
								(_SIO2resource->n_material - i ) * sizeof( void * ) );
					}

					_SIO2resource->_SIO2material = ( void ** ) realloc( _SIO2resource->_SIO2material,
																		 _SIO2resource->n_material * sizeof( void * ) );
					break;
				}
				
				++i;
			}

			break;			
		}
		
		case SIO2_SOUNDBUFFER:
		{
			i = 0;
			
			while( i != _SIO2resource->n_soundbuffer )
			{
				if( _ptr == _SIO2resource->_SIO2soundbuffer[ i ] )
				{
					--_SIO2resource->n_soundbuffer;
					
					if( i < _SIO2resource->n_soundbuffer )
					{				
						memcpy( &_SIO2resource->_SIO2soundbuffer[ i ],
								&_SIO2resource->_SIO2soundbuffer[ i + 1 ],
								(_SIO2resource->n_soundbuffer - i ) * sizeof( void * ) );
					}

					_SIO2resource->_SIO2soundbuffer = ( void ** ) realloc( _SIO2resource->_SIO2soundbuffer,
																		   _SIO2resource->n_soundbuffer * sizeof( void * ) );
					break;
				}
				
				++i;
			}

			break;			
		}
		
		case SIO2_SOUND:
		{
			i = 0;
			
			while( i != _SIO2resource->n_sound )
			{
				if( _ptr == _SIO2resource->_SIO2sound[ i ] )
				{
					--_SIO2resource->n_sound;
					
					if( i < _SIO2resource->n_sound )
					{			
						memcpy( &_SIO2resource->_SIO2sound[ i ],
								&_SIO2resource->_SIO2sound[ i + 1 ],
								(_SIO2resource->n_sound - i ) * sizeof( void * ) );
					}

					_SIO2resource->_SIO2sound = ( void ** ) realloc( _SIO2resource->_SIO2sound,
																	 _SIO2resource->n_sound * sizeof( void * ) );
					break;
				}
				
				++i;
			}

			break;			
		}

		case SIO2_VIDEO:
		{
			i = 0;
			
			while( i != _SIO2resource->n_video )
			{
				if( _ptr == _SIO2resource->_SIO2video[ i ] )
				{
					--_SIO2resource->n_video;
					
					if( i < _SIO2resource->n_video )
					{				
						memcpy( &_SIO2resource->_SIO2video[ i ],
								&_SIO2resource->_SIO2video[ i + 1 ],
								(_SIO2resource->n_video - i ) * sizeof( void * ) );
					}
					
					_SIO2resource->_SIO2video = ( void ** ) realloc( _SIO2resource->_SIO2video,
																	 _SIO2resource->n_video * sizeof( void * ) );
					break;
				}
				
				++i;
			}

			break;			
		}
		
		case SIO2_OBJECT:
		{
			i = 0;
			
			while( i != _SIO2resource->n_object )
			{
				if( _ptr == _SIO2resource->_SIO2object[ i ] )
				{
					--_SIO2resource->n_object;
					
					if( i < _SIO2resource->n_object )
					{
						memcpy( &_SIO2resource->_SIO2object[ i ],
								&_SIO2resource->_SIO2object[ i + 1 ],
								(_SIO2resource->n_object - i ) * sizeof( void * ) );
					}
					
					_SIO2resource->_SIO2object = ( void ** ) realloc( _SIO2resource->_SIO2object,
																	  _SIO2resource->n_object * sizeof( void * ) );
					break;
				}
				
				++i;
			}

			break;			
		}
		
		case SIO2_PHYSIC:
		{
			i = 0;
			
			while( i != _SIO2resource->n_physic )
			{
				if( _ptr == _SIO2resource->_SIO2physic[ i ] )
				{
					--_SIO2resource->n_physic;
					
					if( i < _SIO2resource->n_physic )
					{				
						memcpy( &_SIO2resource->_SIO2physic[ i ],
								&_SIO2resource->_SIO2physic[ i + 1 ],
								(_SIO2resource->n_physic - i ) * sizeof( void * ) );
					}
					
					_SIO2resource->_SIO2physic = ( void ** ) realloc( _SIO2resource->_SIO2physic,
																	  _SIO2resource->n_physic * sizeof( void * ) );
					break;
				}
				
				++i;
			}

			break;			
		}

		case SIO2_SENSOR:
		{
			i = 0;
			
			while( i != _SIO2resource->n_sensor )
			{
				if( _ptr == _SIO2resource->_SIO2sensor[ i ] )
				{
					--_SIO2resource->n_sensor;
					
					if( i < _SIO2resource->n_sensor )
					{				
						memcpy( &_SIO2resource->_SIO2sensor[ i ],
								&_SIO2resource->_SIO2sensor[ i + 1 ],
								(_SIO2resource->n_sensor - i ) * sizeof( void * ) );
					}
					
					_SIO2resource->_SIO2sensor = ( void ** ) realloc( _SIO2resource->_SIO2sensor,
																	  _SIO2resource->n_sensor * sizeof( void * ) );
					break;
				}
				
				++i;
			}

			break;			
		}
		
		case SIO2_EMITTER:
		{
			i = 0;
			
			while( i != _SIO2resource->n_emitter )
			{
				if( _ptr == _SIO2resource->_SIO2emitter[ i ] )
				{
					--_SIO2resource->n_emitter;
					
					if( i < _SIO2resource->n_emitter )
					{				
						memcpy( &_SIO2resource->_SIO2emitter[ i ],
								&_SIO2resource->_SIO2emitter[ i + 1 ],
								(_SIO2resource->n_emitter - i ) * sizeof( void * ) );
					}

					_SIO2resource->_SIO2emitter = ( void ** ) realloc( _SIO2resource->_SIO2emitter,
																	   _SIO2resource->n_emitter * sizeof( void * ) );
					break;
				}
				
				++i;
			}

			break;			
		}
		
		case SIO2_MIST:
		{
			i = 0;
			
			while( i != _SIO2resource->n_mist )
			{
				if( _ptr == _SIO2resource->_SIO2mist[ i ] )
				{
					--_SIO2resource->n_mist;
					
					if( i < _SIO2resource->n_mist )
					{				
						memcpy( &_SIO2resource->_SIO2mist[ i ],
								&_SIO2resource->_SIO2mist[ i + 1 ],
								(_SIO2resource->n_mist - i ) * sizeof( void * ) );
					}

					_SIO2resource->_SIO2mist = ( void ** ) realloc( _SIO2resource->_SIO2mist,
																	_SIO2resource->n_mist * sizeof( void * ) );
					break;
				}
				
				++i;
			}

			break;			
		}
		
		case SIO2_FONT:
		{
			i = 0;
			
			while( i != _SIO2resource->n_font )
			{
				if( _ptr == _SIO2resource->_SIO2font[ i ] )
				{
					--_SIO2resource->n_font;
					
					if( i < _SIO2resource->n_font )
					{				
						memcpy( &_SIO2resource->_SIO2font[ i ],
								&_SIO2resource->_SIO2font[ i + 1 ],
								(_SIO2resource->n_font - i ) * sizeof( void * ) );
					}
					
					_SIO2resource->_SIO2font = ( void ** ) realloc( _SIO2resource->_SIO2font,
																	_SIO2resource->n_font * sizeof( void * ) );
					break;
				}
				
				++i;
			}

			break;			
		}
		
		case SIO2_LAMP:
		{
			i = 0;
			
			while( i != _SIO2resource->n_lamp )
			{
				if( _ptr == _SIO2resource->_SIO2lamp[ i ] )
				{
					--_SIO2resource->n_lamp;
					
					if( i < _SIO2resource->n_lamp )
					{
						memcpy( &_SIO2resource->_SIO2lamp[ i ],
								&_SIO2resource->_SIO2lamp[ i + 1 ],
								(_SIO2resource->n_lamp - i ) * sizeof( void * ) );
					}
					
					_SIO2resource->_SIO2lamp = ( void ** ) realloc( _SIO2resource->_SIO2lamp,
																	_SIO2resource->n_lamp * sizeof( void * ) );
					break;
				}
				
				++i;
			}

			break;			
		}
		
		case SIO2_SCRIPT:
		{
			i = 0;
			
			while( i != _SIO2resource->n_script )
			{
				if( _ptr == _SIO2resource->_SIO2script[ i ] )
				{
					--_SIO2resource->n_script;
					
					if( i < _SIO2resource->n_script )
					{				
						memcpy( &_SIO2resource->_SIO2script[ i ],
								&_SIO2resource->_SIO2script[ i + 1 ],
								(_SIO2resource->n_script - i ) * sizeof( void * ) );
					}
					
					_SIO2resource->_SIO2script = ( void ** ) realloc( _SIO2resource->_SIO2script,
																	_SIO2resource->n_script * sizeof( void * ) );
					break;
				}
				
				++i;
			}

			break;			
		}
		
		case SIO2_IPO:
		{
			i = 0;
			
			while( i != _SIO2resource->n_ipo )
			{
				if( _ptr == _SIO2resource->_SIO2ipo[ i ] )
				{
					--_SIO2resource->n_ipo;
					
					if( i < _SIO2resource->n_ipo )
					{				
						memcpy( &_SIO2resource->_SIO2ipo[ i ],
								&_SIO2resource->_SIO2ipo[ i + 1 ],
								(_SIO2resource->n_ipo - i ) * sizeof( void * ) );
					}
					
					_SIO2resource->_SIO2ipo = ( void ** ) realloc( _SIO2resource->_SIO2ipo,
																   _SIO2resource->n_ipo * sizeof( void * ) );
					break;
				}
				
				++i;
			}

			break;			
		}

		case SIO2_ACTION:
		{
			i = 0;
			
			while( i != _SIO2resource->n_action )
			{
				if( _ptr == _SIO2resource->_SIO2action[ i ] )
				{
					--_SIO2resource->n_action;
					
					if( i < _SIO2resource->n_action )
					{				
						memcpy( &_SIO2resource->_SIO2action[ i ],
								&_SIO2resource->_SIO2action[ i + 1 ],
								(_SIO2resource->n_action - i ) * sizeof( void * ) );
					}
					
					_SIO2resource->_SIO2action = ( void ** ) realloc( _SIO2resource->_SIO2action,
																	  _SIO2resource->n_action * sizeof( void * ) );
					break;
				}
				
				++i;
			}

			break;			
		}
		
		case SIO2_TIMER:
		{
			i = 0;
			
			while( i != _SIO2resource->n_timer )
			{
				if( _ptr == _SIO2resource->_SIO2timer[ i ] )
				{
					--_SIO2resource->n_timer;
					
					if( i < _SIO2resource->n_timer )
					{				
						memcpy( &_SIO2resource->_SIO2timer[ i ],
								&_SIO2resource->_SIO2timer[ i + 1 ],
								(_SIO2resource->n_timer - i ) * sizeof( void * ) );
					}
					
					_SIO2resource->_SIO2timer = ( void ** ) realloc( _SIO2resource->_SIO2timer,
																     _SIO2resource->n_timer * sizeof( void * ) );
					break;
				}
				
				++i;
			}

			break;			
		}		
	}
}
 

void sio2ResourceUnloadAll( SIO2resource  *_SIO2resource )
{
	unsigned int i = 0;

	while( i != SIO2_RESOURCE_ALL )
	{
		sio2ResourceUnload( _SIO2resource, i );
		++i;
	}
}


void sio2ResourceUnload( SIO2resource  *_SIO2resource,
					     unsigned char  _type )
{
	sio2->_SIO2resource = _SIO2resource;
	
	switch( _type )
	{
		case SIO2_IMAGE:
		{
			while( _SIO2resource->n_image )
			{ sio2ImageFree( ( SIO2image * )_SIO2resource->_SIO2image[ 0 ] ); }
			
			break;
		}
		
		case SIO2_CAMERA:
		{
			while( _SIO2resource->n_camera )
			{ sio2CameraFree( ( SIO2camera * )_SIO2resource->_SIO2camera[ 0 ] ); }
			
			break;
		}
		
		case SIO2_WIDGET:
		{
			while( _SIO2resource->n_widget )
			{ sio2WidgetFree( ( SIO2widget * )_SIO2resource->_SIO2widget[ 0 ] ); }
			
			break;
		}
		
		case SIO2_MATERIAL:
		{
			while( _SIO2resource->n_material )
			{ sio2MaterialFree( ( SIO2material * )_SIO2resource->_SIO2material[ 0 ] ); }
			
			break;
		}
		
		case SIO2_SOUNDBUFFER:
		{
			while( _SIO2resource->n_soundbuffer )
			{ sio2SoundBufferFree( ( SIO2soundbuffer * )_SIO2resource->_SIO2soundbuffer[ 0 ] ); }
			
			break;
		}
		
		case SIO2_VIDEO:
		{
			while( _SIO2resource->n_video )
			{ sio2VideoFree( ( SIO2video * )_SIO2resource->_SIO2video[ 0 ] ); }
			
			break;
		}			

		case SIO2_OBJECT:
		{
			while( _SIO2resource->n_object )
			{ sio2ObjectFree( ( SIO2object * )_SIO2resource->_SIO2object[ 0 ] ); }
			
			break;
		}

		case SIO2_SOUND:
		{
			while( _SIO2resource->n_sound )
			{ sio2SoundFree( ( SIO2sound * )_SIO2resource->_SIO2sound[ 0 ] ); }
			
			break;
		}		
		
		case SIO2_PHYSIC:
		{
			while( _SIO2resource->n_physic )
			{ sio2PhysicFree( ( SIO2physic * )_SIO2resource->_SIO2physic[ 0 ] ); }
			
			break;
		}
		
		case SIO2_SENSOR:
		{
			while( _SIO2resource->n_sensor )
			{ sio2SensorFree( ( SIO2sensor * )_SIO2resource->_SIO2sensor[ 0 ] ); }
			
			break;
		}
		
		case SIO2_EMITTER:
		{
			while( _SIO2resource->n_emitter )
			{ sio2EmitterFree( ( SIO2emitter * )_SIO2resource->_SIO2emitter[ 0 ] ); }
			
			break;
		}
		
		case SIO2_MIST:
		{
			while( _SIO2resource->n_mist )
			{ sio2MistFree( ( SIO2mist * )_SIO2resource->_SIO2mist[ 0 ] ); }
			
			break;		
		}
		
		case SIO2_FONT:
		{
			while( _SIO2resource->n_font )
			{ sio2FontFree( ( SIO2font * )_SIO2resource->_SIO2font[ 0 ] ); }
			
			break;		
		}
		
		case SIO2_LAMP:
		{
			while( _SIO2resource->n_lamp )
			{ sio2LampFree( ( SIO2lamp * )_SIO2resource->_SIO2lamp[ 0 ] ); }
			
			break;
		}
		
		case SIO2_SCRIPT:
		{
			while( _SIO2resource->n_script )
			{ sio2ScriptFree( ( SIO2script * )_SIO2resource->_SIO2script[ 0 ] ); }
			
			break;
		}
		
		case SIO2_IPO:
		{
			while( _SIO2resource->n_ipo )
			{ sio2IpoFree( ( SIO2ipo * )_SIO2resource->_SIO2ipo[ 0 ] ); }
			
			break;
		}

		case SIO2_ACTION:
		{
			while( _SIO2resource->n_action )
			{ sio2ActionFree( ( SIO2action * )_SIO2resource->_SIO2action[ 0 ] ); }
			
			break;
		}
		
		case SIO2_TIMER:
		{
			while( _SIO2resource->n_timer )
			{ sio2TimerFree( ( SIO2timer * )_SIO2resource->_SIO2timer[ 0 ] ); }
			
			break;
		}				
	}
}


void sio2ResourceUpdateAllWidgetBoundaries( SIO2resource *_SIO2resource,
											SIO2window   *_SIO2window )
{
	unsigned int i = 0;
	
	while( i != _SIO2resource->n_widget )
	{
		SIO2widget *_SIO2widget = ( SIO2widget * )_SIO2resource->_SIO2widget[ i ];
		
		sio2WidgetUpdateBoundary( _SIO2widget,
								  _SIO2window );
		++i;
	}
}


void sio2ResourceDispatchEvents( SIO2resource  *_SIO2resource,
								 SIO2window	   *_SIO2window,
								 unsigned char  _type,
								 unsigned char  _state )
{
	if( _SIO2resource )
	{
		unsigned int i = 0;

		// Window Event
		switch( _type )
		{
			case SIO2_WINDOW_TAP:
			{
				if( _SIO2window->_SIO2windowtap )
				{ _SIO2window->_SIO2windowtap( _SIO2window, _state ); }		

				break;
			}

			case SIO2_WINDOW_TOUCH_MOVE:
			{
				if( _SIO2window->_SIO2windowtouchmove )
				{ _SIO2window->_SIO2windowtouchmove( _SIO2window ); }

				break;
			}
			
			case SIO2_WINDOW_ACCELEROMETER:
			{
				if( _SIO2window->_SIO2windowaccelerometer )
				{ _SIO2window->_SIO2windowaccelerometer( _SIO2window ); }
			}
		}
											 
		
		// Widget Events
		while( i != _SIO2resource->n_widget )
		{
			SIO2widget *_SIO2widget = ( SIO2widget * )_SIO2resource->_SIO2widget[ i ];
			
			if( !sio2IsStateEnabled( _SIO2widget->flags, SIO2_WIDGET_VISIBLE ) || 
				!sio2IsStateEnabled( _SIO2widget->flags, SIO2_WIDGET_ENABLED ) )
			{
				++i;
				continue;
			}
			else
			{
				unsigned char focused = 0;
				
				unsigned int j = 0;
		
				while( j != _SIO2window->n_touch )
				{
					if( ( _SIO2window->touch[ j ]->x > _SIO2widget->bl->x &&
						  _SIO2window->touch[ j ]->y > _SIO2widget->bl->y )
						&&
						( _SIO2window->touch[ j ]->x < _SIO2widget->tr->x &&
						  _SIO2window->touch[ j ]->y < _SIO2widget->tr->y ) )
					{
						focused = 1;
						
						switch( _type )
						{
							case SIO2_WINDOW_TAP:
							{
								if( _state == SIO2_WINDOW_TAP_DOWN && _SIO2widget->_SIO2widgettapdown )
								{
									sio2EnableState( &_SIO2widget->flags, SIO2_WIDGET_LOCKED );
																
									_SIO2widget->_SIO2widgettapdown( _SIO2widget,
																	 _SIO2window,
																	 _SIO2window->touch[ j ] );
								}
								
								else if( _state == SIO2_WINDOW_TAP_UP &&
										 _SIO2widget->_SIO2widgettapup )
								{
									if( sio2IsStateEnabled( _SIO2widget->flags, SIO2_WIDGET_VALIDATE_LOCK ) )
									{
										if( sio2IsStateEnabled( _SIO2widget->flags, SIO2_WIDGET_LOCKED ) )
										{
											_SIO2widget->_SIO2widgettapup( _SIO2widget,
																		   _SIO2window,
																		   _SIO2window->touch[ j ] );
										}
									}
									else
									{
										_SIO2widget->_SIO2widgettapup( _SIO2widget,
																	   _SIO2window,
																	   _SIO2window->touch[ j ] );
									}
									
									sio2DisableState( &_SIO2widget->flags, SIO2_WIDGET_LOCKED );
								}

								break;
							}
							
							case SIO2_WINDOW_TOUCH_MOVE:
							{
								if( _SIO2widget->_SIO2widgettouchmove )
								{
									_SIO2widget->_SIO2widgettouchmove( _SIO2widget,
																	   _SIO2window,
																	   _SIO2window->touch[ j ] );
								}
							
								break;
							}		
						}

						break;				
					}

					++j;
				}	
				
				
				if( focused && !sio2IsStateEnabled( _SIO2widget->flags, SIO2_WIDGET_FOCUSED ) )
				{ sio2EnableState( &_SIO2widget->flags, SIO2_WIDGET_FOCUSED ); }
				
				else if( !focused && sio2IsStateEnabled( _SIO2widget->flags, SIO2_WIDGET_FOCUSED ) )
				{ sio2DisableState( &_SIO2widget->flags, SIO2_WIDGET_FOCUSED ); }
				
				
				if( !focused && _state == SIO2_WINDOW_TAP_UP )
				{ sio2DisableState( &_SIO2widget->flags, SIO2_WIDGET_LOCKED ); }
			}
		
			++i;	
		}
	}
}


void *sio2ResourceGet( SIO2resource  *_SIO2resource,
					   unsigned char  _type,
					   char			 *_name )
{
	unsigned int i = 0;

	switch( _type )
	{
		case SIO2_IMAGE:
		{
			while( i != _SIO2resource->n_image )
			{
				SIO2image *_SIO2image = ( SIO2image * )_SIO2resource->_SIO2image[ i ];
				
				if( !sio2StringCmp( _SIO2image->name, _name ) )
				{ return _SIO2resource->_SIO2image[ i ]; }
			
				++i;
			}
			
			break;
		}
		
		case SIO2_CAMERA:
		{
			while( i != _SIO2resource->n_camera )
			{ 
				SIO2camera *_SIO2camera = ( SIO2camera * )_SIO2resource->_SIO2camera[ i ];
				
				if( !sio2StringCmp( _SIO2camera->name, _name ) )
				{ return _SIO2resource->_SIO2camera[ i ]; }
				
				++i;
			}
			
			break;
		}
		
		case SIO2_WIDGET:
		{
			while( i != _SIO2resource->n_widget )
			{
				SIO2widget *_SIO2widget = ( SIO2widget * )_SIO2resource->_SIO2widget[ i ];
				
				if( !sio2StringCmp( _SIO2widget->name, _name ) )
				{ return _SIO2resource->_SIO2widget[ i ]; }
				
				++i;
			}
			
			break;
		}
		
		case SIO2_MATERIAL:
		{
			while( i != _SIO2resource->n_material )
			{
				SIO2material *_SIO2material = ( SIO2material * )_SIO2resource->_SIO2material[ i ];
				
				if( !sio2StringCmp( _SIO2material->name, _name ) )
				{ return _SIO2resource->_SIO2material[ i ]; }
				
				++i;
			}
			
			break;
		}
		
		case SIO2_SOUNDBUFFER:
		{
			while( i != _SIO2resource->n_soundbuffer )
			{
				SIO2soundbuffer *_SIO2soundbuffer = ( SIO2soundbuffer * )_SIO2resource->_SIO2soundbuffer[ i ];
				
				if( !sio2StringCmp( _SIO2soundbuffer->name, _name ) )
				{ return _SIO2resource->_SIO2soundbuffer[ i ]; }
				
				++i;
			}
			
			break;
		}

		case SIO2_SOUND:
		{
			while( i != _SIO2resource->n_sound )
			{
				SIO2sound *_SIO2sound = ( SIO2sound * )_SIO2resource->_SIO2sound[ i ];
				
				if( !sio2StringCmp( _SIO2sound->name, _name ) )
				{ return _SIO2resource->_SIO2sound[ i ]; }
				
				++i;
			}
			
			break;
		}
		
		case SIO2_VIDEO:
		{
			while( i != _SIO2resource->n_video )
			{
				SIO2video *_SIO2video = ( SIO2video * )_SIO2resource->_SIO2video[ i ];
				
				if( !sio2StringCmp( _SIO2video->name, _name ) )
				{ return _SIO2resource->_SIO2video[ i ]; }
				
				++i;
			}
			
			break;
		}

		case SIO2_OBJECT:
		{
			while( i != _SIO2resource->n_object )
			{
				SIO2object *_SIO2object = ( SIO2object * )_SIO2resource->_SIO2object[ i ];
				
				if( !sio2StringCmp( _SIO2object->name, _name ) )
				{ return _SIO2resource->_SIO2object[ i ]; }
				
				++i;
			}
			
			break;
		}
		
		case SIO2_PHYSIC:
		{
			while( i != _SIO2resource->n_physic )
			{
				SIO2physic *_SIO2physic = ( SIO2physic * )_SIO2resource->_SIO2physic[ i ];
				
				if( !sio2StringCmp( _SIO2physic->name, _name ) )
				{ return _SIO2resource->_SIO2physic[ i ]; }
				
				++i;
			}
			
			break;
		}
		
		case SIO2_SENSOR:
		{
			while( i != _SIO2resource->n_sensor )
			{
				SIO2sensor *_SIO2sensor = ( SIO2sensor * )_SIO2resource->_SIO2sensor[ i ];
				
				if( !sio2StringCmp( _SIO2sensor->name, _name ) )
				{ return _SIO2resource->_SIO2sensor[ i ]; }
				
				++i;
			}
			
			break;
		}

		case SIO2_EMITTER:
		{
			while( i != _SIO2resource->n_emitter )
			{
				SIO2emitter *_SIO2emitter = ( SIO2emitter * )_SIO2resource->_SIO2emitter[ i ];
				
				if( !sio2StringCmp( _SIO2emitter->name, _name ) )
				{ return _SIO2resource->_SIO2emitter[ i ]; }
				
				++i;
			}
			
			break;
		}
		
		case SIO2_MIST:
		{
			while( i != _SIO2resource->n_mist )
			{
				SIO2mist *_SIO2mist = ( SIO2mist * )_SIO2resource->_SIO2mist[ i ];
				
				if( !sio2StringCmp( _SIO2mist->name, _name ) )
				{ return _SIO2resource->_SIO2mist[ i ]; }
				
				++i;
			}
			
			break;
		}
		
		case SIO2_FONT:
		{
			while( i != _SIO2resource->n_font )
			{
				SIO2font *_SIO2font = ( SIO2font * )_SIO2resource->_SIO2font[ i ];
				
				if( !sio2StringCmp( _SIO2font->name, _name ) )
				{ return _SIO2resource->_SIO2font[ i ]; }
				
				++i;
			}
			
			break;
		}
		
		case SIO2_LAMP:
		{
			while( i != _SIO2resource->n_lamp )
			{
				SIO2lamp *_SIO2lamp = ( SIO2lamp * )_SIO2resource->_SIO2lamp[ i ];
				
				if( !sio2StringCmp( _SIO2lamp->name, _name ) )
				{ return _SIO2resource->_SIO2lamp[ i ]; }
				
				++i;
			}
			
			break;
		}
		
		case SIO2_SCRIPT:
		{
			while( i != _SIO2resource->n_script )
			{
				SIO2script *_SIO2script = ( SIO2script * )_SIO2resource->_SIO2script[ i ];
				
				if( !sio2StringCmp( _SIO2script->name, _name ) )
				{ return _SIO2resource->_SIO2script[ i ]; }
				
				++i;
			}
			
			break;
		}
		
		case SIO2_IPO:
		{
			while( i != _SIO2resource->n_ipo )
			{
				SIO2ipo *_SIO2ipo = ( SIO2ipo * )_SIO2resource->_SIO2ipo[ i ];
				
				if( !sio2StringCmp( _SIO2ipo->name, _name ) )
				{ return _SIO2resource->_SIO2ipo[ i ]; }
				
				++i;
			}
			
			break;
		}
		
		case SIO2_ACTION:
		{
			while( i != _SIO2resource->n_action )
			{
				SIO2action *_SIO2action = ( SIO2action * )_SIO2resource->_SIO2action[ i ];
				
				if( !sio2StringCmp( _SIO2action->name, _name ) )
				{ return _SIO2resource->_SIO2action[ i ]; }
				
				++i;
			}
			
			break;
		}

		case SIO2_TIMER:
		{
			while( i != _SIO2resource->n_timer )
			{
				SIO2timer *_SIO2timer = ( SIO2timer * )_SIO2resource->_SIO2timer[ i ];
				
				if( !sio2StringCmp( _SIO2timer->name, _name ) )
				{ return _SIO2resource->_SIO2timer[ i ]; }
				
				++i;
			}
			
			break;
		}			
	}
	
	return NULL;
}


unsigned char sio2ResourceOpen( SIO2resource  *_SIO2resource,
								const char    *_fname,
								unsigned char  _rel )
{
	if( _rel )
	{
		char fname[ SIO2_MAX_PATH ] = {""};
		sprintf( fname, "%s%s", sio2->app_path, _fname ); 
		
		_SIO2resource->uf = unzOpen( fname );
	}
	else
	{ _SIO2resource->uf = unzOpen( _fname ); }


	if( !_SIO2resource->uf )
	{ return 0; }
	
	
	unzGetGlobalInfo( _SIO2resource->uf, &_SIO2resource->gi );

	unzGoToFirstFile( _SIO2resource->uf );
	
	sio2->_SIO2resource = _SIO2resource;
	
	return 1;
}


void sio2ResourceClose( SIO2resource *_SIO2resource )
{
	unzClose( _SIO2resource->uf );
	_SIO2resource->uf = NULL;
}


void sio2ResourceCreateDictionary( SIO2resource *_SIO2resource )
{
	sio2ResourceAddEntry( _SIO2resource,
						  "object",
						  sio2ObjectLoad,
						  NULL );

	sio2ResourceAddEntry( _SIO2resource,
						  "material",
						  sio2MaterialLoad,
						  NULL );
						  
	sio2ResourceAddEntry( _SIO2resource,
						  "lamp",
						  sio2LampLoad,
						  NULL );

	sio2ResourceAddEntry( _SIO2resource,
						  "camera",
						  sio2CameraLoad,
						  NULL );
						  
	sio2ResourceAddEntry( _SIO2resource,
						  "ipo",
						  sio2IpoLoad,
						  NULL );
						  
	sio2ResourceAddEntry( _SIO2resource,
						  "action",
						  sio2ActionLoad,
						  NULL );
}


void sio2ResourceAddEntry( SIO2resource		  *_SIO2resource,
						   const char		  *_str,
						   SIO2parsercallback *_root,
						   SIO2parsercallback *_custom )
{
	++_SIO2resource->n_entry;
	
	_SIO2resource->_SIO2entry = ( SIO2entry * ) realloc( _SIO2resource->_SIO2entry, _SIO2resource->n_entry * sizeof( SIO2entry ) );
	
	sio2StringCpy( _SIO2resource->_SIO2entry[ _SIO2resource->n_entry - 1 ].str, _str );
	
	_SIO2resource->_SIO2entry[ _SIO2resource->n_entry - 1 ].root   = _root;
	_SIO2resource->_SIO2entry[ _SIO2resource->n_entry - 1 ].custom = _custom;
}


unsigned char sio2ResourceExtractFile( SIO2resource *_SIO2resource,
									   SIO2stream   *_SIO2stream,
									   const char   *_fname,
									   char		    *_password )
{
	unz_file_info fi;
	
	_SIO2stream->fname[ 0 ] = 0;
	
	if( unzLocateFile( _SIO2resource->uf, _fname, 1 ) == UNZ_OK )
	{
		unzGetCurrentFileInfo( _SIO2resource->uf,
							   &fi,
							   _SIO2stream->fname,
							   SIO2_MAX_CHAR,
							   NULL, 0,
							   NULL, 0 );
	
		if( !fi.uncompressed_size )
		{ return 0; }
	
		if( unzOpenCurrentFilePassword( _SIO2resource->uf, _password ) == UNZ_OK )
		{
			_SIO2stream->pos = 0;
			
			_SIO2stream->buf = ( unsigned char * ) realloc( _SIO2stream->buf, fi.uncompressed_size + 1 );
			_SIO2stream->buf[ fi.uncompressed_size ] = 0;			
			
			_SIO2stream->cur = _SIO2stream->buf;
			
			_SIO2stream->size = fi.uncompressed_size;
			
			while( unzReadCurrentFile( _SIO2resource->uf, _SIO2stream->buf, fi.uncompressed_size ) > 0 )
			{}
			
			unzCloseCurrentFile( _SIO2resource->uf );
			
			return 1;
		}
	}
	
	return 0;
}


void sio2ResourceExtract( SIO2resource *_SIO2resource,
						  char		   *_password )
{
	unz_file_info fi;
	
	char name[ SIO2_MAX_CHAR ] = {""};

	unzGetCurrentFileInfo( _SIO2resource->uf, &fi, name, SIO2_MAX_CHAR, NULL, 0, NULL, 0 );
	
	if( !fi.uncompressed_size )
	{
		unzGoToNextFile( _SIO2resource->uf );
		return;
	}
	
	if( unzOpenCurrentFilePassword( _SIO2resource->uf, _password ) == UNZ_OK )
	{
		SIO2stream *_SIO2stream = sio2StreamInit( name );

		_SIO2stream->buf = ( unsigned char * ) malloc( fi.uncompressed_size + 1 );
		_SIO2stream->cur = _SIO2stream->buf;
		
		_SIO2stream->buf[ fi.uncompressed_size ] = 0;		
		
		_SIO2stream->size = fi.uncompressed_size;
		
		while( unzReadCurrentFile( _SIO2resource->uf, _SIO2stream->buf, fi.uncompressed_size ) > 0 )
		{}
		
		unzCloseCurrentFile( _SIO2resource->uf );

		_SIO2stream = sio2ResourceDispatchStream( _SIO2resource,
												  _SIO2stream );
		
		_SIO2stream = sio2StreamClose( _SIO2stream );
	}
	
	unzGoToNextFile( _SIO2resource->uf );	
}


SIO2stream *sio2ResourceDispatchStream( SIO2resource *_SIO2resource,
										SIO2stream   *_SIO2stream )
{
	unsigned int i = 0;
	
	sio2->_SIO2resource = _SIO2resource;
	
	while( i != SIO2_ARCHIVE_TYPE )
	{
		if( sio2StringTok( _SIO2stream->fname, SIO2_RESOURCE_PATH[ i ] ) )
		{ break; }
		
		++i;
	}

	switch( i )
	{
		case SIO2_OBJECT:
		case SIO2_MATERIAL:
		case SIO2_LAMP:
		case SIO2_CAMERA:
		case SIO2_IPO:
		{
			sio2StreamParse( _SIO2stream,
							 _SIO2resource->n_entry,
							 _SIO2resource->_SIO2entry );
			break;
		}

		case SIO2_IMAGE:
		{
			SIO2image *_SIO2image = sio2ImageInit( _SIO2stream->fname );

			sio2ImageLoad( _SIO2image, _SIO2stream );
			break;
		}
		
		case SIO2_SOUNDBUFFER:
		{
			SIO2soundbuffer *_SIO2soundbuffer = sio2SoundBufferInit( _SIO2stream->fname );
			
			sio2SoundBufferLoad( _SIO2soundbuffer,
								 _SIO2stream );
			
			_SIO2stream = NULL;
			
			break;
		}
		
		case SIO2_SCRIPT:
		{
			SIO2script *_SIO2script = sio2ScriptInit( _SIO2stream->fname );
					
			_SIO2stream->buf = ( unsigned char * ) realloc( _SIO2stream->buf,
															_SIO2stream->size + 1 );
			_SIO2stream->buf[ _SIO2stream->size ] = 0;				

			sio2ScriptLoad( _SIO2script,
							_SIO2stream );
			
			_SIO2script = sio2ScriptFree( _SIO2script );
		}
		
		default:
		{
			if( _SIO2resource->_SIO2resourcecustomload )
			{ _SIO2resource->_SIO2resourcecustomload( _SIO2stream ); }
			
			break;
		}
	}
	
	return _SIO2stream;
}


void sio2ResourceBindAllImages( SIO2resource *_SIO2resource )
{
	unsigned int i = 0;
	
	while( i != _SIO2resource->n_material )
	{
		sio2ResourceBindImage( _SIO2resource,
							   ( SIO2material * )_SIO2resource->_SIO2material[ i ] );
		++i;
	}
}


void sio2ResourceBindImage( SIO2resource *_SIO2resource,
							SIO2material *_SIO2material )
{
	unsigned int i = 0;
	
	while( i != SIO2_MATERIAL_NCHANNEL )
	{
		if( _SIO2material->tname[ i ][ 0 ] )
		{
			SIO2image *_SIO2image = ( SIO2image * )sio2ResourceGet( _SIO2resource,
																	SIO2_IMAGE,
																	_SIO2material->tname[ i ] );
			_SIO2material->_SIO2image[ i ] = _SIO2image;
		}
		
		++i;
	}
}


void sio2ResourceBindAllIpos( SIO2resource *_SIO2resource )
{
	unsigned int i = 0;

	while( i != _SIO2resource->n_object )
	{
		sio2ResourceBindObjectIpo( _SIO2resource,
								   ( SIO2object * )_SIO2resource->_SIO2object[ i ] );
		++i;
	}
	
	
	i = 0;
	while( i != _SIO2resource->n_camera )
	{
		sio2ResourceBindCameraIpo( _SIO2resource,
								   ( SIO2camera * )_SIO2resource->_SIO2camera[ i ] );
		++i;
	}
	
	
	i = 0;
	while( i != _SIO2resource->n_lamp )
	{
		sio2ResourceBindLampIpo( _SIO2resource,
								 ( SIO2lamp * )_SIO2resource->_SIO2lamp[ i ] );
		++i;
	}	
}


void sio2ResourceBindObjectIpo( SIO2resource *_SIO2resource,
								SIO2object   *_SIO2object )
{
	if( _SIO2object->iponame[ 0 ] )
	{
		_SIO2object->_SIO2ipo = sio2ResourceGetIpo( _SIO2resource,
													_SIO2object->iponame );
		
		if( _SIO2object->_SIO2ipo )
		{
			sio2IpoReset( _SIO2object->_SIO2ipo,
						  _SIO2object->_SIO2transform ); 
		}
	}
}


void sio2ResourceBindCameraIpo( SIO2resource *_SIO2resource,
								SIO2camera   *_SIO2camera )
{
	if( _SIO2camera->iponame[ 0 ] )
	{
		_SIO2camera->_SIO2ipo = sio2ResourceGetIpo( _SIO2resource,
													_SIO2camera->iponame );
													
		if( _SIO2camera->_SIO2ipo )
		{
			sio2IpoReset( _SIO2camera->_SIO2ipo,
						  _SIO2camera->_SIO2transform );
		}
	}
}


void sio2ResourceBindLampIpo( SIO2resource *_SIO2resource,
							  SIO2lamp	   *_SIO2lamp )
{
	if( _SIO2lamp->iponame[ 0 ] )
	{
		_SIO2lamp->_SIO2ipo = sio2ResourceGetIpo( _SIO2resource,
												  _SIO2lamp->iponame );

		if( _SIO2lamp->_SIO2ipo )
		{ sio2IpoReset( _SIO2lamp->_SIO2ipo,
						NULL ); }
	}
}


void sio2ResourceBindAllSoundBuffers( SIO2resource *_SIO2resource )
{
	unsigned int i = 0;
	
	while( i != _SIO2resource->n_material )
	{
		sio2ResourceBindSoundBuffer( _SIO2resource,
									( SIO2material * )_SIO2resource->_SIO2material[ i ] );
		++i;
	}	
}


void sio2ResourceBindSoundBuffer( SIO2resource *_SIO2resource,
								  SIO2material *_SIO2material )
{
	if( _SIO2material->sbname[ 0 ] )
	{
		SIO2soundbuffer *_SIO2soundbuffer = ( SIO2soundbuffer * )sio2ResourceGet( _SIO2resource,
																				  SIO2_SOUNDBUFFER,
																				  _SIO2material->sbname );
		_SIO2material->_SIO2soundbuffer = _SIO2soundbuffer;
	}
}


void sio2ResourceBindAllMaterials( SIO2resource *_SIO2resource )
{
	unsigned int i = 0;
	
	while( i != _SIO2resource->n_object )
	{
		sio2ResourceBindMaterial( _SIO2resource,
								  ( SIO2object * )_SIO2resource->_SIO2object[ i ] );
		++i;
	}
}


void sio2ResourceBindMaterial( SIO2resource *_SIO2resource,
							   SIO2object	*_SIO2object )
{
	unsigned int i = 0;

	while( i != _SIO2object->n_vgroup )
	{
		if( _SIO2object->_SIO2vertexgroup[ i ]->mname )
		{
			SIO2material *_SIO2material = ( SIO2material * )sio2ResourceGet( _SIO2resource,
																			 SIO2_MATERIAL,
																			 _SIO2object->_SIO2vertexgroup[ i ]->mname );
			
			_SIO2object->_SIO2vertexgroup[ i ]->_SIO2material = _SIO2material;
		}
		
		++i;
	}
}


void sio2ResourceBindAllInstances( SIO2resource *_SIO2resource )
{
	unsigned int i = 0;
	
	while( i != _SIO2resource->n_object )
	{
		sio2ResourceBindInstance( _SIO2resource,
								  ( SIO2object * )_SIO2resource->_SIO2object[ i ] );
		++i;
	}
}


void sio2ResourceBindInstance( SIO2resource *_SIO2resource,
							   SIO2object   *_SIO2object )
{
	if( _SIO2object->instname[ 0 ] )
	{
		SIO2object *_SIO2master = ( SIO2object * )sio2ResourceGet( _SIO2resource,
																   SIO2_OBJECT,
																   _SIO2object->instname );
		
		_SIO2object->_SIO2instance = _SIO2master;
		_SIO2object->flags = _SIO2master->flags;
	}
}


void sio2ResourceBindAllMatrix( SIO2resource *_SIO2resource )
{
	unsigned int i = 0;
	
	while( i != _SIO2resource->n_object )
	{
		SIO2object *_SIO2object = ( SIO2object * )_SIO2resource->_SIO2object[ i ];
		
		sio2TransformBindMatrix( _SIO2object->_SIO2transform );
		++i;
	}
}


void sio2ResourceBindAllPhysicObjects( SIO2resource *_SIO2resource,
									   SIO2physic   *_SIO2physic )
{
	unsigned int i = 0;
	
	while( i != _SIO2resource->n_object )
	{
		SIO2object *_SIO2object = ( SIO2object * )_SIO2resource->_SIO2object[ i ];
		 
		if( sio2IsStateEnabled( _SIO2object->flags, SIO2_OBJECT_ACTOR ) )
		{
			sio2PhysicAddObject( _SIO2physic,
								 _SIO2object );
		}
		++i;
	}
}


void sio2ResourceBindAllSounds( SIO2resource *_SIO2resource )
{
	unsigned int i = 0;
	
	sio2->_SIO2resource = _SIO2resource;	
	
	while( i != _SIO2resource->n_object )
	{
		sio2ObjectBindSound( ( SIO2object * )_SIO2resource->_SIO2object[ i ] );
		++i;
	}
}


void sio2ResourceGenId( SIO2resource *_SIO2resource )
{
	unsigned int i = 0,
				 j;
	
	while( i != _SIO2resource->n_material )
	{
		SIO2material *_SIO2material = ( SIO2material * )_SIO2resource->_SIO2material[ i ];
		
		j = 0;
		while( j != SIO2_MATERIAL_NCHANNEL )
		{
			if(  _SIO2material->tname[ j ][ 0 ] && 
				!_SIO2material->_SIO2image[ j ]->tid )
			{
				sio2ImageGenId( _SIO2material->_SIO2image[ j ], 
								_SIO2material->tflags    [ j ],
								_SIO2material->tfilter   [ j ] );
			}
			
			++j;
		}
		
		if(  _SIO2material->sbname[ 0 ] &&
		     _SIO2material->_SIO2soundbuffer &&
			!_SIO2material->_SIO2soundbuffer->bid[ 0 ] &&
			!_SIO2material->_SIO2soundbuffer->bid[ 1 ] )
		{
			sio2SoundBufferGenId( _SIO2material->_SIO2soundbuffer,
								  sio2IsStateEnabled( _SIO2material->sflags, SIO2_SOUND_STREAM ) );
		}
		
		++i;
	}


	i = 0;
	while( i != _SIO2resource->n_object )
	{
		SIO2object *_SIO2object = ( SIO2object * )_SIO2resource->_SIO2object[ i ];

		if( !_SIO2object->vbo )
		{ sio2ObjectGenId( _SIO2object ); }
		
		j = 0;
		while( j != _SIO2object->n_vgroup )
		{
			if( !_SIO2object->_SIO2vertexgroup[ j ]->vbo )
			{ sio2VertexGroupGenId( _SIO2object->_SIO2vertexgroup[ j ] ); }
			
			++j;
		}
		
		++i;
	}

	sio2ObjectReset();
}


void sio2ResourceRender( SIO2resource *_SIO2resource,
						 SIO2window	  *_SIO2window,
						 SIO2camera	  *_SIO2camera,
						 int		   _mask )
{
	unsigned int i;


	if( _mask & SIO2_RENDER_IPO )
	{
		i = 0;
		while( i != _SIO2resource->n_ipo )
		{
			SIO2ipo *_SIO2ipo = ( SIO2ipo * )_SIO2resource->_SIO2ipo[ i ];
			
			if( _SIO2ipo->state == SIO2_PLAY )
			{ sio2IpoRender( _SIO2ipo, _SIO2window ); }	
			
			++i;
		}
	}


	if( _mask & SIO2_RENDER_LAMP )
	{
		unsigned char index = 0;
		
		sio2LampReset();

		i = 0;
		while( i != _SIO2resource->n_lamp )
		{
			SIO2lamp *_SIO2lamp = ( SIO2lamp * )_SIO2resource->_SIO2lamp[ i ];
			
			if( sio2LampRender( _SIO2lamp, index ) )
			{ ++index; }
			
			if( index == ( SIO2_LAMP_MAX - 1 ) )
			{ break; }
			
			++i;
		}
	}
	
	
	if( _mask & SIO2_RENDER_SOLID_OBJECT )
	{
		i = 0;
		while( i != _SIO2resource->n_object )
		{
			SIO2object *_SIO2object = ( SIO2object * )_SIO2resource->_SIO2object[ i ];

			if( ( _SIO2object->type & SIO2_OBJECT_SOLID ) && _SIO2object->dst )
			{
				sio2ObjectRender( _SIO2object,
								  _SIO2window,			
								  _SIO2camera,
								  !( _mask & SIO2_RENDER_NO_MATERIAL ),
								  !( _mask & SIO2_RENDER_NO_MATRIX ) );
			}

			++i;
		}
	}
	
	
	if( _mask & SIO2_RENDER_TRANSPARENT_OBJECT )
	{
		unsigned int j,
					 n_transp = 0;
		
		void *ptr,
			 **_SIO2transp = NULL;		
		
		i = 0;
		while( i != _SIO2resource->n_object )
		{
			SIO2object *_SIO2object = ( SIO2object * )_SIO2resource->_SIO2object[ i ];

			if( ( _SIO2object->type & SIO2_OBJECT_TRANSPARENT ) && _SIO2object->dst )
			{
				++n_transp;
				_SIO2transp = ( void ** ) realloc( _SIO2transp,
												   n_transp * sizeof( void * ) );
											  
				_SIO2transp[ n_transp - 1 ] = _SIO2object;
			}

			++i;
		}
		

		i = 0;
		while( i != n_transp )
		{
			j = 0;
			while( j != ( n_transp - 1 ) )
			{
				SIO2object *a = ( SIO2object * )_SIO2transp[ j     ],
						   *b = ( SIO2object * )_SIO2transp[ j + 1 ];
			
				if( a->dst < b->dst )
				{
					ptr = _SIO2transp[ j + 1 ];
					_SIO2transp[ j + 1 ] = _SIO2transp[ j ];
					_SIO2transp[ j     ] = ptr;
				}
				++j;
			}

			++i;
		}


		i = 0;
		while( i != n_transp )
		{
			sio2ObjectRender( ( SIO2object * )_SIO2transp[ i ],
							  _SIO2window,			
							  _SIO2camera,
							  !( _mask & SIO2_RENDER_NO_MATERIAL ),
							  !( _mask & SIO2_RENDER_NO_MATRIX ) );
			++i;
		}


		if( _SIO2transp )
		{
			free( _SIO2transp );
			_SIO2transp = NULL;
		}
	}
	
	
	if( _mask & SIO2_RENDER_ALPHA_TESTED_OBJECT )
	{
		unsigned int j,
					 n_alpha = 0;
		
		void *ptr,
			 **_SIO2alpha = NULL;
		
		i = 0;
		while( i != _SIO2resource->n_object )
		{
			SIO2object *_SIO2object = ( SIO2object * )_SIO2resource->_SIO2object[ i ];
			
			if( ( _SIO2object->type & SIO2_OBJECT_ALPHA_TESTED ) && _SIO2object->dst )
			{
				++n_alpha;
				_SIO2alpha = ( void ** ) realloc( _SIO2alpha,
												   n_alpha * sizeof( void * ) );
											  
				_SIO2alpha[ n_alpha - 1 ] = _SIO2object;
			}

			++i;
		}
		

		i = 0;
		while( i != n_alpha )
		{
			j = 0;
			while( j != ( n_alpha - 1 ) )
			{
				SIO2object *a = ( SIO2object * )_SIO2alpha[ j     ],
						   *b = ( SIO2object * )_SIO2alpha[ j + 1 ];
			
				if( a->dst < b->dst )
				{
					ptr = _SIO2alpha[ j + 1 ];
					_SIO2alpha[ j + 1 ] = _SIO2alpha[ j ];
					_SIO2alpha[ j     ] = ptr;
				}
				++j;
			}

			++i;
		}


		i = 0;
		while( i != n_alpha )
		{
			sio2ObjectRender( ( SIO2object * )_SIO2alpha[ i ],
							  _SIO2window,			
							  _SIO2camera,
							  !( _mask & SIO2_RENDER_NO_MATERIAL ),
							  !( _mask & SIO2_RENDER_NO_MATRIX ) );
			++i;
		}


		if( _SIO2alpha )
		{
			free( _SIO2alpha );
			_SIO2alpha = NULL;
		}
	}
	
	
	if( _mask & SIO2_RENDER_SOLID_OBJECT	   ||
		_mask & SIO2_RENDER_TRANSPARENT_OBJECT ||
		_mask & SIO2_RENDER_ALPHA_TESTED_OBJECT  )
	{ sio2ObjectReset(); }


	if( _mask & SIO2_RENDER_CLIPPED_OBJECT )
	{
		i = 0;
		
		while( i != _SIO2resource->n_object )
		{
			SIO2object *_SIO2object = ( SIO2object * )_SIO2resource->_SIO2object[ i ];

			if( !_SIO2object->dst )
			{
				sio2ObjectRender( _SIO2object,
								  _SIO2window,				
								  _SIO2camera,
								  0, 0 );
			}					  
			++i;
		}
	}

	
	if( _mask & SIO2_RENDER_EMITTER )
	{
		i = 0;
		while( i != _SIO2resource->n_emitter )
		{
			SIO2emitter *_SIO2emitter = ( SIO2emitter * )_SIO2resource->_SIO2emitter[ i ];
		
			sio2EmitterRender( _SIO2emitter,
							   _SIO2window,
							   !( _mask & SIO2_RENDER_NO_MATRIX ) );
			++i;
		}
		
		sio2EmitterReset();
	}
	
	
	if( _mask & SIO2_EVALUATE_SENSOR )
	{
		i = 0;
		while( i != _SIO2resource->n_sensor )
		{
			sio2SensorEvaluate( ( SIO2sensor * )_SIO2resource->_SIO2sensor[ i ] );
			++i;
		}	
	}
	
	
	if( _mask & SIO2_EVALUATE_TIMER )
	{
		i = 0;
		while( i != _SIO2resource->n_timer )
		{
			sio2TimerEvaluate( ( SIO2timer * )_SIO2resource->_SIO2timer[ i ] );
			++i;
		}	
	}
	
	
	if( _mask & SIO2_UPDATE_SOUND_STREAM )
	{
		i = 0;
		while( i != _SIO2resource->n_sound )
		{
			sio2SoundUpdateStream( ( SIO2sound * )_SIO2resource->_SIO2sound[ i ] );
			++i;
		}
	}
}


SIO2object *sio2ResourceSelect3D( SIO2resource *_SIO2resource,
								  SIO2camera   *_SIO2camera,
								  SIO2window   *_SIO2window,
								  vec2		   *_v )
{
	unsigned int i = 0,
				 selection = 0;
	
	col4 col;

	while( i != _SIO2resource->n_object )
	{
		SIO2object *_SIO2object = ( SIO2object * )_SIO2resource->_SIO2object[ i ];
		
		sio2GenColorIndex( selection, _SIO2object->col );
		
		if( sio2ObjectRender( _SIO2object,
							  _SIO2window,		
							  _SIO2camera,
							  0, 1 ) )
		{ ++selection; }
		else
		{ _SIO2object->col->a = 0; }
		
		++i;
	}

	glReadPixels( ( int )_v->x,
				  ( int )_v->y,
				  1, 1,
				  GL_RGBA, GL_UNSIGNED_BYTE, &col );
		
	if( !col.a )
	{ return NULL; }
	
	i = 0;
	while( i != _SIO2resource->n_object )
	{
		SIO2object *_SIO2object = ( SIO2object * )_SIO2resource->_SIO2object[ i ];
		
		if( !memcmp( &col, _SIO2object->col, 4 ) )
		{ return _SIO2object; }
		
		++i;
	}

	return NULL;
}


void sio2ResourceSetAmbientVolume( SIO2resource *_SIO2resource,
								   SIO2window   *_SIO2window )
{
	unsigned int i = 0;

	_SIO2window->volume = SIO2_CLAMP( _SIO2window->volume, 0.0f, 1.0f );
	
	while( i != _SIO2resource->n_sound )
	{
		SIO2sound *_SIO2sound = ( SIO2sound * )_SIO2resource->_SIO2sound[ i ];
		
		if( sio2IsStateEnabled( _SIO2sound->flags, SIO2_SOUND_AMBIENT ) )
		{ sio2SoundSetVolume( _SIO2sound, _SIO2window->volume ); }
	
		++i;
	}
	
	#ifdef SIO2_DEBUG_AL

		sio2ErrorAL( __FILE__, __FUNCTION__, __LINE__ );
	#endif	
}

								   
void sio2ResourceSetFxVolume( SIO2resource *_SIO2resource,
							  SIO2window   *_SIO2window )
{
	unsigned int i = 0;
	
	_SIO2window->fx_volume = SIO2_CLAMP( _SIO2window->fx_volume, 0.0f, 1.0f );
	
	while( i != _SIO2resource->n_sound )
	{
		SIO2sound *_SIO2sound = ( SIO2sound * )_SIO2resource->_SIO2sound[ i ];
		
		if( sio2IsStateEnabled( _SIO2sound->flags, SIO2_SOUND_FX ) )
		{ sio2SoundSetVolume( _SIO2sound, _SIO2window->fx_volume ); }
	
		++i;
	}
	
	#ifdef SIO2_DEBUG_AL

		sio2ErrorAL( __FILE__, __FUNCTION__, __LINE__ );
	#endif	
}


void sio2ResourceCull( SIO2resource *_SIO2resource,
					   SIO2camera   *_SIO2camera )
{
	unsigned int i = 0;	

	while( i != _SIO2resource->n_object )
	{
		SIO2object *_SIO2object = ( SIO2object * )_SIO2resource->_SIO2object[ i ];

		_SIO2object->dst = sio2CameraSphereDistInFrustum( _SIO2camera,
														  _SIO2object->_SIO2transform->loc,
														  _SIO2object->rad );
		++i;
	}
	
	
	i = 0;
	while( i != _SIO2resource->n_emitter )
	{
		SIO2emitter *_SIO2emitter = ( SIO2emitter * )_SIO2resource->_SIO2emitter[ i ];
		
		_SIO2emitter->dst = sio2CameraSphereDistInFrustum( _SIO2camera,
														   _SIO2emitter->_SIO2transform->loc,
														   _SIO2emitter->rad );
		++i;
	}
}


SIO2image *sio2ResourceGetImage( SIO2resource *_SIO2resource,
								 char		  *_name )
{
	return ( SIO2image * )sio2ResourceGet( _SIO2resource,
										   SIO2_IMAGE,
										   _name );
}


SIO2widget *sio2ResourceGetWidget( SIO2resource *_SIO2resource,
								   char		    *_name )
{
	return ( SIO2widget * )sio2ResourceGet( _SIO2resource,
										    SIO2_WIDGET,
										    _name );
}


SIO2camera *sio2ResourceGetCamera( SIO2resource *_SIO2resource,
								   char		    *_name )
{
	return ( SIO2camera * )sio2ResourceGet( _SIO2resource,
										    SIO2_CAMERA,
										    _name );
}


SIO2material *sio2ResourceGetMaterial( SIO2resource *_SIO2resource,
								       char		    *_name )
{
	return ( SIO2material * )sio2ResourceGet( _SIO2resource,
										      SIO2_MATERIAL,
										      _name );
}


SIO2soundbuffer *sio2ResourceGetSoundBuffer( SIO2resource *_SIO2resource,
											 char		  *_name )
{
	return ( SIO2soundbuffer * )sio2ResourceGet( _SIO2resource,
												 SIO2_SOUNDBUFFER,
												 _name );
}


SIO2sound *sio2ResourceGetSound( SIO2resource *_SIO2resource,
								 char		  *_name )
{
	return ( SIO2sound * )sio2ResourceGet( _SIO2resource,
										   SIO2_SOUND,
										   _name );
}


SIO2video *sio2ResourceGetVideo( SIO2resource *_SIO2resource,
								 char		  *_name )
{
	return ( SIO2video * )sio2ResourceGet( _SIO2resource,
										   SIO2_VIDEO,
										   _name );
}


SIO2object *sio2ResourceGetObject( SIO2resource *_SIO2resource,
								   char		    *_name )
{
	return ( SIO2object * )sio2ResourceGet( _SIO2resource,
										    SIO2_OBJECT,
										    _name );
}


SIO2physic *sio2ResourceGetPhysic( SIO2resource *_SIO2resource,
								   char		    *_name )
{
	return ( SIO2physic * )sio2ResourceGet( _SIO2resource,
										    SIO2_PHYSIC,
										    _name );
}


SIO2sensor *sio2ResourceGetSensor( SIO2resource *_SIO2resource,
								   char		    *_name )
{
	return ( SIO2sensor * )sio2ResourceGet( _SIO2resource,
										    SIO2_SENSOR,
										    _name );
}


SIO2emitter *sio2ResourceGetEmitter( SIO2resource *_SIO2resource,
								     char		  *_name )
{
	return ( SIO2emitter * )sio2ResourceGet( _SIO2resource,
										     SIO2_EMITTER,
										     _name );
}


SIO2mist *sio2ResourceGetMist( SIO2resource *_SIO2resource,
							   char		    *_name )
{
	return ( SIO2mist * )sio2ResourceGet( _SIO2resource,
										  SIO2_MIST,
										  _name );
}


SIO2font *sio2ResourceGetFont( SIO2resource *_SIO2resource,
							   char		    *_name )
{
	return ( SIO2font * )sio2ResourceGet( _SIO2resource,
										  SIO2_FONT,
										  _name );
}


SIO2lamp *sio2ResourceGetLamp( SIO2resource *_SIO2resource,
							   char		    *_name )
{
	return ( SIO2lamp * )sio2ResourceGet( _SIO2resource,
										  SIO2_LAMP,
										  _name );
}


SIO2script *sio2ResourceGetScript( SIO2resource *_SIO2resource,
								   char		    *_name )
{
	return ( SIO2script * )sio2ResourceGet( _SIO2resource,
										    SIO2_SCRIPT,
										    _name );
}


SIO2ipo *sio2ResourceGetIpo( SIO2resource *_SIO2resource,
							 char		  *_name )
{
	return ( SIO2ipo * )sio2ResourceGet( _SIO2resource,
										 SIO2_IPO,
										 _name );
}


SIO2action *sio2ResourceGetAction( SIO2resource *_SIO2resource,
								   char			*_name )
{
	return ( SIO2action * )sio2ResourceGet( _SIO2resource,
											SIO2_ACTION,
											_name );
}


SIO2timer *sio2ResourceGetTimer( SIO2resource *_SIO2resource,
								 char		  *_name )
{
	return ( SIO2timer * )sio2ResourceGet( _SIO2resource,
										   SIO2_TIMER,
										   _name );
}
