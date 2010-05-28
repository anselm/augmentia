//
//  EXPersistentObject.m
//  Entropy
//  (C) 2007-2009 Codesign
//  Licensed under LGPL (v3)
//

#import "NSObject_iPhone_cat.h"

@implementation NSObject (iPhone)

- (NSString*)className {
	return NSStringFromClass([self class]);
}

@end
