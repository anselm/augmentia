//
//  EXServer.h
//  Entropy
//  (C) 2007-2009 Codesign
//  Licensed under LGPL (v3)
//

#import <Foundation/Foundation.h>

@interface EXServer : NSObject {
	NSMutableDictionary* objects;
	NSMutableDictionary* expirationDates;
	NSTimer* leaseTimer;
}

+ (id)server;
- (void)runWithPort:(NSNumber*)port;
- (void)runInThreadWithPort:(unsigned)port;

@end
