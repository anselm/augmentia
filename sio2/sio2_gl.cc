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


#undef glAlphaFunc
#undef glClearColor
#undef glClearDepthf
#undef glClipPlanef
#undef glColor4f
#undef glDepthRangef
#undef glFogf
#undef glFogfv
#undef glFrustumf
#undef glGetClipPlanef
#undef glGetFloatv
#undef glGetLightfv
#undef glGetMaterialfv
#undef glGetTexEnvfv
#undef glGetTexParameterfv
#undef glLightModelf
#undef glLightModelfv
#undef glLightf
#undef glLightfv
#undef glLineWidth
#undef glLoadMatrixf
#undef glMaterialf
#undef glMaterialfv
#undef glMultMatrixf
#undef glMultiTexCoord4f
#undef glNormal3f
#undef glOrthof
#undef glPointParameterf
#undef glPointParameterfv
#undef glPointSize
#undef glPolygonOffset
#undef glRotatef
#undef glScalef
#undef glTexEnvf
#undef glTexEnvfv
#undef glTexParameterf
#undef glTexParameterfv
#undef glTranslatef
#undef glActiveTexture
#undef glBindBuffer
#undef glBindTexture
#undef glBlendFunc
#undef glBufferData
#undef glBufferSubData
#undef glClear
#undef glClearStencil
#undef glClientActiveTexture
#undef glColor4ub
#undef glColorMask
#undef glColorPointer
#undef glCompressedTexImage2D
#undef glCompressedTexSubImage2D
#undef glCopyTexImage2D
#undef glCopyTexSubImage2D
#undef glCullFace
#undef glDeleteBuffers
#undef glDeleteTextures
#undef glDepthFunc
#undef glDepthMask
#undef glDisable
#undef glDisableClientState
#undef glDrawArrays
#undef glDrawElements
#undef glEnable
#undef glEnableClientState
#undef glFinish
#undef glFlush
#undef glFrontFace
#undef glGetBooleanv
#undef glGetBufferParameteriv
#undef glGenBuffers
#undef glGenTextures
#undef glGetError
#undef glGetIntegerv
#undef glGetPointerv
#undef glGetString
#undef glGetTexEnviv
#undef glGetTexParameteriv
#undef glHint
#undef glIsBuffer
#undef glIsEnabled
#undef glIsTexture
#undef glLoadIdentity
#undef glLogicOp
#undef glMatrixMode
#undef glNormalPointer
#undef glPixelStorei
#undef glPopMatrix
#undef glPushMatrix
#undef glReadPixels
#undef glSampleCoverage
#undef glScissor
#undef glShadeModel
#undef glStencilFunc
#undef glStencilMask
#undef glStencilOp
#undef glTexCoordPointer
#undef glTexEnvi
#undef glTexEnviv
#undef glTexImage2D
#undef glTexParameteri
#undef glTexParameteriv
#undef glTexSubImage2D
#undef glVertexPointer
#undef glViewport
#undef glCurrentPaletteMatrixOES
#undef glLoadPaletteFromModelViewMatrixOES
#undef glMatrixIndexPointerOES
#undef glWeightPointerOES
#undef glPointSizePointerOES
#undef glDrawTexfOES
#undef glDrawTexfvOES


unsigned int sio2_start = 0,
			 sio2_end   = 0;


char str1[ SIO2_MAX_CHAR ] = {""},
	 str2[ SIO2_MAX_CHAR ] = {""};


unsigned int sio2GetMicroTime( void )
{
	struct timeval t;

	gettimeofday( &t, NULL );

	return t.tv_usec;
}


void sio2GetState( unsigned int _f )
{
	switch( _f )
	{
		case GL_FOG:
		{ sio2StringCpy( str1, "GL_FOG" ); break; }

		case GL_LIGHTING:
		{ sio2StringCpy( str1, "GL_LIGHTING" ); break; }

		case GL_TEXTURE_2D:
		{ sio2StringCpy( str1, "GL_TEXTURE_2D" ); break; }				

		case GL_CULL_FACE:
		{ sio2StringCpy( str1, "GL_CULL_FACE" ); break; }
		
		case GL_ALPHA_TEST:
		{ sio2StringCpy( str1, "GL_ALPHA_TEST" ); break; }
		
		case GL_BLEND:
		{ sio2StringCpy( str1, "GL_BLEND" ); break; }
		
		case GL_COLOR_LOGIC_OP:
		{ sio2StringCpy( str1, "GL_COLOR_LOGIC_OP" ); break; }

		case GL_DITHER:
		{ sio2StringCpy( str1, "GL_DITHER" ); break; }

		case GL_STENCIL_TEST:
		{ sio2StringCpy( str1, "GL_STENCIL_TEST" ); break; }

		case GL_DEPTH_TEST:
		{ sio2StringCpy( str1, "GL_DEPTH_TEST" ); break; }

		case GL_LIGHT0:
		{ sio2StringCpy( str1, "GL_LIGHT0" ); break; }

		case GL_LIGHT1:
		{ sio2StringCpy( str1, "GL_LIGHT1" ); break; }

		case GL_LIGHT2:
		{ sio2StringCpy( str1, "GL_LIGHT2" ); break; }

		case GL_LIGHT3:
		{ sio2StringCpy( str1, "GL_LIGHT3" ); break; }
		
		case GL_LIGHT4:
		{ sio2StringCpy( str1, "GL_LIGHT4" ); break; }
		
		case GL_LIGHT5:
		{ sio2StringCpy( str1, "GL_LIGHT5" ); break; }
		
		case GL_LIGHT6:
		{ sio2StringCpy( str1, "GL_LIGHT6" ); break; }
		
		case GL_LIGHT7:
		{ sio2StringCpy( str1, "GL_LIGHT7" ); break; }																														

		case GL_POINT_SMOOTH:
		{ sio2StringCpy( str1, "GL_POINT_SMOOTH" ); break; }																														

		case GL_LINE_SMOOTH:
		{ sio2StringCpy( str1, "GL_LINE_SMOOTH" ); break; }		

		case GL_SCISSOR_TEST:
		{ sio2StringCpy( str1, "GL_SCISSOR_TEST" ); break; }		

		case GL_COLOR_MATERIAL:
		{ sio2StringCpy( str1, "GL_COLOR_MATERIAL" ); break; }		
		
		case GL_NORMALIZE:
		{ sio2StringCpy( str1, "GL_NORMALIZE" ); break; }
		
		case GL_RESCALE_NORMAL:
		{ sio2StringCpy( str1, "GL_RESCALE_NORMAL" ); break; }
		
		case GL_POLYGON_OFFSET_FILL:
		{ sio2StringCpy( str1, "GL_POLYGON_OFFSET_FILL" ); break; }
		
		case GL_VERTEX_ARRAY:
		{ sio2StringCpy( str1, "GL_VERTEX_ARRAY" ); break; }				

		case GL_NORMAL_ARRAY:
		{ sio2StringCpy( str1, "GL_NORMAL_ARRAY" ); break; }

		case GL_COLOR_ARRAY:
		{ sio2StringCpy( str1, "GL_COLOR_ARRAY" ); break; }

		case GL_TEXTURE_COORD_ARRAY:
		{ sio2StringCpy( str1, "GL_TEXTURE_COORD_ARRAY" ); break; }

		case GL_MULTISAMPLE:
		{ sio2StringCpy( str1, "GL_MULTISAMPLE" ); break; }
		
		case GL_SAMPLE_ALPHA_TO_COVERAGE:
		{ sio2StringCpy( str1, "GL_SAMPLE_ALPHA_TO_COVERAGE" ); break; }	

		case GL_SAMPLE_ALPHA_TO_ONE:
		{ sio2StringCpy( str1, "GL_SAMPLE_ALPHA_TO_ONE" ); break; }

		case GL_SAMPLE_COVERAGE:
		{ sio2StringCpy( str1, "GL_SAMPLE_COVERAGE" ); break; }													
	}
}


void sio2GetFace( unsigned int _f )
{
	switch( _f )
	{
		case GL_FRONT:
		{ sio2StringCpy( str1, "GL_FRONT" ); break; }
		
		case GL_BACK:
		{ sio2StringCpy( str1, "GL_BACK" ); break; }

		case GL_FRONT_AND_BACK:
		{ sio2StringCpy( str1, "GL_FRONT_AND_BACK" ); break; }
	}
}


void sio2GetLightParam( unsigned int _lp )
{
	switch( _lp )
	{
		case GL_AMBIENT:
		{ sio2StringCpy( str2, "GL_AMBIENT" ); break; }
		
		case GL_DIFFUSE:
		{ sio2StringCpy( str2, "GL_DIFFUSE" ); break; }

		case GL_SPECULAR:
		{ sio2StringCpy( str2, "GL_SPECULAR" ); break; }

		case GL_SHININESS:
		{ sio2StringCpy( str2, "GL_SHININESS" ); break; }

		case GL_POSITION:
		{ sio2StringCpy( str2, "GL_POSITION" ); break; }

		case GL_SPOT_DIRECTION:
		{ sio2StringCpy( str2, "GL_SPOT_DIRECTION" ); break; }		

		case GL_SPOT_EXPONENT:
		{ sio2StringCpy( str2, "GL_SPOT_EXPONENT" ); break; }	

		case GL_SPOT_CUTOFF:
		{ sio2StringCpy( str2, "GL_SPOT_CUTOFF" ); break; }	

		case GL_CONSTANT_ATTENUATION:
		{ sio2StringCpy( str2, "GL_CONSTANT_ATTENUATION" ); break; }					

		case GL_LINEAR_ATTENUATION:
		{ sio2StringCpy( str2, "GL_LINEAR_ATTENUATION" ); break; }

		case GL_QUADRATIC_ATTENUATION:
		{ sio2StringCpy( str2, "GL_QUADRATIC_ATTENUATION" ); break; }		
	}
}


void sio2GetTexture( unsigned int _t )
{
	switch( _t )
	{
		case GL_TEXTURE0:
		{ sio2StringCpy( str1, "GL_TEXTURE0" ); break; }

		case GL_TEXTURE1:
		{ sio2StringCpy( str1, "GL_TEXTURE1" ); break; }	
	}
}


void sio2AlphaFunc (GLenum func, GLclampf ref)
{
	sio2_start = sio2GetMicroTime();
	
	glAlphaFunc( func, ref );
	
	sio2_end = sio2GetMicroTime();
	
	printf( "glAlphaFunc( %d, %f )::%dus\n", func, ref, ( sio2_end - sio2_start ) );
	
	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif	
}


void sio2ClearColor (GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
{
	sio2_start = sio2GetMicroTime();
	
	glClearColor( red, green, blue, alpha );
	
	sio2_end = sio2GetMicroTime();
	
	printf( "glClearColor( %f, %f, %f, %f )::%dus\n", red, green, blue, alpha, ( sio2_end - sio2_start ) );
	
	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif	
}


void sio2ClearDepthf (GLclampf depth)
{
	sio2_start = sio2GetMicroTime();
	
	glClearDepthf( depth );
	
	sio2_end = sio2GetMicroTime();
	
	printf( "glClearDepthf( %f )::%dus\n", depth, ( sio2_end - sio2_start ) );	

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}


void sio2ClipPlanef (GLenum plane, const GLfloat *equation)
{
	sio2_start = sio2GetMicroTime();

	glClipPlanef( plane, equation );
	
	sio2_end = sio2GetMicroTime();
	
	printf( "glClipPlanef( %d, 0x%x )::%dus\n", plane, equation, ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}


void sio2Color4f (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
	sio2_start = sio2GetMicroTime();
	
	glColor4f( red, green, blue, alpha );
	
	sio2_end = sio2GetMicroTime();
	
	printf( "glColor4f( %f, %f, %f, %f )::%dus\n", red, green, blue, alpha, ( sio2_end - sio2_start ) );	

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}


void sio2DepthRangef (GLclampf zNear, GLclampf zFar)
{
	sio2_start = sio2GetMicroTime();

	glDepthRangef( zNear, zFar );
	
	sio2_end = sio2GetMicroTime();
	
	printf( "glDepthRangef( %f, %f )::%dus\n", zNear, zFar, ( sio2_end - sio2_start ) );	

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}


void sio2Fogf (GLenum pname, GLfloat param)
{
	sio2_start = sio2GetMicroTime();

	glFogf( pname, param );
	
	sio2_end = sio2GetMicroTime();
	
	printf( "glFogf( %d, %f )::%dus\n", pname, param, ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}


void sio2Fogfv (GLenum pname, const GLfloat *params)
{
	sio2_start = sio2GetMicroTime();

	glFogfv( pname, params );
	
	sio2_end = sio2GetMicroTime();
	
	printf( "glFogfv( %d, 0x%x )::%dus\n", pname, params, ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}


void sio2Frustumf (GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar)
{
	sio2_start = sio2GetMicroTime();

	glFrustumf( left, right, bottom, top, zNear, zFar);
	
	sio2_end = sio2GetMicroTime();
	
	printf( "glFrustumf( %f, %f, %f, %f, %f, %f)::%dus\n", left, right, bottom, top, zNear, zFar, ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}


void sio2GetClipPlanef (GLenum pname, GLfloat *equation)
{
	sio2_start = sio2GetMicroTime();

	glGetClipPlanef(pname, equation);

	sio2_end = sio2GetMicroTime();
	
	printf( "glGetClipPlanef( %d, 0x%x )::%dus\n", pname, equation, ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}


void sio2GetFloatv (GLenum pname, GLfloat *params)
{
	sio2_start = sio2GetMicroTime();

	glGetFloatv( pname, params );

	sio2_end = sio2GetMicroTime();
	
	printf( "glGetFloatv( %d, 0x%x )::%dus\n", pname, params, ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}


void sio2GetLightfv (GLenum light, GLenum pname, GLfloat *params)
{
	sio2_start = sio2GetMicroTime();

	glGetLightfv(light, pname, params );

	sio2_end = sio2GetMicroTime();
	
	printf( "glGetLightfv( %d, %d, 0x%x )::%dus\n", light, pname, params, ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}


void sio2GetMaterialfv (GLenum face, GLenum pname, GLfloat *params)
{
	sio2_start = sio2GetMicroTime();

	glGetMaterialfv( face, pname, params );

	sio2_end = sio2GetMicroTime();
	
	printf( "glGetMaterialfv( %d, %d, 0x%x )::%dus\n", face, pname, params, ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}


void sio2GetTexEnvfv (GLenum env, GLenum pname, GLfloat *params)
{
	sio2_start = sio2GetMicroTime();

	glGetTexEnvfv( env, pname, params );

	sio2_end = sio2GetMicroTime();
	
	printf( "glGetTexEnvfv( %d, %d, 0x%x )::%dus\n", env, pname, params, ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}


void sio2GetTexParameterfv (GLenum target, GLenum pname, GLfloat *params)
{
	sio2_start = sio2GetMicroTime();

	glGetTexParameterfv( target, pname, params );

	sio2_end = sio2GetMicroTime();
	
	printf( "glGetTexEnvfv( %d, %d, 0x%x )::%dus\n", target, pname, params, ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}


void sio2LightModelf (GLenum pname, GLfloat param)
{
	sio2_start = sio2GetMicroTime();

	glLightModelf( pname, param );

	sio2_end = sio2GetMicroTime();
	
	printf( "glLightModelf( GL_LIGHT_MODEL_TWO_SIDE, %f )::%dus\n", param, ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}


void sio2LightModelfv (GLenum pname, const GLfloat *params)
{
	sio2_start = sio2GetMicroTime();

	glLightModelfv( pname, params);

	sio2_end = sio2GetMicroTime();
	
	printf( "glLightModelfv( GL_LIGHT_MODEL_AMBIENT, 0x%x )::%dus\n", params, ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}


void sio2Lightf (GLenum light, GLenum pname, GLfloat param)
{
	sio2_start = sio2GetMicroTime();

	glLightf( light, pname, param );

	sio2GetState( light );
	
	sio2GetLightParam( pname );
	
	sio2_end = sio2GetMicroTime();
	
	printf( "glLightf( %s, %s, %f )::%dus\n", str1, str2, param, ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}


void sio2Lightfv (GLenum light, GLenum pname, const GLfloat *params)
{
	sio2_start = sio2GetMicroTime();

	glLightfv( light, pname, params );

	sio2GetState( light );
	
	sio2GetLightParam( pname );

	sio2_end = sio2GetMicroTime();
	
	printf( "glLightfv( %s, %s, 0x%x )::%dus\n", str1, str2, params, ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}


void sio2LineWidth (GLfloat width)
{
	sio2_start = sio2GetMicroTime();

	glLineWidth( width );

	sio2_end = sio2GetMicroTime();
	
	printf( "glLineWidth( %f )::%dus\n", width, ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}


void sio2LoadMatrixf (const GLfloat *m)
{
	sio2_start = sio2GetMicroTime();

	glLoadMatrixf( m );

	sio2_end = sio2GetMicroTime();
	
	printf( "glLoadMatrixf( 0x%x )::%dus\n", m, ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}


void sio2Materialf (GLenum face, GLenum pname, GLfloat param)
{
	sio2_start = sio2GetMicroTime();

	glMaterialf( face, pname, param );

	sio2GetFace( face );
	
	sio2GetLightParam( pname );

	sio2_end = sio2GetMicroTime();
	
	printf( "glMaterialf( %s, %s, %f )::%dus\n", str1, str2, param, ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}


void sio2Materialfv (GLenum face, GLenum pname, const GLfloat *params)
{
	sio2_start = sio2GetMicroTime();

	glMaterialfv( face, pname, params );

	sio2GetFace( face );
	
	sio2GetLightParam( pname );

	sio2_end = sio2GetMicroTime();
	
	printf( "glMaterialfv( %s, %s, 0x%x )::%dus\n", str1, str2, params, ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}


void sio2MultMatrixf (const GLfloat *m)
{
	sio2_start = sio2GetMicroTime();

	glMultMatrixf( m );

	sio2_end = sio2GetMicroTime();
	
	printf( "glMultMatrixf( 0x%x )::%dus\n", m, ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}


void sio2MultiTexCoord4f (GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q)
{
	sio2_start = sio2GetMicroTime();

	glMultiTexCoord4f( target, s, t, r, q );

	sio2_end = sio2GetMicroTime();
	
	printf( "glMultiTexCoord4f( %d, %f, %f, %f, %f )::%dus\n", target, s, t, r, q, ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}


void sio2Normal3f (GLfloat nx, GLfloat ny, GLfloat nz)
{
	sio2_start = sio2GetMicroTime();

	glNormal3f( nx, ny, nz );

	sio2_end = sio2GetMicroTime();
	
	printf( "glNormal3f( %f, %f, %f )::%dus\n", nx, ny, nz, ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}


void sio2Orthof (GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar)
{
	sio2_start = sio2GetMicroTime();

	glOrthof( left, right, bottom, top, zNear, zFar );

	sio2_end = sio2GetMicroTime();
	
	printf( "glOrthof( %f, %f, %f, %f, %f, %f )::%dus\n", left, right, bottom, top, zNear, zFar, ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}


void sio2PointParameterf (GLenum pname, GLfloat param)
{
	sio2_start = sio2GetMicroTime();

	glPointParameterf( pname, param );

	sio2_end = sio2GetMicroTime();
	
	printf( "glPointParameterf( %d, %f )::%dus\n", pname, param, ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}


void sio2PointParameterfv (GLenum pname, const GLfloat *params)
{
	sio2_start = sio2GetMicroTime();

	glPointParameterfv( pname, params );

	sio2_end = sio2GetMicroTime();
	
	printf( "glPointParameterf( %d, 0x%x )::%dus\n", pname, params, ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}


void sio2PointSize (GLfloat size)
{
	sio2_start = sio2GetMicroTime();

	glPointSize( size );

	sio2_end = sio2GetMicroTime();
	
	printf( "glPointSize( %f )::%dus\n", size, ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}


void sio2PolygonOffset (GLfloat factor, GLfloat units)
{
	sio2_start = sio2GetMicroTime();

	glPolygonOffset( factor, units );

	sio2_end = sio2GetMicroTime();
	
	printf( "glPolygonOffset( %f, %f )::%dus\n", factor, units, ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}


void sio2Rotatef (GLfloat ansio2e, GLfloat x, GLfloat y, GLfloat z)
{
	sio2_start = sio2GetMicroTime();

	glRotatef( ansio2e, x, y, z );

	sio2_end = sio2GetMicroTime();
	
	printf( "glRotatef( %f, %f, %f, %f )::%dus\n", ansio2e, x, y, z, ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}



void sio2Scalef (GLfloat x, GLfloat y, GLfloat z)
{
	sio2_start = sio2GetMicroTime();

	glScalef( x, y, z );

	sio2_end = sio2GetMicroTime();
	
	printf( "glScalef( %f, %f, %f )::%dus\n", x, y, z, ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}



void sio2TexEnvf (GLenum target, GLenum pname, GLfloat param)
{
	sio2_start = sio2GetMicroTime();

	glTexEnvf( target, pname, param );

	sio2_end = sio2GetMicroTime();
	
	printf( "glTexEnvf( %d, %d, %f )::%dus\n", target, pname, param, ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}



void sio2TexEnvfv (GLenum target, GLenum pname, const GLfloat *params)
{
	sio2_start = sio2GetMicroTime();

	glTexEnvfv( target, pname, params );

	sio2_end = sio2GetMicroTime();
	
	printf( "glTexEnvfv( %d, %d, 0x%x )::%dus\n", target, pname, params, ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}



void sio2TexParameterf (GLenum target, GLenum pname, GLfloat param)
{
	sio2_start = sio2GetMicroTime();

	glTexParameterf( target, pname, param );
	
	sio2_end = sio2GetMicroTime();
	
	printf( "glTexParameterf( %d, %d, 0x%x )::%dus\n", target, pname, param, ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}


void sio2TexParameterfv (GLenum target, GLenum pname, const GLfloat *params)
{
	sio2_start = sio2GetMicroTime();

	glTexParameterfv( target, pname, params );

	sio2_end = sio2GetMicroTime();
	
	printf( "glTexParameterfv( %d, %d, 0x%x )::%dus\n", target, pname, params, ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}


void sio2Translatef (GLfloat x, GLfloat y, GLfloat z)
{
	sio2_start = sio2GetMicroTime();

	glTranslatef( x, y, z );

	sio2_end = sio2GetMicroTime();
	
	printf( "glTranslatef( %f, %f, %f )::%dus\n", x, y, z, ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}



void sio2ActiveTexture (GLenum texture)
{
	sio2_start = sio2GetMicroTime();

	glActiveTexture( texture );

	sio2GetTexture( texture );

	sio2_end = sio2GetMicroTime();
	
	printf( "glActiveTexture( %s )::%dus\n", str1, ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}


void sio2BindBuffer (GLenum target, GLuint buffer)
{
	sio2_start = sio2GetMicroTime();

	glBindBuffer( target, buffer );

	switch( target )
	{
		case GL_ARRAY_BUFFER:
		{ sio2StringCpy( str1, "GL_ARRAY_BUFFER" ); break; }
		
		case GL_ELEMENT_ARRAY_BUFFER:
		{ sio2StringCpy( str1, "GL_ELEMENT_ARRAY_BUFFER" ); break; }
	}

	sio2_end = sio2GetMicroTime();
	
	printf( "glBindBuffer( %s, %d )::%dus\n", str1, buffer, ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}



void sio2BindTexture (GLenum target, GLuint texture)
{
	sio2_start = sio2GetMicroTime();

	glBindTexture( target, texture );

	sio2_end = sio2GetMicroTime();
	
	printf( "glBindTexture( GL_TEXTURE_2D, %d )::%dus\n", texture, ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}



void sio2BlendFunc (GLenum sfactor, GLenum dfactor)
{
	sio2_start = sio2GetMicroTime();

	glBlendFunc( sfactor, dfactor );

	sio2_end = sio2GetMicroTime();
	
	printf( "glBlendFunc( %d, %d )::%dus\n", sfactor, dfactor, ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}



void sio2BufferData (GLenum target, GLsizeiptr size, const GLvoid *data, GLenum usage)
{
	sio2_start = sio2GetMicroTime();

	glBufferData( target, size, data, usage );

	switch( target )
	{
		case GL_ARRAY_BUFFER:
		{ sio2StringCpy( str1, "GL_ARRAY_BUFFER" ); break; }

		case GL_ELEMENT_ARRAY_BUFFER:
		{ sio2StringCpy( str1, "GL_ELEMENT_ARRAY_BUFFER" ); break; }
	}

	sio2_end = sio2GetMicroTime();
	
	printf( "glBufferData( %s, %d, 0x%x, %d )::%dus\n", str1, size, data, usage, ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}



void sio2BufferSubData (GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid *data)
{
	sio2_start = sio2GetMicroTime();

	glBufferSubData( target, offset, size, data );

	sio2_end = sio2GetMicroTime();
	
	printf( "glBufferSubData( %d, %d, %d, 0x%x )::%dus\n", target, offset, size, data, ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}



void sio2Clear (GLbitfield mask)
{
	sio2_start = sio2GetMicroTime();

	glClear( mask );

	sio2_end = sio2GetMicroTime();
	
	printf( "glClear( %d )::%dus\n", mask, ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}



void sio2ClearStencil (GLint s)
{
	sio2_start = sio2GetMicroTime();

	glClearStencil( s );

	sio2_end = sio2GetMicroTime();
	
	printf( "glClearStencil( %d )::%dus\n", s, ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}



void sio2ClientActiveTexture (GLenum texture)
{
	sio2_start = sio2GetMicroTime();

	glClientActiveTexture( texture );

	switch( texture )
	{
		case GL_TEXTURE0:
		{ sio2StringCpy( str1, "GL_TEXTURE0" ); break; }

		case GL_TEXTURE1:
		{ sio2StringCpy( str1, "GL_TEXTURE1" ); break; }
	}

	sio2_end = sio2GetMicroTime();
	
	printf( "glClientActiveTexture( %s )::%dus\n", str1, ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}



void sio2Color4ub (GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha)
{
	sio2_start = sio2GetMicroTime();

	glColor4ub( red, green, blue, alpha );

	sio2_end = sio2GetMicroTime();
	
	printf( "glColor4ub( %c, %c, %c, %c )::%dus\n", red, green, blue, alpha, ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}



void sio2ColorMask (GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha)
{
	sio2_start = sio2GetMicroTime();

	glColorMask( red, green, blue, alpha );

	sio2_end = sio2GetMicroTime();
	
	printf( "glColorMask( %c, %c, %c, %c )::%dus\n", red, green, blue, alpha, ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}



void sio2ColorPointer (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer)
{
	sio2_start = sio2GetMicroTime();

	glColorPointer( size, type, stride, pointer );

	sio2_end = sio2GetMicroTime();
	
	printf( "glColorPointer( %d, %d, %d, 0x%x )::%dus\n", size, type, stride, pointer, ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}



void sio2CompressedTexImage2D (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid *data)
{
	sio2_start = sio2GetMicroTime();

	glCompressedTexImage2D( target, level, internalformat, width, height, border, imageSize, data );

	sio2_end = sio2GetMicroTime();
	
	printf( "glCompressedTexImage2D( %d, %d, %d, %d, %d, %d, %d, 0x%x )::%dus\n", target, level, internalformat, width, height, border, imageSize, data, ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}



void sio2CompressedTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid *data)
{
	sio2_start = sio2GetMicroTime();

	glCompressedTexSubImage2D( target, level, xoffset, yoffset, width, height, format, imageSize, data );

	sio2_end = sio2GetMicroTime();
	
	printf( "glCompressedTexSubImage2D( %d, %d, %d, %d, %d, %d, %d, %d, 0x%x )::%dus\n", target, level, xoffset, yoffset, width, height, format, imageSize, data, ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}



void sio2CopyTexImage2D (GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border)
{
	sio2_start = sio2GetMicroTime();

	glCopyTexImage2D( target, level, internalformat, x, y, width, height, border );

	sio2_end = sio2GetMicroTime();
	
	printf( "glCopyTexImage2D( %d, %d, %d, %d, %d, %d, %d, %d )::%dus\n", target, level, internalformat, x, y, width, height, border, ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}



void sio2CopyTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height)
{
	sio2_start = sio2GetMicroTime();

	glCopyTexSubImage2D( target, level, xoffset, yoffset, x, y, width, height );

	sio2_end = sio2GetMicroTime();
	
	printf( "glCopyTexSubImage2D( %d, %d, %d, %d, %d, %d, %d, %d )::%dus\n", target, level, xoffset, yoffset, x, y, width, height, ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}



void sio2CullFace (GLenum mode)
{
	sio2_start = sio2GetMicroTime();

	switch( mode )
	{
		case GL_FRONT:
		{ sio2StringCpy( str1, "GL_FRONT" ); break; }

		case GL_BACK:
		{ sio2StringCpy( str1, "GL_BACK" ); break; }

		case GL_FRONT_AND_BACK:
		{ sio2StringCpy( str1, "GL_FRONT_AND_BACK" ); break; }
	}

	glCullFace( mode );

	sio2_end = sio2GetMicroTime();
	
	printf( "glCullFace( %s )::%dus\n", str1, ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}



void sio2DeleteBuffers (GLsizei n, const GLuint *buffers)
{
	sio2_start = sio2GetMicroTime();

	glDeleteBuffers( n, buffers );

	sio2_end = sio2GetMicroTime();
	
	printf( "glDeleteBuffers( %d, 0x%x )::%dus\n", n, buffers, ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}



void sio2DeleteTextures (GLsizei n, const GLuint *textures)
{
	sio2_start = sio2GetMicroTime();

	glDeleteTextures( n, textures );

	sio2_end = sio2GetMicroTime();
	
	printf( "glDeleteTextures( %d, 0x%x )::%dus\n", n, textures, ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}



void sio2DepthFunc (GLenum func)
{
	sio2_start = sio2GetMicroTime();

	switch( func )
	{
		case GL_NEVER:
		{ sio2StringCpy( str1, "GL_NEVER" ); break; }

		case GL_LESS:
		{ sio2StringCpy( str1, "GL_LESS" ); break; }

		case GL_EQUAL:
		{ sio2StringCpy( str1, "GL_EQUAL" ); break; }

		case GL_LEQUAL:
		{ sio2StringCpy( str1, "GL_LEQUAL" ); break; }

		case GL_GREATER:
		{ sio2StringCpy( str1, "GL_GREATER" ); break; }

		case GL_NOTEQUAL:
		{ sio2StringCpy( str1, "GL_NOTEQUAL" ); break; }

		case GL_GEQUAL:
		{ sio2StringCpy( str1, "GL_GEQUAL" ); break; }

		case GL_ALWAYS:
		{ sio2StringCpy( str1, "GL_ALWAYS" ); break; }		
	}

	glDepthFunc( func );

	sio2_end = sio2GetMicroTime();
	
	printf( "glDepthFunc( %s )::%dus\n", str1, ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}



void sio2DepthMask (GLboolean flag)
{
	sio2_start = sio2GetMicroTime();

	glDepthMask( flag );

	sio2_end = sio2GetMicroTime();
	
	printf( "glDepthMask( %d )::%dus\n", flag, ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}



void sio2Disable (GLenum cap)
{
	sio2_start = sio2GetMicroTime();

	glDisable( cap );

	sio2GetState( cap );

	sio2_end = sio2GetMicroTime();
	
	printf( "glDisable( %s )::%dus\n", str1, ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}



void sio2DisableClientState (GLenum array)
{
	sio2_start = sio2GetMicroTime();

	glDisableClientState( array );

	switch( array )
	{
		case GL_VERTEX_ARRAY:
		{ sio2StringCpy( str1, "GL_VERTEX_ARRAY" ); break; }

		case GL_NORMAL_ARRAY:
		{ sio2StringCpy( str1, "GL_NORMAL_ARRAY" ); break; }

		case GL_COLOR_ARRAY:
		{ sio2StringCpy( str1, "GL_COLOR_ARRAY" ); break; }

		case GL_TEXTURE_COORD_ARRAY:
		{ sio2StringCpy( str1, "GL_TEXTURE_COORD_ARRAY" ); break; }
	}

	sio2_end = sio2GetMicroTime();
	
	printf( "glDisableClientState( %s )::%dus\n", str1, ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}



void sio2DrawArrays (GLenum mode, GLint first, GLsizei count)
{
	sio2_start = sio2GetMicroTime();

	glDrawArrays( mode, first, count );

	sio2_end = sio2GetMicroTime();
	
	printf( "glDrawArrays( %d, %d, %d )::%dus\n", mode, first, count, ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}



void sio2DrawElements (GLenum mode, GLsizei count, GLenum type, const GLvoid *indices)
{
	sio2_start = sio2GetMicroTime();

	glDrawElements( mode, count, type, indices );

	sio2_end = sio2GetMicroTime();
	
	printf( "glDrawElements( %d, %d, %d, 0x%x )::%dus\n", mode, count, type, indices, ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}



void sio2Enable (GLenum cap)
{
	sio2_start = sio2GetMicroTime();

	glEnable( cap );

	sio2GetState( cap );

	sio2_end = sio2GetMicroTime();
	
	printf( "glEnable( %s )::%dus\n", str1, ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}



void sio2EnableClientState (GLenum array)
{
	sio2_start = sio2GetMicroTime();

	glEnableClientState( array );

	switch( array )
	{
		case GL_VERTEX_ARRAY:
		{ sio2StringCpy( str1, "GL_VERTEX_ARRAY" ); break; }

		case GL_NORMAL_ARRAY:
		{ sio2StringCpy( str1, "GL_NORMAL_ARRAY" ); break; }

		case GL_COLOR_ARRAY:
		{ sio2StringCpy( str1, "GL_COLOR_ARRAY" ); break; }

		case GL_TEXTURE_COORD_ARRAY:
		{ sio2StringCpy( str1, "GL_TEXTURE_COORD_ARRAY" ); break; }
	}

	sio2_end = sio2GetMicroTime();
	
	printf( "glEnableClientState( %s )::%dus\n", str1, ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}



void sio2Finish (void)
{
	sio2_start = sio2GetMicroTime();

	glFinish();

	sio2_end = sio2GetMicroTime();
	
	printf( "glFinish()::%dus\n", ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}



void sio2Flush (void)
{
	sio2_start = sio2GetMicroTime();

	glFlush();

	sio2_end = sio2GetMicroTime();
	
	printf( "glFlush()::%dus\n",( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}



void sio2FrontFace (GLenum mode)
{
	sio2_start = sio2GetMicroTime();

	glFrontFace( mode );

	switch( mode )
	{
		case GL_CW:
		{ sio2StringCpy( str1, "GL_CW"); break; }

		case GL_CCW:
		{ sio2StringCpy( str1, "GL_CCW"); break; }
	}

	sio2_end = sio2GetMicroTime();
	
	printf( "glFrontFace( %s )::%dus\n", str1, ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}



void sio2GetBooleanv (GLenum pname, GLboolean *params)
{
	sio2_start = sio2GetMicroTime();

	glGetBooleanv( pname, params );

	sio2_end = sio2GetMicroTime();
	
	printf( "glGetBooleanv( %d, 0x%x )::%dus\n", pname, params, ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}



void sio2GetBufferParameteriv (GLenum target, GLenum pname, GLint *params)
{
	sio2_start = sio2GetMicroTime();

	glGetBufferParameteriv( target, pname, params );

	sio2_end = sio2GetMicroTime();
	
	printf( "glGetBooleanv( %d, %d, 0x%x )::%dus\n", target, pname, params, ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}



void sio2GenBuffers (GLsizei n, GLuint *buffers)
{
	sio2_start = sio2GetMicroTime();

	glGenBuffers( n, buffers );

	sio2_end = sio2GetMicroTime();
	
	printf( "glGenBuffers( %d, 0x%x )::%dus\n", n, buffers, ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}



void sio2GenTextures (GLsizei n, GLuint *textures)
{
	sio2_start = sio2GetMicroTime();

	glGenTextures( n, textures );

	sio2_end = sio2GetMicroTime();
	
	printf( "glGenBuffers( %d, 0x%x )::%dus\n", n, textures, ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}



void sio2GetIntegerv (GLenum pname, GLint *params)
{
	sio2_start = sio2GetMicroTime();

	glGetIntegerv( pname, params);

	sio2_end = sio2GetMicroTime();
	
	printf( "glGetIntegerv( %d, 0x%x )::%dus\n", pname, params, ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}



void sio2GetPointerv (GLenum pname, void **params)
{
	sio2_start = sio2GetMicroTime();

	glGetPointerv( pname, params);

	sio2_end = sio2GetMicroTime();
	
	printf( "glGetPointerv( %d, 0x%x )::%dus\n", pname, params, ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}



const GLubyte *sio2GetString (GLenum name)
{
	const GLubyte *r;
	
	sio2_start = sio2GetMicroTime();

	r = glGetString( name );

	switch( name )
	{
		case GL_VENDOR:
		{ sio2StringCpy( str1, "GL_VENDOR" ); break; }

		case GL_RENDERER:
		{ sio2StringCpy( str1, "GL_RENDERER" ); break; }

		case GL_VERSION:
		{ sio2StringCpy( str1, "GL_VERSION" ); break; }

		case GL_EXTENSIONS:
		{ sio2StringCpy( str1, "GL_EXTENSIONS" ); break; }
	}

	sio2_end = sio2GetMicroTime();
	
	printf( "glGetString( %s )::%dus\n", str1, ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
	
	return r;
}



void sio2GetTexEnviv (GLenum env, GLenum pname, GLint *params)
{
	sio2_start = sio2GetMicroTime();

	glGetTexEnviv( env, pname, params );

	sio2_end = sio2GetMicroTime();
	
	printf( "glGetTexEnviv( %d, %d, 0x%x )::%dus\n", env, pname, params, ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}



void sio2GetTexParameteriv (GLenum target, GLenum pname, GLint *params)
{
	sio2_start = sio2GetMicroTime();

	glGetTexParameteriv( target, pname, params );

	sio2_end = sio2GetMicroTime();
	
	printf( "glGetTexParameteriv( %d, %d, 0x%x )::%dus\n", target, pname, params, ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}



void sio2Hint (GLenum target, GLenum mode)
{
	sio2_start = sio2GetMicroTime();

	glHint( target, mode );

	switch( target )
	{
		case GL_PERSPECTIVE_CORRECTION_HINT:
		{ sio2StringCpy( str1, "GL_PERSPECTIVE_CORRECTION_HINT" ); break; }
		
		case GL_POINT_SMOOTH_HINT:
		{ sio2StringCpy( str1, "GL_POINT_SMOOTH_HINT" ); break; }

		case GL_LINE_SMOOTH_HINT:
		{ sio2StringCpy( str1, "GL_LINE_SMOOTH_HINT" ); break; }
	
		case GL_FOG_HINT:
		{ sio2StringCpy( str1, "GL_FOG_HINT" ); break; }

		case GL_GENERATE_MIPMAP_HINT:
		{ sio2StringCpy( str1, "GL_GENERATE_MIPMAP_HINT" ); break; }
	}


	switch( mode )
	{
		case GL_DONT_CARE:
		{ sio2StringCpy( str2, "GL_DONT_CARE" ); break; }

		case GL_FASTEST:
		{ sio2StringCpy( str2, "GL_FASTEST" ); break; }
		
		case GL_NICEST:
		{ sio2StringCpy( str2, "GL_NICEST" ); break; }		
	}

	sio2_end = sio2GetMicroTime();
	
	printf( "glHint( %s, %s )::%dus\n", str1, str2, ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}



GLboolean sio2IsBuffer (GLuint buffer)
{
	GLboolean r;
	
	sio2_start = sio2GetMicroTime();

	r = glIsBuffer( buffer );

	sio2_end = sio2GetMicroTime();
	
	printf( "glIsBuffer( %d )::%dus\n", buffer, ( sio2_end - sio2_start ) );
	
	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
		
	return r;
}



GLboolean sio2IsEnabled (GLenum cap)
{
	GLboolean r;
	
	sio2_start = sio2GetMicroTime();

	r = glIsEnabled( cap );

	sio2GetState( cap );

	sio2_end = sio2GetMicroTime();
	
	printf( "glIsEnabled( %s )::%dus\n", str1, ( sio2_end - sio2_start ) );
	
	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
		
	return r;
}



GLboolean sio2IsTexture (GLuint texture)
{
	GLboolean r;
	
	sio2_start = sio2GetMicroTime();

	r = glIsTexture( texture );

	sio2_end = sio2GetMicroTime();
	
	printf( "glIsTexture( %d )::%dus\n", texture, ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
		
	return r;
}



void sio2LoadIdentity (void)
{
	sio2_start = sio2GetMicroTime();

	glLoadIdentity();

	sio2_end = sio2GetMicroTime();
	
	printf( "glLoadIdentity()::%dus\n", ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}



void sio2LogicOp (GLenum opcode)
{
	sio2_start = sio2GetMicroTime();

	glLogicOp( opcode );

	sio2_end = sio2GetMicroTime();
	
	printf( "glLogicOp( %d )::%dus\n", opcode, ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}



void sio2MatrixMode (GLenum mode)
{
	sio2_start = sio2GetMicroTime();

	glMatrixMode( mode );

	switch( mode )
	{
		case GL_MODELVIEW:
		{ sio2StringCpy( str1, "GL_MODELVIEW" ); break; }

		case GL_PROJECTION:
		{ sio2StringCpy( str1, "GL_PROJECTION" ); break; }

		case GL_TEXTURE:
		{ sio2StringCpy( str1, "GL_TEXTURE" ); break; }
	}

	sio2_end = sio2GetMicroTime();
	
	printf( "glMatrixMode( %s )::%dus\n", str1, ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}



void sio2NormalPointer (GLenum type, GLsizei stride, const GLvoid *pointer)
{
	sio2_start = sio2GetMicroTime();

	glNormalPointer( type, stride, pointer );

	sio2_end = sio2GetMicroTime();
	
	printf( "glNormalPointer( %d, %d, 0x%x )::%dus\n", type, stride, pointer, ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}



void sio2PixelStorei (GLenum pname, GLint param)
{
	sio2_start = sio2GetMicroTime();

	glPixelStorei( pname, param );

	sio2_end = sio2GetMicroTime();
	
	printf( "glPixelStorei( %d, %d )::%dus\n", pname, param, ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}



void sio2PopMatrix (void)
{
	sio2_start = sio2GetMicroTime();

	glPopMatrix();

	sio2_end = sio2GetMicroTime();
	
	printf( "glPopMatrix()::%dus\n", ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}



void sio2PushMatrix (void)
{
	sio2_start = sio2GetMicroTime();

	glPushMatrix();

	sio2_end = sio2GetMicroTime();
	
	printf( "glPushMatrix()::%dus\n", ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}



void sio2ReadPixels (GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid *pixels)
{
	sio2_start = sio2GetMicroTime();

	glReadPixels( x, y, width, height, format, type, pixels );

	sio2_end = sio2GetMicroTime();
	
	printf( "glReadPixels( %d, %d, %d, %d, %d, %d, 0x%x )::%dus\n", x, y, width, height, format, type, pixels, ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}



void sio2SampleCoverage (GLclampf value, GLboolean invert)
{
	sio2_start = sio2GetMicroTime();

	glSampleCoverage( value, invert );

	sio2_end = sio2GetMicroTime();
	
	printf( "glSampleCoverage( %f, %f )::%dus\n", value, invert, ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}



void sio2Scissor (GLint x, GLint y, GLsizei width, GLsizei height)
{
	sio2_start = sio2GetMicroTime();

	glScissor( x, y, width, height );

	sio2_end = sio2GetMicroTime();
	
	printf( "glScissor( %d, %d, %d, %d )::%dus\n", x, y, width, height, ( sio2_end - sio2_start ) );
}



void sio2ShadeModel (GLenum mode)
{
	sio2_start = sio2GetMicroTime();

	glShadeModel( mode );

	switch( mode )
	{
		case GL_FLAT:
		{ sio2StringCpy( str1, "GL_FLAT" ); break; }

		case GL_SMOOTH:
		{ sio2StringCpy( str1, "GL_SMOOTH" ); break; }
	}

	sio2_end = sio2GetMicroTime();
	
	printf( "glShadeModel( %s )::%dus\n", str1, ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}



void sio2StencilFunc (GLenum func, GLint ref, GLuint mask)
{
	sio2_start = sio2GetMicroTime();

	glStencilFunc( func, ref, mask );

	sio2_end = sio2GetMicroTime();
	
	printf( "glStencilFunc( %d, %d, %d )::%dus\n", func, ref, mask, ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}



void sio2StencilMask (GLuint mask)
{
	sio2_start = sio2GetMicroTime();

	glStencilMask( mask);

	sio2_end = sio2GetMicroTime();
	
	printf( "glStencilMask( %d )::%dus\n", mask, ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}



void sio2StencilOp (GLenum fail, GLenum zfail, GLenum zpass)
{
	sio2_start = sio2GetMicroTime();

	glStencilOp( fail, zfail, zpass );

	sio2_end = sio2GetMicroTime();
	
	printf( "glStencilOp( %d, %d, %d )::%dus\n", fail, zfail, zpass, ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}



void sio2TexCoordPointer (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer)
{
	sio2_start = sio2GetMicroTime();

	glTexCoordPointer( size, type, stride, pointer );

	sio2_end = sio2GetMicroTime();
	
	printf( "glTexCoordPointer( %d, %d, %d, 0x%x )::%dus\n", size, type, stride, pointer, ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}



void sio2TexEnvi (GLenum target, GLenum pname, GLint param)
{
	sio2_start = sio2GetMicroTime();

	glTexEnvi( target, pname, param );

	sio2_end = sio2GetMicroTime();
	
	printf( "glTexEnvi( %d, %d, %d )::%dus\n", target, pname, param, ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}



void sio2TexEnviv (GLenum target, GLenum pname, const GLint *params)
{
	sio2_start = sio2GetMicroTime();

	glTexEnviv( target, pname, params );

	sio2_end = sio2GetMicroTime();
	
	printf( "glTexEnviv( %d, %d, 0x%x )::%dus\n", target, pname, params, ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}



void sio2TexImage2D (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid *pixels)
{
	sio2_start = sio2GetMicroTime();

	glTexImage2D( target, level, internalformat, width, height, border, format, type, pixels );

	sio2_end = sio2GetMicroTime();
	
	printf( "glTexImage2D( GL_TEXTURE_2D, %d, %d, %d, %d, %d, %d, %d, 0x%x )::%dus\n", level, internalformat, width, height, border, format, type, pixels, ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}



void sio2TexParameteri (GLenum target, GLenum pname, GLint param)
{
	sio2_start = sio2GetMicroTime();

	glTexParameteri( target, pname, param );

	sio2_end = sio2GetMicroTime();
	
	printf( "glTexParameteri( %d, %d, %d )::%dus\n", target, pname, param, ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}



void sio2TexParameteriv (GLenum target, GLenum pname, const GLint *params)
{
	sio2_start = sio2GetMicroTime();

	glTexParameteriv( target, pname, params );

	sio2_end = sio2GetMicroTime();
	
	printf( "glTexParameteriv( %d, %d, 0x%x )::%dus\n", target, pname, params, ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}



void sio2TexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels)
{
	sio2_start = sio2GetMicroTime();

	glTexSubImage2D( target, level, xoffset, yoffset, width, height, format, type, pixels );

	sio2_end = sio2GetMicroTime();
	
	printf( "glTexSubImage2D( %d, %d, %d, %d, %d, %d, %d, %d, 0x%x )::%dus\n",  target, level, xoffset, yoffset, width, height, format, type, pixels, ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}



void sio2VertexPointer (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer)
{
	sio2_start = sio2GetMicroTime();

	glVertexPointer( size, type, stride, pointer );

	sio2_end = sio2GetMicroTime();
	
	printf( "glVertexPointer( %d, %d, %d, 0x%x )::%dus\n",  size, type, stride, pointer, ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}



void sio2Viewport (GLint x, GLint y, GLsizei width, GLsizei height)
{
	sio2_start = sio2GetMicroTime();

	glViewport( x, y, width, height );

	sio2_end = sio2GetMicroTime();
	
	printf( "glViewport( %d, %d, %d, 0x%x )::%dus\n",  x, y, width, height, ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}



void sio2CurrentPaletteMatrixOES (GLuint matrixpaletteindex)
{
	sio2_start = sio2GetMicroTime();

	glCurrentPaletteMatrixOES( matrixpaletteindex );

	sio2_end = sio2GetMicroTime();
	
	printf( "glCurrentPaletteMatrixOES( %d )::%dus\n",  matrixpaletteindex, ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}



void sio2LoadPaletteFromModelViewMatrixOES (void)
{
	sio2_start = sio2GetMicroTime();

	glLoadPaletteFromModelViewMatrixOES();

	sio2_end = sio2GetMicroTime();
	
	printf( "glLoadPaletteFromModelViewMatrixOES()::%dus\n", ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}



void sio2MatrixIndexPointerOES (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer)
{
	sio2_start = sio2GetMicroTime();

	glMatrixIndexPointerOES( size, type, stride, pointer );

	sio2_end = sio2GetMicroTime();
	
	printf( "glMatrixIndexPointerOES( %d, %d, %d, 0x%x )::%dus\n", size, type, stride, pointer, ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}



void sio2WeightPointerOES (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer)
{
	sio2_start = sio2GetMicroTime();

	glWeightPointerOES( size, type, stride, pointer );

	sio2_end = sio2GetMicroTime();
	
	printf( "glWeightPointerOES( %d, %d, %d, 0x%x )::%dus\n", size, type, stride, pointer, ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}



void sio2PointSizePointerOES (GLenum type, GLsizei stride, const GLvoid *pointer)
{
	sio2_start = sio2GetMicroTime();

	glPointSizePointerOES( type, stride, pointer );

	sio2_end = sio2GetMicroTime();
	
	printf( "glPointSizePointerOES( %d, %d, 0x%x )::%dus\n", type, stride, pointer, ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}


void sio2DrawTexfOES (GLfloat x, GLfloat y, GLfloat z, GLfloat width, GLfloat height)
{
	sio2_start = sio2GetMicroTime();

	glDrawTexfOES( x, y, z, width, height );

	sio2_end = sio2GetMicroTime();
	
	printf( "glDrawTexfOES( %f, %f, %f, %f, %f )::%dus\n", x, y, z, width, height, ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}



void sio2DrawTexfvOES (const GLfloat *coords)
{
	sio2_start = sio2GetMicroTime();

	glDrawTexfvOES( coords );

	sio2_end = sio2GetMicroTime();
	
	printf( "glDrawTexfvOES( 0x%x )::%dus\n", coords, ( sio2_end - sio2_start ) );

	#ifdef SIO2_DEBUG_GL

		sio2ErrorGL( __FILE__, __FUNCTION__, __LINE__ );
	#endif
}
