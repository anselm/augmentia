
#import <UIKit/UIKit.h>

@interface ProfileNewController: UITableViewController <UITextFieldDelegate> {
	UITextField *activeTextField;
	UITextField *playerNameField;
	UITextField *playerPasswordField;
}
- (id) init;
- (void) dealloc;
- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView;
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section;
- (NSString *)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section;
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath;
@end
