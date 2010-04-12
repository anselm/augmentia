//
//  EXSorting.m
//  Entropy
//  (C) 2007-2009 Codesign
//  Licensed under LGPL (v3)
//

#import "EXSorting.h"
#import "EXException.h"
#import <objc/runtime.h>

NSInteger EXSortingFunction(id obj1, id obj2, void* context) {
	EXSorting* sorting = context;
	NSString* fieldName = [sorting fieldName];
	BOOL descending = [sorting isDescending];
	void *_value1, *_value2;
	Ivar ivar1 = object_getInstanceVariable(obj1, [fieldName UTF8String], &_value1);
	if (ivar1 == NULL) [EXException raise: @"EXException" format: @"Unknown instance variable"];
	Ivar ivar2 = object_getInstanceVariable(obj2, [fieldName UTF8String], &_value2);
	if (ivar2 == NULL) [EXException raise: @"EXException" format: @"Unknown instance variable"];
	NSString* type1 = [NSString stringWithUTF8String: ivar_getTypeEncoding(ivar1)];
	NSString* type2 = [NSString stringWithUTF8String: ivar_getTypeEncoding(ivar2)];
	if ([type1 isEqual: @"i"] && [type2 isEqual: @"i"]) {
		int value1 = *(int*)((void*)obj1 + ivar_getOffset(ivar1));
		int value2 = *(int*)((void*)obj2 + ivar_getOffset(ivar2));
		return descending == NO ? (value1 < value2 ? NSOrderedAscending : value1 == value2 ? NSOrderedSame : NSOrderedDescending)
			: (value1 < value2 ? NSOrderedDescending : value1 == value2 ? NSOrderedSame : NSOrderedAscending);
	} else if ([type1 isEqual: @"l"] && [type2 isEqual: @"l"]) {
		long value1 = *(long*)((void*)obj1 + ivar_getOffset(ivar1));
		long value2 = *(long*)((void*)obj2 + ivar_getOffset(ivar2));
		return descending == NO ? (value1 < value2 ? NSOrderedAscending : value1 == value2 ? NSOrderedSame : NSOrderedDescending)
		: (value1 < value2 ? NSOrderedDescending : value1 == value2 ? NSOrderedSame : NSOrderedAscending);
	} else if ([type1 isEqual: @"f"] && [type2 isEqual: @"f"]) {
		float value1 = *(float*)((void*)obj1 + ivar_getOffset(ivar1));
		float value2 = *(float*)((void*)obj2 + ivar_getOffset(ivar2));
		return descending == NO ? (value1 < value2 ? NSOrderedAscending : value1 == value2 ? NSOrderedSame : NSOrderedDescending)
		: (value1 < value2 ? NSOrderedDescending : value1 == value2 ? NSOrderedSame : NSOrderedAscending);
	} else if ([type1 isEqual: @"d"] && [type2 isEqual: @"d"]) {
		double value1 = *(double*)((void*)obj1 + ivar_getOffset(ivar1));
		double value2 = *(double*)((void*)obj2 + ivar_getOffset(ivar2));
		return descending == NO ? (value1 < value2 ? NSOrderedAscending : value1 == value2 ? NSOrderedSame : NSOrderedDescending)
		: (value1 < value2 ? NSOrderedDescending : value1 == value2 ? NSOrderedSame : NSOrderedAscending);
	} else if ([type1 characterAtIndex: 0] == '@' && [type2 characterAtIndex: 0] == '@') {
		id value1 = object_getIvar(obj1, ivar1);
		id value2 = object_getIvar(obj2, ivar2);
		if (value1 != nil && value2 != nil) {
			return descending == NO ? [value1 compare: value2] : [value2 compare: value1];
		} else if (value1 == nil && value2 == nil) {
			return NSOrderedSame;
		} else if (value1 == nil && value2 != nil) {
			return descending == NO ? NSOrderedAscending : NSOrderedDescending;
		} else {
			return descending == YES ? NSOrderedAscending : NSOrderedDescending;
		}
	}
	[EXException raise: @"EXException" format: @"Sorting error"];
	return NSOrderedSame;
}

@implementation EXSorting

- (id)initWithFieldName:(NSString*)_fieldName {
	return [self initWithFieldName: _fieldName descending: NO];
}

- (id)initWithFieldName:(NSString*)_fieldName descending:(BOOL)_descending {
	if (self = [super init]) {
		fieldName = [_fieldName retain];
		descending = _descending;
	}
	return self;
}

+ (id)sortingFieldName:(NSString*)_fieldName descending:(BOOL)_descending {
	return [[[self alloc] initWithFieldName: _fieldName descending: _descending] autorelease];
}

- (NSString*)fieldName {
	return fieldName;
}

- (BOOL)isDescending {
	return descending;
}

- (void)dealloc {
	[fieldName release];
	[super dealloc];
}

@end
