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


#ifndef SIO2_RESOURCE_H
#define SIO2_RESOURCE_H

/*
	The unzip buffer have been set to 128k in unzip.c
	
	#define UNZ_BUFSIZE ( 131072 )			
*/
#include "../zlib/unzip.h"


typedef enum
{
	// .sio2
	SIO2_OBJECT = 0,
	SIO2_MATERIAL,
	SIO2_LAMP,	
	SIO2_CAMERA,	
	SIO2_IMAGE,
	SIO2_SOUNDBUFFER,
	SIO2_SCRIPT,
	SIO2_IPO,
	
	// misc.
	SIO2_ACTION,	
	SIO2_VIDEO,	
	SIO2_SOUND,
	SIO2_WIDGET,
	SIO2_PHYSIC,
	SIO2_SENSOR,
	SIO2_EMITTER,
	SIO2_MIST,
	SIO2_FONT,
	SIO2_TIMER,
	
	SIO2_RESOURCE_ALL
	
} SIO2_RESOURCE_TYPE;


typedef enum
{
	SIO2_RENDER_SOLID_OBJECT		= ( 1 << 0  ),
	SIO2_RENDER_TRANSPARENT_OBJECT	= ( 1 << 1  ),
	SIO2_RENDER_ALPHA_TESTED_OBJECT	= ( 1 << 2  ),
	SIO2_RENDER_NO_MATERIAL			= ( 1 << 3  ),
	SIO2_RENDER_NO_MATRIX			= ( 1 << 4  ),	
	SIO2_RENDER_CLIPPED_OBJECT		= ( 1 << 5  ),
	SIO2_RENDER_LAMP				= ( 1 << 6  ),
	SIO2_RENDER_EMITTER				= ( 1 << 7  ),
	SIO2_RENDER_IPO					= ( 1 << 8  ),
	SIO2_EVALUATE_SENSOR			= ( 1 << 9 ),
	SIO2_EVALUATE_TIMER				= ( 1 << 10 ),
	SIO2_UPDATE_SOUND_STREAM		= ( 1 << 11 )

} SIO2_RESOURCE_MASK;


typedef void( SIO2resourcecustomload( SIO2stream * ) );


typedef struct
{
	char					name[ SIO2_MAX_CHAR ];

	unzFile					uf;
	unz_global_info			gi;

	unsigned int			n_image;
	void					**_SIO2image;
	
	unsigned int			n_widget;
	void					**_SIO2widget;

	unsigned int			n_camera;
	void					**_SIO2camera;

	unsigned int			n_material;
	void					**_SIO2material;

	unsigned int			n_soundbuffer;
	void					**_SIO2soundbuffer;

	unsigned int			n_sound;
	void					**_SIO2sound;
	
	unsigned int			n_video;
	void					**_SIO2video;

	unsigned int			n_object;
	void					**_SIO2object;
	
	unsigned int			n_physic;
	void					**_SIO2physic;

	unsigned int			n_sensor;
	void					**_SIO2sensor;

	unsigned int			n_emitter;
	void					**_SIO2emitter;
	
	unsigned int			n_mist;
	void					**_SIO2mist;

	unsigned int			n_font;
	void					**_SIO2font;
	
	unsigned int			n_lamp;
	void					**_SIO2lamp;

	unsigned int			n_script;
	void					**_SIO2script;

	unsigned int			n_ipo;
	void					**_SIO2ipo;
	
	unsigned int			n_action;
	void					**_SIO2action;

	unsigned int			n_timer;
	void					**_SIO2timer;
	
	unsigned int			n_entry;
	SIO2entry				*_SIO2entry;

	SIO2resourcecustomload	*_SIO2resourcecustomload;

	void					*userdata;

} SIO2resource;


SIO2resource *sio2ResourceInit( char * );

SIO2resource *sio2ResourceFree( SIO2resource * );

unsigned int sio2ResourceGetVRAMSize( SIO2resource * );

void sio2ResourceAdd( SIO2resource *, unsigned char, void * );

void sio2ResourceDel( SIO2resource *, unsigned char, void * );

void sio2ResourceUnload( SIO2resource *, unsigned char );

void sio2ResourceUnloadAll( SIO2resource * );

void sio2ResourceUpdateAllWidgetBoundaries( SIO2resource *, SIO2window * );

void sio2ResourceDispatchEvents( SIO2resource *, SIO2window *, unsigned char, unsigned char );
								  
void *sio2ResourceGet( SIO2resource *, unsigned char, char * );

unsigned char sio2ResourceOpen( SIO2resource *, const char *, unsigned char );

void sio2ResourceClose( SIO2resource * );

void sio2ResourceCreateDictionary( SIO2resource * );

void sio2ResourceAddEntry( SIO2resource *, const char *, SIO2parsercallback *, SIO2parsercallback * );

unsigned char sio2ResourceExtractFile( SIO2resource *, SIO2stream *, const char *, char * );
							  
void sio2ResourceExtract( SIO2resource *, char * );

SIO2stream *sio2ResourceDispatchStream( SIO2resource *, SIO2stream * );

void sio2ResourceBindAllImages( SIO2resource * );

void sio2ResourceBindImage( SIO2resource *, SIO2material * );

void sio2ResourceBindObjectIpo( SIO2resource *, SIO2object * );

void sio2ResourceBindCameraIpo( SIO2resource *, SIO2camera * );

void sio2ResourceBindLampIpo( SIO2resource *, SIO2lamp * );

void sio2ResourceBindAllIpos( SIO2resource * );

void sio2ResourceBindAllSoundBuffers( SIO2resource * );

void sio2ResourceBindSoundBuffer( SIO2resource *, SIO2material * );

void sio2ResourceBindAllMaterials( SIO2resource *_SIO2resource );

void sio2ResourceBindMaterial( SIO2resource *, SIO2object * );

void sio2ResourceBindAllInstances( SIO2resource * );

void sio2ResourceBindAllMatrix( SIO2resource * );

void sio2ResourceBindInstance( SIO2resource *, SIO2object * );

void sio2ResourceBindAllPhysicObjects( SIO2resource *, SIO2physic * );

void sio2ResourceGenId( SIO2resource * );

void sio2ResourceBindAllSounds( SIO2resource * );

void sio2ResourceRender( SIO2resource *, SIO2window *, SIO2camera *, int );

SIO2object *sio2ResourceSelect3D( SIO2resource *, SIO2camera *, SIO2window *, vec2 * );

void sio2ResourceSetAmbientVolume( SIO2resource *, SIO2window * );
								   
void sio2ResourceSetFxVolume( SIO2resource *, SIO2window * );

void sio2ResourceCull( SIO2resource *, SIO2camera * );

SIO2image *sio2ResourceGetImage( SIO2resource *, char * );

SIO2widget *sio2ResourceGetWidget( SIO2resource *, char * );

SIO2camera *sio2ResourceGetCamera( SIO2resource *, char * );

SIO2material *sio2ResourceGetMaterial( SIO2resource *, char * );

SIO2soundbuffer *sio2ResourceGetSoundBuffer( SIO2resource *, char * );

SIO2sound *sio2ResourceGetSound( SIO2resource *, char * );

SIO2video *sio2ResourceGetVideo( SIO2resource *, char * );

SIO2object *sio2ResourceGetObject( SIO2resource *, char * );

SIO2physic *sio2ResourceGetPhysic( SIO2resource *, char * );

SIO2sensor *sio2ResourceGetSensor( SIO2resource *, char * );

SIO2emitter *sio2ResourceGetEmitter( SIO2resource *, char * );

SIO2mist *sio2ResourceGetMist( SIO2resource *, char * );

SIO2font *sio2ResourceGetFont( SIO2resource *, char * );

SIO2lamp *sio2ResourceGetLamp( SIO2resource *, char * );

SIO2script *sio2ResourceGetScript( SIO2resource *, char * );

SIO2ipo *sio2ResourceGetIpo( SIO2resource *, char * );

SIO2action *sio2ResourceGetAction( SIO2resource *, char * );

SIO2timer *sio2ResourceGetTimer( SIO2resource *, char * );

#endif
