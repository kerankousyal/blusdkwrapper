//
//  BZCRealTimeLocation.h
//  Bluzone
//
//  Created by Jason Clary on 7/19/16.
//  Copyright © 2016 Bluvision. All rights reserved.
//

#import <Foundation/Foundation.h>

@class BZCBlufiPeriodStat;
@class BZCLocation;

@import CoreLocation;


/**
 BZCRealTimeLocation objects represent a location of an asset in real time using Bluzone's RTLS Engine
 */
@interface BZCRealTimeLocation : NSObject


@property (readonly, nonatomic) NSString *type;
@property (readonly, nonatomic) NSNumber *projectIdentifier;


/**
 The location object this real time location belongs in, this can change if a asset moves from one location to another @see BZCLocation
 */
@property (readonly, nonatomic) BZCLocation *cloudLocation;
@property (readonly, nonatomic) NSString *generatorType;
@property (readonly, nonatomic) NSString *beaconIdentifier;
@property (readonly, nonatomic) NSString *macAddress;


/**
 The current location of the asset
 */
@property (readonly, nonatomic) CLLocation *location;


/**
 The time stamp this location was generated on
 */
@property (readonly, nonatomic) NSDate *timestamp;
@property (readonly, nonatomic) double varianceX;
@property (readonly, nonatomic) double varianceY;
@property (readonly, nonatomic) double varianceZ;
@property (readonly, nonatomic) double displayRadius;
@property (readonly, nonatomic) NSInteger windowCalculationRange;
@property (readonly, nonatomic) double meterCalculationRange;


/**
 An error that could occur while generating the location
 */
@property (readonly, nonatomic) NSError *error;
@property (readonly, nonatomic, getter=isMotionStatic) BOOL motionStatic;
@property (readonly, nonatomic, getter=isThresholdCorrected) BOOL thresholdCorrected;
@property (readonly, nonatomic, getter=isBoundaryCorrected) BOOL boundaryCorrected;
@property (readonly, nonatomic, getter=boundaryExclusionCorrected) BOOL boundaryExclusionCorrected;
@property (readonly, nonatomic) NSArray <BZCBlufiPeriodStat *> *blufiPeriodStats;


- (instancetype)initWithDictionaryRepresentation:(NSDictionary *)dictionary;

@end
