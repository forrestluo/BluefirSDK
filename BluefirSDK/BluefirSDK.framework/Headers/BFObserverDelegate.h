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

@class BFObserver;
@class BFUserData;
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
 *  退出登录成功时会执行该回调。
 *  如果您使用用户系统提供的登录界面，可以在退出登录后再调用[BFPlatform showUserSystem]显示登录界面
 */
- (void)logoutSuccess;

@optional
#pragma mark - 反馈回调
- (void)feedBackNotify;

#pragma mark - 分享回调
- (void)shareCallbackWithState:(BFShareResponseState)state forPlatform:(BFSharePlatformType)platformType maybeError:(NSError *)error;

#pragma mark - iap回调
/**
 *  当一笔iap支付完成时，本回调会被调用。蓝飞游戏平台SDK的支付部分，客户端SDK在与苹果完成交互，并提交验证票据给蓝飞支付平台后，即会调用该方法，支付验证结果，会由蓝飞支付平台通知游戏服务器，或者由游戏服务器通过相应查询接口进行结果查询（可能需要轮询）。
 *  收到该回调后，游戏客户端可以提示用户支付正在完成，请等待发货，然后当游戏服务器确认该笔订单校验通过后，再进行发货和提示用户支付完成
 *
 *  @param product 支付的商品，BFPaymentProduct对象
 */
- (void)iapPaymentFinishedWithProduct:(BFPaymentProduct *)product;
- (void)iapPaymentFailedWithHint:(NSString *)hintString;
- (void)iapRestoreFinishedWithProductIDs:(NSArray *)productIDArray;
- (void)iapRestoreFailedWithError:(NSError *)error;
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
