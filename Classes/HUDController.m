
#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>
#import <OpenGLES/EAGLDrawable.h>
#include <math.h>
#import <sqlite3.h>

#include "HUDController.h"
#include "Texture2D.h"

//#include <HTTPRiot/HTTPRiot.h>

#import "CDataScanner.h"
#import "CJSONDeserializer.h"

/*****************************************************************************************************************************/
// UTILITIES
/*****************************************************************************************************************************/

// Macros
#define degreesToRadians(__ANGLE__) (M_PI * (__ANGLE__) / 180.0)
#define radiansToDegrees(__ANGLE__) (180.0 * (__ANGLE__) / M_PI)

CGFloat distanceBetweenPoints (CGPoint first, CGPoint second) {
    CGFloat deltaX = second.x - first.x;
    CGFloat deltaY = second.y - first.y;
    return sqrt(deltaX*deltaX + deltaY*deltaY );
};

CGFloat angleBetweenPoints(CGPoint first, CGPoint second) {
    // atan((top - bottom)/(right - left))
    CGFloat rads = atan((second.y - first.y) / (first.x - second.x));
    return radiansToDegrees(rads);
}

CGFloat angleBetweenLines(CGPoint line1Start, CGPoint line1End, CGPoint line2Start, CGPoint line2End) {
	
    CGFloat a = line1End.x - line1Start.x;
    CGFloat b = line1End.y - line1Start.y;
    CGFloat c = line2End.x - line2Start.x;
    CGFloat d = line2End.y - line2Start.y;
	
    CGFloat rads = acos(((a*c) + (b*d)) / ((sqrt(a*a + b*b)) * (sqrt(c*c + d*d))));
	
    return radiansToDegrees(rads);
}

#define USE_DEPTH_BUFFER 1
#define kMinimumTouchLength 30
#define kMaximumScale 7.0f
#define kMinimumPinchDelta 15

/*****************************************************************************************************************************/
/* HUDVIEW SETUP */
/*****************************************************************************************************************************/

// A class extension to declare private methods
@interface HUDView ()
	//@property (nonatomic, retain) NSMutableData *receivedData;
	@property (nonatomic, retain) EAGLContext *context;
	@property (nonatomic, assign) NSTimer *animationTimer;
	- (id)initGLES;
	- (void)drawText :(NSString*)theString :(float)X :(float)Y ;
	- (void)location :(float)lat :(float)lon :(float)accuracy ;
	- (void)orientation :(float)orientation ;
	- (void)perspective :(float)fovy :(float)aspect :(float)zNear :(float)zFar ;
	- (void)orthographic;
	- (void)lookat :(GLfloat)eyex :(GLfloat)eyey :(GLfloat)eyez
				  :(GLfloat)centerx :(GLfloat)centery :(GLfloat)centerz
				  :(GLfloat)upx :(GLfloat)upy :(GLfloat)upz ;
	- (BOOL) createFramebuffer;
	- (void) destroyFramebuffer;
	- (void) data_load;
	- (void) data_save;
@end

@implementation HUDView
//@synthesize receivedData;
@synthesize context;
@synthesize animationTimer;
@synthesize animationInterval;
@synthesize squareData;
@synthesize ellipseData;
@synthesize initialDistance;
@synthesize delegate;

+ (Class)layerClass {
	// Apparently this magic mystery code is mandatory - anselm
	return [CAEAGLLayer class];
}

-(id)initWithFrame:(CGRect)frame {
	self = [super initWithFrame:frame];
	marker_count = 0;
	for(int i = 0; i < 128 ; i++ ) {
		markers[i].latitude = markers[i].longitude = 0.0;
	}
	//[self data_load];
	if(self != nil) {
		self = [self initGLES];
	}
	return self;
}

-(id)initGLES {
	NSLog(@"GlobeView: Initializing the opengl layer" );
	CAEAGLLayer *eaglLayer = (CAEAGLLayer *)self.layer;
	eaglLayer.opaque = YES;
	eaglLayer.drawableProperties = [
									NSDictionary dictionaryWithObjectsAndKeys:
									[NSNumber numberWithBool:NO],
									kEAGLDrawablePropertyRetainedBacking,
									kEAGLColorFormatRGBA8,
									kEAGLDrawablePropertyColorFormat,
									nil
									];
	context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES1];
	if (!context || ![EAGLContext setCurrentContext:context] || ![self createFramebuffer] ) {
		NSLog(@"GlobeView: Initialization error" );
		[self release];
		return nil;
	}
	NSLog(@"View: Initialized 3!!" );
	animationInterval = 1.0 / 60.0;
	[self setupView];
	return self;
}

#pragma mark - HRRequestOperation Delegates
+ (void)restConnection:(NSURLConnection *)connection didFailWithError:(NSError *)error object:(id)object {
    // Handle connection errors.  Failures to connect to the server, etc.
}

+ (void)restConnection:(NSURLConnection *)connection didReceiveError:(NSError *)error response:(NSHTTPURLResponse *)response object:(id)object {
    // Handle invalid responses, 404, 500, etc.
}

+ (void)restConnection:(NSURLConnection *)connection didReceiveParseError:(NSError *)error responseBody:(NSString *)string {
    // Request was successful, but couldn't parse the data returned by the server. 
}
/*
void test(void)
{
	NSString *theSource = NULL;
	//
	theSource = @"{\"a\": [ { ] }";
	
	NSData *theData = [theSource dataUsingEncoding:NSUTF32BigEndianStringEncoding];
	
	NSError *theError = NULL;
	id theObject = [[CJSONDeserializer deserializer] deserialize:theData error:&theError];
	
	NSLog(@"Error: %@", theError);
	NSLog(@"Result: %@", theObject);
}*/
                                                                                                   

-(void) data_load {

	return;

	// create table note ( id integer primary key, latitude float, longitude float, orientation float,
	//						title TEXT, link TEXT, description TEXT, sponsor integer );
	
	
	NSString *databaseName = @"local.sqlite";
	NSArray  *documentPaths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
	NSString *documentsDir = [documentPaths objectAtIndex:0];
	NSString *databasePath = [documentsDir stringByAppendingPathComponent:databaseName];
	NSFileManager *fileManager = [NSFileManager defaultManager];

	// XXX TODO can I do this from here? instead of loading?
	// copy the database if not there
	BOOL success = [fileManager fileExistsAtPath:databasePath];
	if(!success) {
		NSString *databasePathFromApp = [[[NSBundle mainBundle] resourcePath] stringByAppendingPathComponent:databaseName];
		[fileManager copyItemAtPath:databasePathFromApp toPath:databasePath error:nil];	
		[fileManager release];
	}

	sqlite3 *database;
	if(sqlite3_open([databasePath UTF8String], &database) == SQLITE_OK) {
		int idv;
		const char *sqlStatement = "select id,latitude,longitude,orientation from note";
		sqlite3_stmt *compiledStatement;
		if(sqlite3_prepare_v2(database, sqlStatement, -1, &compiledStatement, NULL) == SQLITE_OK) {
			// Loop through the results and add them to the feeds array
			marker_count = 0;
			while(sqlite3_step(compiledStatement) == SQLITE_ROW) {
				idv = sqlite3_column_int64(compiledStatement,0) - 1;
				if(idv < 0 || idv > 128 ) break;
				markers[idv].latitude = sqlite3_column_double(compiledStatement,1);
				markers[idv].longitude = sqlite3_column_double(compiledStatement,2);
				markers[idv].orientation = sqlite3_column_double(compiledStatement,3);
			}
		}
		sqlite3_finalize(compiledStatement);
	}
	sqlite3_close(database);

}

-(void) data_save {
	NSString *databaseName = @"local.sqlite";
	NSArray  *documentPaths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
	NSString *documentsDir = [documentPaths objectAtIndex:0];
	NSString *databasePath = [documentsDir stringByAppendingPathComponent:databaseName];
	sqlite3_stmt *statement1;
	sqlite3_stmt *statement2;
	sqlite3_stmt *statement3;
	sqlite3 *database;
	if(sqlite3_open([databasePath UTF8String], &database) == SQLITE_OK) {
		if(sqlite3_prepare_v2(database,"UPDATE note SET latitude = ?,longitude = ?,orientation = ? WHERE id = ?",-1,&statement1,NULL) != SQLITE_OK ) {
			statement1 = NULL;
		}
		if(sqlite3_prepare_v2(database,"INSERT INTO note (latitude,longitude,orientation,id) VALUES (?,?,?,?)",-1,&statement2,NULL) != SQLITE_OK ) {
			statement2 = NULL;
		}
		if(sqlite3_prepare_v2(database,"SELECT latitude,longitude,orientation FROM note WHERE id = ?",-1,&statement3,NULL) != SQLITE_OK ) {
			statement3 = NULL;
		}
		if(statement1 && statement2 && statement3) {
			for(int i = 0; i < 128 ; i++ ) {
				if(markers[i].latitude == 0 ) {
					continue;
				}
				sqlite3_bind_int(statement3,1,i+1);
				if(sqlite3_step(statement3) == SQLITE_ROW) {
					sqlite3_bind_double(statement1,1,markers[i].latitude);
					sqlite3_bind_double(statement1,2,markers[i].longitude);
					sqlite3_bind_double(statement1,3,markers[i].orientation);
					sqlite3_bind_double(statement1,4,i+1);
					sqlite3_step(statement1);
				} else {
					sqlite3_bind_double(statement2,1,markers[i].latitude);
					sqlite3_bind_double(statement2,2,markers[i].longitude);
					sqlite3_bind_double(statement2,3,markers[i].orientation);
					sqlite3_bind_double(statement2,4,i+1);
					sqlite3_step(statement2);
				}
				sqlite3_reset(statement1);
				sqlite3_reset(statement2);
				sqlite3_reset(statement3);
			}
		}
		sqlite3_finalize(statement1);
		sqlite3_finalize(statement2);
	}
	sqlite3_close(database);
}

/*****************************************************************************************************************************/
/* TOUCH */
/*****************************************************************************************************************************/

// These are four methods touchesBegan, touchesMoved, touchesEnded, touchesCancelled and use to notify about touches and gestures

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event {
    /*
	 NSUInteger numTaps = [[touches anyObject] tapCount]; // number of taps
	 NSUInteger numTouches = [touches count]; // number of touches
	 */
    UITouch *touched = [[touches allObjects] objectAtIndex:0];

    DEBUGLOG(@"TouchBegan event counts = %d ",[[event touchesForView:self] count]);
    DEBUGLOG(@"TouchBegan tounches counts = %d ",[touches count]);
    if ([touches count]== 2) {
		NSArray *twoTouches = [touches allObjects];
		UITouch *first = [twoTouches objectAtIndex:0];
		UITouch *second = [twoTouches objectAtIndex:1];
		initialDistance = distanceBetweenPoints([first locationInView:self], [second locationInView:self]);
		squareData.rotstop = YES;
		squareData.touchInside = NO;
    }
    else if ([touches count]==[[event touchesForView:self] count] & [[event touchesForView:self] count] == 1) {
		squareData.startTouchPosition = [touched locationInView:self];
		if (distanceBetweenPoints([touched locationInView:self], squareData.pos) <= kMinimumTouchLength * squareData.scale) {
			DEBUGLOG(@"Square Touch at %.2f, %.2f ",squareData.pos.x,squareData.pos.y);
			squareData.rotstop = YES;
			squareData.touchInside = YES;
		}
    }

	if( marker_count < 128 ) {
		marker_count++;
	} else {
		marker_count = 0;
	}
	
	markers[marker_count].latitude = latitude - cos(orientation*3.14/180)*5;
	markers[marker_count].longitude = longitude + sin(orientation*3.14/180)*5;
	markers[marker_count].orientation = orientation;

}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event {
    UITouch *touched = [[touches allObjects] objectAtIndex:0];
    squareData.currentTouchPosition = [touched locationInView:self];
    if ([touches count]== 2) {
		NSArray *twoTouches = [touches allObjects];
		UITouch *first = [twoTouches objectAtIndex:0];
		UITouch *second = [twoTouches objectAtIndex:1];
		
		// Calculate the distance bewtween the two fingers(touches) to determine the pinch distance
		CGFloat currentDistance = distanceBetweenPoints([first locationInView:self], [second locationInView:self]);
		
		squareData.rotstop = YES;
		squareData.touchInside = NO;
		
		if (initialDistance == 0.0f)
			initialDistance = currentDistance;
		if (currentDistance - initialDistance > kMinimumPinchDelta) {
			squareData.pinchDistance = currentDistance - initialDistance;
			squareData.scalestart = YES;
			DEBUGLOG(@"Outward Pinch %.2f", squareData.pinchDistance);
		}
		else if (initialDistance - currentDistance > kMinimumPinchDelta) {
			squareData.pinchDistance = currentDistance - initialDistance;
			squareData.scalestart = YES;
			DEBUGLOG(@"Inward Pinch %.2f", squareData.pinchDistance);
		}
    }
    else if ([touches count]==[[event touchesForView:self] count] & [[event touchesForView:self] count] == 1) {
		if (squareData.touchInside) {
			// Only move the square to new position when touchBegan is inside the square
			squareData.pos.x = [touched locationInView:self].x;
			squareData.pos.y = [touched locationInView:self].y;
			DEBUGLOG(@"Square Move to %.2f, %.2f ",squareData.pos.x,squareData.pos.y);
			squareData.rotstop = YES;
		}
    }
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event {
    if ([touches count] == [[event touchesForView:self] count]) {
		initialDistance = squareData.pinchDistanceShown = squareData.pinchDistance = 0.0f;
		squareData.rotstop = squareData.touchInside = squareData.scalestart = NO;
		DEBUGLOG(@"touchesEnded, all fingers up");
    }
    else {
		initialDistance = squareData.pinchDistanceShown = squareData.pinchDistance = 0.0f;
		squareData.scalestart = NO;
		DEBUGLOG(@"touchesEnded");
    }

}

- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event {
    initialDistance = squareData.pinchDistanceShown = squareData.pinchDistance = 0.0f;
    squareData.rotstop = squareData.touchInside = squareData.scalestart = NO;
    DEBUGLOG(@"touchesCancelled");
}

/*****************************************************************************************************************************/
/* TEXT */
/*****************************************************************************************************************************/

- (void) drawText:(NSString*)theString :(float)X :(float)Y {


 }

/*****************************************************************************************************************************/
/* CAMERA */
/*****************************************************************************************************************************/


- (void)location :(float)lat :(float)lon :(float)accuracy {
	// show markers near here
	latitude = lat;
	longitude = lon;
	if(squareData.longitude == 0) {
		squareData.longitude = longitude;
		squareData.latitude = latitude;
	}
}


- (void)orientation :(float)or {
	orientation = or;
}

 // we're moving the camera; so setup the view based on that philosophy
 // http://www.sjbaker.org/steve/omniv/projection_abuse.html
- (void)perspective :(float)fovy :(float)aspect :(float)zNear :(float)zFar {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	double xmin, xmax, ymin, ymax;
	ymax = zNear * tan(fovy * M_PI / 360.0);
	ymin = -ymax;
	xmin = ymin * aspect;
	xmax = ymax * aspect;
	glFrustumf(xmin, xmax, ymin, ymax, zNear, zFar);
	glMatrixMode(GL_MODELVIEW);
//	glEnable(GL_DEPTH_TEST);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glDepthMask(GL_TRUE);
}

-(void)orthographic {                   
	glMatrixMode(GL_PROJECTION);		   
	glLoadIdentity();					   
	glOrthof( 0, 320, 480, 0, 1, 0 );				
	glMatrixMode(GL_MODELVIEW);				
	glLoadIdentity();					
	glDepthMask(GL_FALSE);
}

-(void)lookat :(GLfloat)eyex :(GLfloat)eyey :(GLfloat)eyez
			  :(GLfloat)centerx :(GLfloat)centery :(GLfloat)centerz
			  :(GLfloat)upx :(GLfloat)upy :(GLfloat)upz {
    GLfloat m[16];
    GLfloat x[3], y[3], z[3];
    GLfloat mag;
    /* Make rotation matrix */
    /* Z vector */
    z[0] = eyex - centerx;
    z[1] = eyey - centery;
    z[2] = eyez - centerz;
    mag = sqrt(z[0] * z[0] + z[1] * z[1] + z[2] * z[2]);
    if (mag) {                   /* mpichler, 19950515 */
		z[0] /= mag;
		z[1] /= mag;
		z[2] /= mag;
    }
    /* Y vector */
    y[0] = upx;
    y[1] = upy;
    y[2] = upz;
    /* X vector = Y cross Z */
    x[0] = y[1] * z[2] - y[2] * z[1];
    x[1] = -y[0] * z[2] + y[2] * z[0];
    x[2] = y[0] * z[1] - y[1] * z[0];
    /* Recompute Y = Z cross X */
    y[0] = z[1] * x[2] - z[2] * x[1];
    y[1] = -z[0] * x[2] + z[2] * x[0];
    y[2] = z[0] * x[1] - z[1] * x[0];
    /* mpichler, 19950515 */
    /* cross product gives area of parallelogram, which is < 1.0 for
     * non-perpendicular unit-length vectors; so normalize x, y here
     */
    mag = sqrt(x[0] * x[0] + x[1] * x[1] + x[2] * x[2]);
    if (mag) {
		x[0] /= mag;
		x[1] /= mag;
		x[2] /= mag;
    }
    mag = sqrt(y[0] * y[0] + y[1] * y[1] + y[2] * y[2]);
    if (mag) {
		y[0] /= mag;
		y[1] /= mag;
		y[2] /= mag;
    }
#define M(row,col)  m[col*4+row]
    M(0, 0) = x[0];
    M(0, 1) = x[1];
    M(0, 2) = x[2];
    M(0, 3) = 0.0;
    M(1, 0) = y[0];
    M(1, 1) = y[1];
    M(1, 2) = y[2];
    M(1, 3) = 0.0;
    M(2, 0) = z[0];
    M(2, 1) = z[1];
    M(2, 2) = z[2];
    M(2, 3) = 0.0;
    M(3, 0) = 0.0;
    M(3, 1) = 0.0;
    M(3, 2) = 0.0;
    M(3, 3) = 1.0;
#undef M
    glMultMatrixf(m);
	glRotatef(orientation,0,1,0);
    /* Translate Eye to Origin */	
    glTranslatef(-eyex, -eyey, -eyez);

}

- (void)setupView { // new method for intialisation of variables and states
	
    // Enable Multi Touch of the view
    self.multipleTouchEnabled = YES;

    // Initialise square data
    squareData.rotation = squareData.pinchDistance = squareData.pinchDistanceShown = 0.0f;
    squareData.scale = 1.0f;
    squareData.rotstop = squareData.touchInside = squareData.scalestart = NO;
    squareData.pos.x = 160.0f;
    squareData.pos.y = 240.0f;
    squareData.pinchDistance = 0.0f;
    squareData.rotspeed = 1.0f;

    // Initialise ellipse data
	ellipseData.latitude = 0.0;
	ellipseData.longitude = 0.0;
    ellipseData.rotation = 0.0f;
    ellipseData.rotstop = ellipseData.touchInside = ellipseData.scalestart = NO;
    ellipseData.pos.x = 160.0f;
    ellipseData.pos.y = 100.0f;
    ellipseData.rotspeed = -4.0f;

    // calculate the vertices of ellipse
    const GLfloat xradius = 35.0f;
    const GLfloat yradius = 25.0f;
    for (int i = 0; i < 720; i+=2) {
		ellipseVertices[i] = (cos(degreesToRadians(i)) * xradius) + 0.0f;
		ellipseVertices[i+1] = (sin(degreesToRadians(i)) * yradius) + 0.0f;
		DEBUGLOG(@"ellipseVertices[v%d] %.1f, %.1f",i, ellipseVertices[i], ellipseVertices[i+1]);
    }

	// field of view, aspect ratio, near and far
	[self perspective :45.0 :480.0f/320.0 :0.01 :100.0 ];

/*	
	 const GLfloat zNear = 0.01, zFar = 1000.0, fieldOfView = 45.0; 
	 GLfloat size; 
	 glEnable(GL_DEPTH_TEST);
	 glMatrixMode(GL_PROJECTION); 
	 size = zNear * tanf((fieldOfView/180.0) / 2.0);
	 CGRect rect = [self bounds]; 
	 glFrustumf(-size, size, -size / (rect.size.width / rect.size.height), size / 
	 (rect.size.width / rect.size.height), zNear, zFar); 
	 glViewport(0, 0, rect.size.width, rect.size.height);  
	 glMatrixMode(GL_MODELVIEW);
*/

}

/*****************************************************************************************************************************/
// DRAW
/*****************************************************************************************************************************/

- (void)drawView {

    [EAGLContext setCurrentContext:context];
    glBindFramebufferOES(GL_FRAMEBUFFER_OES, viewFramebuffer);
    glViewport(0, 0, backingWidth, backingHeight);

    // Clear background color
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

	// deal with eye
	if(TRUE) {

		// The default coordinate system in OpenGL is right-handed:
		// the positive x and y axes point right and up, and the negative z axis points forward
		glLoadIdentity();

		// rotate everything by the inverse eye orientation
		glRotatef(orientation,0,1,0);

		// translate everything by the inverse eye translation
		glTranslatef(-longitude, -1, -latitude );

		// let's not use this for now.
		// [self lookat :0 :1 :-5 :0 :0 :0 :0 :1 :0 ];
	}

	// draw field
	const GLfloat box[] = {
		-1.0, 0, -1.0,
		1.0, 0, -1.0,
		1.0, 0,  1.0,
		-1.0, 0,  1.0,
	};
	for(float x = -10; x < 10; x = x + 1 ) {
		for(float z = -10; z < 10; z = z + 1 ) {
			glPushMatrix();
			glTranslatef(x+squareData.longitude,0,z+squareData.latitude);
			glVertexPointer(3,GL_FLOAT,0,box);
			glEnableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_COLOR_ARRAY);
			glColor4f(0.0f,1.0f,0.0f,1.0f);
			glDrawArrays(GL_LINE_LOOP,0,4);
			glPopMatrix();
		}
	}

	// draw markers
	for(int i = 0; i < 128 ; i++ ) {
		
		if(markers[i].latitude == 0.0 ) {
			continue;
		}

		glPushMatrix();
		glTranslatef(markers[i].longitude,0,markers[i].latitude);
		glScalef(0.3,0.3,0.3);
		glRotatef(-markers[i].orientation,0,1,0);

		const GLfloat squareVertices[] = {
			-1, -1,  1, 1, -1,  1, -1,  1,  1, 1,  1,  1,
			-1, -1, -1, -1,  1, -1, 1, -1, -1, 1,  1, -1,
			-1, -1,  1, -1,  1,  1, -1, -1, -1, -1,  1, -1,
			1, -1, -1, 1,  1, -1, 1, -1,  1, 1,  1,  1,
			-1,  1,  1, 1,  1,  1, -1,  1, -1, 1,  1, -1,
			-1, -1,  1, -1, -1, -1, 1, -1,  1, 1, -1, -1,
		};

		glVertexPointer(3, GL_FLOAT, 0, squareVertices);
		glEnableClientState(GL_VERTEX_ARRAY);
		
		glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		glDrawArrays(GL_TRIANGLE_STRIP, 4, 4);
		
		glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
		glDrawArrays(GL_TRIANGLE_STRIP, 8, 4);
		glDrawArrays(GL_TRIANGLE_STRIP, 12, 4);
		
		glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
		glDrawArrays(GL_TRIANGLE_STRIP, 16, 4);
		glDrawArrays(GL_TRIANGLE_STRIP, 20, 4);

		glScalef(7,7,7);

		// draw word latitude in the world
		if( !markers[i].texture ) {
			NSString *theString = [[NSString alloc] initWithFormat:@"%g//%g", markers[i].longitude/10000, markers[i].latitude/10000 ];
			markers[i].texture = [[Texture2D alloc] initWithString:theString dimensions:CGSizeMake(150, 150) alignment:UITextAlignmentLeft fontName:@"Helvetica" fontSize:11];
			[theString release];
		} else {
			glBindTexture(GL_TEXTURE_2D, [markers[i].texture name]);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glEnableClientState(GL_VERTEX_ARRAY);
			glEnable(GL_TEXTURE_2D);
			glEnable(GL_BLEND);
			glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
			glColor4f(0, 0, 0, 1 );
			[markers[i].texture drawInRect:CGRectMake(0,0,1,1)];
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);
			glDisableClientState(GL_VERTEX_ARRAY);
			glDisable(GL_TEXTURE_2D);
			glDisable(GL_BLEND);
		}

		glPopMatrix();
	}


    // control the ellipse rotation
    if (!ellipseData.rotstop) {
		ellipseData.rotation += ellipseData.rotspeed;
		if(ellipseData.rotation > 360.0f)
			ellipseData.rotation -= 360.0f;
		else if(ellipseData.rotation < -360.0f)
			ellipseData.rotation += 360.0f;
    }

    glBindRenderbufferOES(GL_RENDERBUFFER_OES, viewRenderbuffer);
    [context presentRenderbuffer:GL_RENDERBUFFER_OES];
}

/*****************************************************************************************************************************/
// MORE SETUP
/*****************************************************************************************************************************/

- (void)layoutSubviews {
    [EAGLContext setCurrentContext:context];
    [self destroyFramebuffer];
    [self createFramebuffer];
    [self drawView];
}

- (BOOL)createFramebuffer {

    glGenFramebuffersOES(1, &viewFramebuffer);
    glGenRenderbuffersOES(1, &viewRenderbuffer);

    glBindFramebufferOES(GL_FRAMEBUFFER_OES, viewFramebuffer);
    glBindRenderbufferOES(GL_RENDERBUFFER_OES, viewRenderbuffer);
    [context renderbufferStorage:GL_RENDERBUFFER_OES fromDrawable:(CAEAGLLayer*)self.layer];
    glFramebufferRenderbufferOES(GL_FRAMEBUFFER_OES, GL_COLOR_ATTACHMENT0_OES, GL_RENDERBUFFER_OES, viewRenderbuffer);

    glGetRenderbufferParameterivOES(GL_RENDERBUFFER_OES, GL_RENDERBUFFER_WIDTH_OES, &backingWidth);
    glGetRenderbufferParameterivOES(GL_RENDERBUFFER_OES, GL_RENDERBUFFER_HEIGHT_OES, &backingHeight);

    if (USE_DEPTH_BUFFER) {
		glGenRenderbuffersOES(1, &depthRenderbuffer);
		glBindRenderbufferOES(GL_RENDERBUFFER_OES, depthRenderbuffer);
		glRenderbufferStorageOES(GL_RENDERBUFFER_OES, GL_DEPTH_COMPONENT16_OES, backingWidth, backingHeight);
		glFramebufferRenderbufferOES(GL_FRAMEBUFFER_OES, GL_DEPTH_ATTACHMENT_OES, GL_RENDERBUFFER_OES, depthRenderbuffer);
    }

    if(glCheckFramebufferStatusOES(GL_FRAMEBUFFER_OES) != GL_FRAMEBUFFER_COMPLETE_OES) {
		DEBUGLOG(@"failed to make complete framebuffer object %x", glCheckFramebufferStatusOES(GL_FRAMEBUFFER_OES));
		return NO;
    }
	
    return YES;
}


- (void)destroyFramebuffer {
    glDeleteFramebuffersOES(1, &viewFramebuffer);
    viewFramebuffer = 0;
    glDeleteRenderbuffersOES(1, &viewRenderbuffer);
    viewRenderbuffer = 0;
    if(depthRenderbuffer) {
		glDeleteRenderbuffersOES(1, &depthRenderbuffer);
		depthRenderbuffer = 0;
    }
}

- (void)startAnimation {
    self.animationTimer = [NSTimer scheduledTimerWithTimeInterval:animationInterval target:self selector:@selector(drawView) userInfo:nil repeats:YES];
}


- (void)stopAnimation {
    self.animationTimer = nil;
}


- (void)setAnimationTimer:(NSTimer *)newTimer {
    [animationTimer invalidate];
    animationTimer = newTimer;
}


- (void)setAnimationInterval:(NSTimeInterval)interval {
	
    animationInterval = interval;
    if (animationTimer) {
		[self stopAnimation];
		[self startAnimation];
    }
}


- (void)dealloc {
	
    [self stopAnimation];
	
    if ([EAGLContext currentContext] == context) {
		[EAGLContext setCurrentContext:nil];
    }
	
    [context release];
    [super dealloc];
}

@end

/////////////////////////////////////////////////////////////////////////////////////////////
// HUD CONTROLLER
/////////////////////////////////////////////////////////////////////////////////////////////

@implementation HUDController

@synthesize hudview;
@synthesize latitudeTextField, longitudeTextField, accuracyTextField;

- (void) locationManager: (CLLocationManager *) manager didUpdateToLocation: (CLLocation *) newLocation fromLocation: (CLLocation *) oldLocation {
    NSString *lat = [[NSString alloc] initWithFormat:@"%g", newLocation.coordinate.latitude];
    latitudeTextField.text = lat;

    NSString *lng = [[NSString alloc] initWithFormat:@"%g", newLocation.coordinate.longitude];
    longitudeTextField.text = lng;

    NSString *acc = [[NSString alloc] initWithFormat:@"%g", newLocation.horizontalAccuracy];
    accuracyTextField.text = acc;    

    [acc release];
    [lat release];
    [lng release];

	[hudview location :newLocation.coordinate.latitude :newLocation.coordinate.longitude :newLocation.horizontalAccuracy];
}

- (void)locationManager:(CLLocationManager *)manager didUpdateHeading:(CLHeading *)newHeading {
	if (newHeading.headingAccuracy > 0) {
		[newHeading retain];
		[hudview orientation :newHeading.trueHeading];
		//[newHeading retain];
		// headingType = YES for True North or NO for Magnetic North
		//if(newHeading.headingType) {
		//	currentHeading = newHeading.trueHeading;
		//} else { 
		//	currentHeading = newHeading.magneticHeading;
		//}
    }
}

- (void) locationManager: (CLLocationManager *) manager didFailWithError: (NSError *) error {
    NSString *msg = [[NSString alloc] initWithString:@"Error obtaining location"];
    UIAlertView *alert = [[UIAlertView alloc]
                          initWithTitle:@"Error" 
                          message:msg 
                          delegate:nil 
                          cancelButtonTitle: @"Done"
                          otherButtonTitles:nil];
    [alert show];    
    [msg release];
    [alert release];
}

- (HUDController *) init {
	NSLog(@"HUDController: init called");
	self.title = @"hud view";
	return self;
}

- (void)loadView {
	if(hudview == NULL) {
		CGRect frame = [[UIScreen mainScreen] applicationFrame]; //CGRectMake(0, 0, 320, 480);
		hudview = [[HUDView alloc] initWithFrame:frame];
		hudview.animationInterval = 1.0 / 60.0;
		self.view = hudview;
		//[hudview release];
		[hudview startAnimation];
		NSLog(@"HUDController: initialization complete!");
	} else {
		NSLog(@"HUDController: trying to initialize more than once!? Why?");
	}
}

- (void)viewDidLoad {

	lm = [[CLLocationManager alloc] init];
	{ // if ([lm locationServicesEnabled]) {
		lm.delegate = self;
		lm.desiredAccuracy = kCLLocationAccuracyBest;
		lm.distanceFilter = 1000.0f;
		[lm startUpdatingLocation];
		[lm startUpdatingHeading];
	}
	
	[hudview startAnimation];
	NSLog(@"HUDController: view did load");
}

- (void)applicationWillResignActive:(UIApplication *)application {
	NSLog(@"HUDController: Resigned Active");
	hudview.animationInterval = 1.0 / 5.0;
}

- (void)applicationDidBecomeActive:(UIApplication *)application {
	NSLog(@"HUDController: Became Active");
	hudview.animationInterval = 1.0 / 60.0;
}

- (void)dealloc {
	NSLog(@"HUDController: Released");
	[hudview release];
	[lm release];
	[latitudeTextField release];
	[longitudeTextField release];
	[accuracyTextField release];
	[super dealloc];
}

- (void)save_all {
	[hudview data_save];
}

@end

