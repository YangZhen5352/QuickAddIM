//
//  HomeTabBarVC.m
//  QuickAddIM
//
//  Created by edz on 2017/4/18.
//  Copyright © 2017年 edz. All rights reserved.
//

#import "HomeTabBarVC.h"

@interface HomeTabBarVC ()

@end

@implementation HomeTabBarVC

- (void)viewDidLoad {
    [super viewDidLoad];
    
    [self setUpController:1];
}

- (void)setUpController:(NSInteger)index
{
    // 创建子控制器
    ChatsVC *chats = [[ChatsVC alloc] init];
    QuickNavVC *chatsNav = [[QuickNavVC alloc] initWithRootViewController:chats];
    chatsNav.tabBarItem = SetTabBar(@"Chats", @"tabbar_chats@2x.png", @"tabbar_chatsHL@2x.png");
    
    Contacts *contacts = [[Contacts alloc] init];
    QuickNavVC *contactsNav = [[QuickNavVC alloc] initWithRootViewController:contacts];
    contactsNav.tabBarItem = SetTabBar(@"Contacts", @"tabbar_contacts@2x.png", @"tabbar_contactsHL@2x.png");
    
    Settings *settings = [[Settings alloc] init];
    QuickNavVC *settingsNav = [[QuickNavVC alloc] initWithRootViewController:settings];
    settingsNav.tabBarItem = SetTabBar(@"Settings", @"tabbar_setting@2x.png", @"tabbar_settingHL@2x.png");
    // 添加控制器
    self.viewControllers = @[chatsNav, contactsNav, settingsNav];
    
    // 默认所选下角标
    self.selectedIndex = index;
    
    // 设置选中字体的颜色
    [[UITabBarItem appearance] setTitleTextAttributes:@{NSForegroundColorAttributeName:KTabBarTextColor,NSFontAttributeName:[UIFont systemFontOfSize:12]} forState:UIControlStateSelected];
    
    // 设置未选中字体的颜色
    [[UITabBarItem appearance] setTitleTextAttributes:@{NSForegroundColorAttributeName:KWhiteColor,NSFontAttributeName:[UIFont systemFontOfSize:12]} forState:UIControlStateNormal];
    
    // 设置底栏图片
    [[UITabBar appearance] setBackgroundImage:LOADIMAGE(@"Nav_bj@2x.jpg")];
}


@end
