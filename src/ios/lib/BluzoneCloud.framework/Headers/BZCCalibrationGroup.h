//
//  BZCCalibrationGroup.h
//  Bluzone
//
//  Copyright © 2015 Bluvision. All rights reserved.
//

@import Foundation;
@import CoreLocation;

#import "BZCCalibration.h"

@interface BZCCalibrationGroup : NSObject

@property (nonatomic, strong) NSString *identifier;

@property (nonatomic, strong) NSArray *calibrationPoints;

@property (nonatomic, assign) BZCCalibrationType type;
@property (nonatomic, assign) BZCCalibrationMode mode;

@property (nonatomic, strong) CLLocation *location;

- (instancetype)initWithDictionary:(NSDictionary *)dictionary projectIdentifier:(NSNumber *)projectIdentifier;
- (void)deleteWithCompletion:(void (^)(BOOL success, NSError *error))completion;

@end
