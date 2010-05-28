//
//  EXPersistentObject.m
//  Entropy
//  (C) 2007-2009 Codesign
//  Licensed under LGPL (v3)
//

#import "EXPersistentObject.h"
#import "EXContainer.h"

@implementation EXPersistentObject

- (void)setContainer:(EXContainer*)_container {
	container = _container;
}

- (void)store {
	EXContainer* _container = container;
	container = nil;
	[_container storeObject: self];
	container = _container;
}

@end
