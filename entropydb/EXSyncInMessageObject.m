//
//  EXSyncInMessageObject.m
//  Entropy
//  (C) 2007-2009 Codesign
//  Licensed under LGPL (v3)
//

#import "EXSyncInMessageObject.h"

@implementation EXSyncInMessageObject

- (id)initWithLastSyncedUpdate:(NSTimeInterval)_lastSync containerIdentifier:(NSString*)_containerIdentifier {
	if (self = [super init]) {
		lastSync = _lastSync;
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

- (NSTimeInterval)lastSync {
	return lastSync;
}

- (void)encodeWithCoder:(NSCoder*)coder {
	[coder encodeDouble: lastSync forKey: @"lastSync"];
	[coder encodeObject: containerIdentifier forKey: @"containerIdentifier"];
}

- (id)initWithCoder:(NSCoder*)coder {
	if (self = [super init]) {
		lastSync = [coder decodeDoubleForKey: @"lastSync"];
		containerIdentifier = [[coder decodeObjectForKey: @"containerIdentifier"] retain];
	}
	return self;
}

@end
