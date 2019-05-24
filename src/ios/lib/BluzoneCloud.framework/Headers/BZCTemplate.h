//
//  BZCTemplate.h
//  Bluzone
//
//  Copyright © 2015 Bluvision. All rights reserved.
//

@import Foundation;

NS_ASSUME_NONNULL_BEGIN

@class BZCIBeaconTemplateConfiguration;
@class BZCBeaconTemplateConfiguration;
@class BZCTag;
@class BZCDeviceIdentifier;

/**
 *  BZCTemplateType describes the type of template
 */
typedef NS_ENUM(NSUInteger, BZCTemplateType) {
    /**
     *  A Template used only for Blufi's
     */
    BZCTemplateTypeBluFi,
    /**
     *  A Template used only for Beacons
     */
    BZCTemplateTypeBeacon
};

/**
 *  BZCTemplateBlufiSecurityType describes the type of WIFI Security to be used for the template
 */
typedef NS_ENUM(NSUInteger, BZCTemplateBlufiSecurityType) {
    /**
     *  No Security is used
     */
    BZCTemplateBlufiSecurityTypeOpen,
    /**
     *  WEP Security is used
     */
    BZCTemplateBlufiSecurityTypeWEP,
    /**
     *  WAP/WAP2 Security is used
     */
    BZCTemplateBlufiSecurityTypeWPA2,
    /**
     *  Enterprise Security is used
     *  @discussion This is not used via mobile frameworks
     */
    BZCTemplateBlufiSecurityTypeEnterprise
};


@class BZCDeviceConfiguration;

/**
 *  BZCTemplate objects represent a Template for a beacon or a blufi to be shared bewtween multiple devices
 */
@interface BZCTemplate : NSObject

/**
 *  The name of this template
 */
@property (nonatomic, readonly) NSString *name;

/**
 *  The identifier of this template
 */
@property (nonatomic, readonly) NSNumber *identifier;

/**
 *  The description of this template
 */
@property (nonatomic, readonly) NSString *templateDescription;

@property (nonatomic, readonly, nullable) NSString *configType;

/**
 *  A boolean property indicating this template has iBeacon enabled
 */
@property (nonatomic, readonly) BOOL hasIBeacon;

/**
 *  A boolean property indicating this template has sBeacon enabled
 */
@property (nonatomic, readonly) BOOL hasSBeacon;

/**
 *  The WIFI SSID for this template, only when template type is BZCTemplateTypeBlufi
 */
@property (nonatomic, readonly, nullable) NSString *SSID;

/**
 *  The security type of this template, usefull only when template type is BZCTemplateTypeBlufi
 */
@property (nonatomic, readonly) BZCTemplateBlufiSecurityType securityType;

/**
 *  The Type of this template
 */
@property (nonatomic, readonly) BZCTemplateType type;

/**
 *  List all blufi templates 
 *
 *  @param completion a completion block executed once the blufi templates have been listed
 */
+ (void)blufiTemplatesWithCompletion:(nullable void (^)(NSArray <BZCTemplate *> * _Nullable blufiTemplates, NSError * _Nullable error))completion;

/**
 *  Lists all the templates a beacon can use
 *
 *  @param identifer  the identifier of the beacon
 *  @param completion a completion block executed once the beacon templates have been listed
 */
+ (void)beaconTemplatesForDeviceIdentifier:(NSNumber *)identifer completion:(nullable void (^)(NSArray <BZCTemplate *> * _Nullable beaconTemplates, NSError * _Nullable error))completion;

/**
 *  Gets a beacon template with a template identifier
 *
 *  @param identifier the identifier of the beacon template to get
 *  @param completion a completion block executed once the beacon template has been returned
 */
+ (void)beaconTemplateWithIdentifier:(NSString *)identifier completion:(nullable void (^)(BZCTemplate * _Nullable beaconTemplate, NSError * _Nullable error))completion;

/**
 *  Gets a blufi template with a template identifier
 *
 *  @param identifier the identifier of the blufi template to get
 *  @param completion a completion block executed once the blufi template has been retruned
 */
+ (void)blufiTemplateWithIdentifier:(NSString *)identifier completion:(nullable void (^)(BZCTemplate * _Nullable blufiTemplate, NSError * _Nullable error))completion;

/**
 *  Lets all the tags this template is assigned
 *
 *  @param completion a completion block executed once the tags have been listed
 */
- (void)tagsWithCompletion:(nullable void (^)(NSArray <BZCTag *> * _Nullable tags, NSError * _Nullable error))completion;

/**
 *  Get a device configuration for this template
 *
 *  @param completion a completion block executed once the configuration has been retruned
 */
- (void)configurationWithCompletion:(nullable void (^)(BZCDeviceConfiguration * _Nullable configuration, NSError * _Nullable error))completion;

/**
 *  Deletes this template
 *
 *  @param completion a completion block executed once the template has been deleted
 */
- (void)deleteWithCompletion:(nullable void (^)(BOOL success, NSError * _Nullable error))completion;

/**
 *  Creates a new Beacon Template
 *
 *  @param configuration The configuration of this template
 *  @param completion    a completion block executed once the beacon template has been created
 */
+ (void)beaconTemplateWithConfiguration:(BZCDeviceConfiguration *)configuration completion:(void (^)(BZCTemplate * _Nullable beaconTemplate, NSError * _Nullable error))completion;

/**
 *  Creates a new Blufi Template
 *
 *  @param configuration The configuration of this template
 *  @param completion    a completion block executed once the blufi template has been created
 */
+ (void)blufiTemplateWithConfiguration:(BZCDeviceConfiguration *)configuration completion:(void (^)(BZCTemplate * _Nullable blufiTemplate, NSError * _Nullable error))completion;

/**
 *  Saves a new configuation for this template
 *
 *  @param configuraiton the configuration to save
 *  @param completion    a completion block executed once the configuration has been saved
 */
- (void)saveConfiguration:(BZCDeviceConfiguration *)configuraiton completion:(void (^)(BOOL success, NSError * _Nullable error))completion;

@end

NS_ASSUME_NONNULL_END
