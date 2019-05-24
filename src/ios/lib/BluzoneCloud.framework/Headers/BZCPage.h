//
//  BZCPaging.h
//  BluzoneCloud
//
//  Created by Jason Clary on 8/14/18.
//  Copyright © 2018 Bluvision. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface BZCPage : NSObject

@property (nonatomic, readonly) NSInteger page;
@property (nonatomic, readonly) NSInteger size;

+ (BZCPage *)pageZero;

- (instancetype)initWtihPage:(NSInteger)page size:(NSInteger)size;
- (BZCPage *)increment;

- (NSDictionary *)dictionaryRepresentation;

@end
