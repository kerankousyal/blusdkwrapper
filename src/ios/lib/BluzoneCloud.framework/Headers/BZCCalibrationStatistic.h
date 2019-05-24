//
//  BZCCalibrationStatistic.h
//  Bluzone
//
//  Copyright © 2015 Bluvision. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface BZCCalibrationStatistic : NSObject

@property (nonatomic, readonly) NSString *identifier;
@property (nonatomic, readonly) NSString *pointIdentifier;
@property (nonatomic, readonly) NSNumber *blufiIdentifier;
@property (nonatomic, readonly) NSNumber *sampleCount;
@property (nonatomic, readonly) NSNumber *averageRSSI;

@end
