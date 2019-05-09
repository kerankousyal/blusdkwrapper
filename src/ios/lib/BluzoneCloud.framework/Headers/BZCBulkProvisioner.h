//
//  BZCBulkProvisioner.h
//  Bluzone
//
//  Created by Jason Clary on 7/12/17.
//  Copyright © 2017 Bluvision. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN
/**
 BZCBulkProvisioner objects are responsible for provisioning multiple beacons at the same time.
 This kicks off provisioning jobs to blufis to be done when ever the beacon comes in range.
 */
@interface BZCBulkProvisioner : NSObject

/**
 The identifiers of the beacons to be provisioned.
 */
@property (nonatomic, copy) NSArray <NSNumber *> *identifiers;

/**
 The template identifier to be applied to these beacons.
 */
@property (nonatomic, copy) NSNumber *templateIdentifier;

/**
 The location identifier of the location that these beacons should be provisioned to
 */
@property (nonatomic, copy) NSNumber *locationIdentifier;

/**
 a name to append a sequencial number to e.g. MyBeacon 1, MyBeacon 2.
 */
@property (nonatomic, copy) NSString *baseName;

/**
 Starts the provisioning process

 @param completion a completion block to be executed once provisioning has stated.
 */
- (void)provisionWithCompletion:(nullable void (^)(BOOL success,  NSError * _Nullable error))completion;

@end

NS_ASSUME_NONNULL_END
