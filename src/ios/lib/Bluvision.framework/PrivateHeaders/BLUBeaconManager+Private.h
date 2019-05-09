//
//  BLUBeaconManager+Private.h
//
//  Copyright (c) 2015 Bluvision. All rights reserved.
//

#import <Bluvision/BLUBeaconManager.h>

@class BLUConfigurableBeacon;

@protocol BLUBeaconManagerDelegateInternal <BLUBeaconManagerDelegate>

- (void)beaconManager:(BLUBeaconManager *)manager didUpdateLocations:(NSArray<CLLocation *> *)locations;

@end

@interface BLUBeaconManager (Private)

@property (nonatomic, strong) CLLocationManager *locationManager;

- (void)connectBeacon:(BLUConfigurableBeacon *)beacon;
- (void)disconnectBeacon:(BLUConfigurableBeacon *)beacon;

- (void)startScanningForBluFis;

- (BOOL)isAbleToConnectToBeacon:(BLUConfigurableBeacon *)beacon;
@end
