/*!
 *  @header EMCallOptions.h
 *  @abstract EMCallManager setting options
 *  @author Hyphenate
 *  @version 3.00
 */

#import <Foundation/Foundation.h>

#import "EMCallEnum.h"
#import "EMCommonDefs.h"

@interface EMCallOptions : NSObject

/*!
 *  When remote is not online, whether to send offline push
 *  default NO
 */
@property (nonatomic, assign) BOOL isSendPushIfOffline;

/*!
 *  Only effective when isSendPushIfOffline is YES.
 *  default “You have incoming call...”
 */
@property (nonatomic, strong) NSString *offlineMessageText;

/*!
 *  Video resolution
 *  default adaptive
 */
@property (nonatomic, assign) EMCallVideoResolution videoResolution;

/*!
 *  Video kbps
 *  range 50 < videoKbps < 5000, default 0 , 0 means adaptive
 *  advice 0
 */
@property (nonatomic, assign) long maxVideoKbps;

/*!
 *  Min video kbps
 *
 */
@property (nonatomic, assign) int minVideoKbps;

/*!
 *  Enable fixed video resolution，default NO
 *
 */
@property (nonatomic, assign) BOOL isFixedVideoResolution;

/*!
 *  Max video frame rate
 *
 */
@property (nonatomic, assign) int maxVideoFrameRate;

#pragma mark - EM_DEPRECATED_IOS 3.2.2

/*
*  Video kbps
*  range 50 < videoKbps < 5000, default 0 , 0 means adaptive
*  advice 0
*/
@property (nonatomic, assign) long videoKbps EM_DEPRECATED_IOS(3_2_2, 3_2_2, "Use -[EMCallOptions maxVideoKbps]");

@end
