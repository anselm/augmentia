//
//  EXSyncOutMessageObject.h
//  Entropy
//  (C) 2007-2009 Codesign
//  Licensed under LGPL (v3)
//

#import "EXSharedObject.h"
#import "EXSyncInfo.h"

@interface EXSyncOutMessageObject : NSObject {
	id object;
	EXSyncInfoAction action;
	long long uniqueID;
}

- (id)initWithObject:(EXSharedObject*)_object action:(EXSyncInfoAction)_action;
- (id)initWithObject:(NSString*)_object objectUniqueID:(long long)_uniqueID action:(EXSyncInfoAction)_action;
- (id)object;
- (EXSyncInfoAction)objectAction;
- (long long)objectUniqueID;

@end
