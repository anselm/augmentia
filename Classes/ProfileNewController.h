
#import <UIKit/UIKit.h>


#import "SA_OAuthTwitterController.h"

@class SA_OAuthTwitterEngine;

@interface ProfileNewController: UITableViewController <UITextFieldDelegate, SA_OAuthTwitterControllerDelegate> {
	UITextField *activeTextField;
	UITextField *playerNameField;
	UITextField *playerPasswordField;
	SA_OAuthTwitterEngine *twitter_engine;
}
- (id) init;
- (void) dealloc;
- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView;
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section;
- (NSString *)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section;
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath;
@end
