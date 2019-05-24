//
//  BZCLocation.h
//  Bluzone
//
//  Copyright © 2015 Bluvision. All rights reserved.
//

@import UIKit;
@import CoreLocation;

@class BZCDevice;
@class BZCBluFi;
@class BZCBeacon;
@class BZCRealTimeLocation;

#import "BZCCalibration.h"

NS_ASSUME_NONNULL_BEGIN

/**
 *  BZCLocation object represents areas on maps where devices are provisoned
 */
@interface BZCLocation : NSObject

/**
 *  The identifier of this location
 */
@property (nonatomic, readonly) NSNumber *identifier;

/**
 *  The project identifier of this location
 */
@property (nonatomic, readonly) NSNumber *projectIdentifier;

/**
 *  The name of this location
 */
@property (nonatomic, readonly) NSString *name;

/**
 *  The description of this location
 */
@property (nonatomic, readonly, nullable) NSString *locationDescription;

/**
 *  The address of this location
 */
@property (nonatomic, readonly, nullable) NSString *address;

/**
 *  the floor number of this location
 */
@property (nonatomic, readonly, nullable) NSNumber *floorNumber;

/**
 *  The date this location was created
 */
@property (nonatomic, readonly, nullable) NSDate *dateCreated;

/**
 *  The date this location was last modified
 */
@property (nonatomic, readonly, nullable) NSDate *dateModified;

/** @name 3rd party map integration **/

/**
 *  The map provider type of this location
 */
@property (nonatomic, readonly) NSString *mapProviderType;

/**
 *  The map provider map identifier for this location (used for 3rd party map integration)
 */
@property (nonatomic, readonly, nullable) NSString *mapProviderMapIdentifier;

/**
 *  the map provider bluding apirport identifier (used for 3rd party map integration)
 */
@property (nonatomic, readonly, nullable) NSString *mapProviderAirportIdentifier;

/**
 *  the map provider builder identifier (used for 3rd party map integration)
 */
@property (nonatomic, readonly, nullable) NSString *mapProviderBuildingIdentifier;

/**
 *  the map provider api key (used for 3rd party map integration)
 */
@property (nonatomic, readonly, nullable) NSString *mapProviderAPIKey;

/** @name Map Overlays **/

/**
 *  The map overlay file name
 */
@property (nonatomic, readonly, nullable) NSString *overlayFileName;

/**
 *  The map overlay file extension
 */
@property (nonatomic, readonly, nullable) NSString *overlayFileExtension;

/**
 *  The map overlay file URL
 */
@property (nonatomic, readonly, nullable) NSURL *overlayFileURL;

/**
 *  The south west coordinate of the map overlay
 */
@property (nonatomic, readonly) CLLocationCoordinate2D overlaySouthWestCoordinate;

/**
 *  The north east coordinate of the map overlay
 */
@property (nonatomic, readonly) CLLocationCoordinate2D overlayNorthEastCoordinate;

/**
 *  The center coordinate of the map overlay
 */
@property (nonatomic, readonly) CLLocationCoordinate2D overlayCenterCoordinate;

/**
 *  The bounds of the overlay as a parsable string
 */
@property (nonatomic, readonly, nullable) NSString *overlayBounds;

/**
 *  The bearing of the overlay
 */
@property (nonatomic, readonly) CLLocationDirection overlayBearing;

/**
 *  An opacity for the overlay image
 */
@property (nonatomic, readonly) CGFloat overlayOpacity;

/**
 *  Downloads and caches the overlay Image for this location
 *
 *  @param completion a completion block executed once the image is fetched
 */
- (void)overlayImageWithCompletion:(nullable void (^)(id _Nullable overlayImage, NSError * _Nullable error))completion;

/** @name Devices for a location **/

/**
 *  List all the devices provisioned for this location
 *
 *  @param completion a completion block executed once the devices have been listed
 */
- (void)allDevicesWithCompletion:(nullable void (^)(NSArray <BZCDevice *> * _Nullable devices, NSError * _Nullable error))completion;

/**
 *  List all blufis provisioned for this location
 *
 *  @param completion a completion block executed once the Blufis have been listed
 */
- (void)allBluFisWithCompletion:(nullable void (^)(NSArray <BZCBluFi *> * _Nullable blufis, NSError * _Nullable error))completion;

/**
 *  List all beacons provisioned for this location
 *
 *  @param completion a completion block executed once the Beacons have been listed
 */
- (void)allBeaconsWithCompletion:(nullable void (^)(NSArray <BZCBeacon *> * _Nullable beacons, NSError * _Nullable error))completion;

/**
 *  List all preprovisioned devices for this location
 *
 *  @param compleiton a completion block executed once the preprovisioned devices have been listed
 */
- (void)preprovisionedDevicesWithCompletion:(nullable void (^)(NSArray <BZCDevice *> * _Nullable preprovisionedDevices, NSError * _Nullable error))completion;

/**
 *  Refreshes the properties of a location
 *
 *  @param completion a completion block executed once the location is refreshed
 */
- (void)refreshWithCompletion:(nullable void (^)(BOOL success, NSError * _Nullable error))completion;

/** @name RTLS **/

/**
 *  Create a Calibration object to be used in RTLS calibration for this location
 *
 *  @param type              The type of calibration to be done
 *  @param mode              The mode of calibration
 *  @param deviceIdentifiers An array of device identifiers to be used during calibration
 *
 *  @return returns a newly allocated calibration object for RTLS Calibration
 */
- (BZCCalibration *)calibrationWithType:(BZCCalibrationType)type mode:(BZCCalibrationMode)mode beaconGroup:(BZCCalibrationBeaconGroup *)beaconGroup;

/**
 * The Real Time location of a specific beacon parcitipacting in RTLS, this can be polled on in order to get RTLS updates.
 *
 *  @param beacon     The beacon that you want to track.
 *  @param compleiton A completion block to be executed when a real time location is recieved.
 */
- (void)realtimeLocationForBeacon:(BZCBeacon *)beacon completion:(void (^)(BZCRealTimeLocation *realtimeLocation, NSError *error))completion;

@end

NS_ASSUME_NONNULL_END
