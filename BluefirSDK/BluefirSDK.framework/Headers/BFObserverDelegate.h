//
//  BFObserverDelegate.h
//  BluefirSDK
//
//  Created by 罗明伟 on 16/5/12.
//  Copyright © 2016年 Kunpo. All rights reserved.
//

#ifndef BFObserverDelegate_h
#define BFObserverDelegate_h

#import "BFShareDefines.h"
#import "BFUserData.h"

typedef NS_ENUM(NSInteger, BFNetworkReachableStatus) {
    BFNetworkNotReachable = 0,
    BFNetworkReachableViaWiFi,
    BFNetworkReachableViaWWAN
};

@class BFObserver;
//@class BFUserData;
@class BFPaymentProduct;
@class GKLocalPlayer;

@protocol BFObserverDelegate <NSObject>

@required
#pragma mark - 用户系统的登录回调
/**
 *  登录成功后会调用该回调，附带用户信息
 *
 *  @param userData 用户信息的类，详细请查看头文件
 */
- (void)loginNotify:(BFUserData *)userData;
/**
 *  静默登录接口，登录失败后会回调该方法，附带当前使用的登录类型
 *  使用SDK自带UI进行登录的失败情况，不需要用户自行处理，因此该回调只针对静默登录接口生效
 *
 *  @param loginType 登录类型，详见枚举定义
 */
- (void)loginFailedNotifyWithType:(BFUDUserLoginType)loginType;
/**
 *  退出登录成功时会执行该回调。
 *  如果您使用用户系统提供的登录界面，可以在退出登录后再调用[BFPlatform showUserSystem]显示登录界面
 */
- (void)logoutSuccess;
/**
 *  第三方账号和游客号绑定成功的回调
 */
- (void)thirdPartyAccountBindSuccess:(BFUserData *)user;
/**
 *  第三方账号和游客号绑定失败的回调
 */
- (void)thirdPartyAccountBindFailed;
/**
 *  蓝飞用户系统注册用户（手机或邮箱）和游客账号绑定成功
 */
- (void)bluefirAccountBindSuccess:(BFUserData *)user;
/**
 *  蓝飞用户系统注册用户（手机或邮箱）和游客账号绑定失败
 */
- (void)bluefirAccountBindFailed;
@optional

#pragma mark - 设备的网络状态发生变化的回调
/**
 该回调在网络状态发生变化时将被调用

 @param networkStatus 枚举：BFNetworkNotReachable - 无网络，BFNetworkReachableViaWiFi - wifi，BFNetworkReachableViaWWAN - 移动网络
 @param isRequire YES - 设备连着WWAN或Wifi，但需要建立连接后网络才可用，NO - wifi或WWAN时直接可以访问互联网，无网络时该值也为NO。
 */
- (void)networkStatusChanged:(BFNetworkReachableStatus)networkStatus requiredConnection:(BOOL)isRequire;

#pragma mark - 反馈回调
- (void)feedBackNotify;

#pragma mark - 分享回调
- (void)shareCallbackWithState:(BFShareResponseState)state forPlatform:(BFSharePlatformType)platformType maybeError:(NSError *)error;

#pragma mark - iap回调
/**
 支付完成但是尚未和服务器进行票据验证时的回调

 @param product 支付的商品，BFPaymentProduct对象
 */
- (void)iapPaymentCompletedButNotVerifyYetWithProduct:(BFPaymentProduct *)product;
/**
 *  当一笔iap支付完成时，本回调会被调用。蓝飞游戏平台SDK的支付部分，客户端SDK在与苹果完成交互，并提交验证票据给蓝飞支付平台后，即会调用该方法，支付验证结果，会由蓝飞支付平台通知游戏服务器，或者由游戏服务器通过相应查询接口进行结果查询（可能需要轮询）。
 *  收到该回调后，游戏客户端可以提示用户支付正在完成，请等待发货，然后当游戏服务器确认该笔订单校验通过后，再进行发货和提示用户支付完成
 *
 *  @param product 支付的商品，BFPaymentProduct对象
 */
- (void)iapPaymentFinishedWithProduct:(BFPaymentProduct *)product;
/**
 支付本身失败的回调，还未进行支付验证

 @param product 支付的商品，BFPaymentProduct对象
 @param hintString 提示文字
 */
- (void)iapPaymentFailedWithProduct:(BFPaymentProduct *)product andHint:(NSString *)hintString;
/**
 支付验证失败

 @param product 支付的商品，BFPaymentProduct对象
 @param errorCode 错误码
                    "-99995"：支付票据为空；
                    "-99996"：订单ID为空；
                    "-99997"：没能收到正确的验证Response；
                    "-99998"：验证网络超时；
                    "-99999"：支付服务器故障，返回值不对；
                    其他：SDK支付服务器返回的错误码
 */
- (void)iapPaymentVerifyFailedWithProduct:(BFPaymentProduct *)product andErrorCode:(NSString *)errorCode;
/**
 通过getInfoFromAppStoreForProducts方法获取商品数据（以得到本地化商品信息），成功后的回调

 @param productArray 一个数组，数组中的每个元素都是SKProduct
 */
- (void)iapGetInfoFromAppStoreSuccessWithProducts:(NSArray *)productArray;

/**
 通过getInfoFromAppStoreForProducts方法获取商品数据失败，未能拿到有效数据，通常是因为查询的productID不对。

 @param errorProductIDs 错误的productID组成的数组
 */
- (void)iapGetInfoFromAppStoreFailedWithProductIDs:(NSArray *)errorProductIDs;
/**
 恢复内购成功的回调

 @param productIDArray 一个数组，包含了所有恢复内购成功商品的product Id
 */
- (void)iapRestoreFinishedWithProductIDs:(NSArray *)productIDArray;
/**
 恢复内购失败的回调

 @param error 失败信息
 */
- (void)iapRestoreFailedWithError:(NSError *)error;

//仅在iOS11及以上会调用
- (void)appstorePromotionIAPTriggered;
#pragma mark - Game Center回调
/**
 *  已经登录Gamecenter，并成功拿到授权的本地player对象
 *
 *  @param localPlayer GKLocalPlayer对象，本地Player，可以从中获取当前玩家的昵称头像等信息
 */
- (void)gameCenterAuthenticatedWithLocalPlayer:(GKLocalPlayer *)localPlayer;
/**
 *  gameCenter授权失败，不可用的通知
 */
- (void)gameCenterAuthenticatedFailed;
/**
 *  玩家在游戏过程中切换到gamecenter app，将账号切换了
 *
 *  @param newLocalPlayer 切换后的local player对象
 */
- (void)gameCenterHasChangedLocalPlayer:(GKLocalPlayer *)newLocalPlayer;
/**
 *  玩家在游戏过程中切换到gamecenter app，将账号注销登录了
 */
- (void)gameCenterPlayerHasLogout;
/**
 *  上传分数的操作失败了，需要调用BFPlatform中的+(void)submitScoresFailedLastTime方法，来重新上传所有之前失败了的分数。
 */
- (void)gameCenterScoreReportFailed;
/**
 *  上报成就失败后的回调
 *
 *  @param achievementID 透传回来的上报成就的ID字符串
 *  @param number        透传回来的上报成就的百分比数值
 */
- (void)gameCenterReportFailedOfAchievementWithID:(NSString *)achievementID andPercentageNum:(double)number;
@end

#endif /* BFObserverDelegate_h */
