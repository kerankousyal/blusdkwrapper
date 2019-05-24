//
//  BZCEventAnalyticsEvent.h
//  BluzoneCloud
//
//  Created by Jason Clary on 11/13/17.
//  Copyright © 2017 Bluvision. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class BZCEventAnalyticsSession;

@interface BZCEventAnalyticsEvent : NSObject

@property (nonatomic, strong) NSNumber *eventId;
@property (nonatomic, strong) NSString *projectId;
@property (nonatomic, strong) NSString *name;
@property (nonatomic, strong) NSString *eventDescription;
@property (nonatomic, strong) NSString *address;
@property (nonatomic, readwrite, getter=isActive) BOOL active;
@property (nonatomic, strong) NSDate *startDate;
@property (nonatomic, strong) NSDate *endDate;
@property (nonatomic, strong) NSDate *dateCreated;
@property (nonatomic, strong) NSDate *dateUpdated;

- (instancetype)initWithDictionary:(NSDictionary *)dictionary;

+ (void)listEvents:(NSString *)projectId completion:(void(^)(NSArray <BZCEventAnalyticsEvent *> * _Nullable events, NSError * _Nullable error))completion;
+ (void)eventWithIdentifier:(NSNumber *)eventId projectId:(NSString *)projectId completion:(void (^)(BZCEventAnalyticsEvent * _Nullable, NSError * _Nullable))completion;

- (void)createSessionForBeaconId:(NSString *)beaconId completion:(void (^)(BZCEventAnalyticsSession * _Nullable, NSError * _Nullable))completion;
- (void)endSessionForBeaconId:(NSString *)beaconId completion:(void (^)(BOOL didEndSession, NSError * _Nullable error))completion;

@end

NS_ASSUME_NONNULL_END
