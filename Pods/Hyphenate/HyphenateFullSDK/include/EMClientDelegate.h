/*!
 *  @header EMClientDelegate.h
 *  @abstract This protocol provides a number of utility classes callback
 *  @author Hyphenate
 *  @version 3.00
 */

#import <Foundation/Foundation.h>

/*!
 *  Network Connection Status
 */
typedef enum{
    EMConnectionConnected = 0,  /*! * Connected */
    EMConnectionDisconnected,   /*! * Not connected */
}EMConnectionState;

@class EMError;

/*!
 *  @abstract This protocol provides a number of utility classes callback
 */
@protocol EMClientDelegate <NSObject>

@optional

/*!
 *  Delegate method will be invoked when server connection state has changed
 *
 *  @param aConnectionState Current state
 */
- (void)connectionStateDidChange:(EMConnectionState)aConnectionState;

/*!
 *  Delegate method will be invoked when auto login is completed
 *
 *  @param aError Error
 */
- (void)autoLoginDidCompleteWithError:(EMError *)aError;

/*!
 *  Delegate method will be invoked when current IM account logged into another device
 *  当前登录账号在其它设备登录时会接收到该回调
 */
- (void)userAccountDidLoginFromOtherDevice;

/*!
 *  Delegate method will be invoked when current IM account is removed from server
 *  当前登录账号已经被从服务器端删除时会收到该回调
 */
- (void)userAccountDidRemoveFromServer;

/*!
 *  User is forbidden
 */
- (void)userDidForbidByServer;

@end
