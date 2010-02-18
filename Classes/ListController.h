#import <UIKit/UIKit.h>
@interface ListController: UITableViewController <UITextFieldDelegate> {
}
- (id) init;
- (void) dealloc;
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath;
@end
