//
//  BZCSelfie.h
//  Bluzone
//
//  Copyright © 2015 Bluvision. All rights reserved.
//

@import UIKit;

NS_ASSUME_NONNULL_BEGIN

/**
 *  BZCSelfie objects represent an image of a device as well as overlays to direct the user where in the image the device is
 *  
 *  @description These objects are cached internally once downloaded
 */
@interface BZCSelfie : NSObject <NSSecureCoding>

+ (UIImage *) imageForDeviceId:(NSString *)deviceId;

/**
 *  The identifier of this selfie
 */
@property (nonatomic, readonly) NSString *identifier;

/**
 *  The name of this selfie
 */
@property (nonatomic, readonly) NSString *name;

/**
 *  The content type of this selfie
 */
@property (nonatomic, readonly) NSString *contentType;

/**
 *  The overlay center point
 */
@property (nonatomic, assign) CGPoint overlayPoint;

/**
 *  The overlay radius
 */
@property (nonatomic, assign) CGFloat overlayRadius;

/**
 *  The url of the image for this selfie
 */
@property (nonatomic, readonly) NSURL *imageURL;

/**
 *  The Image of this selfie
 */
@property (nonatomic, readonly, nullable) UIImage *image;

/**
 *  Initialize a selfie with a Image
 *
 *  @param image an Image of the device
 *
 *  @return a fully initilized selfie
 */
- (instancetype)initWithImage:(UIImage *)image;

/**
 *  Downloads a selfies image and caches it
 *
 *  @param completion a completion block executed once the image is downloaded
 */
- (void)downloadWithCompletion:(nullable void (^)(UIImage * _Nullable image, NSError * _Nullable error))completion;

/**
 *  Deletes this selfie
 *
 *  @param completion a completion block executed once this selfie is deleted
 */
- (void)deleteWithCompletion:(nullable void (^)(BOOL success, NSError * _Nullable error))completion;

/**
 *  Uploads a selfie to be used by Bluzone.io. This selfie must be associated with a Device before uploading
 *
 *  @param completion a completion block executed once this selfie has been uploaded
 */
- (void)uploadSelfieWithCompletion:(nullable void (^)(BOOL success, NSError * _Nullable error))completion;

@end

NS_ASSUME_NONNULL_END
