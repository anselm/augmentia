
#import "AppDelegate.h"
#import "MapController.h"
#import "PostsController.h"
#import "ProfileController.h"
#import "ARController.h"
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

	// http://edwardbenson.com/uitabbarcontroller-example
	// http://www.iphonemusings.com/2009/01/iphone-programming-tutorial-creating.html

	MapController* map = [[MapController alloc] initWithProfile:profile];
	map.title = map.navigationItem.title = @"explore";
	map.tabBarItem.image = [UIImage imageNamed:@"one.png"];

	PostsController* posts = [[PostsController alloc] init];
	posts.title = posts.navigationItem.title = @"collected";
	posts.tabBarItem.image = [UIImage imageNamed:@"one.png"];

	ARController* ar = [[ARController alloc] init];
	ar.tabBarItem.image = [UIImage imageNamed:@"one.png"];

	self.viewControllers = [NSArray arrayWithObjects:map, posts, ar, nil ];

	// TODO these are not released and waste memory every time we come here.
}

@end
