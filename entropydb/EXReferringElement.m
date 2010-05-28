//
//  EXReferringElement.m
//  Entropy
//  (C) 2007-2009 Codesign
//  Licensed under LGPL (v3)
//

#import "EXReferringElement.h"

@implementation EXReferringElement

- (id)initWithID:(int)_id {
	if (self = [super init]) {
		objectID = _id;
	}
	return self;
}

- (int)objectID {
	return objectID;
}

- (void)encodeWithCoder:(NSCoder*)coder {
	[coder encodeInt: objectID forKey: @"ID"];
}

- (id)initWithCoder:(NSCoder*)coder {
	if (self = [super init]) {
		objectID = [coder decodeIntForKey: @"ID"];
	}
	return self;
}

@end
