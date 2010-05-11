
#import "AppDelegate.h"
#import "ProfileController.h"
#import "ProfilesController.h"
#import "ProfileNewController.h"
#import "Note.h"
#import "DB.h"

@implementation ProfilesController

- (void)viewDidLoad {
	[super viewDidLoad];
	if(true) {
		UIBarButtonItem* addButton = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemAdd target:self action:@selector(addAction:)];
		self.navigationItem.rightBarButtonItem = addButton;
		[addButton release];
	}
	if(notes) {
		[notes release];
		notes = nil;
	}
	notes = [[DB sharedDB] getNotes:@"profile"];
	[self.tableView reloadData];
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
	Note *note = [self getNoteAt:indexPath.row];
	if(note) {
		// TODO should i allocate this with autorelease?
		ProfileController* profile = [[ProfileController alloc] initWithProfile:note];
		[self.navigationController pushViewController:profile animated:true];
		[profile release];
	}
}

-(void) addAction:(id) sender {
	ProfileNewController* profile_new = [[ProfileNewController alloc] init];
	[self.navigationController pushViewController:profile_new animated:true];
	[profile_new release];
}

// TODO delete a profile

@end