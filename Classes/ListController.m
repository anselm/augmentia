
#import "ListController.h"
#import "ASyncImage.h"
#import "DB.h"
#import "Note.h"

@implementation ListController
@synthesize notes;

- (id) init {
	if(self = [super initWithStyle: UITableViewStylePlain]) {
		self.title = @"Profiles";
		self.tableView.delegate = self;
		self.tableView.dataSource = self;
		self.tableView.rowHeight = 48.0;
		self.tableView.separatorStyle = UITableViewCellSeparatorStyleSingleLine;
		self.tableView.sectionHeaderHeight = 0;
	}
	return self;
}

- (void) dealloc {
	if(notes) {
		[notes release];
		notes = nil;
	}
	[super dealloc];
}

- (Note*) getNoteAt:(int)key {
	if(notes && [notes count] > key) {
		Note* note = [notes objectAtIndex:key];
		return note;
	}
	return nil;
}

- (BOOL)shouldAutorotateToInterfaceOrientation: (UIInterfaceOrientation)interfaceOrientation {
	return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
	if(notes == nil) {
		return 0;
	}
	return notes.count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {

	// allocate cell once only - CManagedTableViewController could do this TODO
    static NSString *CellIdentifier = @"ImageCell";
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
    if (cell == nil) {
        cell = [[[UITableViewCell alloc] initWithFrame:CGRectZero reuseIdentifier:CellIdentifier] autorelease];
    } else {
		ASyncImage* oldImage = (ASyncImage*) [cell.contentView viewWithTag:999];
		[oldImage removeFromSuperview];
    }

	// look at note
	Note *note = (Note*)[notes objectAtIndex:indexPath.row];

	// print note title
	NSString *padding = @"       ";
	NSString *title = [padding stringByAppendingString:note.title];
	cell.textLabel.text = title;
	cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;

	// fetch image asynchronously if present
	if(note->image != nil) {
		CGRect frame;
		frame.size.width=48; frame.size.height=48;
		frame.origin.x=0; frame.origin.y=0;
		ASyncImage* asyncImage = [[[ASyncImage alloc] initWithFrame:frame] autorelease];
		asyncImage.tag = 999;
		NSURL* url = [NSURL URLWithString:[note image]];
		[asyncImage loadImageFromURL:url];
		[cell.contentView addSubview:asyncImage];
		// TODO free image? TODO timeout? TODO error handling?
		// http://www.markj.net/iphone-asynchronous-table-image/
		//[NSURLRequest initWithURL: url ... timeoutInterval:60.0];	
	}
	
    return cell;
}

@end

