//
//  BZCRemoteConditionMonitor.h
//  Bluzone
//
//  Copyright © 2015 Bluvision. All rights reserved.
//

@import Foundation;

@class BZCRemoteConditionMonitor;
@class BLUConfigurableBeacon;

NS_ASSUME_NONNULL_BEGIN

/**
 *  The state of remote condition monitoring in relation to the the underlying device
 */
typedef NS_ENUM(NSUInteger, BZCRemoteConditionMonitorState) {
    /**
     *  No state
     */
    BZCRemoteConditionMonitorStateNone,
    /**
     *  Connecting to the device
     */
    BZCRemoteConditionMonitorStateConnecting,
    /**
     *  Connected to the device
     */
    BZCRemoteConditionMonitorStateConnected,
    /**
     *  Reading the devices data
     */
    BZCRemoteConditionMonitorStateReading,
    /**
     *  Processing the devices data
     */
    BZCRemoteConditionMonitorStateProcessing
};

/**
 *  Function to get the human readable string for the state of condition monitoring
 *
 *  @param state the state
 *
 *  @return a human readable string to be used in a UI
 */
NSString * stringForRemoteConditionMonitorState(BZCRemoteConditionMonitorState state);

/**
 *  BZCRemoteConditionMonitorDelegate objects are used to communicate state changes during the reading of beacon data
 */
@protocol BZCRemoteCondtionMonitorDelegate <NSObject>

/**
 *  Delegate method for state change updates
 *
 *  @param conditionMonitor the conditionMonitor
 *  @param state            the new state of the conditionMonitor
 */
- (void)conditionMonitor:(BZCRemoteConditionMonitor *)conditionMonitor didChangeState:(BZCRemoteConditionMonitorState)state;

@end

/**
 *  BZCRemoteConditionMonitor objects connect to provisioned beacons that have enabled remote condition monitoring to read and transmit this data back to Bluzone.io
 */
@interface BZCRemoteConditionMonitor : NSObject

/**
 *  The current state of the monitor
 */
@property (nonatomic, readonly) BZCRemoteConditionMonitorState state;

/**
 *  The Delegate of this condition monitor
 */
@property (nonatomic, weak, nullable) id<BZCRemoteCondtionMonitorDelegate> delegate;


@property (nonatomic, copy, nullable) NSString *beaconPassword;

@property (nonatomic, strong) NSDictionary *userInfo;
/**
 *  Enables a beacon for remote condition monitoring, requires a specific firmware to be install on the beacon
 *
 *  @param temperatureInterval   the interval in seconds for temperature data to be logged
 *  @param lightInterval         the interval in seconds for light data to be logged
 *  @param accelerometerInterval the interval in seconds for accelerometer data to be logged
 *  @param completion            a completion block executed once the beacon has enabled remote condition monitoring
 */
- (void)enableConditionMonitoringWithTemperatureInterval:(NSTimeInterval)temperatureInterval
                                           lightInterval:(NSTimeInterval)lightInterval
                                   accelerometerInterval:(NSTimeInterval)accelerometerInterval
                                              completion:(nullable void (^)(BOOL success, NSError * _Nullable error))completion;

/**
 *  Starts the monitoring process where the beacon log data is read and proccessed to Bluzone.io 
 *
 *  @discussion This method will capture any data from the beacon if there is an error while sending this to Bluzone.io (i.e. network is down)
 *  and will rety sometime during the future when it can.
 *
 *  @param progressBlock a progress block to report state changes and a percentage complete
 *  @param completion    a completion block executed once the beacon has been full read and data has been sent to Bluzone.io.
 */
- (void)startMonitoringWithProgress:(nullable void (^)(BZCRemoteConditionMonitorState state, float percentage))progressBlock
                         completion:(nullable void (^)(BOOL success, NSError * _Nullable error))completion;

- (instancetype)initWithProjectIdentifier:(NSString *)projectIdentifier configurableBeacon:(BLUConfigurableBeacon *)configurableBeacon;

@end

NS_ASSUME_NONNULL_END
