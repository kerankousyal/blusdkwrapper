//
//  BZCCalibrationBeaconEntry.h
//  Bluzone
//
//  Copyright © 2015 Bluvision. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface BZCCalibrationBeaconEntry : NSObject

@property (nonatomic, readonly) NSString *identifier;
@property (nonatomic, readonly) NSString *calibrationPointIdentifier;
@property (nonatomic, readonly) NSString *deviceIdentifier;
@property (nonatomic, readonly) NSArray *stats;
@property (nonatomic, readonly) NSDate *createDate;
@property (nonatomic, readonly) NSDate *modifiedDate;

- (instancetype)initWithDictionary:(NSDictionary *)dictionary;

@end
