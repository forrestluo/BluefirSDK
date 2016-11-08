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
    BFAdsProviderJoying = 1,        //掌盈广告, v3.0.6
    BFAdsProviderChartboost = 2,    //Chartboost, v6.4.6
    BFAdsProviderVungle,            //Vungle, v4.0.6
    BFAdsProviderDomod              //多盟, v3.3.5
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
 *  展示指定广告提供商的广告
 *
 *  @param providerType BFAdsProviderType枚举类型，用来区分广告提供商
 */
- (void)showVideoAdOfProvider:(BFAdsProviderType)providerType;
@end
