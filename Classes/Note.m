#import "note.h"
@implementation Note
@synthesize title, subtitle, description, image, coordinate;
-(id)init:(NSString *)t description:(NSString *)d image:(NSString *)i {
	self.title = t;
	self.subtitle = d;
	self.description = d;
	self.image = i;
	return self;
}
-(void)dealloc {
    [title release];
    [subtitle release];
    [description release];
	[self.image release];
    [super dealloc];
}
@end


