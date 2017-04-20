//
//  Contacts.m
//  QuickAddIM
//
//  Created by edz on 2017/4/18.
//  Copyright © 2017年 edz. All rights reserved.
//

#import "Contacts.h"
#import "AddFriendsVC.h"
#import "FriendTableViewCell.h"
#import "FriendModel.h"

@interface Contacts ()<UITableViewDataSource, UITableViewDelegate>
@property (weak, nonatomic) IBOutlet UITableView *tableView;

@property (nonatomic, strong) NSMutableArray *friends;

@end

@implementation Contacts

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    // 查询数据库中所有的好友
    self.friends = [self searchAllFriend];
    [self.tableView reloadData];
}

// 查询所有
- (NSMutableArray *)searchAllFriend
{
    NSMutableArray *arr = [NSMutableArray array];
    [[YZDBTools sharedDBTools].queue inDatabase:^(FMDatabase *db) {
        
        // order by create_date desc
        // 按照时间戳的降序进行排列
        NSString *sql = @"select * from T_Friend order by create_date desc;";
        FMResultSet *rs = [db executeQuery:sql];
        while ([rs next]) {
            FriendModel *fm = [[FriendModel alloc] init];
            fm.friendId = [rs stringForColumn:@"friendId"];
            fm.applicantUsername = [rs stringForColumn:@"applicantUsername"];
            fm.applicantNick = [rs stringForColumn:@"applicantNick"];
            fm.reason = [rs stringForColumn:@"reason"];
            
            fm.receiverUsername = [rs stringForColumn:@"receiverUsername"];
            fm.receiverNick = [rs stringForColumn:@"receiverNick"];
            fm.style = [rs stringForColumn:@"style"];
            fm.groupId = [rs stringForColumn:@"groupId"];
            fm.groupSubject = [rs stringForColumn:@"groupSubject"];
            [arr addObject:fm];
        }
    }];
    return arr;
}
// 删除
- (void)deleteFriend:(NSString *)applicantUsername
{
    NSLog(@"01---> %ld", [self searchAllFriend].count);
    [[YZDBTools sharedDBTools].queue inDatabase:^(FMDatabase *db) {
        
        BOOL operaResult = [db executeUpdate:@"DELETE FROM T_Friend WHERE applicantUsername=?",applicantUsername];
        NSLog(@"delete-operaResult -> %d", operaResult);
        
    }];
    NSLog(@"02---> %ld", [self searchAllFriend].count);
}
// 插入
- (void)insertFriend:(FriendModel *)fm
{
    [[YZDBTools sharedDBTools].queue inDatabase:^(FMDatabase *db) {
        BOOL operaResult = [db executeUpdate:@"INSERT INTO T_Friend (applicantUsername, applicantNick, reason, receiverUsername, receiverNick, style, groupId, groupSubject) VALUES (?,?,?,?,?,?,?,?)",fm.applicantUsername, fm.applicantNick, fm.reason, fm.receiverUsername, fm.receiverNick, fm.style, fm.groupId, fm.groupSubject];
        NSLog(@"insert-operaResult -> %d", operaResult);
    }];
}
- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.tableView.separatorStyle = UIAccessibilityTraitNone;
    self.tableView.rowHeight = 55;
    self.navigationItem.title = @"Contacts";
    
    self.navigationItem.rightBarButtonItem = self.barButtonItem;
    __weak __typeof(self)weakSelf = self;
    self.rightItemClick = ^{
        AddFriendsVC *addVC = [[AddFriendsVC alloc] init];
        [weakSelf.navigationController pushViewController:addVC animated:YES];
    };
}

#pragma mark - <UITableViewDataSource>
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return self.friends.count;
}
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    FriendTableViewCell *cell = [FriendTableViewCell friendTableViewCell:tableView];
    FriendModel *fm = self.friends[indexPath.row];
    
    cell.friendName.text = fm.applicantUsername;
    cell.addButton.hidden = YES;
    
    return cell;
}
#pragma mark - <UITableViewDelegate>
- (nullable NSArray<UITableViewRowAction *> *)tableView:(UITableView *)tableView editActionsForRowAtIndexPath:(NSIndexPath *)indexPath
{
    __weak __typeof(self)weakSelf = self;
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


- (NSMutableArray *)friends
{
    if (!_friends) {
        _friends = [NSMutableArray array];
    }
    return _friends;
}

@end
