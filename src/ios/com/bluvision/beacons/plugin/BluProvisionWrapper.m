/********* BluProvisionWrapper.m Cordova Plugin Implementation *******/

#import <Cordova/CDV.h>
#import <Bluvision/BLUBluFi.h>
#import "BeaconInteractor.h"

@interface BluProvisionWrapper : CDVPlugin <BeaconInteractorDelegate, CBCentralManagerDelegate> {
    BeaconInteractor *interactor;
    NSString *deviceType;
    CDVInvokedUrlCommand *locationCommand;
    CDVInvokedUrlCommand *bluCommand;
    CDVInvokedUrlCommand *scanCommand;
    CDVInvokedUrlCommand *connectioncommand;
    CDVInvokedUrlCommand *templateCommand;
}

@property (nonatomic, strong) CLLocationManager *locationManager;
@property (nonatomic, strong) CBCentralManager *bluManager;
@property (nonatomic, strong) NSTimer *timer;

- (void)bluetoothPermission:(CDVInvokedUrlCommand*)command;
- (void)locationPermission:(CDVInvokedUrlCommand*)command;
- (void)init:(CDVInvokedUrlCommand*)command;
- (void)signIn:(CDVInvokedUrlCommand*)command;
- (void)startScan:(CDVInvokedUrlCommand*)command;
- (void)stopScan:(CDVInvokedUrlCommand*)command;
- (void)getTemplate:(CDVInvokedUrlCommand*)command;
- (void)provision:(CDVInvokedUrlCommand*)command;

@end

@implementation BluProvisionWrapper

- (void)bluetoothPermission:(CDVInvokedUrlCommand*)command {

    bluCommand = command;
    [self blutoothPermission];
}

- (void)locationPermission:(CDVInvokedUrlCommand*)command {

    locationCommand = command;
    [self requestAlwaysAuth];
}

- (void)requestAlwaysAuth {

    CLAuthorizationStatus status = [CLLocationManager authorizationStatus];

    if (status == kCLAuthorizationStatusNotDetermined) {

        self.locationManager = [[CLLocationManager alloc] init];
        [self.locationManager requestWhenInUseAuthorization];
        self.timer = [NSTimer scheduledTimerWithTimeInterval:1.0
                                                      target:self
                                                    selector:@selector(checkStatus)
                                                    userInfo:nil repeats:YES];
    } else if (status == kCLAuthorizationStatusAuthorizedWhenInUse || status == kCLAuthorizationStatusAuthorizedAlways) {

        // send success
        NSMutableDictionary *dictionary = [[NSMutableDictionary alloc] init];
        [dictionary setValue:@"Location_Success" forKey:@"code"];
        CDVPluginResult* pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsDictionary: dictionary];
        [pluginResult setKeepCallbackAsBool:NO];
        [self.commandDelegate sendPluginResult:pluginResult callbackId:locationCommand.callbackId];
    } else if (status == kCLAuthorizationStatusDenied) {

        [self requestLocationPermissions];
    }
}

- (void)blutoothPermission {

    self.bluManager = [[CBCentralManager alloc] initWithDelegate:self queue:nil];
}

- (void)centralManagerDidUpdateState:(CBCentralManager *)central {

    if (self.bluManager.state == CBManagerStatePoweredOn) {

        NSMutableDictionary *dictionary = [[NSMutableDictionary alloc] init];
        [dictionary setValue:@"Blutooth_Success" forKey:@"code"];
        CDVPluginResult* pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsDictionary: dictionary];
        [pluginResult setKeepCallbackAsBool:NO];
        [self.commandDelegate sendPluginResult:pluginResult callbackId:bluCommand.callbackId];
    } else {

        NSString *stateString = @"";
        if (self.bluManager.state == CBCentralManagerStateResetting) {
            stateString = @"The connection with the system service was momentarily lost, update imminent.";
        } else if (self.bluManager.state == CBCentralManagerStateUnsupported) {
            stateString = @"The platform doesn't support Bluetooth Low Energy.";
        } else if (self.bluManager.state == CBCentralManagerStateUnauthorized) {
            stateString = @"The app is not authorized to use Bluetooth Low Energy.";
        } else if (self.bluManager.state == CBCentralManagerStatePoweredOff) {
            stateString = @"Bluetooth is currently powered off.";
        } else if (self.bluManager.state == CBManagerStateUnknown) {
            stateString = @"State unknown, update imminent.";
        }
        [self enableBluetooth:stateString];
    }
}

- (void)checkStatus {

    CLAuthorizationStatus status = [CLLocationManager authorizationStatus];

    if (status == kCLAuthorizationStatusAuthorizedWhenInUse || status == kCLAuthorizationStatusAuthorizedAlways) {

        [self.timer invalidate];

        NSMutableDictionary *dictionary = [[NSMutableDictionary alloc] init];
        [dictionary setValue:@"Location_Success" forKey:@"code"];
        CDVPluginResult* pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsDictionary: dictionary];
        [pluginResult setKeepCallbackAsBool:NO];
        [self.commandDelegate sendPluginResult:pluginResult callbackId:locationCommand.callbackId];
    } else {
        if (status==kCLAuthorizationStatusDenied) {
            // denied
            [self.timer invalidate];

            [self requestLocationPermissions];
        }
    }
}

- (void)init:(CDVInvokedUrlCommand*)command {

    scanCommand = command;
    NSString* device = [command.arguments objectAtIndex:0];
    if (device != nil && device.length > 0) {
        deviceType = device;
    } else {
        deviceType = @"SBeacon";
    }
    interactor = [[BeaconInteractor alloc] initWithDelegate:self];
}

- (void)signIn:(CDVInvokedUrlCommand*)command {

    scanCommand = command;
    NSString* token = [command.arguments objectAtIndex:0];
    if (token != nil) {
        [interactor signIn:token device:deviceType];
    }
}

- (void)startScan:(CDVInvokedUrlCommand*)command {

    scanCommand = command;
    [interactor startScan:deviceType];
}

- (void)stopScan:(CDVInvokedUrlCommand*)command {

    scanCommand = nil;
    [interactor stopScan];
}

- (void)getTemplate:(CDVInvokedUrlCommand*)command {

    templateCommand = command;
    NSString* beacondentifier = [command.arguments objectAtIndex:0];
    if (beacondentifier != nil) {
        [interactor loadTemplates:beacondentifier];
    }
}

- (void)provision:(CDVInvokedUrlCommand*)command {

    connectioncommand = command;
    NSDictionary* dictionary = [command.arguments objectAtIndex:0];
    NSString* template = [dictionary valueForKey:@"templateId"];
    NSString* notes = [dictionary valueForKey:@"notes"];
    NSString* name = [dictionary valueForKey:@"name"];
    if (notes == nil) {
        notes = @"";
    }
    if (template != nil) {

        [interactor provisionBeaconForTemplate:[template intValue] beaconName:name notes:notes];
    }
}

#pragma mark - BeaconInteractorDelegate

- (void)signInSuccess:(BZCUser *)user {

    NSMutableDictionary *dictionary = [[NSMutableDictionary alloc] init];
    [dictionary setValue:@"SignIn_Success" forKey:@"code"];
    [dictionary setValue:user.username forKey:@"user_name"];
    [dictionary setValue:user.email forKey:@"user_email"];
    [dictionary setValue:user.currentProject.identifier forKey:@"project_id"];
    [dictionary setValue:user.currentProject.name forKey:@"project_name"];

    CDVPluginResult* pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsDictionary: dictionary];
    [pluginResult setKeepCallbackAsBool:YES];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:scanCommand.callbackId];
}

- (void)signInFailure:(NSError *)error {

    NSMutableDictionary *dictionary = [[NSMutableDictionary alloc] init];
    [dictionary setValue:@"SignIn_Failed" forKey:@"Fail"];
    [dictionary setValue:[NSString stringWithFormat:@"%ld", (long)error.code] forKey:@"error_code"];
    [dictionary setValue:error.localizedDescription forKey:@"error_message"];

    CDVPluginResult* pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsDictionary: dictionary];
    [pluginResult setKeepCallbackAsBool:NO];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:scanCommand.callbackId];
    scanCommand = nil;
}

- (void)beaconFound:(BLUSBeacon *)beacon {

    NSMutableDictionary *dictionary = [[NSMutableDictionary alloc] init];
    [dictionary setValue:@"Beacon_Found" forKey:@"code"];
    [dictionary setValue:beacon.name forKey:@"name"];
    if ([beacon isKindOfClass:[BLUBluFi class]]) {
        [dictionary setValue:deviceType forKey:@"type"];
        [dictionary setValue:beacon.identifier.stringValue forKey:@"id"];
    } else {
        [dictionary setValue:beacon.identifier.stringValue forKey:@"id"];
        [dictionary setValue:[self convertToHex:beacon.identifier.stringValue].uppercaseString forKey:@"hex"];
        [dictionary setValue:beacon.device.macAddress forKey:@"address"];
        [dictionary setValue:deviceType forKey:@"type"];
    }

    CDVPluginResult* pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsDictionary: dictionary];
    [pluginResult setKeepCallbackAsBool:YES];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:scanCommand.callbackId];
}

- (void)beaconLost:(BLUSBeacon *)beacon {

    NSMutableDictionary *dictionary = [[NSMutableDictionary alloc] init];
    [dictionary setValue:@"Beacon_Lost" forKey:@"code"];
    [dictionary setValue:beacon.name forKey:@"name"];
    [dictionary setValue:beacon.RSSI forKey:@"rssi"];
    if ([beacon isKindOfClass:[BLUBluFi class]]) {
        [dictionary setValue:beacon.device.typeString forKey:@"type"];
    } else {
        [dictionary setValue:beacon.identifier.stringValue forKey:@"id"];
        [dictionary setValue:[self convertToHex:beacon.identifier.stringValue].uppercaseString forKey:@"hex"];
        [dictionary setValue:beacon.device.macAddress forKey:@"address"];
        [dictionary setValue:beacon.device.typeString forKey:@"type"];
    }

    CDVPluginResult* pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsDictionary: dictionary];
    [pluginResult setKeepCallbackAsBool:YES];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:scanCommand.callbackId];
}

- (void)enableBluetooth:(NSString *)message {

    NSMutableDictionary *dictionary = [[NSMutableDictionary alloc] init];
    [dictionary setValue:message forKey:@"result"];

    CDVPluginResult* pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsDictionary: dictionary];
    [pluginResult setKeepCallbackAsBool:NO];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:bluCommand.callbackId];
    bluCommand = nil;
}

- (void)requestLocationPermissions {

    NSMutableDictionary *dictionary = [[NSMutableDictionary alloc] init];
    [dictionary setValue:@"Location permission required" forKey:@"result"];

    CDVPluginResult* pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsDictionary: dictionary];
    [pluginResult setKeepCallbackAsBool:NO];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:locationCommand.callbackId];
    locationCommand = nil;
}

- (void)loadTemplateSucess:(NSArray *)templates {

    NSMutableDictionary *dictionary = [[NSMutableDictionary alloc] init];

    NSMutableArray *array = [[NSMutableArray alloc] init];
    for (BZCTemplate *template in templates) {

        NSMutableDictionary *dict = [[NSMutableDictionary alloc] init];
        [dict setValue:template.identifier.stringValue forKey:@"templateId"];
        [dict setValue:template.name forKey:@"name"];
        [array addObject:dict];
    }

    [dictionary setValue:array forKey:@"templates"];

    CDVPluginResult* pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsDictionary: dictionary];
    [pluginResult setKeepCallbackAsBool:NO];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:templateCommand.callbackId];
}

- (void)loadTemplateError:(NSString *)message {

    NSMutableDictionary *dictionary = [[NSMutableDictionary alloc] init];
    [dictionary setValue:message forKey:@"Template_Fail"];

    CDVPluginResult* pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsDictionary: dictionary];
    [pluginResult setKeepCallbackAsBool:NO];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:templateCommand.callbackId];
    templateCommand = nil;
}

- (void)provisionSuccess {

    NSMutableDictionary *dictionary = [[NSMutableDictionary alloc] init];
    [dictionary setValue:@"Provision_Sucess" forKey:@"code"];

    CDVPluginResult* pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsDictionary: dictionary];
    [pluginResult setKeepCallbackAsBool:NO];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:connectioncommand.callbackId];
}

- (void)provisionError:(NSString *)message {

    NSMutableDictionary *dictionary = [[NSMutableDictionary alloc] init];
    [dictionary setValue:@"ERROR" forKey:@"result"];
    [dictionary setValue:message forKey:@"reason"];

    CDVPluginResult* pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsDictionary: dictionary];
    [pluginResult setKeepCallbackAsBool:NO];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:connectioncommand.callbackId];
    connectioncommand = nil;
}

- (void)provisionStatusChange:(NSString *)status {

    NSMutableDictionary *dictionary = [[NSMutableDictionary alloc] init];
    [dictionary setValue:@"Status_Changed" forKey:@"code"];
    [dictionary setValue:status forKey:@"result"];

    CDVPluginResult* pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsDictionary: dictionary];
    [pluginResult setKeepCallbackAsBool:YES];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:connectioncommand.callbackId];
}

- (void)provisionDescriptionChange:(NSString *)description {

    NSMutableDictionary *dictionary = [[NSMutableDictionary alloc] init];
    [dictionary setValue:@"Desc_Changed" forKey:@"code"];
    [dictionary setValue:description forKey:@"result"];

    CDVPluginResult* pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsDictionary: dictionary];
    [pluginResult setKeepCallbackAsBool:YES];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:connectioncommand.callbackId];
}

#pragma mark - Private Method

- (NSString *)convertToHex: (NSString *)string {

    NSString *hexString = [NSString stringWithFormat:@"%@",
                           [NSData dataWithBytes:[string cStringUsingEncoding:NSUTF8StringEncoding]
                                          length:strlen([string cStringUsingEncoding:NSUTF8StringEncoding])]];

    for(NSString * toRemove in [NSArray arrayWithObjects:@"<", @">", @" ", nil])
        hexString = [string stringByReplacingOccurrencesOfString:toRemove withString:@""];

    return hexString;
}

@end
