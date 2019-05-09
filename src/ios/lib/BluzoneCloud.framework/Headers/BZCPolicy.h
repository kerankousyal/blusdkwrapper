//
//  BZCPolicy.h
//  Bluzone
//
//  Copyright © 2015 Bluvision. All rights reserved.
//

@import Foundation;

#import "BZCViolation.h"

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, BZCPolicyOperatorType) {
    BZCPolicyOperatorTypeEquals,
    BZCPolicyOperatorTypeGraterThen,
    BZCPolicyOperatorTypeGraterThenOrEquals,
    BZCPolicyOperatorTypeLessThen,
    BZCPolicyOperatorTypeLessThenOrEquals
};

/**
 *  BZCPolicy objects represent a Policy for devices to comply with
 */
@interface BZCPolicy : NSObject

/**
 *  The identifier of this policy
 */
@property (nonatomic, readonly) NSNumber *identifier;

/**
 *  The project identifier for this policy
 */
@property (nonatomic, readonly) NSNumber *projectIdentifier;

/**
 *  The location identifier for this policy
 */
@property (nonatomic, readonly) NSNumber *locationIdentifier;

/**
 *  A boolean property enabled if the policy is scoped globally
 */
@property (nonatomic, readonly, getter=isGolbalScoped) BOOL globalScoped;

/**
 *  The name of this policy
 */
@property (nonatomic, readonly) NSString *name;

/**
 *  The description of this policy
 */
@property (nonatomic, readonly, nullable) NSString *policyDescription;

/**
 *  The type namespace of this policy
 */
@property (nonatomic, readonly, nullable) NSString *typeNamespace;

/**
 *  The violation type of this policy
 */
@property (nonatomic, readonly) BZCViolationType type;

/**
 *  The operator type of this policy
 */
@property (nonatomic, readonly) BZCPolicyOperatorType operatorType;

/**
 *  The minimum duration for a violation to happen for this policy
 */
@property (nonatomic, readonly, nullable) NSNumber *duration;

/**
 *  The sample interval for this policy
 */
@property (nonatomic, readonly, nullable) NSNumber *sampleInterval;

/**
 *  The threshold for this policy
 */
@property (nonatomic, readonly, nullable) NSNumber *threshold;

/**
 *  The threshold hystersis for this policy
 */
@property (nonatomic, readonly, nullable) NSNumber *thresholdHysteresis;

/**
 *  The range of the threashold for this policy
 */
@property (nonatomic, readonly, nullable) NSArray <NSNumber *> *thresholdRange;

/**
 *  The period for this policy
 */
@property (nonatomic, readonly, nullable) NSNumber *period;

/**
 *  An array of email addresses this policy should send an email to when a violation happens
 */
@property (nonatomic, readonly, nullable) NSArray <NSString *> *emailAddresses;

/**
 *  The date this policy was create
 */
@property (nonatomic, readonly) NSDate *dateCreated;

/**
 *  The date this policy was modified
 */
@property (nonatomic, readonly) NSDate *dateUpdated;

@end

NS_ASSUME_NONNULL_END
