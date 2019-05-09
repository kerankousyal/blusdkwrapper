//
//  BZCEventAnalyticsSession.h
//  BluzoneCloud
//
//  Created by Jason Clary on 11/13/17.
//  Copyright © 2017 Bluvision. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface BZCEventAnalyticsSession : NSObject

@property (nonatomic, strong) NSNumber *sessionId;
@property (nonatomic, strong) NSNumber *projectId;
@property (nonatomic, strong) NSString *beaconId;
@property (nonatomic, strong) NSNumber *eventId;
@property (nonatomic, readwrite, getter=isActive) BOOL active;
@property (nonatomic, strong) NSDate *startTime;
@property (nonatomic, strong) NSDate *endTime;
@property (nonatomic, strong) NSDate *dateCreated;
@property (nonatomic, strong) NSDate *dateUpdated;

- (instancetype)initWithDictionary:(NSDictionary *)dictionary;

@end
