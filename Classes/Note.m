#import "note.h"
@implementation Note
@synthesize kind,title, subtitle, description, image, coordinate;
-(id)init:(NSString*)k title:(NSString *)t description:(NSString *)d image:(NSString *)i {
	self.kind = k;
	self.title = t;
	self.subtitle = d;
	self.description = d;
	self.image = i;
	return self;
}
-(void)print {
}
-(void)dealloc {
	[kind release];
    [title release];
    [subtitle release];
    [description release];
	[self.image release];
    [super dealloc];
}
@end


