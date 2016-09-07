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

@interface BFPlatform : NSObject
/**
 *  BFPlatform的单例类方法
 *
 *  @return 返回单例实体
 */
+ (instancetype)sharedBFPlatform;
#pragma mark - 基础
/**
 *  启动服务，在application:didFinishLaunchingWithOptions:中调用，用来进行相应的初始化和配置
 */
+ (void)start;
/**
 *  获取当前蓝飞SDK的版本号
 *
 *  @return 版本号字符串
 */
+ (NSString *)sdkVersion;

#pragma mark - 基本信息
/**
 获取用户的基础信息，包括设备种类，系统版本，游戏版本等。
 返回的dictionary，其key请参见"BFPlatformBasicInfo.h"文件中的定义。
 
 @return 包含基础信息的字典。如果调用该方法时尚未登录，则用户系统相关的value，其值为空字符串。
 */
+ (NSDictionary *)getBasicUserInfo;

#pragma mark - 用户系统相关
/**
 *  展示用户系统的集成交互界面，一般在游戏启动时调用(例如在application:didFinishLaunchingWithOptions:中调用)
 */
+ (void)showUserSystem;
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
 *  设置回调代理.SDK中所有回调都会通过该代理对象来传达。
 *
 *  @param delegateObject 采纳BFObserverDelegate协议的代理对象。
 */
+ (void)setObserverDelegate:(id<BFObserverDelegate>)delegateObject;

#pragma mark - 支付相关
/**
 *  调用支付功能，进行IAP支付
 *
 *  @param productId   商品ID，需在蓝飞游戏平台配置，与苹果IAP绑定（必填）
 *  @param productType 支付类型，具体参见BFIAPType枚举
 *  @param zoneId      游戏分区（必填）
 *  @param message     自定义的消息，最后会透传给游戏服务器（选填）
 *  @param url         支付验证完成后的服务器回调地址（选填）。如果没有填，则会以蓝飞支付平台后台配置的回调地址为准，如果填写了，则以填写的为准，一般在使用测试服时才填写该项，正式运营时建议不要使用该参数，接入者需保证蓝飞支付平台后台配置正确内容
 *  @param isShow      是否显示HUD提示，显示的话会禁止UI上的触摸响应（YES的话您不用自己做UI提示），但由于iap支付期间苹果会自己弹出提示框，所以最好未收到支付完成回调前，还是手动屏蔽掉支付按钮的响应，以防用户反复点击
 */
+ (void)payWithProductId:(NSString *)productId
             productType:(BFIAPType)productType
                  zoneId:(NSString *)zoneId
           customMessage:(NSString *)message
             callbackUrl:(NSString *)url
                 showHud:(BOOL)isShow;
/**
 *  恢复内购，仅在您的游戏里付费点有非消费型或者订阅型时才有用
 *
 *  @param showHud 是否显示HUD提示，显示的话会禁止UI上的触摸响应（YES的话您不用自己做UI提示）
 */
+ (void)restoreProducts:(BOOL)showHud;

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

#pragma mark - 游戏属性相关
/**
 *  更新在线参数
 */
+ (void)updateOnlineParameters;
+ (NSDictionary *)getOnlineParameters;
+ (NSString *)getOnlineParameter:(NSString *)keyStr;

#pragma mark - 分享相关
/**
 *  弹出分享菜单，进行分享
 *
 *  @param text                待分享的文本
 *  @param images              待分享的图片，传入参数可以为单张图片信息，也可以为一个NSArray，数组元素可以为UIImage、NSString（图片路径）、NSURL（图片路径）
 *  @param url                 网页路径/应用路径
 *  @param title               分享标题
 *  @param itemArray           UI上显示的分享平台图标数组，数组元素为BFSharePlatformType定义枚举对应的int值所构成的NSNumber，例如[NSNumber numberWithUnsignedInteger:BFSharePlatformTypeSinaWeibo].如果为nil，则显示所有目前支持的平台
 */
+ (void)showShareViewWithText:(NSString *)text
                       images:(id)images
                          url:(NSURL *)url
                        title:(NSString *)title
                   shareItems:(NSArray *)itemArray;
@end
