//
//  BLUContentManager.h
//  Bluvision
//
//  Created by Jason Clary on 4/11/16.
//  Copyright © 2016 BluVision. All rights reserved.
//

#import <UIKit/UIKit.h>

@class BLUContentManager;
@class BLUEvent;

FOUNDATION_EXPORT NSString * const kBLUContentManagerLocalNotificationScheduled;

@protocol BLUContentManagerDelegate <NSObject>

- (void)contentManagerDidStartMonitoringBeacons:(BLUContentManager *)manager;
- (void)contentManager:(BLUContentManager *)manager didFailWithError:(NSError *)error;
- (void)contentManager:(BLUContentManager *)manager didRecieveEvent:(BLUEvent *)event;

@optional
- (BOOL)contentManager:(BLUContentManager *)manager shouldDisplayAlertForNotification:(NSDictionary *)notification;

@end

@interface BLUContentManager : NSObject

@property (nonatomic, readonly) NSString *APIKey;
@property (nonatomic, readonly) NSString *APISecret;
@property (nonatomic, readonly) NSString *projectIdentifier;
@property (nonatomic, readonly) NSURL *offersURL;
@property (nonatomic, weak) id<BLUContentManagerDelegate> delegate;
@property (nonatomic, assign) BOOL disableNotificiations;

+ (void)managerWithInviteToken:(NSString *)inviteToken completion:(void (^)(BLUContentManager *mananger, NSError *error))completion;

- (instancetype)initWithKey:(NSString *)key secret:(NSString *)secret projectIdentifier:(NSString *)projectIdentifer;


#pragma mark - Notifications
- (void)registerForRemoteNotificationsWithDeviceToken:(NSData *)deviceToken completion:(void (^)(BOOL success, NSError *error))completion;

- (BOOL)isBluzoneNotification:(UILocalNotification *)notification;
- (BOOL)isBluzoneRemoteNotification:(NSDictionary *)userInfo;

- (void)application:(UIApplication *)application didRecieveNotification:(NSDictionary *)userInfo;
- (void)application:(UIApplication *)aplication didRecieveLocalNotification:(UILocalNotification *)notification;

#pragma mark - Beacon Scanning

- (void)startBeaconMonitoring;
- (void)stopBeaconMonitoring;

@end
