//
//  BZCMusteringZone.h
//  BluzoneCloud
//
//  Created by Jason Clary on 2/16/18.
//  Copyright © 2018 Bluvision. All rights reserved.
//

#import <Foundation/Foundation.h>

@class BZCProject;
@class BZCMusteringZone;

NS_ASSUME_NONNULL_BEGIN

@interface BZCMusteringZoneSumary : NSObject

@property (nonatomic, strong) NSNumber *zoneIdentifier;
@property (nonatomic, strong) NSNumber *count;

@end

@protocol BZCMustringZoneDelegate <NSObject>

- (void)musteringZone:(BZCMusteringZone *)musteringZone didUpdateCount:(NSNumber *)count;
- (void)musteringZone:(BZCMusteringZone *)musteringZone didFailWithError:(NSError *)error;
- (void)musteringZoneDidDisconnect:(BZCMusteringZone *)musteringZone;

@optional

- (void)musteringZone:(BZCMusteringZone *)musteringZone didUpdateSeenBeacons:(NSArray <NSNumber *> *)beacons;

@end

@interface BZCMusteringZone : NSObject <NSSecureCoding>

@property (nonatomic, strong) NSNumber *identfier;
@property (nonatomic, strong) NSString *name;
@property (nonatomic, strong, nullable) NSString *zoneDescription;
@property (nonatomic, strong) NSNumber *projectIdentifier;
@property (nonatomic, strong) NSDate *dateCreated;
@property (nonatomic, strong) NSDate *dateUpdated;

@property (nonatomic, weak) id <BZCMustringZoneDelegate> delegate;

+ (void)listZonesForProject:(BZCProject *)project completion:(void (^)(NSArray <BZCMusteringZone *> * _Nullable zones, NSError * _Nullable error))completion;
+ (void)createZoneForProject:(BZCProject *)project name:(NSString *)name description:(NSString * _Nullable )description completion:(void (^)(BZCMusteringZone * _Nullable zone, NSError * _Nullable error))completion;
+ (void)zoneSummaryForProject:(BZCProject *)project completion:(void(^)(NSArray <BZCMusteringZoneSumary *> * _Nullable summary, NSError * _Nullable error))completion;

- (void)deleteWithCompletion:(void (^)(BOOL success, NSError * _Nullable error))completion;

- (void)startMustering;
- (void)stopMustering;

@end

NS_ASSUME_NONNULL_END
