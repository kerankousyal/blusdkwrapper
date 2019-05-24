//
//  BZCRemoteCondtionMonitoringConfiguration.h
//  Bluzone
//
//  Created by Jason Clary on 7/26/16.
//  Copyright © 2016 Bluvision. All rights reserved.
//
@import Foundation;

@interface BZCRemoteConditionMonitoringConfiguration : NSObject

@property (nonatomic, assign, getter=isEnabled) BOOL enabled;

@property (nonatomic, strong) NSNumber *temperatureInterval;
@property (nonatomic, strong) NSNumber *accelerometerInterval;
@property (nonatomic, strong) NSNumber *lightInterval;
@property (nonatomic, strong) NSNumber *magnometerInterval;

- (instancetype)initWithDictionary:(NSDictionary *)dictionary;

- (NSDictionary *)dictionaryRepresentation;

@end
