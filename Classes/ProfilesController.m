
#import "AppDelegate.h"
#import "ProfilesController.h"
#import "DB.h"

@implementation ProfilesController

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
	AppDelegate *d = (AppDelegate *)[[UIApplication sharedApplication] delegate];
	DB *db = [DB sharedDB];
	Note *note = (Note*)[db.notes objectAtIndex:indexPath.row];
	db.cursor = note;
	[d setActiveViewController:@"map"];
}

-(void) addAction:(id) sender {
	AppDelegate *d = (AppDelegate *)[[UIApplication sharedApplication] delegate];
	[d setActiveViewController:@"ProfileNew"];
}

- (void)viewDidLoad {
	[super viewDidLoad];
	UIBarButtonItem *addButton = [[UIBarButtonItem alloc]
                                  initWithBarButtonSystemItem:UIBarButtonSystemItemAdd target:self action:@selector(addAction:)];
	self.navigationItem.rightBarButtonItem = addButton;
}	

@end