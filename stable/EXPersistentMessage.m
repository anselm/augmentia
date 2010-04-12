//
//  EXMessage.m
//  Entropy
//  (C) 2007-2009 Codesign
//  Licensed under LGPL (v3)
//

#import "EXPersistentMessage.h"

@implementation EXPersistentMessage

- (id)initWithFrom:(id)_from to:(id)_to content:(id)_content {
	if (self = [super init]) {
		from = [_from retain];
		to = [_to retain];
		content = [_content retain];
	}
	return self;
}

- (id)mutableCopyWithZone:(NSZone*)zone {
	EXPersistentMessage* message = [[EXPersistentMessage allocWithZone: zone] initWithFrom: from to: to content: content];
	return message;
}

- (void)setPosted:(NSDate*)date {
	posted = [date retain];
}

- (void)setSent:(NSDate*)date {
	posted = [sent retain];
}

- (void)setDelivered:(NSDate*)date {
	delivered = [sent retain];
}

- (void)encodeWithCoder:(NSCoder*)coder {
	[coder encodeObject: from forKey: @"from"];
	[coder encodeObject: to forKey: @"to"];
	[coder encodeObject: content forKey: @"content"];
	[coder encodeObject: posted forKey: @"posted"];
	[coder encodeObject: sent forKey: @"sent"];
	[coder encodeObject: delivered forKey: @"delivered"];
}

- (id)initWithCoder:(NSCoder*)coder {
	if (self = [super init]) {
		from = [[coder decodeObjectForKey: @"from"] retain];
		to = [[coder decodeObjectForKey: @"to"] retain];
		content = [[coder decodeObjectForKey: @"content"] retain];
		posted = [[coder decodeObjectForKey: @"posted"] retain];
		sent = [[coder decodeObjectForKey: @"sent"] retain];
		delivered = [[coder decodeObjectForKey: @"delivered"] retain];
	}
	return self;
}

- (id)content {
	return content;
}

- (id)from {
	return from;
}

- (id)to {
	return to;
}

- (void)setTo:(id)_to {
	if (to != _to) {
		[to release];
		to = [_to retain];
	}
}

- (NSComparisonResult)compare:(EXPersistentMessage*)message {
	return [self->sent compare: message->sent];
}

- (void)dealloc {
	[from release];
	[to release];
	[content release];
	[posted release];
	[sent release];
	[delivered release];
	//NSLog(@"Message - dealloced");
	[super dealloc];
}

@end
