
#ifndef AUGMENTIA_H
#define AUGMENTIA_H

void augmentiaRender( void );
void augmentiaShutdown( void );
void augmentiaLoading( void );
void augmentiaScreenTap( void *_ptr, unsigned char _state );
void augmentiaScreenTouchMove( void *_ptr );
void augmentiaScreenAccelerometer( void *_ptr );

#endif