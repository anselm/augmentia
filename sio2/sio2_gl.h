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

#ifndef SIO2_GL_H
#define SIO2_GL_H


#define glAlphaFunc( func, ref ) sio2AlphaFunc( func, ref )
#define glClearColor( red, green, blue, alpha ) sio2ClearColor( red, green, blue, alpha )
#define glClearDepthf( depth ) sio2ClearDepthf( depth )
#define glClipPlanef( plane, equation ) sio2ClipPlanef( plane, equation )
#define glColor4f( red, green, blue, alpha ) sio2Color4f( red, green, blue, alpha )
#define glDepthRangef( zNear,  zFar ) sio2DepthRangef( zNear,  zFar ) 
#define glFogf( pname,  param ) sio2Fogf( pname,  param )
#define glFogfv( pname, params ) sio2Fogfv( pname, params )
#define glFrustumf( left, right, bottom, top, zNear, zFar ) sio2Frustumf( left, right, bottom, top, zNear, zFar ) 
#define glGetClipPlanef( pname, equation ) sio2GetClipPlanef( pname, equation )
#define glGetFloatv( pname, params ) sio2GetFloatv( pname, params )
#define glGetLightfv( light, pname, params ) sio2GetLightfv( light, pname, params )
#define glGetMaterialfv( face, pname, params ) sio2GetMaterialfv( face, pname, params )
#define glGetTexEnvfv( env, pname, params ) sio2GetTexEnvfv( env, pname, params )
#define glGetTexParameterfv( target, pname, params ) sio2GetTexParameterfv( target, pname, params ) 
#define glLightModelf( pname, param ) sio2LightModelf( pname, param )
#define glLightModelfv( pname, params ) sio2LightModelfv( pname, params )
#define glLightf( light, pname, param ) sio2Lightf( light, pname, param ) 
#define glLightfv( light, pname, params ) sio2Lightfv( light, pname, params )
#define glLineWidth( width ) sio2LineWidth( width )
#define glLoadMatrixf( m ) sio2LoadMatrixf( m ) 
#define glMaterialf( face, pname, param ) sio2Materialf( face, pname, param )
#define glMaterialfv( face, pname, params ) sio2Materialfv( face, pname, params )
#define glMultMatrixf( m ) sio2MultMatrixf( m )
#define glMultiTexCoord4f( target, s, t, r, q ) sio2MultiTexCoord4f( target, s, t, r, q )
#define glNormal3f( nx, ny, nz ) sio2Normal3f( nx, ny, nz )
#define glOrthof( left, right, bottom, top, zNear, zFar ) sio2Orthof( left, right, bottom, top, zNear, zFar )
#define glPointParameterf( pname, param ) sio2PointParameterf( pname, param )
#define glPointParameterfv( pname, params ) sio2PointParameterfv( pname, params )
#define glPointSize( size ) sio2PointSize( size )
#define glPolygonOffset( factor, units ) sio2PolygonOffset( factor, units )
#define glRotatef( angle, x, y, z ) sio2Rotatef( angle, x, y, z )
#define glScalef( x, y, z ) sio2Scalef( x, y, z )
#define glTexEnvf( target, pname, param ) sio2TexEnvf( target, pname, param )
#define glTexEnvfv( target, pname, params ) sio2TexEnvfv( target, pname, params )
#define glTexParameterf( target, pname, param ) sio2TexParameterf( target, pname, param )
#define glTexParameterfv( target, pname, params ) sio2TexParameterfv( target, pname, params )
#define glTranslatef( x, y, z ) sio2Translatef( x, y, z )
#define glActiveTexture( texture ) sio2ActiveTexture( texture )
#define glBindBuffer( target, buffer ) sio2BindBuffer( target, buffer )
#define glBindTexture( target, texture ) sio2BindTexture( target, texture )
#define glBlendFunc( sfactor, dfactor ) sio2BlendFunc( sfactor, dfactor )
#define glBufferData( target, size, data, usage ) sio2BufferData( target, size, data, usage )
#define glBufferSubData( target, offset, size, data ) sio2BufferSubData( target, offset, size, data )
#define glClear( mask ) sio2Clear( mask )
#define glClearStencil( s ) sio2ClearStencil( s )
#define glClientActiveTexture( texture ) sio2ClientActiveTexture( texture ) 
#define glColor4ub( red, green, blue,  alpha ) sio2Color4ub( red, green, blue,  alpha ) 
#define glColorMask( red, green, blue, alpha ) sio2ColorMask( red, green, blue, alpha )
#define glColorPointer( size, type, stride, pointer ) sio2ColorPointer( size, type, stride, pointer )
#define glCompressedTexImage2D( target, level, internalformat, width, height, border, imageSize, data ) sio2CompressedTexImage2D( target, level, internalformat, width, height, border, imageSize, data ) 
#define glCompressedTexSubImage2D( target, level, xoffset, yoffset, width, height, format, imageSize, data ) sio2CompressedTexSubImage2D( target, level, xoffset, yoffset, width, height, format, imageSize, data )
#define glCopyTexImage2D( target, level, internalformat, x, y, width, height, border ) sio2CopyTexImage2D( target, level, internalformat, x, y, width, height, border ) 
#define glCopyTexSubImage2D( target, level, xoffset, yoffset, x, y, width, height ) sio2CopyTexSubImage2D( target, level, xoffset, yoffset, x, y, width, height ) 
#define glCullFace( mode ) sio2CullFace( mode ) 
#define glDeleteBuffers( n, buffers ) sio2DeleteBuffers( n, buffers ) 
#define glDeleteTextures( n, textures ) sio2DeleteTextures( n, textures ) 
#define glDepthFunc( func ) sio2DepthFunc( func ) 
#define glDepthMask( flag ) sio2DepthMask( flag )
#define glDisable( cap ) sio2Disable( cap ) 
#define glDisableClientState( array ) sio2DisableClientState( array ) 
#define glDrawArrays( mode, first, count ) sio2DrawArrays( mode, first, count ) 
#define glDrawElements( mode, count, type, indices ) sio2DrawElements( mode, count, type, indices ) 
#define glEnable( cap ) sio2Enable( cap ) 
#define glEnableClientState( array ) sio2EnableClientState( array ) 
#define glFinish( void ) sio2Finish( void ) 
#define glFlush( void ) sio2Flush( void ) 
#define glFrontFace( mode ) sio2FrontFace( mode )

#define glGetBooleanv( pname, params ) sio2GetBooleanv( pname, params ) 
#define glGetBufferParameteriv( target, pname, params ) sio2GetBufferParameteriv( target, pname, params ) 
#define glGenBuffers( n, buffers ) sio2GenBuffers( n, buffers ) 
#define glGenTextures( n, textures ) sio2GenTextures( n, textures ) 
#define glGetIntegerv( pname, params ) sio2GetIntegerv( pname, params ) 
#define glGetPointerv( pname, params ) sio2GetPointerv( pname, params ) 
#define glGetString( name ) sio2GetString( name ) 
#define glGetTexEnviv( env,  pname, params ) sio2GetTexEnviv( env,  pname, params ) 
#define glGetTexParameteriv( target, pname, params ) sio2GetTexParameteriv( target, pname, params ) 
#define glHint( target,  mode ) sio2Hint( target,  mode ) 
#define glIsBuffer( buffer ) sio2IsBuffer( buffer ) 
#define glIsEnabled( cap ) sio2IsEnabled( cap )  
#define glIsTexture( texture ) sio2IsTexture( texture ) 
#define glLoadIdentity() sio2LoadIdentity() 
#define glLogicOp( opcode ) sio2LogicOp( opcode ) 
#define glMatrixMode( mode ) sio2MatrixMode( mode ) 
#define glNormalPointer( type, stride, pointer ) sio2NormalPointer( type, stride, pointer ) 
#define glPixelStorei( pname, param ) sio2PixelStorei( pname, param ) 
#define glPopMatrix() sio2PopMatrix() 
#define glPushMatrix() sio2PushMatrix() 
#define glReadPixels( x, y, width, height, format, type, pixels ) sio2ReadPixels( x, y, width, height, format, type, pixels ) 
#define glSampleCoverage( value, invert ) sio2SampleCoverage( value, invert ) 
#define glScissor( x, y, width, height ) sio2Scissor( x, y, width, height ) 
#define glShadeModel( mode ) sio2ShadeModel( mode ) 
#define glStencilFunc( func, ref, mask ) sio2StencilFunc( func, ref, mask ) 
#define glStencilMask( mask ) sio2StencilMask( mask ) 
#define glStencilOp( fail, zfail, zpass ) sio2StencilOp( fail, zfail, zpass ) 
#define glTexCoordPointer( size, type, stride, pointer )  sio2TexCoordPointer( size, type, stride, pointer ) 
#define glTexEnvi( target, pname,  param ) sio2TexEnvi( target, pname,  param )
#define glTexEnviv( target, pname, params ) sio2TexEnviv( target, pname, params )
#define glTexImage2D( target, level, internalformat, width, height, border, format, type, pixels ) sio2TexImage2D( target, level, internalformat, width, height, border, format, type, pixels ) 
#define glTexParameteri( target, pname, param ) sio2TexParameteri( target, pname, param ) 
#define glTexParameteriv( target, pname, params ) sio2TexParameteriv( target, pname, params ) 
#define glTexSubImage2D( target, level, xoffset, yoffset, width, height, format, type, pixels ) sio2TexSubImage2D( target, level, xoffset, yoffset, width, height, format, type, pixels ) 
#define glVertexPointer( size, type, stride, pointer ) sio2VertexPointer( size, type, stride, pointer ) 
#define glViewport( x, y, width, height ) sio2Viewport( x, y, width, height ) 
#define glCurrentPaletteMatrixOES( matrixpaletteindex ) sio2CurrentPaletteMatrixOES( matrixpaletteindex ) 
#define glLoadPaletteFromModelViewMatrixOES() sio2LoadPaletteFromModelViewMatrixOES() 
#define glMatrixIndexPointerOES( size, type, stride, pointer ) sio2MatrixIndexPointerOES( size, type, stride, pointer ) 
#define glWeightPointerOES( size, type, stride, pointer ) sio2WeightPointerOES( size, type, stride, pointer ) 
#define glPointSizePointerOES( type, stride, pointer ) sio2PointSizePointerOES( type, stride, pointer ) 
#define glDrawTexfOES( x, y, z, width, height ) sio2DrawTexfOES( x, y, z, width, height ) 
#define glDrawTexfvOES( coords ) sio2DrawTexfvOES( coords ) 


extern unsigned int sio2_start,
					sio2_end;

extern char str1[ SIO2_MAX_CHAR ],
			str2[ SIO2_MAX_CHAR  ];

unsigned int sio2GetMicroTime( void );

void sio2GetState( unsigned int );

void sio2GetFace( unsigned int );

void sio2GetLightParam( unsigned int );

void sio2GetTexture( unsigned int );

void sio2AlphaFunc (GLenum func, GLclampf ref);

void sio2ClearColor (GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);

void sio2ClearDepthf (GLclampf depth);

void sio2ClipPlanef (GLenum plane, const GLfloat *equation);

void sio2Color4f (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);

void sio2DepthRangef (GLclampf zNear, GLclampf zFar);

void sio2Fogf (GLenum pname, GLfloat param);

void sio2Fogfv (GLenum pname, const GLfloat *params);

void sio2Frustumf (GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar);

void sio2GetClipPlanef (GLenum pname, GLfloat *equation);

void sio2GetFloatv (GLenum pname, GLfloat *params);

void sio2GetLightfv (GLenum light, GLenum pname, GLfloat *params);

void sio2GetMaterialfv (GLenum face, GLenum pname, GLfloat *params);

void sio2GetTexEnvfv (GLenum env, GLenum pname, GLfloat *params);

void sio2GetTexParameterfv (GLenum target, GLenum pname, GLfloat *params);

void sio2LightModelf (GLenum pname, GLfloat param);

void sio2LightModelfv (GLenum pname, const GLfloat *params);

void sio2Lightf (GLenum light, GLenum pname, GLfloat param);

void sio2Lightfv (GLenum light, GLenum pname, const GLfloat *params);

void sio2LineWidth (GLfloat width);

void sio2LoadMatrixf (const GLfloat *m);

void sio2Materialf (GLenum face, GLenum pname, GLfloat param);

void sio2Materialfv (GLenum face, GLenum pname, const GLfloat *params);

void sio2MultMatrixf (const GLfloat *m);

void sio2MultiTexCoord4f (GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q);

void sio2Normal3f (GLfloat nx, GLfloat ny, GLfloat nz);

void sio2Orthof (GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar);

void sio2PointParameterf (GLenum pname, GLfloat param);

void sio2PointParameterfv (GLenum pname, const GLfloat *params);

void sio2PointSize (GLfloat size);

void sio2PolygonOffset (GLfloat factor, GLfloat units);

void sio2Rotatef (GLfloat ansio2e, GLfloat x, GLfloat y, GLfloat z);

void sio2Scalef (GLfloat x, GLfloat y, GLfloat z);

void sio2TexEnvf (GLenum target, GLenum pname, GLfloat param);

void sio2TexEnvfv (GLenum target, GLenum pname, const GLfloat *params);

void sio2TexParameterf (GLenum target, GLenum pname, GLfloat param);

void sio2TexParameterfv (GLenum target, GLenum pname, const GLfloat *params);

void sio2Translatef (GLfloat x, GLfloat y, GLfloat z);

void sio2ActiveTexture (GLenum texture);

void sio2BindBuffer (GLenum target, GLuint buffer);

void sio2BindTexture (GLenum target, GLuint texture);

void sio2BlendFunc (GLenum sfactor, GLenum dfactor);

void sio2BufferData (GLenum target, GLsizeiptr size, const GLvoid *data, GLenum usage);

void sio2BufferSubData (GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid *data);

void sio2Clear (GLbitfield mask);

void sio2ClearStencil (GLint s);

void sio2ClientActiveTexture (GLenum texture);

void sio2Color4ub (GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha);

void sio2ColorMask (GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);

void sio2ColorPointer (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);

void sio2CompressedTexImage2D (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid *data);

void sio2CompressedTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid *data);

void sio2CopyTexImage2D (GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border);

void sio2CopyTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);

void sio2CullFace (GLenum mode);

void sio2DeleteBuffers (GLsizei n, const GLuint *buffers);

void sio2DeleteTextures (GLsizei n, const GLuint *textures);

void sio2DepthFunc (GLenum func);

void sio2DepthMask (GLboolean flag);

void sio2Disable (GLenum cap);

void sio2DisableClientState (GLenum array);

void sio2DrawArrays (GLenum mode, GLint first, GLsizei count);

void sio2DrawElements (GLenum mode, GLsizei count, GLenum type, const GLvoid *indices);

void sio2Enable (GLenum cap);

void sio2EnableClientState (GLenum array);

void sio2Finish (void);

void sio2Flush (void);

void sio2FrontFace (GLenum mode);

void sio2GetBooleanv (GLenum pname, GLboolean *params);

void sio2GetBufferParameteriv (GLenum target, GLenum pname, GLint *params);

void sio2GenBuffers (GLsizei n, GLuint *buffers);

void sio2GenTextures (GLsizei n, GLuint *textures);

void sio2GetIntegerv (GLenum pname, GLint *params);

void sio2GetPointerv (GLenum pname, void **params);

const GLubyte *sio2GetString (GLenum name);

void sio2GetTexEnviv (GLenum env, GLenum pname, GLint *params);

void sio2GetTexParameteriv (GLenum target, GLenum pname, GLint *params);

void sio2Hint (GLenum target, GLenum mode);

GLboolean sio2IsBuffer (GLuint buffer);

GLboolean sio2IsEnabled (GLenum cap);

GLboolean sio2IsTexture (GLuint texture);

void sio2LoadIdentity (void);

void sio2LogicOp (GLenum opcode);

void sio2MatrixMode (GLenum mode);

void sio2NormalPointer (GLenum type, GLsizei stride, const GLvoid *pointer);

void sio2PixelStorei (GLenum pname, GLint param);

void sio2PopMatrix (void);

void sio2PushMatrix (void);

void sio2ReadPixels (GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid *pixels);

void sio2SampleCoverage (GLclampf value, GLboolean invert);

void sio2Scissor (GLint x, GLint y, GLsizei width, GLsizei height);

void sio2ShadeModel (GLenum mode);

void sio2StencilFunc (GLenum func, GLint ref, GLuint mask);

void sio2StencilMask (GLuint mask);

void sio2StencilOp (GLenum fail, GLenum zfail, GLenum zpass);

void sio2TexCoordPointer (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);

void sio2TexEnvi (GLenum target, GLenum pname, GLint param);

void sio2TexEnviv (GLenum target, GLenum pname, const GLint *params);

void sio2TexImage2D (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid *pixels);

void sio2TexParameteri (GLenum target, GLenum pname, GLint param);

void sio2TexParameteriv (GLenum target, GLenum pname, const GLint *params);

void sio2TexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels);

void sio2VertexPointer (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);

void sio2Viewport (GLint x, GLint y, GLsizei width, GLsizei height);

void sio2CurrentPaletteMatrixOES (GLuint matrixpaletteindex);

void sio2LoadPaletteFromModelViewMatrixOES (void);

void sio2MatrixIndexPointerOES (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);

void sio2WeightPointerOES (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);

void sio2PointSizePointerOES (GLenum type, GLsizei stride, const GLvoid *pointer);

void sio2DrawTexfOES (GLfloat x, GLfloat y, GLfloat z, GLfloat width, GLfloat height);

void sio2DrawTexfvOES (const GLfloat *coords);

#endif
