
#import "AppDelegate.h"
#import "ListController.h"
#import "ASyncImage.h"
#import "DB.h"
#import "Note.h"

@implementation ListController

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

- (void)viewWillAppear:(BOOL)animated {
	//[self reloadData];
	//[super viewWillAppear];
}

- (void)viewDidLoad {
	[super viewDidLoad];
}

- (void)dealloc {
	[super dealloc];
}

- (void)didReceiveMemoryWarning {
	[ super didReceiveMemoryWarning ];
}

- (BOOL)shouldAutorotateToInterfaceOrientation: (UIInterfaceOrientation)interfaceOrientation {
	return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
	AppDelegate *d = (AppDelegate *)[[UIApplication sharedApplication] delegate];
	return d.db.notes.count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    static NSString *CellIdentifier = @"ImageCell";
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
    if (cell == nil) {
        cell = [[[UITableViewCell alloc] initWithFrame:CGRectZero reuseIdentifier:CellIdentifier] autorelease];
    } else {
		ASyncImage* oldImage = (ASyncImage*) [cell.contentView viewWithTag:999];
		[oldImage removeFromSuperview];
    }
	
	AppDelegate *d = (AppDelegate *)[[UIApplication sharedApplication] delegate];
	Note *note = (Note*)[d.db.notes objectAtIndex:indexPath.row];
	
	// old way
	//NSData *file = [NSData dataWithContentsOfURL:[NSURL URLWithString:[note image]]];
	//UIImage *uiimage = [[UIImage alloc] initWithData:file];
	//cell.imageView.image = uiimage;
	//[uiimage release];
	
	NSString *padding = @"       ";
	NSString *title = [padding stringByAppendingString:note.title];		
	cell.textLabel.text = title;
	cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
	
	// new way
	CGRect frame;
	frame.size.width=48; frame.size.height=48;
	frame.origin.x=0; frame.origin.y=0;
	ASyncImage* asyncImage = [[[ASyncImage alloc] initWithFrame:frame] autorelease];
	asyncImage.tag = 999;
	NSURL* url = [NSURL URLWithString:[note image]];
	[asyncImage loadImageFromURL:url];
	[cell.contentView addSubview:asyncImage];

	// http://www.markj.net/iphone-asynchronous-table-image/
	//[NSURLRequest initWithURL: url ... timeoutInterval:60.0];	
	
    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
	AppDelegate *d = (AppDelegate *)[[UIApplication sharedApplication] delegate];
	Note *note = (Note*)[d.db.notes objectAtIndex:indexPath.row];
	d.db.cursor = note;
	[d setActiveViewController:@"detail"];
}

- (void)tableView:(UITableView *)tableView accessoryButtonTappedForRowWithIndexPath:(NSIndexPath *)indexPath {
	//NSLog(@"accessoryButtonTappedForRowWithIndexPath: row=%d", indexPath.row);
}

@end

