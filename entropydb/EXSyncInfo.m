//
//  EXSyncInfo.m
//  Entropy
//  (C) 2007-2009 Codesign
//  Licensed under LGPL (v3)
//

#import "EXSyncInfo.h"

@implementation EXSyncInfo

- (id)initWithObjectID:(int)_objectID objectUniqueID:(long long)_objectUniqueID action:(EXSyncInfoAction)_action className:(NSString*)_className containerIdentifier:(NSString*)_containerIdentifier {
	if (self = [super init]) {
		objectID = _objectID;
		objectUniqueID = _objectUniqueID;
		action = _action;
		timeStamp = [[NSDate date] timeIntervalSinceReferenceDate];
		objectClassName = [_className retain];
		containerIdentifier = [_containerIdentifier retain];
	}
	return self;
}

- (void)setSyncedOut:(BOOL)_syncedOut {
	syncedOut = _syncedOut;
}

- (void)setTimeStampToNow {
	timeStamp = [[NSDate date] timeIntervalSinceReferenceDate];
}

- (long long)objectUniqueID {
	return objectUniqueID;
}

- (int)objectID {
	return objectID;
}

- (NSString*)objectClassName {
	return objectClassName;
}

- (EXSyncInfoAction)objectAction {
	return action;
}

- (NSTimeInterval)timeStamp {
	return timeStamp;
}

- (NSString*)containerIdentifier {
	return containerIdentifier;
}

- (void)setObjectAction:(EXSyncInfoAction)_action {
	action = _action;
}

- (NSComparisonResult)compare:(EXSyncInfo*)syncInfo {
	if (timeStamp < syncInfo->timeStamp) return NSOrderedAscending;
	else if (timeStamp > syncInfo->timeStamp) return NSOrderedDescending;
	else return NSOrderedSame;
}

- (void)dealloc {
	[objectClassName release];
	[containerIdentifier release];
	[super dealloc];
}

@end
