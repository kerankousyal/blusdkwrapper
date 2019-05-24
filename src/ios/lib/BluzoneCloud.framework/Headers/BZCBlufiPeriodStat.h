//
//  BZCBlufiPeriodStat.h
//  Bluzone
//
//  Created by Jason Clary on 7/19/16.
//  Copyright © 2016 Bluvision. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface BZCBlufiPeriodStat : NSObject

@property (readonly, nonatomic) NSString *blufiIdentifier;
@property (readonly, nonatomic) NSString *name;
@property (readonly, nonatomic) NSString *sid64;
@property (readonly, nonatomic) NSInteger RSSICount;
@property (readonly, nonatomic) double RSSIAverage;
@property (readonly, nonatomic) double meterToLocation;

- (instancetype)initWithDictionaryRepresentation:(NSDictionary *)dictionary;

@end
