//
//  EXPredicate.h
//  Entropy
//  (C) 2007-2009 Codesign
//  Licensed under LGPL (v3)
//

#import <Foundation/Foundation.h>
#import "EXSorting.h"

@interface EXPredicate : NSObject {
	NSString* fieldName;
	EXSorting* sorting;
}

- (id)initWithFieldName:(NSString*)_fieldName;
- (id)initWithSorting:(EXSorting*)_sorting;
+ (id)predicateWithSorting:(EXSorting*)_sorting;
- (void)setSorting:(EXSorting*)_sorting;
- (EXSorting*)sorting;
- (NSString*)fieldName;
- (BOOL)evaluateWithObject:(id)object;

@end
