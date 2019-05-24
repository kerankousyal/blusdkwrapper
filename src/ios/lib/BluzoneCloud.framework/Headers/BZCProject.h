//
//  BZCProject.h
//  Bluzone
//
//  Copyright © 2015 Bluvision. All rights reserved.
//

@import Foundation;
@class BLUConfigurableBeacon;

@class BZCRemoteConditionMonitor;
@class BZCDevice;
@class BZCBeacon;
@class BZCBluFi;
@class BZCBeaconTemplateConfiguration;
@class BZCIBeaconTemplateConfiguration;
@class BZCViolation;
@class BZCDashboard;
@class BZCPolicy;
@class BZCLocation;
@class BZCPage;
@class BZCServerFilters;

@import CoreLocation;

#import "BZCTemplate.h"

NS_ASSUME_NONNULL_BEGIN

FOUNDATION_EXPORT NSString *const BZCProjectCurrentProjectDidChangeNotification;

/**
 *  Represents a project in Bluzone
 */
@interface BZCProject : NSObject <NSSecureCoding>

/**
 *  The identifier of the project
 */
@property (nonatomic, readonly) NSString *identifier;

/**
 *  The Name of the project
 */
@property (nonatomic, readonly) NSString *name;

/**
 *  The Description of the project
 */
@property (nonatomic, readonly) NSString *projectDescription;

/**
 *  The default iBeacon UUID
 */
@property (nonatomic, readonly) NSUUID *defaultUUID;

/**
 *  a boolean to indicate that locus labs maps are enabled for this project
 */
@property (nonatomic, readonly, getter=isLocusLabsMapsEnabled) BOOL locusLabMapsEnabled;

/**
 *  The map provider API key (@see locusLabsMapsEnabled)
 */
@property (nonatomic, readonly, nullable) NSString *mapProviderAPIKey;

@property (nonatomic, readonly, nullable) NSString *mapProviderType;

/**
 *  The project owner's username
 */
@property (nonatomic, readonly) NSString *ownersUsername;

/**
 *  The date this project was created
 */
@property (nonatomic, readonly) NSDate *dateCreated;

/**
 *  The date this project was last modified
 */
@property (nonatomic, readonly) NSDate *dateModified;

/**
 *  Sets this project as the users current project
 *
 *  @param completion a completion block executed when the project gets set
 */
- (void)setAsProjectWithCompletion:(nullable void (^)(BOOL success, NSError * _Nullable error))completion;

/**
 *  Lists all the devices this project has provisioned
 *
 *  @param completion a compleiton block executed when all the devices have been returned
 */
- (void)allDevicesWithCompletion:(nullable void (^)(NSArray <BZCDevice *> * _Nullable devices, NSError * _Nullable error))completion;

/**
 *  List all the Blufi's this project has provisioned
 *
 *  @param completion a completion block executed when all the Blufi's have been returned
 */
- (void)allBluFisWithCompletion:(nullable void (^)(NSArray <BZCBluFi *> * _Nullable blufis, NSError * _Nullable error))completion;
- (void)allBlufisForPage:(BZCPage *)page completion:(void (^)(NSArray <BZCBluFi *> *blufis, NSNumber *count, NSError *error))completion;
- (void)allBlufisForPage:(BZCPage *)page filters:(nullable BZCServerFilters *)filters completion:(void (^)(NSArray <BZCBluFi *> *blufis, NSNumber *count, NSError *error))completion;
/**
 *  Lists all the Beacons' this project has provisioned
 *
 *  @param completion a completion block executed when all the Beacon's have been returned
 */
- (void)allBeaconsWithCompletion:(nullable void (^)(NSArray <BZCBeacon *> * _Nullable beacons, NSError * _Nullable error))completion;
- (void)allBeaconsForPage:(BZCPage *)page completion:(void (^)(NSArray <BZCBeacon *> *beacons, NSNumber *count, NSError *error))completion;
- (void)allBeaconsForPage:(BZCPage *)page filters:(nullable BZCServerFilters *)filters completion:(void (^)(NSArray <BZCBeacon *> *beacons, NSNumber *count, NSError *error))completion;
/**
 *  Lists all the Templates that this project has
 *
 *  @param completion a completion block executed when all the Templates have been returned
 */
- (void)allTemplatesWithCompletion:(nullable void (^)(NSArray <BZCTemplate *> * _Nullable templates, NSError * _Nullable error))completion;

/**
 *  Lists all the Locations in this project
 *
 *  @param completion a completion block executed when all the Locations have been retruned
 */
- (void)locationsWithCompletion:(nullable void (^)(NSArray <BZCLocation *> * _Nullable locations, NSError * _Nullable error))completion;
- (void)createLocationWithName:(NSString *)name description:(NSString *)description centerCoordinate:(CLLocationCoordinate2D)center northEastCoordinate:(CLLocationCoordinate2D)northEast southWestCoordinate:(CLLocationCoordinate2D)southWest completion:(void (^)(BZCLocation *location, NSError *error))completion;
/**
 *  Lists all the projects the Current User can access
 *
 *  @param compleiton a completion block executed when all the Projects have been retruned
 */
+ (void)projectsWithCompletion:(nullable void (^)(NSArray <BZCProject *> * _Nullable project, NSError * _Nullable error))compleiton;

/**
 *  Creates A new Project
 *
 *  @param name                 The name of the project
 *  @param description          The description of the project
 *  @param defaultProximityUUID The default Proximity UUID for iBeacons
 *  @param setAsCurrentProject  a boolean in order to set the newly created project as your current project
 *  @param completion           a completion block executed once the project has been created
 */
+ (void)createProjectWithName:(NSString *)name description:(NSString *)description defaultProximityUUID:(NSUUID *)defaultProximityUUID setAsCurrentProject:(BOOL)setAsCurrentProject completion:(nullable void (^)(BZCProject * _Nullable project, NSError * _Nullable error))completion;

/**
 *  Updated a Project
 *
 *  @param name                 The project's new name
 *  @param description          The project's new description
 *  @param defaultProximityUUID The project's new default UUID for iBeacons
 *  @param completion           a completion block executed once the project has been updated
 */
- (void)updateProjectWithName:(NSString *)name description:(NSString *)description defaultProximityUUID:(NSUUID *)defaultProximityUUID completion:(nullable void (^)(BZCProject * _Nullable project, NSError * _Nullable error))completion;

/**
 *  A light weight dashboard representing high level data for this project
 *
 *  @param completion a completion block executed once the dashboard has been returned
 */
- (void)beaconDashboardWithCompletion:(nullable void (^)(BZCDashboard * _Nullable dashboard, NSError * _Nullable error))completion;

/**
 *  List all the beacon violations this project has
 *
 *  @param completion a compleiton block executed once the violations have been returned
 */
- (void)violationsWithCompletion:(nullable void (^)(NSArray <BZCViolation *> * _Nullable violations, NSError * _Nullable error))completion;

/**
 *  Prepars a BLUConfigurableBeacon for use with Remote Condition Monitoring
 *
 *  @param configurableBeacon the Beacon to be used for remote condition monitoring
 *
 *  @return a newly allocated remote condition monitor @see BZCRemoteConditionMonitor
 */
- (BZCRemoteConditionMonitor *)remoteConditionMonitorForConfigurableBeacon:(BLUConfigurableBeacon *)configurableBeacon;

/**
 *  List all the policies for this project
 *
 *  @param completion a completion block executed once the policies have been returned.
 */
- (void)policiesWithCompletion:(nullable void (^)(NSArray <BZCPolicy *> * _Nullable policies, NSError * _Nullable error))completion;

- (void)allFullRepresentedBeaconsWithCompletion:(void (^)(NSArray <BZCBeacon *> * _Nullable beacons, NSError * _Nullable error))completion;

@end

NS_ASSUME_NONNULL_END
