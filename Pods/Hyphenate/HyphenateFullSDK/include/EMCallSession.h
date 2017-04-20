/*!
 *  @header EMCallSession.h
 *  @abstract Call session
 *  @author Hyphenate
 *  @version 3.00
 */

#import <Foundation/Foundation.h>

#import "EMCallLocalView.h"
#import "EMCallRemoteView.h"
#import "EMCallEnum.h"
#import "EMCommonDefs.h"

/*!
 *  Call session
 */
@class EMError;
@interface EMCallSession : NSObject

/*!
 *  Unique call id
 */
@property (nonatomic, strong, readonly) NSString *callId;

/*!
 *  Local username
 */
@property (nonatomic, strong, readonly) NSString *localName;

/*!
 *  Call type
 */
@property (nonatomic, readonly) EMCallType type;

/*!
 *  Whether it is the caller
 */
@property (nonatomic, readonly) BOOL isCaller;

/*!
 *  The other side's username
 */
@property (nonatomic, strong, readonly) NSString *remoteName;

/*!
 *  Call session status
 */
@property (nonatomic, readonly) EMCallSessionStatus status;

/*!
 *  Local display view
 */
@property (nonatomic, strong) EMCallLocalView *localVideoView;

/*!
 *  Remote display view
 */
@property (nonatomic, strong) EMCallRemoteView *remoteVideoView;

#pragma mark - Statistics Property

/*!
 *  Connection type
 */
@property (nonatomic, readonly) EMCallConnectType connectType;

/*!
 *  Video latency, in milliseconds, changing in real time
 *  Didn't get to show -1
 */
@property (nonatomic, readonly) int videoLatency;

/*!
 *  Local video frame rate, changing in real time
 *  Didn't get to show -1
 */
@property (nonatomic, readonly) int localVideoFrameRate;

/*!
 *  Remote video frame rate, changing in real time
 *  Didn't get to show -1
 */
@property (nonatomic, readonly) int remoteVideoFrameRate;

/*!
 *  Local the other party's bitrate, changing in real time
 *  Didn't get to show -1
 */
@property (nonatomic, readonly) int localVideoBitrate;

/*!
 *  Remote the other party's bitrate, changing in real time
 *  Didn't get to show -1
 */
@property (nonatomic, readonly) int remoteVideoBitrate;

/*!
 *  Local video package lost rate, changing in real time
 *  Didn't get to show -1
 */
@property (nonatomic, readonly) int localVideoLostRateInPercent;

/*!
 *  Remote video package lost rate, changing in real time
 *  Didn't get to show -1
 */
@property (nonatomic, readonly) int remoteVideoLostRateInPercent;

/*!
 *  Remote video resolution
 *  Didn't get to show (-1,-1)
 */
@property (nonatomic, readonly) CGSize remoteVideoResolution;

/*!
 *  Call extention
 *
 *  Type must be NSString
 */
@property (nonatomic, readonly) NSString *ext;

#pragma mark - Control Stream

/*!
 *  Suspend voice data transmission
 *
 *  @result Error
 */
- (EMError *)pauseVoice;

/*!
 *  Resume voice data transmission
 *
 *  @result Error
 */
- (EMError *)resumeVoice;

/*!
 * Suspend video data transmission
 *
 *  @result Error
 */
- (EMError *)pauseVideo;

/*!
 *  Resume video data transmission
 *
 *  @result Error
 */
- (EMError *)resumeVideo;

#pragma mark - Camera

/*!
 *  Use front camera or back camera, default use front
 *
 *  @param  aIsFrontCamera    YES for front camera, NO for back camera.
 */
- (void)switchCameraPosition:(BOOL)aIsFrontCamera;

#pragma mark - EM_DEPRECATED_IOS 3.2.0

/*!
 *  Unique session id
 */
@property (nonatomic, strong, readonly) NSString *sessionId EM_DEPRECATED_IOS(3_1_0, 3_1_5, "Use EMCallSession.callId");

/*!
 *  Local username
 */
@property (nonatomic, strong, readonly) NSString *username EM_DEPRECATED_IOS(3_1_0, 3_1_5, "Use EMCallSession.localName");

/*!
 *  The other side's username
 */
@property (nonatomic, strong, readonly) NSString *remoteUsername EM_DEPRECATED_IOS(3_1_0, 3_1_5, "Use EMCallSession.remoteName");

/*!
 *  Video bit rate, must be set before call session is started.
 *
 *  Value range is 150-1000, the default is 600.
 */
@property (nonatomic) int videoBitrate EM_DEPRECATED_IOS(3_1_0, 3_1_5, "Use EMCallOptions.videoKbps");

/*!
 *  Get voice volume of the call
 *
 *  @return Volume
 */
- (int)getVoiceVolume EM_DEPRECATED_IOS(3_1_0, 3_1_5, "Delete");

/*!
 *  Get video latency, in milliseconds, changing in real time
 *
 *  @result The delay time
 */
- (int)getVideoLatency EM_DEPRECATED_IOS(3_1_0, 3_1_5, "Use -EMCallSession.videoLatency");

/*!
 *  Get video frame rate, changing in real time
 *
 *  @result The video frame rate
 */
- (int)getVideoFrameRate EM_DEPRECATED_IOS(3_1_0, 3_1_5, "Use -EMCallSession.remoteVideoFrameRate");

/*!
 *  Get video package lost rate
 *
 *  @result Video package lost rate
 */
- (int)getVideoLostRateInPercent EM_DEPRECATED_IOS(3_1_0, 3_1_5, "Use -EMCallSession.remoteVideoLostRateInPercent");

/*!
 *  Get video original width
 *
 *  @result Video original width
 */
- (int)getVideoWidth EM_DEPRECATED_IOS(3_1_0, 3_1_5, "Use -EMCallSession.remoteVideoResolution");

/*!
 *  Get fixed video original height
 *
 *  @result Video original height
 */
- (int)getVideoHeight EM_DEPRECATED_IOS(3_1_0, 3_1_5, "Use -EMCallSession.remoteVideoResolution");

/*!
 *  Get the other party's bitrate, changing in real time
 *
 *  @result The other party's bitrate
 */
- (int)getVideoRemoteBitrate EM_DEPRECATED_IOS(3_1_0, 3_1_5, "Use -EMCallSession.remoteVideoBitrate");

/*!
 *  Get bitrate of video call, changing in real time
 *
 *  @result Bitrate of video call
 */
- (int)getVideoLocalBitrate EM_DEPRECATED_IOS(3_1_0, 3_1_5, "Use -EMCallSession.localVideoBitrate");

/*!
 *  Get a snapshot of current video screen as jpeg picture and save to the local file system.
 *
 *  @param aPath  Saved path of picture
 */
- (void)screenCaptureToFilePath:(NSString *)aPath
                          error:(EMError**)pError EM_DEPRECATED_IOS(3_1_0, 3_1_5, "Use -[EMPluginVideoRecorder screenCaptureToFilePath:error:]");

/*!
 *  Start recording video
 *
 *  @param aPath            File saved path
 *  @param aError           Error
 
 *
 */
- (void)startVideoRecordingToFilePath:(NSString*)aPath
                                error:(EMError**)aError EM_DEPRECATED_IOS(3_1_0, 3_1_5, "Use -[EMPluginVideoRecorder startVideoRecordingToFilePath:error]");

/*!
 *  Stop recording video
 *
 *  @param aError           Error
 *
 */
- (NSString *)stopVideoRecording:(EMError**)aError EM_DEPRECATED_IOS(3_1_0, 3_1_5, "Use -[EMPluginVideoRecorder stopVideoRecording:]");

#pragma mark - EM_DEPRECATED_IOS < 3.2.0

/*!
 *  Get video delay time, in milliseconds, it's real time changed
 *
 *  @result The delay time
 */
- (int)getVideoTimedelay __deprecated_msg("Use -getVideoLatency");

/*!
 *  Get video frame rate, it's real time changed
 *
 *  @result The frame rate
 */
- (int)getVideoFramerate __deprecated_msg("Use -getVideoFrameRate");

/*!
 *  Get video package lost rate
 *
 *  @result Package lost rate
 */
- (int)getVideoLostcnt __deprecated_msg("Use -getVideoLostRateInPercent");

/*!
 *  Get snapshot of video
 *
 *  @param aFullPath  Save path of picture
 */
- (void)takeRemotePicture:(NSString *)aFullPath __deprecated_msg("Use -screenCaptureToFilePath:");

/*!
 *  Start recording video
 *
 *  @param  aPath    File save path
 */
- (BOOL)startVideoRecord:(NSString*)aPath __deprecated_msg("Use startVideoRecordingToFilePath:error:");

/*!
 *  Stop recording video
 *
 *  @result path of record file
 */
- (NSString *)stopVideoRecord __deprecated_msg("Use -stopVideoRecording:");

/*!
 *  Use front camera or back camera,default use front
 *
 *  @param  isFont    Weather use front camera or not,Yes is Front,No is Back
 */
- (void)setCameraBackOrFront:(BOOL)isFont __deprecated_msg("Use -switchCameraPosition:");


@end
