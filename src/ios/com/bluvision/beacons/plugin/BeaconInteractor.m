//
//  BeaconInteractor.m
//  BluPro
//

#import "BeaconInteractor.h"

#import <Bluvision/BLUBeaconManager+Private.h>

@interface BZCClient ()

- (void)enableNetworkLogging;

@end

@interface BeaconInteractor()<BLUBeaconManagerDelegate, BZCProvisionerDelegate>

@property (nonatomic, strong) BZCProvisioner *provisioner;
@property (nonatomic, strong) NSMutableDictionary *beaconList;
@property (nonatomic, strong) NSMutableDictionary *templateList;
@property (nonatomic, strong) BLUBeaconManager *beaconManager;
@property (nonatomic, strong) BZCDevice *provisionedDevice;
@property (nonatomic, weak) id<BeaconInteractorDelegate> delegate;

@end

@implementation BeaconInteractor

BOOL scanning = false;

- (id)initWithDelegate:(id <BeaconInteractorDelegate>)delegate {

    if (self = [super init])
    {
        self.delegate = delegate;
        self.beaconList = [[NSMutableDictionary alloc] init];
        self.beaconManager = [[BLUBeaconManager alloc] initWithDelegate:self];
    }
    return self;
}

- (void)signIn:(NSString *)token device:(NSString *)deviceType {

    scanning = false;
    [[BZCClient client] enableNetworkLogging];

    [BZCUser authenticateWithAPIToken:token completion:^(BZCUser * _Nullable user, NSError * _Nullable error) {
        if (error == nil && user != nil) {
            [self.delegate signInSuccess:user];
            [self startScan:deviceType];
        } else {
            [self.delegate signInFailure:error];
        }
    }];
}

- (void)startScan:(NSString *)deviceType {

    if (self.beaconManager != nil && scanning == false) {
        scanning = true;
        if ([deviceType isEqualToString:@"SBeacon"]) {
            [self.beaconManager startScanningForBeacons];
        } else {
            [self.beaconManager startScanningForBluFis];
        }
    }
}

- (void)stopScan {

    if (self.beaconManager != nil && scanning == true) {
        [self.beaconManager stopScanning];
        scanning = false;
    }
}

- (void)loadTemplates:(NSString *)beacondentifier {

    if (self.provisioner != nil) {
        self.provisioner = nil;
    }

    void (^completion)(NSArray *templates, NSError *error) = ^(NSArray *templates, NSError *error) {
        if (error) {
            if (error.code >= 50000) {
                if (error.code == 50404) {
                    NSString *error = @"This transmitter is already provisioned for use with another project";
                    [self.delegate loadTemplateError:error];
                } else {
                    NSString *error = @"This device cannot be provisioned, Please contact support for assistance";
                    [self.delegate loadTemplateError:error];
                }
            }
            else {
                [self.delegate loadTemplateError:error.localizedDescription];
            }
        } else {
            for (BZCTemplate *template in templates) {
                [self.templateList setObject:template forKey:template.identifier.stringValue];
            }
            [self.delegate loadTemplateSucess:templates];
        }
    };

    BLUSBeacon *configurableBeacon = [self.beaconList objectForKey:beacondentifier];
    self.provisioner = [[BZCProvisioner alloc] initWithConfigurableBeacon:configurableBeacon];

    switch (deviceTypeFromString(self.provisioner.deviceType)) {
        case BZCDeviceTypeBeacon:
            [BZCTemplate beaconTemplatesForDeviceIdentifier:self.provisioner.configurableBeacon.identifier completion:completion];
            break;
        case BZCDeviceTypeBluFi:
            [BZCTemplate blufiTemplatesWithCompletion:completion];
            break;
        default:
            break;
    }
}

- (void)provisionBeaconForTemplate:(int)templateId beaconName:(NSString *)name notes:(NSString *)notes {

    if (self.provisioner != nil) {

        self.provisioner.templateIdentifier = [NSNumber numberWithInt:templateId];
        self.provisioner.deviceFriendlyName = name;
        self.provisioner.notes = notes;
        [self getLocations];
    }
}

- (void)getLocations {

    [[[BZCUser currentUser] currentProject] locationsWithCompletion:^(NSArray<BZCLocation *> * _Nullable locations, NSError * _Nullable error) {
        if (locations.count == 0) {
            NSLog(@"Locations are needed for this example, locations can be auto generated if there are none but require a geo location that is not (0,0). "
                  "Please create a location on your cloud or supply a geo location to the provisioner object in prepareForSegue:");
        }

        if (locations != nil && locations.count > 0) {
            BZCLocation *location = locations[0];
            self.provisioner.location = location;
            self.provisioner.geolocation = [[CLLocation alloc] initWithCoordinate:location.overlayCenterCoordinate altitude:0 horizontalAccuracy:0 verticalAccuracy:0 timestamp:[NSDate date]];
            [self provisionBeacon];
        }
    }];
}

- (void)provisionBeacon {

    self.provisioner.delegate = self;

    [self.provisioner startProvisioningWithCompletion:^(BZCDevice * _Nullable device, NSError * _Nullable error) {

        if (error) {

            NSLog(@"%@", error.localizedDescription);
            [self.delegate provisionError:error.localizedDescription];
            return;
        }
        self.provisionedDevice = device;
        [self.delegate provisionSuccess];
    } recoverableConnectionFailureBlock:^BOOL(NSError * _Nullable error) {
        if (error.code == 5022) {

            [self.delegate provisionError:error.localizedDescription];
        }
        return NO;
    }];

}

#pragma mark BLUBeaconManagerDelegate

- (void)beaconManager:(BLUBeaconManager *)manager didFindBeacon:(BLUBeacon *)beacon {

    if (beacon != nil && [beacon isKindOfClass:[BLUSBeacon class]]) {

        BLUSBeacon *device = (BLUSBeacon *)beacon;
        [self.beaconList setObject:device forKey:device.identifier.stringValue];
        [self.delegate beaconFound:device];
    }
}

- (void)beaconManager:(BLUBeaconManager *)manager didLoseBeacon:(BLUBeacon *)beacon {

    if (beacon != nil && [beacon isKindOfClass:[BLUSBeacon class]]) {

        BLUSBeacon *device = (BLUSBeacon *)beacon;
        [self.beaconList removeObjectForKey:device.identifier.stringValue];
        [self.delegate beaconLost:device];
    }
}

- (void)beaconManager:(BLUBeaconManager *)manager didFailWithError:(nullable NSError *)error {

    NSLog(@"Error = %@", error.localizedDescription);
}

#pragma mark - provisioner delegate

- (void)provisioner:(BZCProvisioner *)provisioner didChangeStatus:(NSString *)status {

    [self.delegate provisionStatusChange:status];
}

- (void)provisioner:(BZCProvisioner *)provisioner didChangeDescription:(NSString *)description {

    [self.delegate provisionDescriptionChange:description];
}

- (void)provisioner:(nonnull BZCProvisioner *)provisioner willRetryProvisioningWithError:(nonnull NSError *)error {

    NSLog(@"%@", error.localizedDescription);
}


@end
