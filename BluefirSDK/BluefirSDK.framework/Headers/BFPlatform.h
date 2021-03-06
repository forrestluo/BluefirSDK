//
//  BFPlatform.h
//  BluefirSDK
//
//  Created by 罗明伟 on 16/4/20.
//  Copyright © 2016年 Kunpo. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "BFObserverDelegate.h"
#import "BFPaymentProduct.h"
#import "BFShareDefines.h"
#import "BFReplayKitHandlerDelegate.h"

@interface BFPlatform : NSObject

/**
 属性，用来标识当前是否是单机游戏模式，YES - 单机，NO - 联网。默认值为NO。
 
 如果是单机模式，则silentLogin和guestLogin方法，在网络不通畅或者登录成功等情况下，都不会弹窗提示当前网络状态。
 */
@property (assign, nonatomic) BOOL isConsoleGame;

/**
 *  BFPlatform的单例类方法
 *
 *  @return 返回单例实体
 */
+ (instancetype)sharedBFPlatform;
#pragma mark - 基础
/**
 *  启动服务，在application:didFinishLaunchingWithOptions:中调用，用来进行相应的初始化和配置。
 *  ConfigDict中是三方平台的AppID和AppKey。如果要支持三方登录或者分享，该平台的AppID和Appkey（或AppSecret），需要包含在该字典中。
 *  如果不需要三方登录或者分享功能，则configDict可传入nil。
 *  例如：@{@"QQAppID":@"xxx", @"QQAppKey":@"xxx", @"WXAppID":@"xxx", @"WXAppKey":@"xxx"}
 */
+ (void)startWithConfigDict:(NSDictionary *)configDict;
/**
 *  获取当前蓝飞SDK的版本号
 *
 *  @return 版本号字符串
 */
+ (NSString *)sdkVersion;

+ (BOOL)handleOpenURL:(NSURL *)url;

#pragma mark - 基本信息
/**
 获取用户的基础信息，包括设备种类，系统版本，游戏版本等。
 返回的dictionary，其key请参见"BFPlatformBasicInfo.h"文件中的定义。
 
 @return 包含基础信息的字典。如果调用该方法时尚未登录，则用户系统相关的value，其值为空字符串。
 */
+ (NSDictionary *)getBasicUserInfo;
/**
 判断当前iOS设备是否为wifi网络连通的快捷方法

 @return Yes - wifi连接
 */
+ (BOOL)isWifiReachable;

/**
 返回当前的网络状态，无连接，wifi，还是WWAN

 @return BFNetworkReachableStatus枚举
 */
+(BFNetworkReachableStatus)currentNetworkStatus;

#pragma mark - 用户系统相关
/**
 *  展示用户系统的集成交互界面，一般在游戏启动时调用(例如在application:didFinishLaunchingWithOptions:中调用)
 */
+ (void)showUserSystem;
/**
 展示用户系统的集成交互界面，但是不提供快速游戏（游客登录）按钮。
 */
+ (void)showUserSystemWithoutGuestLogin;
/**
 *  展示绑定账号的UI，用来进行游客账号与正式账号的绑定操作，只会在游客登录的情况下显示。
 */
+ (void)showGuestAccountBindUI;
/**
 *  关闭当前展示的用户登录或者账号绑定界面
 */
+ (void)closeUIShowing;
/**
 *  设置游客模式（即：快速登录）页面的提示文字，默认文字为：
 *  敬爱的玩家，您正在使用游客模式进行游戏，游客模式下的游戏数据（包括付费数据）会在删除游戏、更换设备后清空，请尽快在
 *  游戏设置中绑定为正式账户，以保障您的账户安全。
 *
 *  如果希望自定义，则调用该方法设置；如想使用默认文字，则可以不去理会。
 *  @param hintString 您需要设置的提示文字，如果传入的为nil，则会使用默认提示语。
 */
+ (void)setGuestLoginHintString:(NSString *)hintString;
/**
 *  静默登录。
 *  该方法是个性化需求(爸爸去哪儿：全明星提出)，请在不展示登录交互UI的时候使用（不调用showUserSystem方法)。
 *  其流程为：如果上一次有登录，就用上一次登录的账号登录，如果没有登录过，则直接使用游客进行登录。如果上一次登录的账号，用户系统Token已过期，则重新走各种登录的登录流程
 */
+ (void)silentLogin;
/**
 *  不通过用户系统交互界面的游客登录方法
 */
+ (void)guestLogin;
/**
 *  退出登录当前账号，当退出登录成功后，会回调BFObserverDelegate协议中的方法logoutSuccess方法，作为通知。
 *  由于退出登录主要用于游戏平台记录用户行为，所以您可以选择采取调用该方法后不等待回调，立即返回登录界面，也可以
 *  在收到回调后再返回。
 */
+ (void)logout;
/**
 *  当前是不是游客账号登录的。
 *  如果游客登录后又绑定了其他三方账号，则当前登录方式已经从游客转化为选择的三方账号。
 *
 *  @return YES - 是游客登录；NO - 不是游客登录
 */
+ (BOOL)isGuestLogin;
/**
 *  使用指定的第三方账号来登录游戏并与当前游客账号进行绑定
 *
 *  @param theType 用户登录类型的枚举
 */
+ (void)bindGuestWithAccountType:(BFUDUserLoginType)theType;

#pragma mark - 回调相关
/**
 *  设置回调代理.SDK中的一些回调会通过该代理对象来传达。
 *
 *  @param delegateObject 采纳BFObserverDelegate协议的代理对象。
 */
+ (void)setObserverDelegate:(id<BFObserverDelegate>)delegateObject;

#pragma mark - 支付相关
/**
 *  开启或关闭iAP的SKPaymentQueue监听。
 *
 *  @param theSwitch YES-开启，NO-关闭。
 */
+ (void)enableIAPObserver:(BOOL)theSwitch;
/**
 *  调用支付功能，进行IAP支付
 *
 *  @param productId   商品ID，需在蓝飞游戏平台配置，与苹果IAP绑定（必填）
 *  @param productType 支付类型，具体参见BFIAPType枚举
 *  @param zoneId      游戏分区（必填）
 *  @param message     自定义的消息，最后会透传给游戏服务器（选填）
 *  @param url         支付验证完成后的服务器回调地址（选填）。如果没有填，则会以蓝飞支付平台后台配置的回调地址为准，如果填写了，则以填写的为准，一般在使用测试服时才填写该项，正式运营时建议不要使用该参数，接入者需保证蓝飞支付平台后台配置正确内容
 *  @param openId      用户登录后分配的openID
 *  @param isShow      是否显示HUD提示，显示的话会禁止UI上的触摸响应（YES的话您不用自己做UI提示），但由于iap支付期间苹果会自己弹出提示框，所以最好未收到支付完成回调前，还是手动屏蔽掉支付按钮的响应，以防用户反复点击
 */
+ (void)payWithProductId:(NSString *)productId
             productType:(BFIAPType)productType
                  zoneId:(NSString *)zoneId
           customMessage:(NSString *)message
             callbackUrl:(NSString *)url
              userOpenId:(NSString *)openId
                 showHud:(BOOL)isShow;
/**
 从AppStore获取产品信息，主要用于单机游戏在不同国家地区获取本地的价格、单位和描述。查询结果通过
 
 注意：由于上面的payWithProductId也会先查询商品信息，而网络请求可能有延迟，所以本方法最好不要和上述的支付方法同时使用，以免处理错误。
 @param productIDArray 一个NSArray，元素是待查询的
 */
+ (void)getInfoFromAppStoreForProducts:(NSArray *)productIDArray;
/**
 改变是否与服务器验证的设置，默认为需要与服务器验证。如果不需要随订单改变，则仅需要设置一次。

 @param validationOrNot YES - 需要支付验证；NO - 不需要支付验证
 */
+ (void)changePaymentValidationStatus:(BOOL)validationOrNot;
/**
 *  恢复内购，仅在您的游戏里付费点有非消费型或者订阅型时才有用
 *
 *  @param showHud 是否显示HUD提示，显示的话会禁止UI上的触摸响应（YES的话您不用自己做UI提示）
 */
+ (void)restoreProducts:(BOOL)showHud;
/**
 主动检查用户有没有通过Appstore点击跳转来进行应用内购买
 
 @return iAP的productID，如果为空，说明目前没有promotion的IAP等待支付
 */
+ (NSString *)checkPromotionPayment;
//支付可能需要支付的promotion IAP
+ (void)makePaymentForPromotionIAPIfNeeded:(NSString *)openID;

#pragma mark - Game Center相关
// ********* 说明 ************
// 对于有用户系统的蓝飞游戏平台来说，Gamecenter不是必须的，提供该接口的原因仅仅是为了满足个别需求。
// SDK提供的接口都是封装苹果的GameKit中的方法，如果不满足您的需求，您也可以自行使用GameKit。

/**
 *  GameCenter的一些UI展示需要基于游戏现有的ViewController，请在使用蓝飞SDK的GameCenter相关接口前调用该方法。
 *  本方法不会对传入的ViewController进行强引用，所以请务必保证在调用其他GameCenter相关接口期间，您设置的controller是有效的。
 *
 *  @param theVC 一般是您游戏目前使用的viewController
 */
+ (void)setupGameCenterUsedViewController:(UIViewController *)theVC;
/**
 *  授权，并获取Local Player对象，成功后会回调<BFObserverDelegate>中的gameCenterAuthenticatedWithLocalPlayer:方法
 */
+ (void)gameCenterAuthenticate;
/**
 *  为指定的排行报上报分数.上报如果失败，会回调<BFObserverDelegate>中的gameCenterScoreReportFailed方法
 *
 *  @param score         分数
 *  @param identifierStr 排行榜ID，您在itunesconnect后台配置的排行榜字符串
 */
+ (void)reportScore:(int64_t)score withLeaderboardID:(NSString *)identifierStr;
/**
 *  上传分数有可能失败，每一次提交失败的分数都会保存下来。如果失败，会收到回调gameCenterScoreReportFailed。选择选择合适的时候再次上传，调用该方法可再次上传之前提交失败了的分数。 如果使用GameCenter，建议每次进入游戏或者退出游戏的时候都调用一次该方法。
 */
+ (void)submitScoresFailedLastTime;
/**
 *  使用GKGameCenterViewController来显示指定ID的排行榜
 *
 *  @param leaderboardID 排行榜ID字符串
 */
+ (void)showLeaderBoard:(NSString *)leaderboardID;
/**
 *  上报成就，如果上报失败，会会回调<BFObserverDelegate>中的gameCenterReportFailedOfAchievementWithID:andPercentageNum:方法
 *
 *  @param identifier      成就ID
 *  @param percentComplete 成就进度，0.0~100.0之间
 */
+ (void)reportAchievment:(NSString *)identifier withPercentageComplete:(double)percentComplete;

#pragma mark - 内置浏览器
/**
 *  在内置浏览器中显示网页
 *
 *  @param url   要显示页面的URL地址
 *  @param theVC 要在哪个ViewController里显示
 */
+ (void)showBuiltInWebViewWithURL:(NSString *)url inViewController:(UIViewController *)theVC;

#pragma mark - 游戏内邮件

/**
 在游戏中用模态对话框来发送邮件，所有入参都不能为nil

 @param recipient 收件人，一般填公司客服邮箱
 @param subject 邮件标题
 @param content 邮件中要附加的正文
 */
+ (void)sendMailTo:(NSString *)recipient withSubject:(NSString *)subject andContent:(NSString *)content;

#pragma mark - 游戏属性相关
/**
 *  更新在线参数
 */
+ (void)updateOnlineParameters;
+ (NSDictionary *)getOnlineParameters;
+ (NSString *)getOnlineParameter:(NSString *)keyStr;

+ (void)updateAnnouncement;
+ (NSArray *)getAnnouncement;

#pragma mark - 分享相关
/**
 *  弹出分享菜单，进行分享
 *
 *  @param text                待分享的文本
 *  @param images              待分享的图片，传入参数可以为单张图片信息，也可以为一个NSArray，数组元素可以为UIImage、NSString（图片路径）、NSURL（图片路径）
 *  @param url                 网页路径/应用路径，如果为nil，则微信QQ上是大图分享
 *  @param title               分享标题
 *  @param itemArray           UI上显示的分享平台图标数组，数组元素为BFSharePlatformType定义枚举对应的int值所构成的NSNumber，例如[NSNumber numberWithUnsignedInteger:BFSharePlatformTypeSinaWeibo].如果为nil，则显示所有目前支持的平台
 */
+ (void)showShareViewWithText:(NSString *)text
                       images:(id)images
                          url:(NSURL *)url
                        title:(NSString *)title
                   shareItems:(NSArray *)itemArray;

/**
 *  无UI分享，针对某个平台直接进行分享
 *
 *  @param text                待分享的文本
 *  @param images              待分享的图片，传入参数可以为单张图片信息，也可以为一个NSArray，数组元素可以为UIImage、NSString（图片路径）、NSURL（图片路径）
 *  @param url                 网页路径/应用路径，如果为nil，则微信QQ上是大图分享
 *  @param title               分享标题
 *  @param platformType        将要分享到的平台，值为BFSharePlatformType的枚举，例如分享给微信好友，则传入BFSharePlatformSubTypeWechatSession
 */
+ (void)shareWithText:(NSString *)text
               images:(id)images
                  url:(NSURL *)url
                title:(NSString *)title
              shareTo:(BFSharePlatformType)platformType;
#pragma mark - ReplayKit封装
/**
 判断当前是否支持replayKit功能。
 
 本SDK不提供录屏按钮的UI，需要各游戏自己根据UI来放置。由于有些设备不支持Replaykit，或者由于正在使用AirPlay或TV-out功能，replaykit会不可用，因此各游戏应当根据本方法来处理录屏按钮的显示状态。

 @return YES - 支持；NO - 不支持
 */
- (BOOL)screenRecordAvailable;
/**
 启动屏幕录制。
 
 屏幕录制功能使用ReplayKit，支持iOS9及以上系统，A7及以上芯片的设备。不符合条件的设备，调用该方法，则没有作用。
 */
- (void)startScreenRecord;

/**
 停止屏幕录制。
 
 屏幕录制停止后，代理方法中的screenRecordingHasStopedWithPreviewController:会被调用，返回一个RPPreviewViewController实例。您可以持有该实例的引用，在需要给用户展示刚刚录屏内容时，使用presentViewController:animated:completion:方法，modal的展示这个viewController，在这个controller里，用户可以查看录屏视频，保存，分享。
 */
- (void)stopScreenRecord;

/**
 放弃本次录屏。
 
 在不需要刚刚录制的视频时，可以调用该方法，用来放弃上次录屏内容。代理方法中会有相关的回调，如果您在停止录屏时，持有了RPPreviewViewController的引用，可以在回调中进行相关回收处理。
 */
- (void)discardScreenRecord;

/**
 配置录屏功能的代理对象

 @param theDelegate 符合BFReplayKitHandlerDelegate协议的代理对象
 */
- (void)setupScreenRecordDelegate:(id<BFReplayKitHandlerDelegate>)theDelegate;

#pragma mark - 统计相关
/**
 自定义事件。最简调用，只需传入事件ID。
 事件时间为调用时间，事件计数为1。

 @param eventID 用来区分事件的ID，整数类型。
 */
- (void)event:(NSInteger)eventID;
/**
 自定义事件。需传入事件ID和事件计数

 @param eventID 用来区分事件的ID，整数类型。
 @param count 用来记录事件的计数，整数类型。
 */
- (void)event:(NSInteger)eventID counter:(NSInteger)count;
/**
 自定义事件。需传入事件ID，事件标签，以及事件计数。

 @param eventID 用来区分事件的ID，整数类型。
 @param eventLabel 用来区分同一ID下不同事件的标签，字符串类型。
 @param count 用来记录事件的计数，整数类型。
 */
- (void)event:(NSInteger)eventID withLabel:(NSString *)eventLabel counter:(NSInteger)count;
/**
 自定义事件。需传入事件ID，事件标签，事件计数，以及额外描述信息的。

 @param eventID 用来区分事件的ID，整数类型。
 @param eventLabel 用来区分同一ID下不同事件的标签，字符串类型。
 @param count 用来记录事件的计数，整数类型。
 @param infoDict 详细的描述信息，字典类型，key只能为字符串，value只能为数字或字符串。
 */
- (void)event:(NSInteger)eventID withLabel:(NSString *)eventLabel counter:(NSInteger)count extraInfo:(NSDictionary *)infoDict;
/**
 自定义事件。需传入事件ID，事件标签，事件计数，额外描述信息，以及需要事件发生的时间。（由于绝大多数情况下，都是在事件发生时就调用来进行统计，所以本方法只应在事件时间需要特别指定时调用。）

 @param eventID 用来区分事件的ID，整数类型。
 @param eventLabel 用来区分同一ID下不同事件的标签，字符串类型。
 @param count 用来记录事件的计数，整数类型。
 @param infoDict 详细的描述信息，字典类型，key只能为字符串，value只能为数字或字符串。
 @param eventDate 事件的发生时间，NSDate类型。
 */
- (void)event:(NSInteger)eventID withLabel:(NSString *)eventLabel counter:(NSInteger)count extraInfo:(NSDictionary *)infoDict andDate:(NSDate *)eventDate;

@end
