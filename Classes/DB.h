
//
// Database - implemented as a singleton class
//
// http://developer.apple.com/mac/library/documentation/Cocoa/Conceptual/CocoaFundamentals/CocoaObjects/CocoaObjects.html#//apple_ref/doc/uid/TP40002974-CH4-SW32
// http://iphone.galloway.me.uk/iphone-sdktutorials/singleton-classes/
// http://www.mulle-kybernetik.com/artikel/Optimization/opti-2.html
// http://cocoawithlove.com/2008/11/singletons-appdelegates-and-top-level.html
//

@class Note;

@interface DB : NSObject {
	NSString *databaseName;
	NSString *databasePath;
	NSMutableDictionary *notes;
}
@property (nonatomic, retain) NSMutableDictionary* notes;
+ (id)sharedDB;
- (void) updateNote:(NSString *)k Title:(NSString *)t Description:(NSString *)d Image:(NSString *)i;
- (Note*) getNote:(NSString *)kind Title:(NSString *)title;
- (NSArray*) getNotes:(NSString*)kind;
- (id) init;
- (void) dealloc;
@end
