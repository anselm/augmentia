//
//  EXPredicateEqualText.m
//  Entropy
//  (C) 2007-2009 Codesign
//  Licensed under LGPL (v3)
//

#import "EXPredicateEqualText.h"
#import <objc/runtime.h>

@implementation EXPredicateEqualText

- (id)initWithFieldName:(NSString*)_fieldName value:(NSString*)_value {
	if (self = [super initWithFieldName: _fieldName]) {
		value = [_value retain];
	}
	return self;
}

- (BOOL)evaluateWithObject:(id)object {
	void* _value;
	Ivar ivar = object_getInstanceVariable(object, [fieldName UTF8String], &_value);
	id valueInObject = object_getIvar(object, ivar);
	return [value isEqual: valueInObject];
}

- (NSString*)textValue {
	return value;
}

- (void)dealloc {
	[value release];
	[super dealloc];
}

@end
