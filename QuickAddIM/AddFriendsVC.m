//
//  AddFriendsVC.m
//  QuickAddIM
//
//  Created by edz on 2017/4/18.
//  Copyright © 2017年 edz. All rights reserved.
//

#import "AddFriendsVC.h"
#import "FriendTableViewCell.h"

@interface AddFriendsVC ()<UITableViewDelegate, UITableViewDataSource, UISearchBarDelegate>
@property (weak, nonatomic) IBOutlet UISearchBar *searchBar;
@property (weak, nonatomic) IBOutlet UITableView *tableView;

@property (strong, nonatomic) NSIndexPath *selectedIndexPath;
@property (nonatomic, copy) NSString *searchName;
@property (nonatomic, strong) NSMutableArray *addFriends;

@end

@implementation AddFriendsVC

- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.tableView.rowHeight = 50;
    self.tableView.separatorStyle = UIAccessibilityTraitNone;
    self.navigationItem.title = @"AddFriends";
    self.navigationItem.leftBarButtonItem = [[UIBarButtonItem alloc] initWithTitle:@"返回" style:UIBarButtonItemStylePlain target:self action:@selector(goBack)];
    
}
- (void)goBack
{
    [self.navigationController popViewControllerAnimated:YES];
}
- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}
#pragma mark - <UITableViewDataSource>
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return self.addFriends.count;
}
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    FriendTableViewCell *cell = [FriendTableViewCell friendTableViewCell:tableView];
    cell.friendName.text = self.addFriends[indexPath.row];
    cell.addFriendBlock = ^{
        
    dispatch_sync(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
        
        [self.searchBar resignFirstResponder];
        self.selectedIndexPath = indexPath;
        [self showMessageAlertView];
        
        });
    };
    return cell;
}

#pragma mark - <UITableViewDelegate>
- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    self.selectedIndexPath = indexPath;
    [self showMessageAlertView];
}
- (void)showMessageAlertView
{
    UIAlertView *alert = [[UIAlertView alloc] initWithTitle:nil
                                                    message:NSLocalizedString(@"saySomething", @"say somthing")
                                                   delegate:self
                                          cancelButtonTitle:NSLocalizedString(@"cancel", @"Cancel")
                                          otherButtonTitles:NSLocalizedString(@"ok", @"OK"), nil];
    [alert setAlertViewStyle:UIAlertViewStylePlainTextInput];
    [alert show];
}

- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex{
    if ([alertView cancelButtonIndex] != buttonIndex) {
        UITextField *messageTextField = [alertView textFieldAtIndex:0];
        
        NSString *messageStr = @"";
        NSString *username = [[EMClient sharedClient] currentUsername];
        if (messageTextField.text.length > 0) {
            messageStr = [NSString stringWithFormat:@"%@：%@", username, messageTextField.text];
        }
        else{
            messageStr = [NSString stringWithFormat:NSLocalizedString(@"friend.somebodyInvite", @"%@ invite you as a friend"), username];
        }
        [self sendFriendApplyAtIndexPath:self.selectedIndexPath
                                 message:messageStr];
    }
}
- (void)sendFriendApplyAtIndexPath:(NSIndexPath *)indexPath
                           message:(NSString *)message
{
    NSString *buddyName = [self.addFriends objectAtIndex:indexPath.row];
    if (buddyName && buddyName.length > 0) {
        [self showHudInView:self.view hint:NSLocalizedString(@"friend.sendApply", @"sending application...")];
        
        [[EMClient sharedClient].contactManager addContact:buddyName message:message completion:^(NSString *aUsername, EMError *aError) {
            [self hideHud];
            if (aError) {
                [self showHint:NSLocalizedString(@"friend.sendApplyFail", @"send application fails, please operate again")];
            }
            else{
                [self showHint:NSLocalizedString(@"friend.sendApplySuccess", @"send successfully")];
                
                // 添加好友
                [[YZDBTools sharedDBTools].queue inDatabase:^(FMDatabase *db) {
                    [db executeUpdate:@"insert into T_Friend (applicantUsername) values (?)", self.addFriends[indexPath.row]];
                    NSLog(@"新增好友成功");
                }];
                
                [self.navigationController popViewControllerAnimated:YES];
            }
        }];
    }
}
#pragma mark - <UISearchBarDelegate>
- (void)searchBarSearchButtonClicked:(UISearchBar *)searchBar
{
    NSLog(@"text -> %@", searchBar.text);
    if ([self.searchName isEqual:searchBar.text]) {
        return;
    }
    
    // 从服务器获取所有的好友
    [[EMClient sharedClient].contactManager getContactsFromServerWithCompletion:^(NSArray *aList, EMError *aError) {
        if (!aError) {
            NSLog(@"01从服务器获取所有的好友 -- %@",aList);
        }
    }];
    
//    NSArray *userlist = [[EMClient sharedClient].contactManager getContacts];
//    NSLog(@"02从数据库获取所有的好友 -- %@",userlist);
    
    [self.addFriends addObject:searchBar.text];
    [self.tableView reloadData];
    self.searchName = searchBar.text;
}

#pragma mark - 懒加载
- (NSMutableArray *)addFriends
{
    if (!_addFriends) {
        _addFriends = [NSMutableArray array];
    }
    return _addFriends;
}
@end
