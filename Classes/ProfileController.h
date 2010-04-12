#import "ListController.h"
@class Note;
// http://edwardbenson.com/uitabbarcontroller-example
// http://www.iphonemusings.com/2009/01/iphone-programming-tutorial-creating.html
@interface ProfileController: UITabBarController {
	Note* profile;
}
@property (nonatomic, retain) Note* profile;
- (id)initWithProfile:(Note*)profileParam;
@end
