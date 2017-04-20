//
//  SuperVC.m
//  QuickAddIM
//
//  Created by edz on 2017/4/18.
//  Copyright © 2017年 edz. All rights reserved.
//

#import "SuperVC.h"
#import "LoginViewController.h"

@interface SuperVC ()<EMClientDelegate>

@end

@implementation SuperVC

- (void)viewDidLoad {
    [super viewDidLoad];
    
    [[EMClient sharedClient] addDelegate:self];
    
    [self.navigationController.navigationBar setTitleTextAttributes:@{NSFontAttributeName:[UIFont systemFontOfSize:19], NSForegroundColorAttributeName:KWhiteColor}];
    
    [self.navigationController.navigationBar setBarTintColor:KTabBarTextColor];
    [self.navigationController.navigationBar setTintColor:KWhiteColor];
    
    UIButton *addButton = [[UIButton alloc] initWithFrame:CGRectMake(0, 0, 44, 44)];
    [addButton setImage:[UIImage imageNamed:@"add@2x.png"] forState:UIControlStateNormal];
    [addButton addTarget:self action:@selector(addFriendAction) forControlEvents:UIControlEventTouchUpInside];
    self.barButtonItem = [[UIBarButtonItem alloc] initWithCustomView:addButton];
    
}


- (void)addFriendAction
{
    if (self.rightItemClick) {
        self.rightItemClick();
    }
}

#pragma mark - <EMClientDelegate>
/*!
 *  Delegate method will be invoked when current IM account logged into another device
 *  当前登录账号在其它设备登录时会接收到该回调
 */
- (void)userAccountDidLoginFromOtherDevice
{
    
}

/*!
 *  Delegate method will be invoked when current IM account is removed from server
 *  当前登录账号已经被从服务器端删除时会收到该回调
 */
- (void)userAccountDidRemoveFromServer
{
    [[EMClient sharedClient] logout:YES completion:^(EMError *aError) {
        if (!aError) {
            UIWindow *window = [UIApplication sharedApplication].keyWindow;
            TTAlertNoTitle(@"退出登陆成功");
            LoginViewController *lg = [[LoginViewController alloc] init];
            window.rootViewController = lg;
        } else {
            
        }
    }];
}


@end
