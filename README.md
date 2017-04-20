
- -(nullable NSArray<UITableViewRowAction *> *)tableView:(UITableView *)tableView editActionsForRowAtIndexPath:(NSIndexPath *)indexPath
{
    __weak __typeof(self)weakSelf = self;
    // 删除
    UITableViewRowAction *action1 = [UITableViewRowAction rowActionWithStyle:UITableViewRowActionStyleDestructive title:@"删除" handler:^(UITableViewRowAction * _Nonnull action, NSIndexPath * _Nonnull indexPath) {
        
        // 删除数据表中的数据
        FriendModel *fm = self.friends[indexPath.row];
        [weakSelf deleteFriend: fm.applicantUsername];
        
        // 更新数组中的数据
        weakSelf.friends = [self searchAllFriend];
        
        // 刷新列表
        [self.tableView deleteRowsAtIndexPaths:[NSArray arrayWithObject:indexPath]
                             withRowAnimation:UITableViewRowAnimationRight];
    }];
    // 置顶
    UITableViewRowAction *action2 = [UITableViewRowAction rowActionWithStyle:UITableViewRowActionStyleNormal title:@"置顶" handler:^(UITableViewRowAction * _Nonnull action, NSIndexPath * _Nonnull indexPath) {
        
        // 删除数据
        FriendModel *fm = self.friends[indexPath.row];
        [weakSelf deleteFriend: fm.applicantUsername];
        
        // 重新插入到顶端
        [self insertFriend:fm];
        
        // 更新数组中的数据
        weakSelf.friends = [self searchAllFriend];
        
        // 更新列表
        [self.tableView reloadData];
    }];
    
    return @[action1, action2];
}
