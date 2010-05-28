//
//  EXMessage.m
//  Entropy
//  (C) 2007-2009 Codesign
//  Licensed under LGPL (v3)
//

#import "EXMessage.h"

@implementation EXMessage

- (id)initWithObject:(id)_object {
	if (self = [super init]) {
		object = [_object retain];
		status = EXMessageStatusPending;
		timeStamp = [[NSDate date] timeIntervalSinceReferenceDate];
	}
	return self;
}

- (void)setHost:(NSString*)_host port:(int)_port {
	host = [_host retain];
	port = _port;
}

- (void)setStatusToProcessed {
	status = EXMessageStatusProcessed;
}

- (NSComparisonResult)compare:(EXMessage*)message {
	NSComparisonResult result = [host compare: message->host];
	if (result == NSOrderedSame) {
		if (port < message->port) result = NSOrderedAscending;
		else if (port > message->port) result = NSOrderedDescending;
		else if (timeStamp < message->timeStamp) result = NSOrderedAscending;
		else if (timeStamp > message->timeStamp) result = NSOrderedDescending;
	}
	return result;
}

- (NSString*)host {
	return host;
}

- (int)port {
	return port;
}

- (id)object {
	return object;
}

- (EXMessageStatus)status {
	return status;
}

- (void)dealloc {
	[object release];
	[host release];
	[super dealloc];
}

@end
