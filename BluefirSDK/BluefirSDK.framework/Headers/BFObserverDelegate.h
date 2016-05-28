//
//  BFObserverDelegate.h
//  BluefirSDK
//
//  Created by 罗明伟 on 16/5/12.
//  Copyright © 2016年 Kunpo. All rights reserved.
//

#ifndef BFObserverDelegate_h
#define BFObserverDelegate_h

@class BFObserver;
@class BFUserData;
@class BFPaymentProduct;

@protocol BFObserverDelegate <NSObject>

@required
/**
 *  登录成功后会调用该回调，附带用户信息
 *
 *  @param userData 用户信息的类，详细请查看头文件
 */
- (void)loginNotify:(BFUserData *)userData;

@optional
- (void)shareNotify;
- (void)feedBackNotify;
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

@end

#endif /* BFObserverDelegate_h */
