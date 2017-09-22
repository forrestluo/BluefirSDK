//
//  BFPlatformBasicInfo.h
//  BluefirSDK
//
//  Created by 罗明伟 on 2016/9/6.
//  Copyright © 2016年 Kunpo. All rights reserved.
//

#ifndef BFPlatformBasicInfo_h
#define BFPlatformBasicInfo_h

// BFPlatform中有一个getBasicUserInfo方法，返回一个NSDictionary，里面信息的key在下面定义。
static NSString * const kBFBasicInfoUserOpenId = @"kBFBasicInfoUserOpenId";                 //当前登录用户的OpenID
static NSString * const kBFBasicInfoUserAccessToken = @"kBFBasicInfoUserAccessToken";       //当前登录用户的用户系统AccessToken

static NSString * const kBFBasicInfoClientVersion = @"kBFBasicInfoClientVersion";           //客户端的版本号
static NSString * const kBFBasicInfoHardwareType = @"kBFBasicInfoHardwareType";             //硬件型号
static NSString * const kBFBasicInfoOsVersion = @"kBFBasicInfoOsVersion";                   //iOS软件版本
static NSString * const kBFBasicInfoTelecomOperator = @"kBFBasicInfoTelecomOperator";       //电信运营商信息
static NSString * const kBFBasicInfoNetworkType = @"kBFBasicInfoNetworkType";               //网络类型 - 2G、3G、4G、Wifi、无服务
static NSString * const kBFBasicScreenWidthPixel = @"kBFBasicScreenWidthPixel";             //屏幕分辨率 - 宽度
static NSString * const kBFBasicScreenHeightPixel = @"kBFBasicScreenHeightPixel";           //屏幕分辨率 - 高度
static NSString * const kBFBasicScreenScale = @"kBFBasicScreenScale";                       //像素密度 - 1.0：非retina；2.0：retina(1个点4个像素)
static NSString * const kBFBasicDeviceId = @"kBFBasicDeviceId";                             //设备唯一识别码


#endif /* BFPlatformBasicInfo_h */
