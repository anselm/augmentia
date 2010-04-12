//
//  EXFile.m
//  Entropy
//  (C) 2007-2009 Codesign
//  Licensed under LGPL (v3)
//

#import "EXFile.h"

@implementation EXFile

- (id)initWithName:(NSString*)_fileName {
	if (self = [super init]) {
		fileName = [_fileName retain];
	}
	return self;
}

+ (id)fileWithName:(NSString*)_fileName {
	return [[[self alloc] initWithName: _fileName] autorelease];
}

- (BOOL)exists {
	return [[NSFileManager defaultManager] fileExistsAtPath: fileName];
}

- (NSString*)fileName {
	return fileName;
}

- (void)dealloc {
	[fileName release];
	[super dealloc];
}

@end
