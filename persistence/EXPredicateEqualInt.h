//
//  EXPredicateEqualInt.h
//  Entropy
//  (C) 2007-2009 Codesign
//  Licensed under LGPL (v3)
//

#import "EXPredicate.h"

@interface EXPredicateEqualInt : EXPredicate {
	int value;
}

- (id)initWithFieldName:(NSString*)_fieldName intValue:(int)_value;
- (int)intValue;

@end
