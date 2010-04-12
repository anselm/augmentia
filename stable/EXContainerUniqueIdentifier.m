//
//  EXContainerUniqueIdentifier.m
//  Entropy
//  (C) 2007-2009 Codesign
//  Licensed under LGPL (v3)
//

#import "EXContainerUniqueIdentifier.h"
#import "EXContainer.h"

@implementation EXContainerUniqueIdentifier

- (id)init {
	if (self = [super init]) {
		uniqueIdentifier = [[NSString stringWithFormat: @"%lld", [EXContainer uniqueID]] retain];
	}
	return self;
}

- (NSString*)uniqueIdentifier {
	return uniqueIdentifier;
}

- (void)dealloc {
	[uniqueIdentifier release];
	[super dealloc];
}

@end
