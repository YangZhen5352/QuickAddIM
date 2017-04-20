//
//  SuperVC.h
//  QuickAddIM
//
//  Created by edz on 2017/4/18.
//  Copyright © 2017年 edz. All rights reserved.
//

#import <UIKit/UIKit.h>

typedef void (^RightItemClick)();

@interface SuperVC : UIViewController

@property (nonatomic, copy) RightItemClick rightItemClick;
@property (nonatomic, strong) UIBarButtonItem *barButtonItem;
@end
