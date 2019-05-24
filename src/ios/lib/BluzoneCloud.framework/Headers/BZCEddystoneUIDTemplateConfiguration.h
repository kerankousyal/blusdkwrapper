//
//  BZCEddystoneUIDTemplateConfiguration.h
//  Bluzone
//
//  Created by Jason Clary on 4/6/16.
//  Copyright © 2016 Bluvision. All rights reserved.
//

@import Foundation;

#import "BZCBeaconTemplateConfiguration.h"

@interface BZCEddystoneUIDTemplateConfiguration : BZCBeaconTemplateConfiguration

@property (nonatomic, copy) NSString *UIDNamespace;
@property (nonatomic, copy) NSString *UIDInstance;
@property (nonatomic, assign, getter=isUIDInstanceAutoAssigned) BOOL UIDInstanceAutoAssigned;

@end
