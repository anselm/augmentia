
#import "AppDelegate.h"
#import "ProfilesController.h"
#import "DB.h"

@implementation ProfilesController

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
	AppDelegate *d = (AppDelegate *)[[UIApplication sharedApplication] delegate];
	Note *note = (Note*)[d.db.notes objectAtIndex:indexPath.row];
	d.db.cursor = note;
	[d setActiveViewController:@"map"];
}

@end
