#import "AppDelegate.h"
#import "ProfileController.h"
#import "Note.h"
#import "DB.h"

@implementation ProfileController

- (id) init {
	if(self = [super init ]) {
		self.title = @"Profile";
	}
	return self;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
	AppDelegate *d = (AppDelegate *)[[UIApplication sharedApplication] delegate];
	Note *note = (Note*)[d.db.notes objectAtIndex:indexPath.row];
	d.db.cursor = note;
	[d setActiveViewController:@"map"];
}

@end

