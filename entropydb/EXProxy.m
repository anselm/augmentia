//
//  EXProxy.m
//  Entropy
//  (C) 2007-2009 Codesign
//  Licensed under LGPL (v3)
//

#import "EXProxy.h"

@implementation EXProxy

- (id)initWithObjectID:(int)oid container:(EXContainer*)_container loadedObjects:(NSMutableDictionary*)_loadedObjects {
	if (self = [super init]) {
		objectID = oid;
		container = _container;
		loadedObjects = _loadedObjects;
	}
	return self;
}

- (BOOL)__isUnused {
	return object == nil;
}

- (id)__object {
	if (object == nil) {
		//NSNumber* key = [NSNumber numberWithInt: objectID];
		//object = [loadedObjects objectForKey: key]; // causes an infinite loop
		//if (object == nil) {
			object = [[container queryWithID: objectID atomically: ![container isTransactionInProgress]
						   retrievedObjects: [NSMutableDictionary dictionary] lazyLoading: YES] retain];
			//[loadedObjects setObject: object forKey: key]; // probably not necessary but avoids forwarding
		//}
	}
	return object;
}

- (NSString*)className {
	return [[self __object] className];
}

- (NSString*)description {
	id _object = [self __object];
	NSString* desc = [_object description];
	return desc; //[NSString stringWithFormat: @"(proxy) %@", desc];
}

- (BOOL)isKindOfClass:(Class)cls {
	return [[self __object] isKindOfClass: cls];
}

- (BOOL)isMemberOfClass:(Class)cls {
	return [[self __object] isMemberOfClass: cls];
}

- (void)encodeWithCoder:(NSCoder*)coder {
	[[self __object] encodeWithCoder: coder];
}

- (NSMethodSignature*)methodSignatureForSelector:(SEL)selector {
	NSMethodSignature* signature = [super methodSignatureForSelector: selector];
	if (signature) return signature;
	signature = [[self __object] methodSignatureForSelector: selector];
	if (signature == nil) NSLog(@"the wrapped object doesn't recognize the forwarded selector");
	return signature;
}

- (void)forwardInvocation:(NSInvocation*)invocation {
	if ([object respondsToSelector: [invocation selector]]) [invocation invokeWithTarget: object];
	else [self doesNotRecognizeSelector: [invocation selector]];
}

- (void)dealloc {
	[object release];
	[super dealloc];
}

@end
