//
//  EXSharedObject.m
//  Entropy
//  (C) 2007-2009 Codesign
//  Licensed under LGPL (v3)
//

#import "EXSharedObject.h"
#import "EXContainer.h"
#import "LXSocket.h"
#import "NSObject_iPhone_cat.h"

@implementation EXSharedObject

- (id)init {
	if (self = [super init]) {
		__uniqueID = [EXContainer uniqueID];
	}
	return self;
}

- (void)dealloc {
	[containerIdentifier release];
	[super dealloc];
}

- (long long)__uniqueID {
	return __uniqueID;
}

- (void)encodeWithCoder:(NSCoder*)coder {
	[coder encodeInt64: __uniqueID forKey: @"__uniqueID"];
	[coder encodeObject: containerIdentifier forKey: @"__containerIdentifier"];
}

- (id)initWithCoder:(NSCoder*)coder {
	if (self = [super init]) {
		__uniqueID = [coder decodeInt64ForKey: @"__uniqueID"];
		containerIdentifier = [[coder decodeObjectForKey: @"__containerIdentifier"] retain];
	}
	return self;
}

- (NSString*)containerIdentifier {
	return containerIdentifier;
}

- (void)setContainerIdentifier:(NSString*)_containerIdentifier {
	containerIdentifier = [_containerIdentifier retain];
}

- (NSString*)description {
	return [NSString stringWithFormat: @"<%@:%lld:%@>", [self className], __uniqueID, containerIdentifier];
}

@end
