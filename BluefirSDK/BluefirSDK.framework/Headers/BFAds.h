//
//  BFAds.h
//  BluefirSDK
//
//  Created by 罗明伟 on 16/7/5.
//  Copyright © 2016年 Kunpo. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSUInteger, BFAdsProviderType) {
    BFAdsProviderChance = 0,        //畅思广告, v6.3.0
    BFAdsProviderJoying = 1,        //有米（也就是掌盈）广告, v4.1.3 (支持https)
    BFAdsProviderChartboost = 2,    //Chartboost, v6.6.0 (支持https)
    BFAdsProviderVungle,            //Vungle, 通过cocoaPods引入最新版本 (支持https)
    BFAdsProviderDomod              //多盟, v3.5.2 (支持https)
};

@protocol BFAdsDelegate <NSObject>

@optional
/**
 *  目前无法播放视频广告，可能是因为暂时已经没有视频可以播放了，也可能是因为网络问题
 *
 *  @param providerType BFAdsProviderType枚举类型，用来区分广告提供商
 */
- (void)canNotPlayVideoAdsNowForProvider:(BFAdsProviderType)providerType;
/**
 *  视频广告没能播放完成，多数情况是由于玩家取消了
 *
 *  @param providerType BFAdsProviderType枚举类型，用来区分广告提供商
 */
- (void)failedOfVideoAdsForProvider:(BFAdsProviderType)providerType;
/**
 *  成功播放完毕视频广告，游戏端应该考虑在这里给玩家以相应奖励
 *
 *  @param providerType BFAdsProviderType枚举类型，用来区分广告提供商
 */
- (void)successOfVideoAdsForProvider:(BFAdsProviderType)providerType;

/**
 目前无法弹出插屏广告，主要是由于广告设置没有初始化成功造成。

 @param providerType BFAdsProviderType枚举类型，用来区分广告提供商
 */
- (void)canNotPopInterstitialAdsForProvider:(BFAdsProviderType)providerType;
/**
 插屏广告没能成功弹出

 @param providerType BFAdsProviderType枚举类型，用来区分广告提供商
 */
- (void)failedOfInterstitialAdsForProvider:(BFAdsProviderType)providerType;

/**
 插屏广告弹出成功

 @param providerType BFAdsProviderType枚举类型，用来区分广告提供商
 */
- (void)successOfInterstitialAdsForProvider:(BFAdsProviderType)providerType;

@end

@interface BFAds : NSObject

/**
 *  符合BFAdsDelegate协议的代理对象
 */
@property (weak, nonatomic) id<BFAdsDelegate> delegate;

/**
 *  单例
 *
 *  @return 单例
 */
+ (instancetype)sharedInstance;
/**
 *  根据在info.plist文件中填写的各广告平台配置数据，进行初始化
 */
- (void)setupAndStart;
/**
 *  展示指定广告提供商的视频广告
 *
 *  @param providerType BFAdsProviderType枚举类型，用来区分广告提供商
 */
- (void)showVideoAdOfProvider:(BFAdsProviderType)providerType;
/**
 展示指定广告提供商的插屏广告（当前只支持畅思的插屏广告）

 @param providerType BFAdsProviderType枚举类型，用来区分广告提供商
 */
- (void)showInterstitialAdOfProvider:(BFAdsProviderType)providerType;

@end
