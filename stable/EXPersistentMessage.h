//
//  EXMessage.h
//  Entropy
//  (C) 2007-2009 Codesign
//  Licensed under LGPL (v3)
//

#import <Foundation/Foundation.h>

@interface EXPersistentMessage : NSObject {
	id from;
	id to;
	id content;
	NSDate* posted;
	NSDate* sent;
	NSDate* delivered;
}

- (id)initWithFrom:(id)_from to:(id)_to content:(id)_content;
- (void)setPosted:(NSDate*)date;
- (void)setSent:(NSDate*)date;
- (void)setDelivered:(NSDate*)date;
- (id)content;
- (id)from;
- (id)to;
- (void)setTo:(id)_to;

@end
