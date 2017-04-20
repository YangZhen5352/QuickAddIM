//
//  FriendTableViewCell.h
//  QuickAddIM
//
//  Created by edz on 2017/4/18.
//  Copyright © 2017年 edz. All rights reserved.
//

#import <UIKit/UIKit.h>

typedef void (^AddFriendBlock)();
@interface FriendTableViewCell : UITableViewCell

@property (nonatomic, copy) AddFriendBlock addFriendBlock;
@property (weak, nonatomic) IBOutlet UIImageView *friendIcon;
@property (weak, nonatomic) IBOutlet UILabel *friendName;
@property (weak, nonatomic) IBOutlet UIButton *addButton;


+ (instancetype)friendTableViewCell:(UITableView *)tableView;
@end
