
#import "AppDelegate.h"
#import "MapController.h"
#import "PostsController.h"
#import "ProfileController.h"
#import "Note.h"
#import "DB.h"

@implementation ProfileController
@synthesize profile;

- (id)initWithProfile:(Note*)profileParam {
	if(self = [super init ]) {
		self.title = @"Profile";
	}
	self.profile = profileParam;
	return self;
}

- (void) loadView {
	[super loadView];

	MapController* map = [[MapController alloc] initWithProfile:profile];
	map.title = map.navigationItem.title = @"explore";
	map.tabBarItem.image = [UIImage imageNamed:@"icon.png"];

	PostsController* posts = [[PostsController alloc] init];
	posts.title = posts.navigationItem.title = @"collected";
	posts.tabBarItem.image = [UIImage imageNamed:@"icon.png"];

	self.viewControllers = [NSArray arrayWithObjects:map, posts, nil ];

	// TODO these are not released and waste memory every time we come here.
}

@end
