
#import "AppDelegate.h"
#import "ProfileController.h"
#import "ProfilesController.h"
#import "ProfileNewController.h"
#import "Note.h"
#import "DB.h"

@implementation ProfilesController

- (void)viewWillAppear:(BOOL)animated {
	[super viewWillAppear:animated];
	if(notes) {
		[notes release];
		notes = nil;
	}
	notes = [[DB sharedDB] getNotes:@"profile"];
	if(!notes || [notes count] < 1 ) {
		// TODO remove hack.
		NSLog(@"hmmm");
		Note *note = [[Note alloc] init:@"profile" title:@"me" description:@"and" image:@"icon.png"];
		[note retain];
		notes = [NSArray arrayWithObjects:note, nil ];
		[notes retain];
	}
	[self.tableView reloadData];
}

- (void)viewDidLoad {
	[super viewDidLoad];
	if(true) {
		UIBarButtonItem* addButton = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemAdd target:self action:@selector(addAction:)];
		self.navigationItem.rightBarButtonItem = addButton;
		[addButton release];
	}
}

//- (void)viewDidUnload {
//}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
	Note *note = [self getNoteAt:indexPath.row];
	if(note) {
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