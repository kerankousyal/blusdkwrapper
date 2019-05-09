//
//  BZCScanData.h
//  BluzoneCloud
//
//  Created by Jason Clary on 11/21/18.
//  Copyright © 2018 Bluvision. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface BZCScanData : NSObject

@property (nonatomic, strong) NSString *beaconId;
@property (nonatomic, strong) NSNumber *blufiId;
@property (nonatomic, strong) NSNumber *rssi;
@property (nonatomic, strong) NSNumber *temperature;
@property (nonatomic, strong) NSNumber *battery;
@property (nonatomic, strong) NSDate *timestamp;
@property (nonatomic, strong) NSNumber *latitude;
@property (nonatomic, strong) NSNumber *longitude;
@property (nonatomic, strong) NSString *status;
@property (nonatomic, strong) NSString *beaconName;
@property (nonatomic, strong) NSString *blufiName;
@property (nonatomic, strong) NSNumber *channel;

- (instancetype)initWithDictionary:(NSDictionary *)dictionary;

@end

NS_ASSUME_NONNULL_END
