//
//  FriendTableViewCell.m
//  QuickAddIM
//
//  Created by edz on 2017/4/18.
//  Copyright © 2017年 edz. All rights reserved.
//

#import "FriendTableViewCell.h"

@implementation FriendTableViewCell

- (void)awakeFromNib {
    [super awakeFromNib];
    
    
}
- (IBAction)addFriend:(id)sender {
    if (self.addFriendBlock) {
        self.addFriendBlock();
    }
}

+ (instancetype)friendTableViewCell:(UITableView *)tableView
{
    FriendTableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"FriendTableViewCell"];
    if (!cell) {
        cell = LoadNib(@"FriendTableViewCell");
    }
    tableView.separatorStyle = UITableViewCellSeparatorStyleNone;
    cell.selectionStyle = UITableViewCellSelectionStyleNone;
    
    return cell;
}
- (void)setSelected:(BOOL)selected animated:(BOOL)animated {
    [super setSelected:selected animated:animated];

    // Configure the view for the selected state
}


@end
