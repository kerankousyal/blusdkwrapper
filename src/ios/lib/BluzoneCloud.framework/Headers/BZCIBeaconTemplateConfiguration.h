//
//  BZCIBeaconTemplateConfiguration.h
//  Bluzone
//
//  Copyright © 2015 Bluvision. All rights reserved.
//

@import Foundation;

#import "BZCBeaconTemplateConfiguration.h"

NS_ASSUME_NONNULL_BEGIN

/**
 *  BZCIBeaconTemplateProximityUUID templates how the iBeacon Proximity UUID should be assigned
 */
typedef NS_ENUM(NSUInteger, BZCIBeaconTemplateProximityUUID) {
    /**
     *  Will set the template iBeacon Proximity UUID to the default project UUID
     */
    BZCIBeaconTemplateProximityUUIDProject,
    /**
     *  Will set the template iBeacon Proximity UUID to an auto generated one
     */
    BZCIBeaconTemplateProximityUUIDAuto,
    /**
     *  WIll set the template iBeacon Proximity UUID to any user generate UUID
     */
    BZCIBeaconTemplateProximityUUIDUser
};

/**
 *  BZCIBeaconTemplateConfiguration object represent iBeacon template information for handling iBeacon broadcasts
 */
@interface BZCIBeaconTemplateConfiguration : BZCBeaconTemplateConfiguration

/**
 *  The type of prioximity UUID assignment to use
 */
@property (nonatomic, assign) BZCIBeaconTemplateProximityUUID proximityUUIDType;

/**
 *  The iBeacon Proximity UUID, set only if procximityUUIDType is set to `User`
 */
@property (nonatomic, strong) NSUUID *proximityUUID;

/**
 *  The iBeacon Major value for this template
 */
@property (nonatomic, strong) NSNumber *major;

@property (nonatomic, assign, getter=isAutoIncrementingMajor) BOOL autoIncrementMajor;

@property (nonatomic, strong) NSNumber *minor;

@property (nonatomic, assign, getter=isAutoIncrementingMinor) BOOL autoIncrementMinor;

@end

NS_ASSUME_NONNULL_END