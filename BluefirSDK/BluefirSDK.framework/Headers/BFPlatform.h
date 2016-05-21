//
//  BFPlatform.h
//  BluefirSDK
//
//  Created by 罗明伟 on 16/4/20.
//  Copyright © 2016年 Kunpo. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "BFObserverDelegate.h"

@interface BFPlatform : NSObject
/**
 *  BFPlatform的单例类方法
 *
 *  @return 返回单例实体
 */
+ (instancetype)sharedBFPlatform;
/**
 *  展示用户系统的集成交互界面，一般在游戏启动时调用
 */
- (void)showUserSystem;
/**
 *  设置回调代理
 *
 *  @param delegateObject 采纳BFObserverDelegate协议的代理对象。
 */
- (void)setObserverDelegate:(id<BFObserverDelegate>)delegateObject;
/**
 *  设置游客模式（即：快速登录）页面的提示文字，默认文字为：
 *  敬爱的玩家，您正在使用游客模式进行游戏，游客模式下的游戏数据（包括付费数据）会在删除游戏、更换设备后清空，请尽快在
 *  游戏设置中绑定为正式账户，以保障您的账户安全。
 *
 *  如果希望自定义，则调用该方法设置；如想使用默认文字，则可以不去理会。
 *  @param hintString 您需要设置的提示文字，如果传入的为nil，则会使用默认提示语。
 */
- (void)setGuestLoginHintString:(NSString *)hintString;

@end
