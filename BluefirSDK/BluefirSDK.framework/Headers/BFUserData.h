//
//  BFUserData.h
//  BluefirSDK
//
//  Created by 罗明伟 on 16/5/11.
//  Copyright © 2016年 Kunpo. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSUInteger, BFUDUserLoginType) {
    BFUDUserLoginTypeUserName = 0,
    BFUDUserLoginTypeGuest = 1,
    BFUDUserLoginTypeQQ = 2,
    BFUDUserLoginTypeWechat = 3,
    BFUDUserLoginTypeWeibo = 4,
    BFUDUserLoginTypeFacebook = 5,
    BFUDUserLoginTypeTwitter = 6
};

@interface BFUserData : NSObject <NSCoding>

@property (strong, nonatomic) NSString *accessToken;           //用户系统交互使用的Token
@property (strong, nonatomic) NSDate *expiresDate;             //和用户系统交互的Token过期时间
@property (strong, nonatomic) NSString *userId;                //用户的识别短号
@property (strong, nonatomic) NSString *email;                 //用户的电子邮箱
@property (strong, nonatomic) NSString *phoneNumber;           //用户的手机号码
@property (strong, nonatomic) NSString *nickName;              //昵称
@property (strong, nonatomic) NSString *headerImgUrl;          //用户头像的链接地址
@property (strong, nonatomic) NSString *idCard;                //身份证号
@property (strong, nonatomic) NSString *realName;              //用户的真实姓名
@property (strong, nonatomic) NSString *gender;                //用户的性别
//当前登录时候使用的UserName，可能是手机，可能是邮箱，如果是游客则为--BFSDKLocalizedString(@"游客", @"")，如果是三方登录，则为”渠道_昵称或号码“
@property (strong, nonatomic) NSString *currentLoginUserName;
@property (assign, nonatomic) BFUDUserLoginType loginType;    //用户登录使用的账号类型

@end
