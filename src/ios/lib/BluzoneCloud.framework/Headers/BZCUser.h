//
//  BZCUser.h
//  Bluzone
//
//  Copyright © 2015 Bluvision. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

FOUNDATION_EXPORT NSString *const BZCUserDidSignOutNotification;

@class BZCProject;
@class BZCContext;

/**
 *  BZCUser represents a user of Bluzone
 */
@interface BZCUser : NSObject <NSSecureCoding>

/**
 *  The Username of the User
 */
@property (nonatomic, readonly) NSString *username;

/**
 *  The Email address of the User
 */
@property (nonatomic, readonly) NSString *email;

/**
 *  The current project of the User
 */
@property (nonatomic, readonly) BZCProject *currentProject;

/**
 *  The Auth token of the User
 */
@property (nonatomic, readonly) NSString *authToken;

@property (nonatomic, readonly) BZCContext *context;

/**
 *  An array of projects for the user
 */
@property (nonatomic, readonly) NSArray <BZCProject *> *projects;

/**
 *  Authenticates and signs in a user with an API Token from bluzone.io
 *
 *  @param apiToken   the apiToken from bluzone.io
 *  @param completion a compleiton block that will be executed when the user is authenticated.
 */
+ (void)authenticateWithAPIToken:(NSString *)apiToken completion:(nullable void (^)(BZCUser * _Nullable user, NSError * _Nullable error))completion;

/**
 *  The Current Users
 *
 *  @return the currently logged in user, this is persisted between application launches.
 */
+ (BZCUser * _Nullable)currentUser;

/**
 *  Sign in a User
 *
 *  @param username   the username of the user to be signed in
 *  @param password   the password of the user to be signed in
 *  @param completion a completion block that will be executed when the user is signed in.
 */
+ (void)signInWithUsername:(NSString *)username password:(NSString *)password completion:(nullable void (^)(BZCUser * _Nullable user, NSError * _Nullable error))completion;

/**
 *  Sign up a User to Bluzone.io
 *
 *  @param username   a username of a new user
 *  @param email      the email address of the new user
 *  @param password   the password for the new user
 *  @param completion a completion block that will be executed when the user is signed up.
 */
+ (void)signUpWithUsername:(NSString *)username email:(NSString *)email password:(NSString *)password completion:(nullable void (^)(BZCUser * _Nullable user, NSError * _Nullable error))completion;

+ (void)signInWithToken:(NSString *)token provider:(NSString *)provider completion:(nullable void (^)(BZCUser * _Nullable user, NSError * _Nullable error))completion;

/**
 *  Signs out the Current User
 */
- (void)signOut;

@end

NS_ASSUME_NONNULL_END
