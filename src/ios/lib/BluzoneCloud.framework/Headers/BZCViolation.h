//
//  BZCViolation.h
//  Bluzone
//
//  Copyright © 2015 Bluvision. All rights reserved.
//

@import Foundation;

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, BZCViolationType) {
    BZCViolationTypeUnknown,
    BZCViolationTypePresence,
    BZCViolationTypeBattery,
    BZCViolationTypeTemperature,
    BZCViolationTypeAccelerometer,
    BZCViolationTypeLight,
    BZCViolationTypeDisplacement,
    BZCViolationTypeGeofence,
    BZCViolationTypeSignal,
    BZCViolationTypeDistance,
    BZCViolationTypeRogueBeacon,
    BZCViolationTypeMotion,
    BZCViolationTypeDwellTime,
    BZCViolationTypeProximityAlert,
    BZCViolationTypeAmbientTemperature,
    BZCViolationTypeEnterExit,
    BZCViolationTypeLocationChange,
    BZCViolationTypeTamper,
    BZCViolationTypeParking,
    BZCViolationTypeMotionCondition,
    BZCViolationTypeMagnetometer
};

BZCViolationType violationTypeForString(NSString *string);

/**
 *  BZCViolation objects represent a violation of a policy
 */
@interface BZCViolation : NSObject

/**
 *  The identifier of this violation
 */
@property (nonatomic, readonly) NSNumber *identifier;

/**
 *  The project identifier for this violaiton
 */
@property (nonatomic, readonly) NSNumber *projectIdentifier;

/**
 *  The policy identifier for this violation
 */
@property (nonatomic, readonly) NSNumber *policyIdentifier;

/**
 *  The policy name of this identifier
 */
@property (nonatomic, readonly) NSString *policyName;

/**
 *  The type namespace for this violation
 */
@property (nonatomic, readonly, nullable) NSString *typeNamespace;

/**
 *  The type of violation
 */
@property (nonatomic, readonly) BZCViolationType type;

/**
 *  The Blufi identifier for this violation
 */
@property (nonatomic, readonly, nullable) NSString *blufiIdentifier;

/**
 *  The Blufi name for this violation
 */
@property (nonatomic, readonly, nullable) NSString *blufiName;

/**
 *  The Beacon identifier for this violation
 */
@property (nonatomic, readonly, nullable) NSString *beaconIdentifier;

/**
 *  The Beacon name for this violation
 */
@property (nonatomic, readonly, nullable) NSString *beaconName;

/**
 *  The Policy Event identifier for this violation
 */
@property (nonatomic, readonly, nullable) NSNumber *policyEventIdentifier;

/**
 *  The Value of this violation
 */
@property (nonatomic, readonly, nullable) NSString *value;

/**
 *  A URL for the device selfie that is in violation
 */
@property (nonatomic, readonly, nullable) NSURL *selfieURL;

/**
 *  The date this violation was created
 */
@property (nonatomic, readonly) NSDate *dateCreated;

@end

NS_ASSUME_NONNULL_END
