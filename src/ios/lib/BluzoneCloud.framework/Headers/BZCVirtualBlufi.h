//
//  BZCVirtualBlufi.h
//  BluzoneCloud
//
//  Created by Jason Clary on 8/27/18.
//  Copyright © 2018 Bluvision. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "BZCDevice.h"

@class BZCPage;
@class BZCServerFilters;
@class BZCLocation;
@class BZCTemplate;
@class BZCBluFi;
@import CoreLocation;

NS_ASSUME_NONNULL_BEGIN
@interface BZCVirtualBlufi : BZCDevice;

@property (nonatomic, strong) BZCTemplate *blufiTemplate;

+ (void)virtualBlufisForLocation:(BZCLocation *)location completion:(nullable void (^)(NSArray <BZCVirtualBlufi *> * _Nullable virtualBlufis, NSError * _Nullable error))completion;

- (void)bindBlufi:(NSNumber *)blufiSid64 completion:(void (^)(BZCBluFi *blufi, NSError *error))completion;

@end

NS_ASSUME_NONNULL_END
