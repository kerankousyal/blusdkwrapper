//
//  BZCHistoricalValue.h
//  BluzoneCloud
//
//  Created by Jason Clary on 8/29/17.
//  Copyright © 2017 Bluvision. All rights reserved.
//

@import UIKit;

@class BZCAggregateValue;
@class BZCMetricValue;
@class BZCRawValue;

NS_ASSUME_NONNULL_BEGIN


/**
 Represents a time interval

 - BZCTimeRangeIntervalMinutes: Interval in Minutes
 - BZCTimeRangeIntervalHours: Interval in Hours
 - BZCTimeRangeIntervalDays: Interval in Days
 - BZCTimeRangeIntervalWeeks: Interval in Weeks
 */
typedef NS_ENUM(NSUInteger, BZCTimeRangeInterval) {
    BZCTimeRangeIntervalMinutes,
    BZCTimeRangeIntervalHours,
    BZCTimeRangeIntervalDays,
    BZCTimeRangeIntervalWeeks
};



/**
 Represents a range in time as well as an interval over that range
 */
typedef struct {
    NSTimeInterval startDateTimeIntervalSince1970;
    NSTimeInterval endDateTimeIntervalSince1970;
    BZCTimeRangeInterval interval;

} BZCTimeRange;


/**
 Makes a new TimeRange

 @param startDate A Start date for the range
 @param endDate A End date for the range
 @param interval An Interval for the range to be over
 @return A fully initialized BZCTimeRange
 */
BZCTimeRange BZCMakeTimeRange(NSDate *startDate, NSDate *endDate, BZCTimeRangeInterval interval);


/**
 Represents different metrics of historical data

 - BZCMetricTypeTemperature: Temperature Metric
 - BZCMetricTypeLight: Light Metric
 - BZCMetricTypeRSSI: RSSI Metric
 - BZCMetricTypeXAccel: Accelerometer X Axis Metric
 - BZCMetricTypeYAccel: Accelerometer Y Axis Metric
 - BZCMetricTypeZAccel: Accelerometer Z Axis Metric
 - BZCMetricTypeXMag: Magnetometer X Axis Metric
 - BZCMetricTypeYMag: Magnetometer Y Axis Metric
 - BZCMetricTypeZMag: Magnetometer Z Axis Metric
 - BZCMetricTypeMagState: Magnetometer State Metric
 - BZCMetricTypeBattery: Battery Metric
 - BZCMetricTypeXAccelHighSpeed: Accelerometer High Speed X Axis Metric
 - BZCMetricTypeYAccelHighSpeed: Accelerometer High Speed Y Axis Metric
 - BZCMetricTypeZAccelHighSpeed: Accelerometer High Speed Z Axis Metric
 - BZCMetricTypePerRSSIBlufi: RSSI Per Blufi Metric
 - BZCMetricTypeXVelocity: Velocity X Metric
 - BZCMetricTypeYVelocity: Velocity Y Metric
 - BZCMetricTypeZVelocity: Velocity Z Metric
 */
typedef NS_ENUM(NSUInteger, BZCMetricType) {
    BZCMetricTypeTemperature,
    BZCMetricTypeLight,
    BZCMetricTypeRSSI,
    BZCMetricTypeXAccel,
    BZCMetricTypeYAccel,
    BZCMetricTypeZAccel,
    BZCMetricTypeXMag,
    BZCMetricTypeYMag,
    BZCMetricTypeZMag,
    BZCMetricTypeMagState,
    BZCMetricTypeBattery,
    BZCMetricTypeXAccelHighSpeed,
    BZCMetricTypeYAccelHighSpeed,
    BZCMetricTypeZAccelHighSpeed,
    BZCMetricTypePerRSSIBlufi,
    BZCMetricTypeXVelocity,
    BZCMetricTypeYVelocity,
    BZCMetricTypeZVelocity
};

/**
 *  BZCHistoricalValue objects respresent a single historical value in time read from a beacon either with a Blufi or Remote Condition Monitoring
 */
@interface BZCHistoryController : NSObject


/**
 Gets the Aggergate history of a beacon, this is a heavy call and should only be used when multiple metrics are needed

 @param beaconIdentifier The Identifier of the beacon
 @param range The TimeRange for the history
 @param completion A completion block executed once the history of the beacon has been retruned
 */
+ (void)aggregateBeaconHistory:(NSString *)beaconIdentifier timeRange:(BZCTimeRange)range compleiton:(void (^)( NSArray <BZCAggregateValue *> * _Nullable values,  NSError * _Nullable error))completion;


/**
 Gets an indiviual historical metric of a beacon, this call is considered light weight and will respond faster then the Aggergate method.

 @param beaconIdentifier The Identifier of the beacon
 @param metric The specific metric of historical values
 @param range The TimeRange for the history
 @param completion A completion block executed once the history of the beacon has been retruned
 */
+ (void)beaconHistory:(NSString *)beaconIdentifier metric:(BZCMetricType)metric timeRange:(BZCTimeRange)range completion:(void (^)(NSArray <BZCMetricValue *> * _Nullable values, NSError * _Nullable error))completion;


/**
 Get the raw high speed historical values over a given period of time. This can return a lot of results and it's not suggested that a large Time Range is used.

 @param beaconIdentifier The identifier of the beacon
 @param range The TimeRange for the hisoty, Interval is ignored
 @param completion A completion block executed once the history of the beacon has been returned
 */
+ (void)rawHighSpeedBeaconHistory:(NSString *)beaconIdentifier timeRange:(BZCTimeRange)range completion:(void (^)(NSArray <BZCRawValue *> * _Nullable values, NSError * _Nullable error))completion;

@end


/**
 BZCAggergateValue objects represent Aggergate historical values.
 */
@interface BZCAggregateValue : NSObject


/**
 The Beacon's Identifier for the Value
 */
@property (nonatomic, strong) NSString *identifier;


/**
 The Key as a string value
 */
@property (nonatomic, strong) NSString *keyAsString;


/**
 The key as a date time interval since epoch
 */
@property (nonatomic, nullable, strong) NSNumber *key;


/**
 Count of all temperature values
 */
@property (nonatomic, nullable, strong) NSNumber *tempCount;


/**
 Average of all temperature
 */
@property (nonatomic, nullable, strong) NSNumber *tempAvg;


/**
 Sum of all temperature values
 */
@property (nonatomic, nullable, strong) NSNumber *tempSum;


/**
 Count of all RSSI Values
 */
@property (nonatomic, nullable, strong) NSNumber *rssiCount;


/**
 Average of all RSSI Values
 */
@property (nonatomic, nullable, strong) NSNumber *rssiAvg;


/**
 Sum of all RSSI Values
 */
@property (nonatomic, nullable, strong) NSNumber *rssiSum;


/**
 Count of all Lums (Light) values
 */
@property (nonatomic, nullable, strong) NSNumber *lumsCount;


/**
 Average of all Lums (Light) values
 */
@property (nonatomic, nullable, strong) NSNumber *lumsAvg;


/**
 Sum of all Lums (Light) values
 */
@property (nonatomic, nullable, strong) NSNumber *lumsSum;


/**
 Count of all Magnetometer State changes
 */
@property (nonatomic, nullable, strong) NSNumber *magStateCount;


/**
 Average of all Magnetometer State changes
 */
@property (nonatomic, nullable, strong) NSNumber *magStateAvg;


/**
 Sum of all Magnetometer State changes
 */
@property (nonatomic, nullable, strong) NSNumber *magstateSum;

/**
 Count of all battery values
 */
@property (nonatomic, nullable, strong) NSNumber *batteryCount;


/**
 Average of all battery values
 */
@property (nonatomic, nullable, strong) NSNumber *batteryAvg;


/**
 Sum of all battery values
 */
@property (nonatomic, nullable, strong) NSNumber *batterySum;


/**
 The Peak value of temperature
 */
@property (nonatomic, nullable, strong) NSNumber *tempPeak;


/**
 The Peak value of RSSI
 */
@property (nonatomic, nullable, strong) NSNumber *rssiPeak;


/**
 The Peak value of Lums (Light)
 */
@property (nonatomic, nullable, strong) NSNumber *lumsPeak;


/**
 The Peak Magnetometer State change value
 */
@property (nonatomic, nullable, strong) NSNumber *magStatePeak;

/**
 The Peak value of Battery
 */
@property (nonatomic, nullable, strong) NSNumber *batteryPeak;


/**
 The High Speed X Axis Peak to Peak value
 */
@property (nonatomic, nullable, strong) NSNumber *xhsPeakToPeak;


/**
 The count of all High Speed Y Axis values
 */
@property (nonatomic, nullable, strong) NSNumber *yhsCount;


/**
 The Average High Speed Y Axis RMS values
 */
@property (nonatomic, nullable, strong) NSNumber *yhsRmsAvg;


/**
 The Sum of All High Speed Y Axis RMS values
 */
@property (nonatomic, nullable, strong) NSNumber *yhsRmsSum;


/**
 The Peak To Peak of the Accelerometer Y Axis
 */
@property (nonatomic, nullable, strong) NSNumber *yaccelPeakToPeak;


/**
 The Count of all Accelerometer Z Axis values
 */
@property (nonatomic, nullable, strong) NSNumber *zaccelCount;

/**
 The Average Accelerometer Z Axis values
 */
@property (nonatomic, nullable, strong) NSNumber *zaccelAvg;


/**
 The RMS of Accelerometer Z Axis
 */
@property (nonatomic, nullable, strong) NSNumber *zaccelRms;


/**
 The sum of all Acceleromter Z Axis values
 */
@property (nonatomic, nullable, strong) NSNumber *zaccelSum;


/**
 The Squared Sum of Accelerometer Z Axis values
 */
@property (nonatomic, nullable, strong) NSNumber *zaccelSqSum;


/**
 The Peak to Peak of High Speed Y Axis
 */
@property (nonatomic, nullable, strong) NSNumber *yhsPeakToPeak;


/**
 The count of all High Speec Z Axis values
 */
@property (nonatomic, nullable, strong) NSNumber *zhsCount;


/**
 The peak High Speed Y Axis Value
 */
@property (nonatomic, nullable, strong) NSNumber *yhsPeak;


/**
 The Peak Accelerometer Y Axis value
 */
@property (nonatomic, nullable, strong) NSNumber *yaccelPeak;

/**
 The Peak Accelerometer Z Axis value
 */
@property (nonatomic, nullable, strong) NSNumber *zaccelPeak;

/**
 The Magnetometer X Axis Peak value
 */
@property (nonatomic, nullable, strong) NSNumber *xmagPeak;

/**
 The Acceleromter X Axis Peak value
 */
@property (nonatomic, nullable, strong) NSNumber *xaccelPeak;

/**
 The Accelerometer Z Axis Peak to Peak value
 */
@property (nonatomic, nullable, strong) NSNumber *zaccelPeakToPeak;

/**
 The count of all Accelerometer X Axis values
 */
@property (nonatomic, nullable, strong) NSNumber *xaccelCount;

/**
 The average of all Accelerometer X Axis values
 */
@property (nonatomic, nullable, strong) NSNumber *xaccelAvg;

/**
 The minimum value of Accelerometer X Axis values
 */
@property (nonatomic, nullable, strong) NSNumber *xaccelMin;

/**
 The RMS value of Acceleromet X Axis values
 */
@property (nonatomic, nullable, strong) NSNumber *xaccelRms;

/**
 The sum of all Accelerometer X Axis values
 */
@property (nonatomic, nullable, strong) NSNumber *xaccelSum;

/**
 The minimum value of Accelerometer Y Axis values
 */
@property (nonatomic, nullable, strong) NSNumber *yaccelMin;

/**
 The Accelerometer X Axis Peak to Peak value
 */
@property (nonatomic, nullable, strong) NSNumber *xaccelPeakToPeak;

/**
 The Squared Sum of Accelerometer X Axis values
 */
@property (nonatomic, nullable, strong) NSNumber *xaccelSqSum;

/**
 The sum of all Accelerometer Y Axis values
 */
@property (nonatomic, nullable, strong) NSNumber *yaccelSum;

/**
 The Squared Sum of Accelerometer Y Axis values
 */
@property (nonatomic, nullable, strong) NSNumber *yaccelSqSum;

/**
 The count of all Accelerometer Y Axis values
 */
@property (nonatomic, nullable, strong) NSNumber *yaccelCount;

/**
 The average of all Accelerometer Y Axis values
 */
@property (nonatomic, nullable, strong) NSNumber *yaccelAvg;

/**
 The RMS of Accelerometer Y Axis values
 */
@property (nonatomic, nullable, strong) NSNumber *yaccelRms;

/**
 The average RMS of High Speed X Axis values
 */
@property (nonatomic, nullable, strong) NSNumber *xhsRmsAvg;

/**
 The sum of RMS Hish Speed X Axis Values
 */
@property (nonatomic, nullable, strong) NSNumber *xhsRmsSum;

/**
 The minimum Accelerometer Z Axis value
 */
@property (nonatomic, nullable, strong) NSNumber *zaccelMin;

/**
 The count of all High Speed X Axis values
 */
@property (nonatomic, nullable, strong) NSNumber *xhsCount;

/**
 The sum of all RMS High Speed Z Axis values
 */
@property (nonatomic, nullable, strong) NSNumber *zhsRmsSum;

/**
 The peak High Speed Z Axis value
 */
@property (nonatomic, nullable, strong) NSNumber *zhsPeak;

/**
 The average of all RMS High Speed Z Axis values
 */
@property (nonatomic, nullable, strong) NSNumber *zhsRmsAvg;

/**
 The peak High Speed X Axis value
 */
@property (nonatomic, nullable, strong) NSNumber *xhsPeak;

/**
 The count of all Magnetometer Y Axis values
 */
@property (nonatomic, nullable, strong) NSNumber *ymagCount;

/**
 The count of all Magnetometer Z Axis values
 */
@property (nonatomic, nullable, strong) NSNumber *zmagCount;

/**
 The average of all Magnetometer Z Axis values
 */
@property (nonatomic, nullable, strong) NSNumber *zmagAvg;

/**
 The sum of all Magnetometer Z Axis values
 */
@property (nonatomic, nullable, strong) NSNumber *zmagSum;

/**
 The peak Magnetometer Z Axis value
 */
@property (nonatomic, nullable, strong) NSNumber *zmagPeak;

/**
 The sum of all Magnetometer Y Axis values
 */
@property (nonatomic, nullable, strong) NSNumber *ymagSum;

/**
 The peak Magnetometer Y Axis value
 */
@property (nonatomic, nullable, strong) NSNumber *ymagPeak;

/**
 The average of all Magnetometer Y Axis values
 */
@property (nonatomic, nullable, strong) NSNumber *ymagAvg;

/**
 The count of all Magnetometer X Axis values
 */
@property (nonatomic, nullable, strong) NSNumber *xmagCount;

/**
 The average of all Magnetometer X Axis values
 */
@property (nonatomic, nullable, strong) NSNumber *xmagAvg;

/**
 The sum of all Magnetometer X Axis values
 */
@property (nonatomic, nullable, strong) NSNumber *xmagSum;

/**
 The Peak to Peak High Speed Z Axis value
 */
@property (nonatomic, nullable, strong) NSNumber *zhsPeakToPeak;

@property (nonatomic, nullable, strong) NSNumber *xhsRmsPeak;
@property (nonatomic, nullable, strong) NSNumber *yhsRmsPeak;
@property (nonatomic, nullable, strong) NSNumber *zhsRmsPeak;

@property (nonatomic, nullable, strong) NSNumber *xVelocityPeak;
@property (nonatomic, nullable, strong) NSNumber *xVelocityPeakToPeak;
@property (nonatomic, nullable, strong) NSNumber *xVelocityRMSAverage;
@property (nonatomic, nullable, strong) NSNumber *xVelocityRMSCount;
@property (nonatomic, nullable, strong) NSNumber *xVelocityRMSPeak;
@property (nonatomic, nullable, strong) NSNumber *xVelocityRMSSum;

@property (nonatomic, nullable, strong) NSNumber *yVelocityPeak;
@property (nonatomic, nullable, strong) NSNumber *yVelocityPeakToPeak;
@property (nonatomic, nullable, strong) NSNumber *yVelocityRMSAverage;
@property (nonatomic, nullable, strong) NSNumber *yVelocityRMSCount;
@property (nonatomic, nullable, strong) NSNumber *yVelocityRMSPeak;
@property (nonatomic, nullable, strong) NSNumber *yVelocityRMSSum;

@property (nonatomic, nullable, strong) NSNumber *zVelocityPeak;
@property (nonatomic, nullable, strong) NSNumber *zVelocityPeakToPeak;
@property (nonatomic, nullable, strong) NSNumber *zVelocityRMSAverage;
@property (nonatomic, nullable, strong) NSNumber *zVelocityRMSCount;
@property (nonatomic, nullable, strong) NSNumber *zVelocityRMSPeak;
@property (nonatomic, nullable, strong) NSNumber *zVelocityRMSSum;

@end


/**
 Represents a Historical value for a specific metric
 */
@interface BZCMetricValue : NSObject

/**
 The beacon's identifier for the value
 */
@property (nonatomic, strong) NSString *identifier;

/**
 The key as a date time interval since epoch
 */
@property (nonatomic, nullable, strong) NSNumber *key;

/**
 The key as a string value
 */
@property (nonatomic, nullable, strong) NSString *keyAsString;

/**
 The metric type for this value
 */
@property (nonatomic, assign) BZCMetricType metric;

/**
 The average of all values
 */
@property (nonatomic, nullable, strong) NSNumber *avg;

/**
 The count of all values
 */
@property (nonatomic, nullable, strong) NSNumber *count;

/**
 The peak value
 */
@property (nonatomic, nullable, strong) NSNumber *peak;

/**
 The sum of all values
 */
@property (nonatomic, nullable, strong) NSNumber *sum;

/*
 The rms of all values
 */
@property (nonatomic, nullable, strong) NSNumber *rms;

/*
 The min of all values
 */
@property (nonatomic, nullable, strong) NSNumber *min;

/*
 The Peak to Peak of all values
 */
@property (nonatomic, nullable, strong) NSNumber *peakToPeak;

/*
 The squared sums of all values
 */
@property (nonatomic, nullable, strong) NSNumber *squaredSum;


@property (nonatomic, nullable, strong) NSNumber *rmsPeak;

@end

@interface BZCRawValue : NSObject

@property (nonatomic, strong) NSNumber *projectId;

@property (nonatomic, strong) NSString *identifier;

@property (nonatomic, strong, nullable) NSString *blufiId;

@property (nonatomic, strong) NSNumber *dateKey;

@property (nonatomic, strong) NSString *dateStringKey;

@property (nonatomic, strong) NSNumber *sourceTime;

@property (nonatomic, readwrite, getter=isHighRes) BOOL highRes;

@property (nonatomic, readwrite, getter=isAdvanced) BOOL advanced;

@property (nonatomic, strong, nullable) NSNumber *xPeak;

@property (nonatomic, strong, nullable) NSNumber *yPeak;

@property (nonatomic, strong, nullable) NSNumber *zPeak;

@property (nonatomic, strong, nullable) NSNumber *xPeakToPeak;

@property (nonatomic, strong, nullable) NSNumber *yPeakToPeak;

@property (nonatomic, strong, nullable) NSNumber *zPeakToPeak;

@property (nonatomic, strong, nullable) NSNumber *xRms;

@property (nonatomic, strong, nullable) NSNumber *yRms;

@property (nonatomic, strong, nullable) NSNumber *zRms;

@property (nonatomic, strong, nullable) NSNumber *started;

@end

NS_ASSUME_NONNULL_END
