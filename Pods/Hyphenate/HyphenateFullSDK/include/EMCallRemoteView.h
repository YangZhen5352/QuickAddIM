/*!
 *  @header EMCallRemoteView.h
 *  @abstract Video call remote view
 *  @author Hyphenate
 *  @version 3.00
 */

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#import "EMCallEnum.h"

@interface EMCallRemoteView : UIView

/*!
 *  Video view scale mode
 */
@property (atomic, assign) EMCallViewScaleMode scaleMode;

@end

