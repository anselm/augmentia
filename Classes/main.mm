#import <UIKit/UIKit.h>
#import "main.h"
int tmp_argc;
char **tmp_argv;
int main(int argc, char *argv[]) {
	tmp_argc = argc;
	tmp_argv = argv;
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	int retVal = UIApplicationMain(argc, argv, nil, @"AppDelegate" );
	[pool release];
	return retVal;
}

