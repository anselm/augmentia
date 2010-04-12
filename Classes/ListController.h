#import <UIKit/UIKit.h>
@class Note;
@interface ListController: UITableViewController <UITextFieldDelegate> {
	@public NSArray *notes;
}
@property (nonatomic, retain) NSArray *notes;
- (id) init;
- (void) dealloc;
- (Note*) getNoteAt:(int)key;
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath;
@end
