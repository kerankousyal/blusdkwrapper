//
//  BZCConfigurableBeaconProtocol.h
//  Bluzone
//
//  Copyright © 2015 Bluvision. All rights reserved.
//

@import Foundation;

#ifndef BluZone_BZCConfigurableBeaconProtocol_h
#define BluZone_BZCConfigurableBeaconProtocol_h

@protocol BZCConfigurableBeaconProtocol <NSObject>
@property (nonatomic, readonly) NSString *name;
@property (nonatomic, readonly) NSString *deviceType;
@property (nonatomic, readonly) NSNumber *identifier;
@end

#endif
