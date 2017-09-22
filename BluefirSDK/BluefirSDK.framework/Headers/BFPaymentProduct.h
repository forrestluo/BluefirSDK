//
//  BFPaymentProduct.h
//  BluefirSDK
//
//  Created by 罗明伟 on 16/5/24.
//  Copyright © 2016年 Kunpo. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSUInteger, BFIAPType) {
    BFIAPConsumable = 0,                 //消费型，比如游戏币，一次性道具，会反复购买
    BFIAPNonConsumable = 1,              //非消费型，只购买一次的商品，比如关卡解锁
    BFIAPAutoRenewableSubscription = 2,  //包月+自动续费
    BFIAPFreeSubscription = 3,           //免费订阅
    BFIAPNonRenewableSubscription = 4,   //包月+非自动续费
};

@interface BFPaymentProduct : NSObject <NSCoding>

@property (nonatomic, strong) NSString *productID;      //商品ID，在itunesconnect后台配置
@property (nonatomic, assign) BFIAPType productType;    //商品的iap类型
@property (nonatomic, strong) NSString *zoneID;         //游戏的区服
@property (nonatomic, strong) NSString *customMessage;  //要透传给游戏服务器的消息
@property (nonatomic, strong) NSString *callbackUrl;    //蓝飞支付平台服务器验证完支付后回调的服务器地址
@property (nonatomic, strong) NSString *orderID;        //蓝飞游戏支付平台创建的支付ID
@property (nonatomic, strong) NSString *receipt;        //苹果返回的校验用支付票据
@property (nonatomic, strong) NSString *transactionIdentifier; //苹果iAP支付生成的transactionID

+ (BFPaymentProduct *)productWithID:(NSString *)productId type:(BFIAPType)productType zoneID:(NSString *)zoneID customMessage:(NSString *)message callbackUrl:(NSString *)url;

@end
