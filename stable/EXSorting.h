//
//  EXSorting.h
//  Entropy
//  (C) 2007-2009 Codesign
//  Licensed under LGPL (v3)
//

#import <Foundation/Foundation.h>

NSInteger EXSortingFunction(id num1, id num2, void* context);

@interface EXSorting : NSObject {
	NSString* fieldName;
	BOOL descending;
}

- (id)initWithFieldName:(NSString*)_fieldName;
- (id)initWithFieldName:(NSString*)_fieldName descending:(BOOL)_descending;
+ (id)sortingFieldName:(NSString*)_fieldName descending:(BOOL)_descending;
- (NSString*)fieldName;
- (BOOL)isDescending;

@end
