//
//  EXProxy.h
//  CRo
//  Entropy
//  (C) 2007-2009 Codesign
//  Licensed under LGPL (v3)
//

#import <Foundation/Foundation.h>

#define LEASETIME 600

@interface EXObjectProxy : NSObject {
	Class cls;
	NSValue* key;
	NSTimer* leaseTimer;
	unsigned port;
	NSString* host;
}

+ (id)proxyForClass:(Class)_cls port:(unsigned)_port host:(NSString*)_host;
- (id)initWithClass:(Class)_cls port:(unsigned)_port host:(NSString*)_host;

@end
