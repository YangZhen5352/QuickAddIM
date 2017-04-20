/*!
 *  @header IEMCallManager.h
 *  @abstract This protocol defined the operations of real time voice/video call
 *  @author Hyphenate
 *  @version 3.00
 */

#import <Foundation/Foundation.h>

#import "EMCallOptions.h"
#import "EMCallManagerDelegate.h"

@class EMError;
@class EMCallStream;

/*!
 *
 */
@protocol IEMCallManager <NSObject>

@optional

#pragma mark - Delegate

/*!
 *  Add delegate
 *
 *  @param aDelegate  Delegate
 *  @param aQueue     The queue of call delegate method
 */
- (void)addDelegate:(id<EMCallManagerDelegate>)aDelegate
      delegateQueue:(dispatch_queue_t)aQueue;

/*!
 *  Remove delegate
 *
 *  @param aDelegate  Delegate
 */
- (void)removeDelegate:(id<EMCallManagerDelegate>)aDelegate;

#pragma mark - Options

/*!
 *  Set setting options
 *
 *  @param aOptions  Setting options
 */
- (void)setCallOptions:(EMCallOptions *)aOptions;

/*!
 *  Get setting options
 *
 *  @result Setting options
 */
- (EMCallOptions *)getCallOptions;

#pragma mark - Make and Answer and End

/*!
 *  Start a call
 *
 *  @param aType            Call type
 *  @param aRemoteName      The callee
 *  @param aExt             Call extention, to the callee
 *  @param aCompletionBlock The callback of completion
 *
 */
- (void)startCall:(EMCallType)aType
       remoteName:(NSString *)aRemoteName
              ext:(NSString *)aExt
       completion:(void (^)(EMCallSession *aCallSession, EMError *aError))aCompletionBlock;

/*!
 *  Receiver answer the call
 *
 *  @param  aCallId     Call Id
 *  @param  aRemoteName Remote name
 *
 *  @result Error
 */
- (EMError *)answerIncomingCall:(NSString *)aCallId;

/*!
 *  End the call
 *
 *  @param aCallId     Call ID
 *  @param aReason     End reason
 *
 *  @result Error
 */
- (EMError *)endCall:(NSString *)aCallId
              reason:(EMCallEndReason)aReason;

#pragma mark - EM_DEPRECATED_IOS 3.2.1

/*!
 *  Start a voice call
 *
 *  @param aUsername        The callee
 *  @param aCompletionBlock The callback of completion
 *
 */
- (void)startVoiceCall:(NSString *)aUsername
            completion:(void (^)(EMCallSession *aCallSession, EMError *aError))aCompletionBlock EM_DEPRECATED_IOS(3_1_0, 3_2_0, "Use -[IEMCallManager startCall:remoteName:ext:completion:]");

/*!
 *  Start a video call
 *
 *  @param aUsername        The callee
 *  @param aSuccessBlock    The callback block of completion
 *
 */
- (void)startVideoCall:(NSString *)aUsername
            completion:(void (^)(EMCallSession *aCallSession, EMError *aError))aCompletionBlock EM_DEPRECATED_IOS(3_1_0, 3_2_0, "Use -[IEMCallManager startCall:remoteName:ext:completion:]");

#pragma mark - EM_DEPRECATED_IOS 3.2.0

/*!
 *  Pause voice streaming
 *
 *  @param aSessionId   Session ID
 */
- (void)pauseVoiceWithSession:(NSString *)aSessionId
                        error:(EMError**)pError EM_DEPRECATED_IOS(3_1_0, 3_1_5, "Use -[EMCallSession pauseVoice]");

/*!
 *  Resume voice streaming
 *
 *  @param aSessionId   Session ID
 */
- (void)resumeVoiceWithSession:(NSString *)aSessionId
                         error:(EMError**)pError EM_DEPRECATED_IOS(3_1_0, 3_1_5, "Use -[EMCallSession resumeVoice]");

/*!
 * Pause video streaming
 *
 *  @param aSessionId   Session ID
 */
- (void)pauseVideoWithSession:(NSString *)aSessionId
                        error:(EMError**)pError EM_DEPRECATED_IOS(3_1_0, 3_1_5, "Use -[EMCallSession pauseVideo]");

/*!
 *  Resume video streaming
 *
 *  @param aSessionId   Session ID
 */
- (void)resumeVideoWithSession:(NSString *)aSessionId
                         error:(EMError**)pError EM_DEPRECATED_IOS(3_1_0, 3_1_5, "Use -[EMCallSession resumeVideo]");

/*!
 *  Enable video adaptive, default is disable
 *
 *  @param isAdaptive   YES is enable, NO is disable
 */
- (void)enableAdaptiveBirateStreaming:(BOOL)isAdaptive EM_DEPRECATED_IOS(3_1_0, 3_1_5, "Use -[EMCallOptions videoKbps]");


#pragma mark - EM_DEPRECATED_IOS < 3.2.0

/*!
 *  Start a voice call session
 *
 *  @param aUsername  The callee
 *  @param pError     Error
 *
 *  @result Session instance
 */
- (EMCallSession *)makeVoiceCall:(NSString *)aUsername
                           error:(EMError **)pError __deprecated_msg("Use -startVoiceCall:completion:");

/*!
 *  Get video package lost rate
 *
 *  @param aSessionId   Session ID
 *  @param aIsSilence   Is Silence
 *
 *  @result             Error
 */
- (EMError *)markCallSession:(NSString *)aSessionId
                   isSilence:(BOOL)aIsSilence __deprecated_msg("Use -pauseVoiceWithSession:error:");


/*!
 *  Suspend voice data transmission
 *
 *  @param aSessionId   Session ID
 */
- (void)pauseVoiceTransfer:(NSString *)aSessionId __deprecated_msg("Use -pauseVoiceWithSession:error:");

/*!
 *  Resume voice data transmission
 *
 *  @param aSessionId   Session ID
 */
- (void)resumeVoiceTransfer:(NSString *)aSessionId __deprecated_msg("Use -resumeVoiceWithSession:error:");

/*!
 *  Start a video call session
 *
 *  @param aUsername  The callee
 *  @param pError     Error
 *
 *  @result Session instance
 */
- (EMCallSession *)makeVideoCall:(NSString *)aUsername
                           error:(EMError **)pError __deprecated_msg("Use -startVideoCall:completion:");

/*!
 * Suspend video data transmission
 *
 *  @param aSessionId   Session ID
 */
- (void)pauseVideoTransfer:(NSString *)aSessionId __deprecated_msg("Use -pauseVideoWithSession:error:");

/*!
 *  Resume video data transmission
 *
 *  @param aSessionId   Session ID
 */
- (void)resumeVideoTransfer:(NSString *)aSessionId __deprecated_msg("Use -resumeVideoWithSession:error:");

/*!
 * Suspend voice and video data transmission
 *
 *  @param aSessionId   Session ID
 */
- (void)pauseVoiceAndVideoTransfer:(NSString *)aSessionId __deprecated_msg("Delete");

/*!
 *  Resume voice and video data transmission
 *
 *  @param aSessionId   Session ID
 */
- (void)resumeVoiceAndVideoTransfer:(NSString *)aSessionId __deprecated_msg("Delete");

/*!
 *  Enable video adaptive, default is disable
 *
 *  @param aFlag   YES is enable, NO is disable
 */
- (void)setVideoAdaptive:(BOOL)aFlag  __deprecated_msg("Use -enableAdaptiveBirateStreaming:");


@end
