//
//  BZCCalibration.h
//  Bluzone
//
//  Copyright © 2015 Bluvision. All rights reserved.
//

#import <Foundation/Foundation.h>

@import CoreLocation;
@class BZCCalibrationPoint;
@class BZCCalibrationGroup;

typedef NS_ENUM(NSUInteger, BZCCalibrationType) {
    BZCCalibrationTypeStandard,
    BZCCalibrationTypeOffset,
    BZCCalibrationTypeWalking
};

typedef NS_ENUM(NSUInteger, BZCCalibrationMode) {
    BZCCalibrationModeMetal,
    BZCCalibrationModeBox,
    BZCCalibrationModeHuman,
    BZCCalibrationModeAll
};

typedef NS_ENUM(NSUInteger, BZCCalibrationDirection) {
    BZCCalibrationDirectionNorth,
    BZCCalibrationDirectionEast,
    BZCCalibrationDirectionSouth,
    BZCCalibrationDirectionWest,
    BZCCalibrationDirectionRotating
};

NSString * stringForCalibrationDirection(BZCCalibrationDirection direction);
NSString * stringForCalibrationMode(BZCCalibrationMode mode);

@interface BZCCalibrationBeaconGroup : NSObject

@property (nonatomic, strong) NSString *northIdentifer;
@property (nonatomic, strong) NSString *southIdentifier;
@property (nonatomic, strong) NSString *eastIdentifier;
@property (nonatomic, strong) NSString *westIdentifier;

- (NSDictionary *)dictionaryRepresentation;

@end

@interface BZCCalibration : NSObject

@property (nonatomic, readonly) BZCCalibrationType type;
@property (nonatomic, readonly) BZCCalibrationMode mode;

@property (nonatomic, strong) NSString *offsetBlufiIdentifier;

- (void)allCalibrationPointsWithCompletion:(void (^)(NSArray *calibrationPoints, NSError *error))completion;
- (void)calibrationPointsForType:(BZCCalibrationType)type completion:(void (^)(NSArray *calibrationPoints, NSError *error))completion;

- (void)startWithLocation:(CLLocation *)location interval:(NSTimeInterval)interval direction:(BZCCalibrationDirection)direction group:(BZCCalibrationGroup *)group completion:(void (^)(BZCCalibrationPoint *calibrationPoint, NSError *error))completion;

- (void)completeCalibrationWithCompletion:(void (^)(BOOL success, NSError *error))completion;
- (void)resetWithCompletion:(void (^)(BOOL success, NSError *error))completion;

- (void)startInitialWalkingCalibrationWithLocation:(CLLocation *)location endLocation:(CLLocation *)endLocation completion:(void (^)(BZCCalibrationPoint *, NSError *))completion;
- (void)hasCompletedInitialWalkingCalibrationWithCompletion:(void (^)(BOOL hasCompletedInitalCalibration, NSError *error))completion;

- (void)referenceBeaconIdentifierWithCompletion:(void (^)(NSString *identifier, NSError *error))completion;

// Groups
- (void)createCalibrationGroupForType:(BZCCalibrationType)type location:(CLLocation *)location completion:(void (^)(BZCCalibrationGroup *, NSError *))completion;
- (void)allGroupsForType:(BZCCalibrationType)type completion:(void (^)(NSArray *groups, NSError *error))compleiton;

@end
 