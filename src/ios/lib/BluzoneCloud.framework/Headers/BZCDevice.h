//
//  BZCDevice.h
//  Bluzone
//
//  Copyright © 2015 Bluvision. All rights reserved.
//

@import UIKit;

@import CoreLocation;
@import CoreBluetooth;

#import "BZCConfigurableBeaconProtocol.h"

@class BZCFirmware;
@class BLUSBeacon;
@class BZCLocation;
@class BZCSelfie;
@class BZCTag;
@class BZCViolation;
@class BZCScanData;

/**
 *  The Device Type
 */
typedef NS_ENUM(NSUInteger, BZCDeviceType) {
    /**
     *  An unknown device
     */
    BZCDeviceTypeUnknown = 0,
    /**
     *  a Blufi
     */
    BZCDeviceTypeBluFi,
    /**
     *  a Beacon
     */
    BZCDeviceTypeBeacon
};

/**
 *  The manager type of the beacon
 */
typedef NS_ENUM(NSUInteger, BZCDeviceManagerType) {
    /**
     *  An unknown manager
     */
    BZCDeviceManagerTypeUnknown,
    /**
     *  The cloud
     */
    BZCDeviceManagerTypeCloud,
    /**
     *  An App.
     */
    BZCDeviceManagerTypeApp
};

NS_ASSUME_NONNULL_BEGIN

/**
 *  Associates a String to a BZCDeviceType
 *
 *  @param deviceTypeString a string
 *
 *  @return the device type for this string
 */
BZCDeviceType deviceTypeFromString(NSString *deviceTypeString);

/**
 *  BZCDevice objects represent common interfaces between beacons and blufis'
 */
@interface BZCDevice : NSObject <NSSecureCoding>

/**
 *  The Device's identifier
 */
@property (nonatomic, readonly) NSString *identifier;

/**
 *  The Device's project identifer
 */
@property (nonatomic, readonly) NSNumber *projectIdentifier;

/**
 *  The Device's virtual device identifier, used only if this is a virtual device this is preproviosend but has no real device associated with it.
 */
@property (nonatomic, readonly, nullable) NSNumber *virtualDeviceIdentifier;

/**
 *  The Device's name
 */
@property (nonatomic, copy) NSString *name;

/**
 *  The Device's notes for the last job that was performed
 */
@property (nonatomic, copy) NSString *notes;

/**
 *  The Device's status
 */
@property (nonatomic, readonly) NSString *status;

/**
 *  The Device's tags
 */
@property (nonatomic, copy) NSArray<BZCTag *> *tags;

/**
 *  The Altitude of the device
 */
@property (nonatomic, copy) NSNumber *altitude;

/**
 *  THe Geolocation coordinate of the device
 */
@property (nonatomic, assign) CLLocationCoordinate2D coordinate;

/**
 *  The Floor number of the device
 */
@property (nonatomic, copy) NSNumber *floor;

/**
 *  The Location this device is provisioned at
 */
@property (nonatomic, strong) BZCLocation *location;

/**
 *  The Selfie of the device
 */
@property (nonatomic, strong) BZCSelfie *selfie;

/**
 *  The Device's Mac address
 */
@property (nonatomic, readonly) NSString *macAddress;

/**
 *  The date the device was created
 */
@property (nonatomic, readonly) NSDate *dateCreated;

/**
 *  The date the device was last modified
 */
@property (nonatomic, readonly) NSDate *dateModified;

/**
 *  The date the device was provisioned
 */
@property (nonatomic, readonly) NSDate *dateProvisioned;

/**
 *  The number of violations this device has caused
 */
@property (nonatomic, readonly) NSNumber *totalViolations;

/**
 *  The device's violations
 */
@property (nonatomic, readonly) NSArray <BZCViolation *> *violations;

/**
 *  The template identifier for this device
 */
@property (nonatomic, readonly) NSNumber *templateIdentifier;

/**
 *  The firmware of this device
 */
@property (nonatomic, readonly) BZCFirmware *firmware;

/**
 *  An optional configurable sBeacon associated with this device (used during provisioning)
 */
@property (nonatomic, readonly, nullable) BLUSBeacon *configurableBeacon;

@property (nonatomic, readonly, getter=isAssetTrackable) BOOL assetTrackable;
@property (nonatomic, strong) NSString *assetMaterialType;


/**
 *  Creates a Device from a dictionary
 *
 *  @param deviceDictionary A dictionary representing the properties of a device
 *
 *  @return A fully allocated BZCDevice object
 */
+ (BZCDevice *)deviceForDeviceDictionary:(NSDictionary *)deviceDictionary;

/**
 *  Gets a device for a specific identifier and type
 *
 *  @param identifier The identifier of the device
 *  @param type       The type of device
 *  @param completion A completion block executed once the device has been returned
 */
+ (void)deviceForIdentifier:(NSNumber *)identifier type:(BZCDeviceType)type completion:(nullable void (^)(BZCDevice * _Nullable device, NSError * _Nullable error))completion;

/**
 *  Gets a device for a specific configurable beacon from the cloud
 *
 *  @param configurableBeacon The Configurable beacon
 *  @param completion         A completion block executed once the device has been retruned
 */
+ (void)deviceForConfigruableBeacon:(BLUSBeacon *)configurableBeacon completion:(nullable void (^)(BZCDevice * _Nullable device, NSError * _Nullable error))completion;

/**
 *  Saves a device to Bluzone
 *
 *  @param completion A completion block executed once the device has been saved
 */
- (void)saveWithCompletion:(nullable void (^)(BOOL success, NSError * _Nullable error))completion;

/**
 *  Deletes a device from Bluzone
 *
 *  @param completion A completion block executed once the device has been deleted
 */
- (void)deleteWithCompletion:(nullable void (^)(BOOL success, NSError * _Nullable error))completion;
/**
 *  Binds a preprovisioned device to a virtual device, requires this device to have a virtualDeviceIdentifier
 *
 *  @param deviceIdentifier The 'real' device identifier to be provisioned
 *  @param completion       A completion block executed once the device has been bound.
 */
- (void)bindPreprovisionedDeviceToDeviceIdentifier:(NSNumber *)deviceIdentifier completion:(nullable void (^)(BZCDevice * _Nullable device, NSError * _Nullable error))completion;


/**
 Gets the Scan Data map for either a beacon or a blufi.

 @param completion A completion block executed once the scan data has been returned
 */
- (void)scanDataWithCompletion:(void(^)(NSDictionary <NSString *, BZCScanData *> * _Nullable scanData, NSError * _Nullable error))completion;

@end

NS_ASSUME_NONNULL_END
