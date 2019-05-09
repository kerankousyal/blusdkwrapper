//
//  BZCAccelerometerReadConfiguration.h
//  Bluzone
//
//  Created by Jason Clary on 4/7/16.
//  Copyright © 2016 Bluvision. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "BZCDeviceJobConfiguration.h"

@interface BZCAccelerometerReadConfiguration : NSObject <BZCDeviceJobConfiguration>

@property (nonatomic, strong) NSNumber *rateIndex;
@property (nonatomic, strong) NSNumber *durationInMilliseconds;
@property (nonatomic, assign, getter=requiresMovememnt) BOOL requireMovement;

@end
