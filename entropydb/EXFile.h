//
//  EXFile.h
//  Entropy
//  (C) 2007-2009 Codesign
//  Licensed under LGPL (v3)
//

#import <Foundation/Foundation.h>

@interface EXFile : NSObject {
	NSString* fileName;
}

- (id)initWithName:(NSString*)_fileName;
+ (id)fileWithName:(NSString*)_fileName;
- (BOOL)exists;
- (NSString*)fileName;

@end
