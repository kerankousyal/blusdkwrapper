//
//  BZCDeviceConfiguration.h
//  Bluzone
//
//  Copyright © 2015 Bluvision. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "BZCTemplate.h"
#import "BZCDeviceJobConfiguration.h"
#import "BZCDeviceIdentifier.h"

NS_ASSUME_NONNULL_BEGIN

@class BZCIBeaconTemplateConfiguration;
@class BZCBeaconTemplateConfiguration;
@class BZCEddystoneUIDTemplateConfiguration;
@class BZCEddystoneURLTemplateConfiguration;
@class BZCRemoteConditionMonitoringConfiguration;

/**
 *  BZCDeviceConfiguration object describe a device's configation based off its template
 */
@interface BZCDeviceConfiguration : NSObject <BZCDeviceJobConfiguration>

/**
 *  The template Identifier
 */
@property (nonatomic, readonly, nullable) NSNumber *templateID;

@property (nonatomic, nullable) BZCDeviceIdentifier *deviceIdentifier;

@property (nonatomic, strong) NSString *projectIdentifier;

/**
 *  The name of the configuration
 */
@property (nonatomic, strong) NSString *name;

/**
 *  The description of the configuration
 */
@property (nonatomic, strong) NSString *configurationDescription;

/** @name Beacon Properties **/

/**
 *  A boolean property set if the beacon is locked
 */
@property (nonatomic, assign, getter=isBeaconLocked) BOOL beaconLocked;

@property (nonatomic, copy) BZCBeaconTemplateConfiguration *sBeaconConfiguration;
@property (nonatomic, copy, nullable) BZCIBeaconTemplateConfiguration *iBeaconConfiguration;
@property (nonatomic, copy) BZCBeaconTemplateConfiguration *motionConfiguration;
@property (nonatomic, copy) BZCBeaconTemplateConfiguration *lightConfiguration;
@property (nonatomic, copy) BZCEddystoneUIDTemplateConfiguration *eddystoneUIDConfiguration;
@property (nonatomic, copy) BZCEddystoneURLTemplateConfiguration *eddystoneURLConfiguration;
@property (nonatomic, copy) BZCBeaconTemplateConfiguration *eddystoneTLMConfiguration;
@property (nonatomic, strong) BZCRemoteConditionMonitoringConfiguration *remoteConditionMonitoringConfiguration;
@property (nonatomic, copy) BZCBeaconTemplateConfiguration *assetTrackingConfiguration;

@property (nonatomic, assign, getter=isAssetTrackingEnabled) BOOL assetTrackingEnabled;

/** @name Blufi properties **/

/**
 *  A dictionary of user defined metadata
 */
@property (nonatomic, strong) NSDictionary *metadata;

/**
 *  The WIFI SSID if this configuration is for a Blufi
 */
@property (nonatomic, strong, nullable) NSString *SSID;

/**
 *  The WIFI security type if this configuration is for a Blufi
 */
@property (nonatomic, assign) BZCTemplateBlufiSecurityType securityType;

/**
 *  The WIFI username if this configuration is for a Blufi
 */
@property (nonatomic, strong, nullable) NSString *username;

/**
 *  The WIFI passphrase if this configuration is for a Blufi
 */
@property (nonatomic, strong, nullable) NSString *passphrase;

@property (nonatomic, strong, nullable) NSNumber *paringRSSI;

@end

NS_ASSUME_NONNULL_END
