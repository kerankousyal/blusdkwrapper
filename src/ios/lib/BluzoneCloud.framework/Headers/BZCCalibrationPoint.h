//
//  BZCCalibrationPoint.h
//  Bluzone
//
//  Copyright © 2015 Bluvision. All rights reserved.
//

@import Foundation;
@import CoreLocation;

#import "BZCCalibration.h"
#import "BZCCalibrationBeaconEntry.h"

@interface BZCCalibrationPoint : NSObject

@property (nonatomic, readonly) NSArray *pointIdentifiers;
@property (nonatomic, readonly) NSArray *channels;
@property (nonatomic, readonly) NSString *identifier;
@property (nonatomic, readonly) NSString *locationIdentifier;
@property (nonatomic, readonly) NSString *projectIdentifier;
@property (nonatomic, readonly) NSString *deviceIdentifier;
@property (nonatomic, readonly) CLLocationCoordinate2D coordinate;
@property (nonatomic, readonly) NSURL *storageURL;
@property (nonatomic, readonly) NSArray <BZCCalibrationBeaconEntry *> *statistics;
@property (nonatomic, readonly) NSString *status;
@property (nonatomic, readonly) NSDate *dateCreated;
@property (nonatomic, readonly) NSDate *dateModified;
@property (nonatomic, readonly) BZCCalibrationType type;
@property (nonatomic, readonly) BZCCalibrationMode mode;
@property (nonatomic, readonly) BZCCalibrationDirection direction;

- (void)stopWithCompletion:(void (^)(BOOL success, NSError *error))completion;
- (void)deleteWithCompletion:(void (^)(BOOL success, NSError *error))completion;

@end
