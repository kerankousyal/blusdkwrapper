//
//  BZCClient.h
//  Bluzone
//
//  Copyright © 2015 Bluvision. All rights reserved.
//

#import <Foundation/Foundation.h>

@class BZCUser;

NS_ASSUME_NONNULL_BEGIN

/**
 *  `BZCClient` objects represent an REST interface with Bluzone.
 */
@interface BZCClient : NSObject


@property (nonatomic, strong) NSURL *baseURL;
@property (nonatomic, strong, nullable) NSString *apiToken;
@property (nonatomic, readwrite, getter=isOffline) BOOL offline;


/**
 *  Singleton Client
 *
 *  @return Singleton Client
 */
+ (BZCClient *)client NS_SWIFT_NAME(shared());

/**
 *  Sets the underlying operation queue for all callbacks to be dispatched to
 *
 *  @param queue the que you want
 */
- (void)setOperationQueue:(dispatch_queue_t)queue;


/**
 *  Performs a REST GET
 *
 *  @param path       the path to the REST endpoint
 *  @param parameters the parameters for the REST endpoint
 *  @param completion a completion block to be executed once the request has been processed
 */
- (void)GET:(NSString *)path parameters:(nullable id)parameters completion:(nullable void (^)(id _Nullable responseObject, NSError * _Nullable error))completion;

/**
 *  Performs a REST POST
 *
 *  @param path       the path to the REST endpoint
 *  @param parameters the parameters for the REST endpoint
 *  @param completion a completion block to be executed once the request has been processed
 */
- (void)POST:(NSString *)path parameters:(nullable id)parameters completion:(nullable void (^)(id _Nullable responseObject, NSError * _Nullable error))completion;


- (void)POST:(NSString *)path parameters:(nullable id)parameters constructingBodyWithBlock:(void (^)(id _Nonnull formData))bodyBlock completion:(void (^)(id responseObject, NSError *error))completion;

/**
 *  Performs a REST PUT
 *
 *  @param path       the path to the REST endpoint
 *  @param parameters the parameters for the REST endpoint
 *  @param completion a completion block to be executed once the request has been processed
 */
- (void)PUT:(NSString *)path parameters:(nullable id)parameters completion:(nullable void (^)(id _Nullable responseObject, NSError * _Nullable error))completion;

/**
 *  Performs a REST DELETE
 *
 *  @param path       the path to the REST endpoint
 *  @param completion a completion block to be executed once the request has been processed
 */
- (void)DELETE:(NSString *)path completion:(nullable void (^)(id _Nullable responseObject, NSError * _Nullable error))completion;

/**
 *  Performs a REST POST which will cache the request if it fails and will retry later
 *
 *  @param path       the path to the REST endpoint
 *  @param parameters the parameters for the REST endpoint
 *  @param completion a completion block to be executed once the request has been processed
 */
- (void)cacheblePOST:(NSString *)path parameters:(nullable id)parameters completion:(nullable void (^)(id _Nullable responseObject, NSError * _Nullable error))completion;

/**
 *  Performs a REST PUT which will cache the request if it fails and will retry later
 *
 *  @param path       the path to the REST endpoint
 *  @param parameters the parameters for the REST endpoint
 *  @param completion a completion block to be executed once the request has been processed
 */
- (void)cachablePUT:(NSString *)path parameters:(nullable id)parameters completion:(nullable void (^)(id _Nullable responseObject, NSError * _Nullable error))completion;

/**
 *  Force Process any cached requests
 */
- (void)processCachedRequests;

/**
 *  Clears the cache
 */
- (void)clearCache;

- (void)setRequestTimeout:(NSTimeInterval)timeout;

@end

NS_ASSUME_NONNULL_END
