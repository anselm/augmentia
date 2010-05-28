//
//  EXPredicateEqualInt.m
//  Entropy
//  (C) 2007-2009 Codesign
//  Licensed under LGPL (v3)
//

#import "EXPredicateEqualInt.h"
#import <objc/runtime.h>

@implementation EXPredicateEqualInt

- (id)initWithFieldName:(NSString*)_fieldName intValue:(int)_value {
	if (self = [super initWithFieldName: _fieldName]) {
		value = _value;
	}
	return self;
}

- (BOOL)evaluateWithObject:(id)object {
	void* _value;
	Ivar ivar = object_getInstanceVariable(object, [fieldName UTF8String], &_value);
	int __value = *(int*)((void*)object + ivar_getOffset(ivar));
	return value == __value;
}

- (int)intValue {
	return value;
}

@end
