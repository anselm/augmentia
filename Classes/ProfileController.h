@class Note;
@interface ProfileController: UITabBarController {
	Note* profile;
}
@property (nonatomic, retain) Note* profile;
- (id)initWithProfile:(Note*)profileParam;
@end
