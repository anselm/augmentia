//
//  EXMessage.h
//  Entropy
//  (C) 2007-2009 Codesign
//  Licensed under LGPL (v3)
//

#import <Foundation/Foundation.h>

typedef int EXMessageStatus;

#define EXMessageStatusPending		1
#define EXMessageStatusProcessed	2

@interface EXMessage : NSObject {
	id object;
	NSString* host;
	int port;
	EXMessageStatus status;
	NSTimeInterval timeStamp;
}

- (id)initWithObject:(id)_object;
- (void)setHost:(NSString*)_host port:(int)_port;
- (void)setStatusToProcessed;
- (NSComparisonResult)compare:(EXMessage*)message;
- (NSString*)host;
- (int)port;
- (id)object;
- (EXMessageStatus)status;

@end
