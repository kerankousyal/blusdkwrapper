//
//  BLUEvent.h
//  Bluvision
//
//  Created by Jason Clary on 4/11/16.
//  Copyright © 2016 BluVision. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>

@interface BLUEvent : NSObject

@property (nonatomic, copy) NSNumber *minor;
@property (nonatomic, copy) NSString *uuid;
@property (nonatomic, copy) NSString *eventid;
@property (nonatomic, copy) NSString *contentid;
@property (nonatomic, copy) NSString *campaignid;
@property (nonatomic, copy) NSString *beaconid;
@property (nonatomic, copy) NSNumber *major;
@property (nonatomic, copy) NSNumber *rssiThreshold;
@property (nonatomic, copy) NSNumber *cloudmute;
@property (nonatomic) CLProximity proximity;
@property (nonatomic, copy) NSNumber *eventtype;
@property (nonatomic, copy) NSDate *time;
@property (nonatomic, copy) NSNumber *contentSent;
@property (nonatomic, copy) NSNumber *eventConfigInterval;
@property (nonatomic, copy) NSNumber *eventConfigProximity;
@property (nonatomic, copy) NSNumber *eventConfigDelay;
@property (nonatomic, copy) NSDictionary *eventContent;

@end
