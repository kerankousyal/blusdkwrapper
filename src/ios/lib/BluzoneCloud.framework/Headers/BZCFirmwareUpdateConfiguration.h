//
//  BZCFirmwareUpdateConfiguration.h
//  Bluzone
//
//  Created by Jason Clary on 4/7/16.
//  Copyright © 2016 Bluvision. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "BZCDeviceJobConfiguration.h"

@interface BZCFirmwareUpdateConfiguration : NSObject <BZCDeviceJobConfiguration>

@property (nonatomic, assign, getter=isLegacy) BOOL legacy;
@property (nonatomic, assign, getter=isDataLog) BOOL dataLog;
@property (nonatomic, assign, getter=isLoader) BOOL loader;
@property (nonatomic, assign) BOOL noManufacturer;
@property (nonatomic, assign) BOOL allowsDowngrade;
@property (nonatomic, assign, getter=isForced) BOOL forced;

@end
