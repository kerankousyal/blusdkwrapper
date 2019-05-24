//
//  BZCBeacon.h
//  Bluzone
//
//  Copyright © 2015 Bluvision. All rights reserved.
//

#import "BZCDevice.h"
#import "BZCHistoryController.h"

@class BZCDeviceConfiguration;
@class BZCDeviceIdentifier;
@class BZCStatistics;

NS_ASSUME_NONNULL_BEGIN

/**
 *  BZCBeacon objects represent Beacons provisioned in Bluzone
 */
@interface BZCBeacon : BZCDevice <NSSecureCoding>

/**
 *  The last temperature of the beacon
 */
@property (nonatomic, readonly, nullable) NSNumber *temperature;

/**
 *  The last battery voltage of the beacon
 */
@property (nonatomic, readonly, nullable) NSNumber *batteryVoltage;

/**
 The current stats of a beacon
 */
@property (nonatomic, readonly, nullable) BZCStatistics *stats;

@property (nonatomic, readonly) BZCDeviceIdentifier *deviceIdentifier;

/**
 *  The mamanger type of this beacon
 */
@property (nonatomic, readonly) BZCDeviceManagerType managerType;

@property (nonatomic, readonly) CLLocationCoordinate2D assetTrackingLocation;

@property (nonatomic, readonly) NSDictionary *scanDataMap;

/**
 *  Gets the configuration of the beacon
 *
 *  @param completion a completion block executed once the configuration has been returned
 */
- (void)configurationWithCompletion:(nullable void (^)(BZCDeviceConfiguration * _Nullable configuration, NSError * _Nullable error))completion;

/**
 *  Gets the current signal strength to a blufi for this beacon
 *
 *  @param completion a completion block executed once the Beacon to BluFi RSSI has been retruned
 */
- (void)signalToBlufiWithCompletion:(nullable void (^)(NSNumber * _Nullable RSSIToBluFi, NSError * _Nullable error))completion;

/**
 *  Gets this Aggergate history of a beacon
 *
 *  @discussion This is a heavy API call that returns all historical values for a given beacon for the time range specified.
 *  If only a few historical metrics are needed @see -[BZCBeacon beaconHistory:timeRange:completion:];
 *
 *  @param timeRange   The timeRange of the history
 *  @param completion  A completion block executed once the history of the beacon has been retruned
 */
- (void)beaconHistoryForTimeRange:(BZCTimeRange)timeRange completion:(nullable void (^)(NSArray <BZCAggregateValue *> * _Nullable history, NSError * _Nullable error))completion;


/**
 Gets a specific metric history for a beacon within a given time range

 @param metric The metric that historical values are wanted
 @param range The timeRange of the history
 @param completion A completion block executed once the history of the beacon has been retruned
 */
- (void)beaconHistory:(BZCMetricType)metric timeRange:(BZCTimeRange)range completion:(nullable void (^)(NSArray <BZCMetricValue *> * _Nullable history, NSError * _Nullable error))completion;

- (void)beaconMetadataWithCompletion:(void (^)(NSDictionary *metadata, NSError *error))completion;
- (void)setBeaconMetadata:(NSDictionary *)metadata completion:(void (^)(NSDictionary *metadata, NSError *error))completion;

@end


/**
 BZCStatistics objects represent current statistics of a beacon
 */
@interface BZCStatistics : NSObject


/**
 The date this statitistic was created
 */
@property (nonatomic, strong) NSDate *dateCreated;

/**
 The date the beacon was last seen
 */
@property (nonatomic, strong) NSDate *dateSeen;

/**
 The date this statistic was updated
 */
@property (nonatomic, strong) NSDate *dateUpdated;

/**
 The peak Accelerometer X Axis value
 */
@property (nonatomic, strong) NSNumber *peakX;

/**
 The peak Accelerometer Y Axis value
 */
@property (nonatomic, strong) NSNumber *peakY;

/**
 The peak Acceleromet Z Axis value
 */
@property (nonatomic, strong) NSNumber *peakZ;

/**
 The peak to peak Accelerometer X Axis value
 */
@property (nonatomic, strong) NSNumber *peakToPeakX;

/**
 The peak to peak Accelerometer Y Axis value
 */
@property (nonatomic, strong) NSNumber *peakToPeakY;

/**
 The peak to peak Accelerometer Z Axis value
 */
@property (nonatomic, strong) NSNumber *peakToPeakZ;

/**
 The RMS Accelerometer X Axis value
 */
@property (nonatomic, strong) NSNumber *rmsX;

/**
 The RMS Accelerometer Y Axis value
 */
@property (nonatomic, strong) NSNumber *rmsY;

/**
 The RMS Accelerometer Z Axis value
 */
@property (nonatomic, strong) NSNumber *rmsZ;

/**
 The temperature of the beacon
 */
@property (nonatomic, strong) NSNumber *temperature;

/**
 The Maximum temperature the beacon has
 */
@property (nonatomic, strong) NSNumber *temperatureMax;

/**
 The Minimum temperatuer the beacon has
 */
@property (nonatomic, strong) NSNumber *temperatureMin;

/**
 The count of active violations for the beacon
 */
@property (nonatomic, strong) NSNumber *violationsActive;


@end

NS_ASSUME_NONNULL_END
