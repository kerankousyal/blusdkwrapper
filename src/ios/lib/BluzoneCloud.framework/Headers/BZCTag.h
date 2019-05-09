//
//  BZCTag.h
//  Bluzone
//
//  Copyright © 2015 Bluvision. All rights reserved.
//

@import Foundation;

NS_ASSUME_NONNULL_BEGIN

/**
 *  BZCTag objects describe tags associated to devices/templates/policies
 */
@interface BZCTag : NSObject <NSSecureCoding>

/**
 *  The name of this tag
 */
@property (nonatomic, readonly) NSString *name;

/**
 *  The project identifier of this tag
 */
@property (nonatomic, readonly) NSString *projectIdentifier;

/**
 *  The identifier of this tag
 */
@property (nonatomic, readonly) NSNumber *identifier;

/**
 *  The value of this tag
 */
@property (nonatomic, strong) NSString *value;

/**
 *  Searches for tags containing a search string
 *
 *  @param string     a string to search on
 *  @param completion a completion block executed once the tags have been found
 */
+ (void)tagsContainingString:(NSString *)string completion:(nullable void (^)(NSArray * _Nullable tags, NSError * _Nullable error))completion;

@end

NS_ASSUME_NONNULL_END
