//
//  BZCErrorFormatter.h
//  BluzoneCloud
//
//  Created by Jason Clary on 10/23/17.
//  Copyright © 2017 Bluvision. All rights reserved.
//

#import <Foundation/Foundation.h>

// Dictionary key for formatted errors titles
FOUNDATION_EXPORT NSString * const kBZCErrorTitleKey;

// Dictionary key for formatted errors attributed string
FOUNDATION_EXPORT NSString * const kBZCErrorDescriptionAttributedStringKey;

// Dictionary key for boolean value to determine if this error is retryable
FOUNDATION_EXPORT NSString * const kBZCErrorRetryableKey;

// Formats internal errors for better understnading of what an error could be and what actions to take on the error
@interface BZCErrorFormatter : NSObject

+ (NSError *)formattedErrorForError:(NSError *)originalError status:(NSDictionary *)status;

@end
