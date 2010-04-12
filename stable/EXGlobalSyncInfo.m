//
//  EXGlobalSyncInfo.m
//  Entropy
//  (C) 2007-2009 Codesign
//  Licensed under LGPL (v3)
//

#import "EXGlobalSyncInfo.h"

@implementation EXGlobalSyncInfo

- (id)initWithContainerIdentifier:(NSString*)_containerIdentifier {
	if (self = [super init]) {
		containerIdentifier = [_containerIdentifier retain];
	}
	return self;
}

- (void)dealloc {
	[containerIdentifier release];
	[super dealloc];
}

- (NSString*)containerIdentifier {
	return containerIdentifier;
}

- (void)setLastIncomingSync:(NSTimeInterval)timeInterval {
	lastIncomingSync = timeInterval;
}

- (NSTimeInterval)lastIncomingSync {
	return lastIncomingSync;
}

@end
