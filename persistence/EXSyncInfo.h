//
//  EXSyncInfo.h
//  Entropy
//  (C) 2007-2009 Codesign
//  Licensed under LGPL (v3)
//

typedef int EXSyncInfoAction;

#define EXSyncInfoActionUpdate		1
#define EXSyncInfoActionDeletion	2

#import <Foundation/Foundation.h>

@interface EXSyncInfo : NSObject {
	int objectID;
	EXSyncInfoAction action;
	NSTimeInterval timeStamp;
	BOOL syncedOut;
	NSString* objectClassName;
	NSString* containerIdentifier;
	long long objectUniqueID;
}

- (id)initWithObjectID:(int)_objectID objectUniqueID:(long long)_objectUniqueID action:(EXSyncInfoAction)_action className:(NSString*)_className containerIdentifier:(NSString*)_containerIdentifier;
- (void)setSyncedOut:(BOOL)_syncedOut;
- (void)setTimeStampToNow;
- (int)objectID;
- (long long)objectUniqueID;
- (EXSyncInfoAction)objectAction;
- (NSComparisonResult)compare:(EXSyncInfo*)syncInfo;
- (NSString*)objectClassName;
- (NSTimeInterval)timeStamp;
- (NSString*)containerIdentifier;
- (void)setObjectAction:(EXSyncInfoAction)_action;

@end
