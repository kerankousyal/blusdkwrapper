//
//  BZCFirmware.h
//  Bluzone
//
//  Copyright © 2015 Bluvision. All rights reserved.
//

@import Foundation;

NS_ASSUME_NONNULL_BEGIN

/**
 *  BZCFirmware objects describe the properties of the firmware install on a device
 */
@interface BZCFirmware : NSObject <NSSecureCoding>

/**
 *  The Identifier of this firmware
 */
@property (nonatomic, readonly) NSString *identifier;

/**
 *  The Type of this firmware
 */
@property (nonatomic, readonly) NSString *type;

/**
 *  The firmware version number
 */
@property (nonatomic, readonly) NSNumber *version;

@end

NS_ASSUME_NONNULL_END
