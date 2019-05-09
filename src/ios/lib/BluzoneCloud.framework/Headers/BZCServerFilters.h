//
//  BZCServerFilter.h
//  BluzoneCloud
//
//  Created by Jason Clary on 8/14/18.
//  Copyright © 2018 Bluvision. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSUInteger, BZCLogic) {
    BZCLogicAnd,
    BZCLogicOr
};

typedef NS_ENUM(NSUInteger, BZCOperator) {
    BZCOperatorEqual,
    BZCOperatorNotEqual,
    BZCOperatorIsNull,
    BZCOperatorIsNotNull,
    BZCOperatorLessThan,
    BZCOperatorLessThanEqual,
    BZCOperatorGreaterThan,
    BZCOperatorGreaterThanEqual,
    BZCOperatorStartsWith,
    BZCOperatorEndsWith,
    BZCOperatorContains,
    BZCOperatorDoesNotContain,
    BZCOperatorIsEmpty,
    BZCOperatorIsNotEmpty
};

@interface BZCFilter : NSObject

@property (nonatomic, strong) NSString *field;
@property (nonatomic, assign) BZCOperator filterOperator;
@property (nonatomic, strong) NSString *value;

- (NSDictionary *)dictionaryRepresentation;

@end

@interface BZCServerFilters : NSObject

@property (nonatomic, strong) NSArray <BZCFilter *> * filters;
@property (nonatomic, assign) BZCLogic logic;

+ (BZCServerFilters *)defaultBeaconFiltersForValue:(NSString *)value;
+ (BZCServerFilters *)defaultBlufiFiltersForValue:(NSString *)value;

- (NSDictionary *)dictionaryRepresentation;

@end
