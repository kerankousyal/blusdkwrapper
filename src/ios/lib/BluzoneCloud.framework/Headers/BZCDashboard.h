//
//  BZCDashboard.h
//  Bluzone
//
//  Copyright © 2015 Bluvision. All rights reserved.
//

#import <Foundation/Foundation.h>

@class BZCDevice;

NS_ASSUME_NONNULL_BEGIN

/**
 *  BZCDashboardType represent the type of dashboad being displayed
 */
typedef NS_ENUM(NSUInteger, BZCDashboardType) {
    /**
     *  A dashboard for Blufi data
     */
    BZCDashboardTypeBlufi,
    /**
     *  A dashboard for Beacon data (default)
     */
    BZCDashboardTypeBeacon
};

/**
 *  BZCDashboard represent a high level view of the Bluzone.io project
 */
@interface BZCDashboard : NSObject

/**
 *  The type of dashboard
 */
@property (nonatomic, readonly) BZCDashboardType type;

/**
 *  The total count of Devices
 */
@property (nonatomic, readonly) NSNumber *totalDevices;

/**
 *  The total count of Blufis
 */
@property (nonatomic, readonly) NSNumber *totalBlufis;

/**
 *  The total count of Beacons
 */
@property (nonatomic, readonly) NSNumber *totalBeacons;

/**
 *  The total count of active Devices
 */
@property (nonatomic, readonly) NSNumber *totalActive;

/**
 *  The total count of active Blufis
 */
@property (nonatomic, readonly) NSNumber *totalActiveBlufis;

/**
 *  The total count of active Beacons
 */
@property (nonatomic, readonly) NSNumber *totalActiveBeacons;

/**
 *  The total count of inactive Devices
 */
@property (nonatomic, readonly) NSNumber *totalInactive;

/**
 *  The total count of inactive Blufis
 */
@property (nonatomic, readonly) NSNumber *totalInactiveBlufis;

/**
 *  The total count of inactive Beacons
 */
@property (nonatomic, readonly) NSNumber *totalInactiveBeacons;

/**
 *  The total count of violations
 */
@property (nonatomic, readonly) NSNumber *totalViolations;

/**
 *  The total count of Blufi Violations
 */
@property (nonatomic, readonly) NSNumber *totalViolationsBlufis;

/**
 *  The total count of Beacon Violations
 */
@property (nonatomic, readonly) NSNumber *totalViolationsBeacons;

/**
 *  The total count of violating Beacons
 */
@property (nonatomic, readonly) NSNumber *totalViolatingBeacons;

/**
 *  The total count of violating Blufis
 */
@property (nonatomic, readonly) NSNumber *totalViolatingBlufis;

/**
 *  A list of devices for this project
 */
@property (nonatomic, readonly) NSArray <BZCDevice *> *devices;

/**
 *  Refreshes the dashboard
 *
 *  @param completion a completion block executed once the dashboard has been refreshed
 */
- (void)refreshWithCompletion:(nullable void (^)(BOOL success, NSError * _Nullable error))completion;

@end

NS_ASSUME_NONNULL_END
