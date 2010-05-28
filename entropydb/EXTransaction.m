//
//  EXTransaction.m
//  Entropy
//  (C) 2007-2009 Codesign
//  Licensed under LGPL (v3)
//

#import "EXTransaction.h"
#import "EXContainer.h"
#import "EXException.h"

@implementation EXTransaction

- (id)initWithContainer:(EXContainer*)_container timeout:(NSTimeInterval)timeout {
	if (self = [super init]) {
		if (timeout > 0) {
			timer = [NSTimer scheduledTimerWithTimeInterval: timeout target: self selector: @selector(timedOut:) userInfo: nil repeats: NO];
			//NSLog(@"Transaction timer set up: %f %d %@", timeout, [timer isValid], [timer fireDate]);
		}
		container = [_container retain];
		[container lockForTransaction];
		[container executeSQL: @"BEGIN EXCLUSIVE TRANSACTION"];
		storedObjects = [[NSMutableDictionary alloc] init];
	}
	return self;
}

- (void)timedOut:(NSTimer*)_timer {
	NSLog(@"Transaction timed out - rolling back");
	timer = nil;
	[self rollback];
	invalidated = YES;
}

- (NSTimer*)timer {
	return timer;
}

- (void)commit {
	if (invalidated == YES) {
		if (timeoutExceptionRaised == NO) {
			timeoutExceptionRaised = YES;
			[EXException raise: @"EXException" format: @"Transaction timeout"];
		} else return;
	}
	[timer invalidate];
	if ([container executeSQL: @"COMMIT"] == NO) [EXException raise: @"EXException" format: @"Commit failed"];
	else [container unlockForTransaction];
}

- (void)rollback {
	if (invalidated == YES) {
		if (timeoutExceptionRaised == NO) {
			timeoutExceptionRaised = YES;
			[EXException raise: @"EXException" format: @"Transaction timeout"];
		} else return;
	}
	[timer invalidate];
	if ([container executeSQL: @"ROLLBACK"] == NO) [EXException raise: @"EXException" format: @"Rollback failed"];
	else [container unlockForTransaction];
}

- (int)storeObject:(id)object {
	if (invalidated == YES) {
		if (timeoutExceptionRaised == NO) {
			timeoutExceptionRaised = YES;
			[EXException raise: @"EXException" format: @"Transaction timeout"];
		} else return -1;
	}
	if ([EXContainer isCollection: object]) {
		[EXException raise: @"EXException" format: @"A collection object cannot be stored directly"];
		return -1;
	}
	NSMutableSet* processedObjects = [[NSMutableSet alloc] init];
	int objectID = [container store: object atomically: NO storedObjects: storedObjects locally: NO processedObjects: processedObjects];
	[processedObjects release];
	return objectID;
}

- (BOOL)removeObject:(id)object {
	if (invalidated == YES) {
		if (timeoutExceptionRaised == NO) {
			timeoutExceptionRaised = YES;
			[EXException raise: @"EXException" format: @"Transaction timeout"];
		} else return NO;
	}
	return [container removeObject: object atomically: NO locally: NO];
}

- (void)dealloc {
	//NSLog(@"Transaction dealloced");
	[container release];
	[storedObjects release];
	[super dealloc];
}

@end
