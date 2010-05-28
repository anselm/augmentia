//
//  EXDrainer.m
//  Entropy
//  (C) 2007-2009 Codesign
//  Licensed under LGPL (v3)
//

#import "EXDrainer.h"
#import "EXContainer.h"

@implementation EXDrainer

- (id)initWithContainer:(EXContainer*)_container {
	if (self = [super init]) {
		container = _container;
		active = YES;
	}
	return self;
}

- (void)deactivate {
	active = NO;
}

- (id)autorelease {
	[super autorelease];
	autoreleased = YES;
	return self;
}

- (BOOL)isAutoreleased {
	return autoreleased;
}

- (void)dealloc {
	if (active == YES) {
		[container drain];
		[container createDrainer];
	}
	[super dealloc];
}

@end
