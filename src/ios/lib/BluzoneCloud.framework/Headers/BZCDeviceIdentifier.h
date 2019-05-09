//
//  BZCDeviceIdentifier.h
//  Bluzone
//
//  Created by Jason Clary on 5/19/17.
//  Copyright © 2017 Bluvision. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface BZCDeviceIdentifier : NSObject <NSSecureCoding>

@property (nonatomic, readonly) NSNumber *identifier;
@property (nonatomic, readonly) NSString *name;
@property (nonatomic, readonly) NSString *code;
@property (nonatomic, readonly ,getter=isActive) BOOL active;
@property (nonatomic, readonly ,getter=isBlufi) BOOL blufi;

- (instancetype)initWithDictionary:(NSDictionary *)dictionary;

+ (void)deviceIdentifiersWithCompletion:(void (^)( NSArray <BZCDeviceIdentifier *> * _Nullable deviceIdentifiers, NSError * _Nullable error))completion;

- (NSDictionary *)dictionaryRepresentation;

@end

NS_ASSUME_NONNULL_END
