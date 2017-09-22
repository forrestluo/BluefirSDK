//
//  BFReplayKitHandlerDelegate.h
//  BluefirSDK
//
//  Created by 罗明伟 on 2016/9/20.
//  Copyright © 2016年 Kunpo. All rights reserved.
//

#ifndef BFReplayKitHandlerDelegate_h
#define BFReplayKitHandlerDelegate_h

@class BFReplayKitHandler;
@class RPPreviewViewController;

@protocol BFReplayKitHandlerDelegate <NSObject>

@optional

/**
 当屏幕录制正常启动的时候，该方法会被调用。如果录屏按钮需要改变状态，你可以在这里进行操作。
 */
- (void)screenRecordingHasStarted;


/**
 当屏幕录制正常停止的时候，该方法会被调用。如果录屏按钮需要改变状态，你可以在这里进行操作。

 @param controller RPPreviewViewController实例，要展示本次录屏，你需要在需要的地方present这个viewController
 */
- (void)screenRecordingHasStopedWithPreviewController:(RPPreviewViewController *)controller;

/**
 当屏幕录制过程中出错，或者录制停止时出错，该方法会被调用。
 您在这个方法中，仅应该对录屏按钮的UI表现进行操作。错误的弹窗提示和Replaykit的响应的处理，在SDK中已经完成。
 */
- (void)screenRecordEncouteredAnError;

/**
 抛弃刚刚录制的视频成功后，会调用该方法。在该方法里，一般会处理你持有的RPPreviewViewController引用，将其置为nil。
 */
- (void)screenRecordDiscardSuccess;
@end

#endif /* BFReplayKitHandlerDelegate_h */
