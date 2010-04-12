//
//  EXPredicateEqualInt64.m
//  Entropy
//  (C) 2007-2009 Codesign
//  Licensed under LGPL (v3)
//

#import "EXPredicateEqualInt64.h"
#import <objc/runtime.h>

@implementation EXPredicateEqualInt64

- (id)initWithFieldName:(NSString*)_fieldName int64Value:(long long)_value {
	if (self = [super initWithFieldName: _fieldName]) {
		value = _value;
	}
	return self;
}

- (BOOL)evaluateWithObject:(id)object {
	void* _value;
	Ivar ivar = object_getInstanceVariable(object, [fieldName UTF8String], &_value);
	long long __value = *(long long*)((void*)object + ivar_getOffset(ivar));
	return value == __value;
}

@end
