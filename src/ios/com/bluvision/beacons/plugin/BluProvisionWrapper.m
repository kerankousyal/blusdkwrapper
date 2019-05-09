/********* BluProvisionWrapper.m Cordova Plugin Implementation *******/

#import <Cordova/CDV.h>

@interface BluProvisionWrapper : CDVPlugin {
 	BeaconInteractor *interactor = nil;
 	NSString *deviceType = nil;
 	CDVInvokedUrlCommand *scanCommand = nil;
 	CDVInvokedUrlCommand *connectioncommand = nil;
 	CDVInvokedUrlCommand *templateCommand = nil;
}

- (void)coolMethod:(CDVInvokedUrlCommand*)command;
@end

@implementation BluProvisionWrapper

- (void)init:(CDVInvokedUrlCommand*)command {

	scanCommand = command;
    NSString* deviceType = [command.arguments objectAtIndex:0];
    if (deviceType != nil && deviceType.length > 0) {
        self.deviceType = deviceType;
    } else {
        self.deviceType = @"SBeacon";
    }
    self.interactor = [[BeaconInteractor alloc] initWithDelegate:self];
}

- (void)signIn:(CDVInvokedUrlCommand*)command {

	scanCommand = command;
    NSString* token = [command.arguments objectAtIndex:0];
    if (token != nil) {
    	[self.interactor signIn:token];
    }
}

- (void)startScan:(CDVInvokedUrlCommand*)command {

	scanCommand = command;
    [self.interactor startScan];
}

- (void)stopScan:(CDVInvokedUrlCommand*)command {

	scanCommand = nil;
    [self.interactor stopScan];
}

- (void)getTemplates:(CDVInvokedUrlCommand*)command {

	templateCommand = command;
    NSString* beacondentifier = [command.arguments objectAtIndex:0];
    if (beacondentifier != nil) {
    	[self.interactor loadTemplates:beacondentifier];
    }
}

- (void)provision:(CDVInvokedUrlCommand*)command {

	connectioncommand = command;
    NSDictionary* data = [command.arguments objectAtIndex:0];
    NSString* templateId = [dictionary valueForKey:@"templateId"];
    NSString* notes = [dictionary valueForKey:@"notes"];
    if (notes == nil) {
    	notes = @"";
    }
    if (templateId != nil) {
    	[self.interactor provisionBeaconForTemplate:templateId notes:notes];
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
    [dictionary setValue:user.currentProject forKey:@"current_project"];

    CDVPluginResult* pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK message: dictionary];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:scanCommand.callbackId];
}

- (void)signInFailure:(NSError *)error {
    
    NSMutableDictionary *dictionary = [[NSMutableDictionary alloc] init];
    [dictionary setValue:@"Fail" forKey:@"SignIn_Failed"];
    [dictionary setValue:[NSString stringWithFormat:@"%ld", (long)error.code] forKey:@"error_code"];
    [dictionary setValue:error.localizedDescription forKey:@"error_message"];
    
    CDVPluginResult* pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR message: dictionary];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:scanCommand.callbackId];
    scanCommand = nil;
}

- (void)beaconFound:(BLUSBeacon *)beacon {
    
    if (beacon.device.typeString == self.deviceType) {
        
        NSMutableDictionary *dictionary = [[NSMutableDictionary alloc] init];
        [dictionary setObject:@"code" forKey:@"Beacon_Found"];
        [dictionary setObject:beacon.name forKey:@"name"];
        if ([beacon isKindOfClass:[BLUBluFi class]]) {
            [dictionary setObject:beacon.device.typeString forKey:@"type"];
        } else {
            [dictionary setObject:beacon.identifier.stringValue forKey:@"id"];
            [dictionary setObject:[self convertToHex:beacon.identifier.stringValue].uppercaseString forKey:@"hex"];
            [dictionary setObject:beacon.device.macAddress forKey:@"address"];
            [dictionary setObject:beacon.device.typeString forKey:@"type"];
        }
        
        CDVPluginResult* pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK message: dictionary];
    	[self.commandDelegate sendPluginResult:pluginResult callbackId:scanCommand.callbackId];
    }
}

- (void)beaconLost:(BLUSBeacon *)beacon {
    
    if (beacon.device.typeString == self.deviceType)
        
        NSMutableDictionary *dictionary = [[NSMutableDictionary alloc] init];
        [dictionary setObject:@"code" forKey:@"Beacon_Lost"];
        [dictionary setObject:beacon.name forKey:@"name"];
        if ([beacon isKindOfClass:[BLUBluFi class]]) {
            [dictionary setObject:beacon.device.typeString forKey:@"type"];
        } else {
            [dictionary setObject:beacon.identifier.stringValue forKey:@"id"];
            [dictionary setObject:[self convertToHex:beacon.identifier.stringValue].uppercaseString forKey:@"hex"];
            [dictionary setObject:beacon.device.macAddress forKey:@"address"];
            [dictionary setObject:beacon.device.typeString forKey:@"type"];
        }
        
        CDVPluginResult* pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK message: dictionary];
    	[self.commandDelegate sendPluginResult:pluginResult callbackId:scanCommand.callbackId];
    } {
}

- (void)enableBluetooth {
    
    NSMutableDictionary *dictionary = [[NSMutableDictionary alloc] init];
    [dictionary setValue:@"Fail" forKey:@"Bluetooth"];
    
    CDVPluginResult* pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR message: dictionary];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:scanCommand.callbackId];
    scanCommand = nil;
}

- (void)requestLocationPermissions {
    
    NSMutableDictionary *dictionary = [[NSMutableDictionary alloc] init];
    [dictionary setValue:@"Fail" forKey:@"Location"];
    
    CDVPluginResult* pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR message: dictionary];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:scanCommand.callbackId];
    scanCommand = nil;
}

- (void)loadTemplateSucess:(NSArray *)templates {
    
    NSMutableDictionary *dictionary = [[NSMutableDictionary alloc] init];
    
    NSMutableArray *array = [[NSMutableArray alloc] init];
    for (BZCTemplate *template in templates) {
        
        NSMutableDictionary *dict = [[NSMutableDictionary alloc] init];
        [dict setObject:template.identifier.stringValue forKey:@"templateId"];
        [dict setObject:template.name forKey:@"name"];
    }
    
    [dictionary setObject:array forKey:@"templates"];

    CDVPluginResult* pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK message: dictionary];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:templateCommand.callbackId];
}

- (void)loadTemplateError:(NSString *)message {
    
    NSMutableDictionary *dictionary = [[NSMutableDictionary alloc] init];
    [dictionary setObject:message forKey:@"Template_Fail"];

    CDVPluginResult* pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR message: dictionary];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:templateCommand.callbackId];
    templateCommand = nil;
}

- (void)provisionSuccess {
    
    NSMutableDictionary *dictionary = [[NSMutableDictionary alloc] init];
    [dictionary setValue:@"code" forKey:@"Provision_Sucess"];
    
    CDVPluginResult* pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK message: dictionary];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:connectioncommand.callbackId];
}

- (void)provisionError:(NSString *)message {
    
    NSMutableDictionary *dictionary = [[NSMutableDictionary alloc] init];
    [dictionary setValue:@"result" forKey:@"ERROR"];
    [dictionary setValue:@"reason" forKey:message];
    
    CDVPluginResult* pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR message: dictionary];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:connectioncommand.callbackId];
    connectioncommand = nil;
}

- (void)provisionStatusChange:(NSString *)status {
    
    NSMutableDictionary *dictionary = [[NSMutableDictionary alloc] init];
    [dictionary setValue:@"code" forKey:@"Status_Changed"];
    [dictionary setValue:@"result" forKey:status];
    
    CDVPluginResult* pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK message: dictionary];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:connectioncommand.callbackId];
}

- (void)provisionDescriptionChange:(NSString *)description {
    
    NSMutableDictionary *dictionary = [[NSMutableDictionary alloc] init];
    [dictionary setValue:@"code" forKey:@"Desc_Changed"];
    [dictionary setValue:@"result" forKey:description];
    
    CDVPluginResult* pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK message: dictionary];
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