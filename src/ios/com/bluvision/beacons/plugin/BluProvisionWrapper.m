/********* BluProvisionWrapper.m Cordova Plugin Implementation *******/

#import <Cordova/CDV.h>
#import <Bluvision/BLUBluFi.h>
#import "BeaconInteractor.h"

@interface BluProvisionWrapper : CDVPlugin <BeaconInteractorDelegate> {
    BeaconInteractor *interactor;
    NSString *deviceType;
    CDVInvokedUrlCommand *scanCommand;
    CDVInvokedUrlCommand *connectioncommand;
    CDVInvokedUrlCommand *templateCommand;
}

- (void)init:(CDVInvokedUrlCommand*)command;
- (void)signIn:(CDVInvokedUrlCommand*)command;
- (void)startScan:(CDVInvokedUrlCommand*)command;
- (void)stopScan:(CDVInvokedUrlCommand*)command;
- (void)getTemplates:(CDVInvokedUrlCommand*)command;
- (void)provision:(CDVInvokedUrlCommand*)command;

@end

@implementation BluProvisionWrapper

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
    	[interactor signIn:token];
    }
}

- (void)startScan:(CDVInvokedUrlCommand*)command {

	scanCommand = command;
    [interactor startScan];
}

- (void)stopScan:(CDVInvokedUrlCommand*)command {

	scanCommand = nil;
    [interactor stopScan];
}

- (void)getTemplates:(CDVInvokedUrlCommand*)command {

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
    [dictionary setValue:@"code" forKey:@"SignIn_Success"];
    [dictionary setValue:user.username forKey:@"user_name"];
    [dictionary setValue:user.email forKey:@"user_email"];
    [dictionary setValue:user.currentProject.identifier forKey:@"project_id"];
    [dictionary setValue:user.currentProject.name forKey:@"project_name"];

    CDVPluginResult* pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsDictionary: dictionary];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:scanCommand.callbackId];
}

- (void)signInFailure:(NSError *)error {
    
    NSMutableDictionary *dictionary = [[NSMutableDictionary alloc] init];
    [dictionary setValue:@"Fail" forKey:@"SignIn_Failed"];
    [dictionary setValue:[NSString stringWithFormat:@"%ld", (long)error.code] forKey:@"error_code"];
    [dictionary setValue:error.localizedDescription forKey:@"error_message"];
    
    CDVPluginResult* pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsDictionary: dictionary];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:scanCommand.callbackId];
    scanCommand = nil;
}

- (void)beaconFound:(BLUSBeacon *)beacon {
    
    if (beacon.device.typeString == deviceType) {
        
        NSMutableDictionary *dictionary = [[NSMutableDictionary alloc] init];
        [dictionary setValue:@"code" forKey:@"Beacon_Found"];
        [dictionary setValue:beacon.name forKey:@"name"];
        if ([beacon isKindOfClass:[BLUBluFi class]]) {
            [dictionary setValue:beacon.device.typeString forKey:@"type"];
        } else {
            [dictionary setValue:beacon.identifier.stringValue forKey:@"id"];
            [dictionary setValue:[self convertToHex:beacon.identifier.stringValue].uppercaseString forKey:@"hex"];
            [dictionary setValue:beacon.device.macAddress forKey:@"address"];
            [dictionary setValue:beacon.device.typeString forKey:@"type"];
        }
        
        CDVPluginResult* pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsDictionary: dictionary];
    	[self.commandDelegate sendPluginResult:pluginResult callbackId:scanCommand.callbackId];
    }
}

- (void)beaconLost:(BLUSBeacon *)beacon {
    
    if (beacon.device.typeString == deviceType) {
        
        NSMutableDictionary *dictionary = [[NSMutableDictionary alloc] init];
        [dictionary setValue:@"code" forKey:@"Beacon_Lost"];
        [dictionary setValue:beacon.name forKey:@"name"];
        if ([beacon isKindOfClass:[BLUBluFi class]]) {
            [dictionary setValue:beacon.device.typeString forKey:@"type"];
        } else {
            [dictionary setValue:beacon.identifier.stringValue forKey:@"id"];
            [dictionary setValue:[self convertToHex:beacon.identifier.stringValue].uppercaseString forKey:@"hex"];
            [dictionary setValue:beacon.device.macAddress forKey:@"address"];
            [dictionary setValue:beacon.device.typeString forKey:@"type"];
        }
        
        CDVPluginResult* pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsDictionary: dictionary];
    	[self.commandDelegate sendPluginResult:pluginResult callbackId:scanCommand.callbackId];
    }
}

- (void)enableBluetooth {
    
    NSMutableDictionary *dictionary = [[NSMutableDictionary alloc] init];
    [dictionary setValue:@"Fail" forKey:@"Bluetooth"];
    
    CDVPluginResult* pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsDictionary: dictionary];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:scanCommand.callbackId];
    scanCommand = nil;
}

- (void)requestLocationPermissions {
    
    NSMutableDictionary *dictionary = [[NSMutableDictionary alloc] init];
    [dictionary setValue:@"Fail" forKey:@"Location"];
    
    CDVPluginResult* pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsDictionary: dictionary];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:scanCommand.callbackId];
    scanCommand = nil;
}

- (void)loadTemplateSucess:(NSArray *)templates {
    
    NSMutableDictionary *dictionary = [[NSMutableDictionary alloc] init];
    
    NSMutableArray *array = [[NSMutableArray alloc] init];
    for (BZCTemplate *template in templates) {
        
        NSMutableDictionary *dict = [[NSMutableDictionary alloc] init];
        [dict setValue:template.identifier.stringValue forKey:@"templateId"];
        [dict setValue:template.name forKey:@"name"];
    }
    
    [dictionary setValue:array forKey:@"templates"];

    CDVPluginResult* pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsDictionary: dictionary];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:templateCommand.callbackId];
}

- (void)loadTemplateError:(NSString *)message {
    
    NSMutableDictionary *dictionary = [[NSMutableDictionary alloc] init];
    [dictionary setValue:message forKey:@"Template_Fail"];

    CDVPluginResult* pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsDictionary: dictionary];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:templateCommand.callbackId];
    templateCommand = nil;
}

- (void)provisionSuccess {
    
    NSMutableDictionary *dictionary = [[NSMutableDictionary alloc] init];
    [dictionary setValue:@"code" forKey:@"Provision_Sucess"];
    
    CDVPluginResult* pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsDictionary: dictionary];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:connectioncommand.callbackId];
}

- (void)provisionError:(NSString *)message {
    
    NSMutableDictionary *dictionary = [[NSMutableDictionary alloc] init];
    [dictionary setValue:@"result" forKey:@"ERROR"];
    [dictionary setValue:@"reason" forKey:message];
    
    CDVPluginResult* pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsDictionary: dictionary];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:connectioncommand.callbackId];
    connectioncommand = nil;
}

- (void)provisionStatusChange:(NSString *)status {
    
    NSMutableDictionary *dictionary = [[NSMutableDictionary alloc] init];
    [dictionary setValue:@"code" forKey:@"Status_Changed"];
    [dictionary setValue:@"result" forKey:status];
    
    CDVPluginResult* pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsDictionary: dictionary];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:connectioncommand.callbackId];
}

- (void)provisionDescriptionChange:(NSString *)description {
    
    NSMutableDictionary *dictionary = [[NSMutableDictionary alloc] init];
    [dictionary setValue:@"code" forKey:@"Desc_Changed"];
    [dictionary setValue:@"result" forKey:description];
    
    CDVPluginResult* pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsDictionary: dictionary];
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
