//
//  BFShareDefines.h
//  BluefirSDK
//
//  Created by 罗明伟 on 16/7/7.
//  Copyright © 2016年 Kunpo. All rights reserved.
//

#ifndef BFShareDefines_h
#define BFShareDefines_h

typedef NS_ENUM(NSUInteger, BFShareResponseState){
    //开始
    BFShareResponseStateBegin      = 0,
    //成功
    BFShareResponseStateSuccess    = 1,
    //失败
    BFShareResponseStateFail       = 2,
    //取消
    BFShareResponseStateCancel     = 3
};

typedef NS_ENUM(NSUInteger, BFSharePlatformType){
    //未知
    BFSharePlatformTypeUnknown             = 0,
    //新浪微博
    BFSharePlatformTypeSinaWeibo           = 1,
    //腾讯微博
    BFSharePlatformTypeTencentWeibo        = 2,
    //豆瓣
    BFSharePlatformTypeDouBan              = 5,
    //QQ空间
    BFSharePlatformSubTypeQZone            = 6,
    //人人网
    BFSharePlatformTypeRenren              = 7,
    //开心网
    BFSharePlatformTypeKaixin              = 8,
    //Facebook
    BFSharePlatformTypeFacebook            = 10,
    //Twitter
    BFSharePlatformTypeTwitter             = 11,
    //印象笔记
    BFSharePlatformTypeYinXiang            = 12,
    //Google+
    BFSharePlatformTypeGooglePlus          = 14,
    //Instagram
    BFSharePlatformTypeInstagram           = 15,
    //LinkedIn
    BFSharePlatformTypeLinkedIn            = 16,
    //Tumblr
    BFSharePlatformTypeTumblr              = 17,
    //邮件
    BFSharePlatformTypeMail                = 18,
    //短信
    BFSharePlatformTypeSMS                 = 19,
    //打印
    BFSharePlatformTypePrint               = 20,
    //拷贝
    BFSharePlatformTypeCopy                = 21,
    //微信好友
    BFSharePlatformSubTypeWechatSession    = 22,
    //微信朋友圈
    BFSharePlatformSubTypeWechatTimeline   = 23,
    //QQ好友
    BFSharePlatformSubTypeQQFriend         = 24,
    //Instapaper
    BFSharePlatformTypeInstapaper          = 25,
    //Pocket
    BFSharePlatformTypePocket              = 26,
    //有道云笔记
    BFSharePlatformTypeYouDaoNote          = 27,
    //Pinterest
    BFSharePlatformTypePinterest           = 30,
    //Flickr
    BFSharePlatformTypeFlickr              = 34,
    //Dropbox
    BFSharePlatformTypeDropbox             = 35,
    //VKontakte
    BFSharePlatformTypeVKontakte           = 36,
    //微信收藏
    BFSharePlatformSubTypeWechatFav        = 37,
    //易信好友
    BFSharePlatformSubTypeYiXinSession     = 38,
    //易信朋友圈
    BFSharePlatformSubTypeYiXinTimeline    = 39,
    //易信收藏
    BFSharePlatformSubTypeYiXinFav         = 40,
    //明道
    BFSharePlatformTypeMingDao             = 41,
    //Line
    BFSharePlatformTypeLine                = 42,
    //WhatsApp
    BFSharePlatformTypeWhatsApp            = 43,
    //KaKao Talk
    BFSharePlatformSubTypeKakaoTalk        = 44,
    //KaKao Story
    BFSharePlatformSubTypeKakaoStory       = 45,
    //Facebook Messenger
    BFSharePlatformTypeFacebookMessenger   = 46,
    //支付宝好友
    BFSharePlatformTypeAliPaySocial        = 50,
    //易信
    BFSharePlatformTypeYiXin               = 994,
    //KaKao
    BFSharePlatformTypeKakao               = 995,
    //印象笔记国际版
    BFSharePlatformTypeEvernote            = 996,
    //微信平台,
    BFSharePlatformTypeWechat              = 997,
    //QQ平台
    BFSharePlatformTypeQQ                  = 998,
    //任意平台
    BFSharePlatformTypeAny                 = 999
};

#endif /* BFShareDefines_h */
