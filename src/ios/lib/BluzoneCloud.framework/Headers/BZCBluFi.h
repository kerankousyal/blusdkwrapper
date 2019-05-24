//
//  BZCBluFi.h
//  Bluzone
//
//  Copyright © 2015 Bluvision. All rights reserved.
//

#import "BZCDevice.h"
@class BZCTemplate;

NS_ASSUME_NONNULL_BEGIN

/**
 *  BZCBluFi represent a provisioned Blufi
 */
@interface BZCBluFi : BZCDevice <NSSecureCoding>

/**
 *  The template name of the Blufi
 */
@property (nonatomic, readonly) NSString *templateName;

/**
 *  The 64 bit identifier of the Blufi
 */
@property (nonatomic, readonly) NSString *sid64;

/**
 *  The Cloud Address of the Blufi
 */
@property (nonatomic, readonly) NSString *cloudAddress;

/**
 *  The WIFI firmware revision of the Blufi
 */
@property (nonatomic, readonly) NSNumber *WIFIFirmwareRevision;

/**
 *  The WIFI SSID of the Blufi
 */
@property (nonatomic, readonly) NSString *WIFISSID;

/**
 *  The WIFI Security Type
 */
@property (nonatomic, readonly) NSString *WIFITemplateSecurityType;

/**
 *  The WIFI Template SSID
 */
@property (nonatomic, readonly) NSString *WIFITemplateSSID;

/**
 *  The DNS IP Address of the Blufi
 */
@property (nonatomic, readonly) NSString *DNSIPAddress;

/**
 *  The IP Address of the Blufi
 */
@property (nonatomic, readonly) NSString *IPAddress;

/**
 *  The GWIP Address of the Blufi
 */
@property (nonatomic, readonly) NSString *GWIPAddress;

/**
 *  The Mac Address of the Bluetooth device on the Blufi
 */
@property (nonatomic, readonly) NSString *BLEMacAddress;

/**
 *  Resets the Bluetooth chip on the blufi
 *
 *  @param completion A completion block executed once the Bluetooth chip has been reset on the blufi.
 */
- (void)resetBluetoothWithCompletion:(nullable void (^)(BOOL success, NSError * _Nullable error))completion;

- (void)refreshWithCompletion:(void (^)(BOOL success, NSError *error))completion;

+ (void)isBlufiPreprovisionedAtFactory:(NSString *)blufiIdentifier completion:(void(^)(BZCTemplate * _Nullable provisionedTemplate, NSError * _Nullable error))completion;
@end

NS_ASSUME_NONNULL_END
