//
//  BZCSBeaconTemplateConfiguration.h
//  Bluzone
//
//  Copyright © 2015 Bluvision. All rights reserved.
//

@import Foundation;

NS_ASSUME_NONNULL_BEGIN

/**
 *  BZCBeaconTemplateConfiguration objects represents common settings for configurations of different types of broadcasts
 */
@interface BZCBeaconTemplateConfiguration : NSObject

@property (nonatomic, assign, getter=isEnabled) BOOL enabled;
/**
 *  The interval for the broadcast
 */
@property (nonatomic, strong) NSNumber *interval;

/**
 *  The transmission power for the boradcast
 */
@property (nonatomic, strong) NSNumber *transmissionPower;

@property (nonatomic, strong) NSString *type;

/**
 *  A dictionary representation of the configuration
 *
 *  @return a dictionary representation of this configuration
 */
- (NSDictionary *)dictionaryRepresentation;

- (instancetype)initWithType:(NSString *)type dictionary:(nullable NSDictionary *)dictionary;

+ (BZCBeaconTemplateConfiguration *)defaultConfiguration;

@end

NS_ASSUME_NONNULL_END