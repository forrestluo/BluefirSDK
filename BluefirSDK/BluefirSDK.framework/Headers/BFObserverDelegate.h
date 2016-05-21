//
//  BFObserverDelegate.h
//  BluefirSDK
//
//  Created by 罗明伟 on 16/5/12.
//  Copyright © 2016年 Kunpo. All rights reserved.
//

#ifndef BFObserverDelegate_h
#define BFObserverDelegate_h

#import "BFUserData.h"

@class BFObserver;

@protocol BFObserverDelegate <NSObject>

@required
- (void)loginNotify:(BFUserData *)userData;
- (void)shareNotify;
- (void)feedBackNotify;

@end

#endif /* BFObserverDelegate_h */
