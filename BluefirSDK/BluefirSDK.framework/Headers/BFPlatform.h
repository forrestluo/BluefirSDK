//
//  BFPlatform.h
//  BluefirSDK
//
//  Created by 罗明伟 on 16/4/20.
//  Copyright © 2016年 Kunpo. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "BFObserverDelegate.h"
#import "BFPaymentProduct.h"

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
#pragma mark - 界面相关
/**
 *  展示用户系统的集成交互界面，一般在游戏启动时调用(例如在application:didFinishLaunchingWithOptions:中调用)
 */
+ (void)showUserSystem;
/**
 *  设置游客模式（即：快速登录）页面的提示文字，默认文字为：
 *  敬爱的玩家，您正在使用游客模式进行游戏，游客模式下的游戏数据（包括付费数据）会在删除游戏、更换设备后清空，请尽快在
 *  游戏设置中绑定为正式账户，以保障您的账户安全。
 *
 *  如果希望自定义，则调用该方法设置；如想使用默认文字，则可以不去理会。
 *  @param hintString 您需要设置的提示文字，如果传入的为nil，则会使用默认提示语。
 */
+ (void)setGuestLoginHintString:(NSString *)hintString;

#pragma mark - 回调相关
/**
 *  设置回调代理
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

@end
