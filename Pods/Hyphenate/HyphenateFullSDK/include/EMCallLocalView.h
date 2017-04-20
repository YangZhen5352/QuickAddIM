/*!
 *  @header EMCallLocalView.h
 *  @abstract Video call local view
 *  @author Hyphenate
 *  @version 3.00
 */


#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#import "EMCallEnum.h"

@interface EMCallLocalView : UIView

/*!
 *  Video view scale mode
 */
@property (atomic, assign) EMCallViewScaleMode scaleMode;

@end

