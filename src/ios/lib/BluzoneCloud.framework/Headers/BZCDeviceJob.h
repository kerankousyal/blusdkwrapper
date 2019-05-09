//
//  BZCDeviceJob.h
//  Bluzone
//
//  Created by Jason Clary on 4/7/16.
//  Copyright © 2016 Bluvision. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "BZCDeviceJobConfiguration.h"

@class BZCDeviceConfiguration;
@class BZCDevice;

typedef NS_ENUM(NSUInteger, BZCDeviceJobType) {
    BZCDeviceJobTypeConfiguration,
    BZCDeviceJobTypeAccelerometerRead,
    BZCDeviceJobTypeFirmwareUpdate,
    BZCDeviceJobTypeBlink
};

@interface BZCDeviceJobLog : NSObject

@property (nonatomic, readonly) NSNumber *logIdentifier;
@property (nonatomic, readonly) NSNumber *jobIdentifier;
@property (nonatomic, readonly) NSNumber *blufiIdentifier;
@property (nonatomic, readonly) NSString *state;
@property (nonatomic, readonly) NSString *logDescription;
@property (nonatomic, readonly) NSString *webSocketSessionId;
@property (nonatomic, readonly) NSDate *dateCreated;

@end

@interface BZCDeviceJob : NSObject

@property (nonatomic, readonly) NSString *identifier;
@property (nonatomic, readonly) BZCDeviceJobType type;
@property (nonatomic, readonly) NSNumber *projectIdentifier;
@property (nonatomic, readonly) NSString *deviceIdentifier;
@property (nonatomic, readonly) NSString *notes;
@property (nonatomic, readonly) NSDate *createdDate;
@property (nonatomic, readonly) NSDate *updateDate;
@property (nonatomic, readonly) NSString *state;
@property (nonatomic, readonly) NSNumber *blufiIdentifier;
@property (nonatomic, readonly) NSString *blufiName;
@property (nonatomic, readonly) NSString *emailAddress;
@property (nonatomic, readonly) NSDate *startDate;
@property (nonatomic, readonly) BOOL bulkProvisioning;

@property (nonatomic, readonly) id<BZCDeviceJobConfiguration> configuration;

- (void)logsWithCompletion:(void (^)(NSArray <BZCDeviceJobLog *> *logs, NSError *error))completion;

+ (void)jobsForBeacon:(NSString *)beaconId completion:(void (^)(NSArray <BZCDeviceJob *> *jobs, NSError *error))completion;
+ (void)scheduleJob:(BZCDeviceJobType)job forDevice:(BZCDevice *)device notes:(NSString *)notes configuration:(id<BZCDeviceJobConfiguration>)configuration completion:(void (^)(BZCDeviceJob *job, NSError *error))completion;

- (void)cancelWithCompletion:(void (^)(BOOL success, NSError *error))completion;

@end
