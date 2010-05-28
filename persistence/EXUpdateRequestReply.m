//
//  EXUpdateRequestReply.m
//  Entropy
//  (C) 2007-2009 Codesign
//  Licensed under LGPL (v3)
//

#import "EXUpdateRequestReply.h"

@implementation EXUpdateRequestReply

- (id)initWithLastSyncedUpdate:(NSTimeInterval)timeInterval updates:(NSArray*)_updates {
	if (self = [super init]) {
		lastSyncedUpdate = timeInterval;
		updates = [_updates retain];
	}
	return self;
}

- (NSTimeInterval)lastSyncedUpdate {
	return lastSyncedUpdate;
}

- (void)encodeWithCoder:(NSCoder*)coder {
	[coder encodeDouble: lastSyncedUpdate forKey: @"lastSyncedUpdate"];
	[coder encodeObject: updates forKey: @"updates"];
}

- (id)initWithCoder:(NSCoder*)coder {
	if (self = [super init]) {
		lastSyncedUpdate = [coder decodeDoubleForKey: @"lastSyncedUpdate"];
		updates = [[coder decodeObjectForKey: @"updates"] retain];
	}
	return self;
}

- (NSArray*)updates {
	return updates;
}

- (void)dealloc {
	[updates release];
	[super dealloc];
}

@end
