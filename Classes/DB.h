
@class Note;
@interface DB : NSObject {
	NSString *databaseName;
	NSString *databasePath;
	NSMutableArray *notes;
	Note *cursor;
}
@property (nonatomic, retain) NSMutableArray *notes;
@property (nonatomic, retain) Note* cursor;
+ (id)sharedDB;
-(void) addProfile:(NSString *)title Password:(NSString *)password;
@end
