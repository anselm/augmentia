#import "AppDelegate.h"
#import "PostController.h"
#import "PostsController.h"
#import "Note.h"
#import "DB.h"

@implementation PostsController

- (void)viewWillAppear:(BOOL)animated {
	[super viewWillAppear:animated];
	if(notes) {
		[notes release];
		notes = nil;
	}
	
	// TODO remove hack.
	NSLog(@"hmmm");
	Note *note = [[Note alloc] init:@"profile" title:@"me stuff" description:@"and" image:@"icon.png"];
	[note retain];
	notes = [NSArray arrayWithObjects:note, nil ];
	[notes retain];
	[self.tableView reloadData];
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
	Note *note = [self getNoteAt:indexPath.row];
	if(note) {
		PostController* controller = [[PostController alloc] init];
		[self.navigationController pushViewController:controller animated:true];
		[controller release];
	}
}

@end


