/*!
 *  @header EMCallEnum.h
 *  @abstract Enum
 *  @author Hyphenate
 *  @version 3.00
 */

#ifndef EMCallEnum_h
#define EMCallEnum_h

/*!
 *  Call session status
 */
typedef enum{
    EMCallSessionStatusDisconnected = 0,    /*!  Disconnected */
    EMCallSessionStatusConnecting,          /*!  It's ready, wait to answer */
    EMCallSessionStatusConnected,           /*!  Connection is established */
    EMCallSessionStatusAccepted,            /*!  Accepted */
}EMCallSessionStatus;

typedef EMCallSessionStatus EMCallStatus;

/*!
 *  Call type
 */
typedef enum{
    EMCallTypeVoice = 0,    /*!  Voice call */
    EMCallTypeVideo,        /*!  Video call */
}EMCallType;

/*!
 *  Call end reason
 */
typedef enum{
    EMCallEndReasonHangup   = 0,    /*!  Another peer hang up */
    EMCallEndReasonNoResponse,      /*!  No response */
    EMCallEndReasonDecline,         /*!  Another peer declined the call */
    EMCallEndReasonBusy,            /*!  User is busy */
    EMCallEndReasonFailed,          /*!  Establish the call failed */
    EMCallEndReasonUnsupported,     /*!  Unsupported */
    EMCallEndReasonRemoteOffline,   /*!  Remote offline */
}EMCallEndReason;

/*!
 *  Connection type of the call
 */
typedef enum{
    EMCallConnectTypeNone = 0,  /*!  None */
    EMCallConnectTypeDirect,    /*!   Direct connect */
    EMCallConnectTypeRelay,     /*!  Relay connect */
}EMCallConnectType;


/*!
 *  Call status
 */
typedef enum{
    EMCallStreamStatusVoicePause = 0,  /*!  Pause voice streaming */
    EMCallStreamStatusVoiceResume,     /*!  Resume voice streaming */
    EMCallStreamStatusVideoPause,      /*!  Pause video streaming */
    EMCallStreamStatusVideoResume,     /*!  Resume video streaming */
}EMCallStreamingStatus;

/*!
 *  Network status
 */
typedef enum{
    EMCallNetworkStatusNormal = 0,  /*!  Normal */
    EMCallNetworkStatusUnstable,    /*!  Unstable */
    EMCallNetworkStatusNoData,      /*!  No data */
}EMCallNetworkStatus;

#ifndef EM_SCALEASPECT_DEFINE
#define EM_SCALEASPECT_DEFINE
/*!
 *  Video view scale mode
 */
typedef enum{
    EMCallViewScaleModeAspectFit = 0,   /*!  Aspect fit */
    EMCallViewScaleModeAspectFill = 1,  /*!  Aspect fill */
}EMCallViewScaleMode;
#endif

/*!
 *  Video resolution
 */
typedef enum{
    EMCallVideoResolutionAdaptive = 0,   /*!  Adaptive resolution */
    EMCallVideoResolution352_288,       /*!  352 * 288 */
    EMCallVideoResolution640_480,       /*!  640 * 480 */
    EMCallVideoResolution1280_720,      /*!  1280 * 720 */
}EMCallVideoResolution;


#pragma mark - EM_DEPRECATED_IOS
/*!
 *  Stream control
 */
typedef enum{
    EMCallStreamControlTypeVoicePause __deprecated_msg("Use EMCallStreamStatusVoicePause") = 0,  /*!  Pause Voice */
    EMCallStreamControlTypeVoiceResume __deprecated_msg("Use EMCallStreamStatusVoiceResume"),     /*!  Resume Voice */
    EMCallStreamControlTypeVideoPause __deprecated_msg("Use EMCallStreamStatusVideoPause"),      /*!  Pause Video */
    EMCallStreamControlTypeVideoResume __deprecated_msg("Use EMCallStreamStatusVideoResume"),     /*!  Resume Video */
}EMCallStreamControlType __deprecated_msg("Use EMCallStreamingStatus");


#endif /* EMCallEnum_h */
