//
//  HomeTabBarVC.h
//  QuickAddIM
//
//  Created by edz on 2017/4/18.
//  Copyright © 2017年 edz. All rights reserved.
//

#import <UIKit/UIKit.h>
//  图片文件
#define LOADIMAGE(file) [UIImage imageWithContentsOfFile:[[NSBundle mainBundle]pathForResource:file ofType:nil]]
//设置图片
#define SetTabBar(title, imgName, selectImgName) [[UITabBarItem alloc] initWithTitle:title image:[LOADIMAGE(imgName) imageWithRenderingMode:UIImageRenderingModeAlwaysOriginal] selectedImage:[LOADIMAGE(selectImgName) imageWithRenderingMode:UIImageRenderingModeAlwaysOriginal]]

#import "QuickNavVC.h"
#import "ChatsVC.h"
#import "Contacts.h"
#import "Settings.h"

@interface HomeTabBarVC : UITabBarController

@end
