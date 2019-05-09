//
//  BZCContext.h
//  BluzoneCloud
//
//  Created by Jason Clary on 8/27/18.
//  Copyright © 2018 Bluvision. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface BZCContext : NSObject

@property (nonatomic, strong) NSNumber *accountId;
@property (nonatomic, strong) NSString *username;
@property (nonatomic, strong) NSString *email;
@property (nonatomic, strong) NSNumber *projectId;
@property (nonatomic, strong) NSArray<NSString *> * roles;
@property (nonatomic, strong) NSArray<NSString *> * features;
@property (nonatomic, strong) NSArray<NSString *> * products;
@property (nonatomic, strong) NSString *temperatureFormat;
@property (nonatomic, strong) NSString *language;

- (instancetype)initWithDictionary:(NSDictionary *)dictionary;

@end
