//
//  BZCProvisioner.h
//  Bluzone
//
//  Copyright © 2015 Bluvision. All rights reserved.
//

@import UIKit;
@import CoreBluetooth;
@import CoreLocation;

@class BZCDevice;
@class BZCSelfie;
@class BLUSBeacon;
@class BZCLocation;
@class BZCProvisioner;


NS_ASSUME_NONNULL_BEGIN

/**
 *  BZCProvisionerDelegate handle status and description changes during the provisioning process
 */
@protocol BZCProvisionerDelegate <NSObject>

/**
 Delegate method called when provisioning status changes.

 @param provisioner the provisioner object calling the delegate
 @param status the current status of provisioning
 */
- (void)provisioner:(BZCProvisioner *)provisioner didChangeStatus:(NSString *)status;


/**
 Delegate method called when the provisioning description changes.

 @param provisioner the provisioner object calling the delegate
 @param description the current description of provisioning
 */
- (void)provisioner:(BZCProvisioner *)provisioner didChangeDescription:(NSString *)description;


/**
 Delegate method called when an error occurs during provisioning and the provisioner retries provisioning

 @param provisioner the provisioner object calling the delegate
 @param error an error that occurec
 */
- (void)provisioner:(BZCProvisioner *)provisioner willRetryProvisioningWithError:(NSError *)error;

@optional


/**
 Delegate method called after a blufi has been provisioned and its connection status to bluzone is being monitored

 @param provisioner the provisioner object calling the delegate
 @param wifiStatus the wifi status of the blufi
 @param websocketStatus the websocket status of the blufi
 */
- (void)provisioner:(BZCProvisioner *)provisioner didChangeBlufiStaus:(NSString *)wifiStatus websocketStatus:(NSString *)websocketStatus;

@end

/**
 *  BZCProvisioner objects handle provisioning a physical device to Bluzone.io
 */
@interface BZCProvisioner : NSObject

/**
 *  The transaction identifier of this provisioner
 */
@property (nonatomic, readonly) NSString *transactionIdentifier;

/**
 *  The template identifier that is to be used during provisioning
 */
@property (nonatomic, copy) NSNumber *templateIdentifier;

@property (nullable, nonatomic, copy) NSString *templateDeviceType;
/**
 *  The password for a password protected beacon, this does not configure a beacon with a password. max length 16
 */
@property (nullable, nonatomic, copy) NSString *beaconPassword;

/**
 *  The notes to give this this provisioning transaction
 */
@property (nonatomic, copy, nullable) NSString *notes;

/**
 *  A name of the device to be provisioned with, this will overwrite any 'name' given to a already provisoned device
 */
@property (nonatomic, strong, nullable) NSString *deviceFriendlyName;

/**
 *  The geolocation of this device
 */
@property (nonatomic, copy) CLLocation *geolocation;

/**
 *  The selfie of this device
 */
@property (nonatomic, strong, nullable) BZCSelfie *selfie;

/**
 *  The tags of this device
 */
@property (nonatomic, strong, nullable) NSArray *tags;

/**
 *  The Location of this device
 */
@property (nonatomic, strong, nullable) BZCLocation *location;

/**
 *  The virtual device identifier for preprovioned devices
 */
@property (nonatomic, strong, nullable) NSString *virtualDeviceIdentifier;

/**
 *  A boolean property to indicate if provisoning is currently happening
 */
@property (nonatomic, readonly, getter=isProvisoning) BOOL provisioning;

/**
 *  A boolean property to indicate that the provisoner is connected to the physical device
 */
@property (nonatomic, readonly, getter=isConnected) BOOL connected;

/**
 *  A string of the device type
 */
@property (nonatomic, readonly) NSString *deviceType;

/**
 *  A configurable beacon to be used during provisioning (this is the physical device that is being provisoined)
 */
@property (nonatomic, readonly) BLUSBeacon *configurableBeacon;

/**
 *  A discription of the provisoning
 */
@property (nonatomic, readonly, nullable) NSString *provisioningDescription;

/**
 *  The delegate of the provisioner
 */
@property (nonatomic, weak, nullable) id<BZCProvisionerDelegate> delegate;

/**
 *  A already provisoned device, used druing reprovisoning.
 */
@property (nonatomic, strong, nullable) BZCDevice *alreadyProvisionedDevice;


/**
 *  Initilizes a provisoner object with a configurable beacon
 *
 *  @param configurableBeacon The configurableBeacon to be provisioned by Bluzone.io (i.e. a BLUSBeacon or BLUBluFi)
 *
 *  @return a fully initialized provisioner object
 */
- (instancetype)initWithConfigurableBeacon:(BLUSBeacon *)configurableBeacon NS_DESIGNATED_INITIALIZER;
- (instancetype)init NS_UNAVAILABLE;

/**
 *  Starts the provisoning process
 *
 *  @param completion             a completion block executed once provisioning has completed
 *  @param connectionFailureBlock a connection failure block executed if there is an error while connecting to the device. using the error can override this and we can try to continue again.
 */
- (void)startProvisioningWithCompletion:(nullable void (^)(BZCDevice * _Nullable device, NSError * _Nullable error))completion recoverableConnectionFailureBlock:(nullable BOOL (^)(NSError * _Nullable error))connectionFailureBlock;

- (void)startBlufiRecovertyWithCompletion:(nullable void (^)(BZCDevice * _Nullable device, NSError * _Nullable error))completion recoverableConnectionFailureBlock:(BOOL (^)(NSError *))connectionRecoveryBlock;
/**
 *  Cancels any current provisioning
 */
- (void)cancelProvisioning;

/**
 *  Logs of the provisoning process, can be useful when debugging
 *
 *  @return A string containing all the logs of the provisoning process.
 */
- (nullable NSString *)provisioningLog;


@property (nonatomic, readonly, getter=isBlufiProvisioning) BOOL blufiProvisioning;

@end

FOUNDATION_EXPORT NSString * const kBZCProvisioningErrorDomain;

NS_ASSUME_NONNULL_END
