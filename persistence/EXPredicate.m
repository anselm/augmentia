//
//  EXPredicate.m
//  Entropy
//  (C) 2007-2009 Codesign
//  Licensed under LGPL (v3)
//

#import "EXPredicate.h"

@implementation EXPredicate

- (id)initWithFieldName:(NSString*)_fieldName {
	if (self = [super init]) {
		fieldName = [_fieldName retain];
	}
	return self;
}

- (id)initWithSorting:(EXSorting*)_sorting {
	if (self = [super init]) {
		sorting = [_sorting retain];
	}
	return self;
}

+ (id)predicateWithSorting:(EXSorting*)_sorting {
	return [[[self alloc] initWithSorting: _sorting] autorelease];
}

- (void)setSorting:(EXSorting*)_sorting {
	if (sorting != _sorting) {
		[sorting release];
		sorting = [_sorting retain];
	}
}

- (EXSorting*)sorting {
	return sorting;
}

- (NSString*)fieldName {
	return fieldName;
}

- (BOOL)evaluateWithObject:(id)object {
	return YES;
}

- (void)dealloc {
	[fieldName release];
	[sorting release];
	[super dealloc];
}

@end
