//
//  EXSyncOutMessageObject.m
//  Entropy
//  (C) 2007-2009 Codesign
//  Licensed under LGPL (v3)
//

#import "EXSyncOutMessageObject.h"

@implementation EXSyncOutMessageObject

- (id)initWithObject:(EXSharedObject*)_object action:(EXSyncInfoAction)_action {
	if (self = [super init]) {
		object = [_object retain];
		uniqueID = [object __uniqueID];
		action = _action;
	}
	return self;
}

- (id)initWithObject:(NSString*)_object objectUniqueID:(long long)_uniqueID action:(EXSyncInfoAction)_action {
	if (self = [super init]) {
		object = [_object retain];
		uniqueID = _uniqueID;
		action = _action;
	}
	return self;
}

- (id)initWithCoder:(NSCoder*)coder {
	if (self = [super init]) {
		action = [coder decodeIntForKey: @"action"];
		uniqueID = [coder decodeInt64ForKey: @"uniqueID"];
		object = [[coder decodeObjectForKey: @"object"] retain];
	}
	return self;
}

- (void)encodeWithCoder:(NSCoder*)coder {
	[coder encodeInt: action forKey: @"action"];
	[coder encodeInt64: uniqueID forKey: @"uniqueID"];
	[coder encodeObject: object forKey: @"object"];
}

- (id)object {
	return object;
}

- (EXSyncInfoAction)objectAction {
	return action;
}

- (long long)objectUniqueID {
	return uniqueID;
}

- (void)dealloc {
	[object release];
	[super dealloc];
}

@end
