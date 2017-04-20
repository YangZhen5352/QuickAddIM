//
//  YZDBTools.m
//  QuickAddIM
//
//  Created by edz on 2017/4/18.
//  Copyright © 2017年 edz. All rights reserved.
//

#import "YZDBTools.h"

@implementation YZDBTools
// 1. 全局的单里
+ (instancetype)sharedDBTools {
    
    static YZDBTools *tools;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        tools = [[self alloc] init];
    });
    return tools;
}
// 2. 初始化数据库
- (instancetype)init
{
    self = [super init];
    if (self) {
        NSString *dbPath = [[NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) lastObject] stringByAppendingPathComponent:@"readme.db"];
        
        NSLog(@"dbPath = %@", dbPath);
        self.queue = [[FMDatabaseQueue alloc] initWithPath:dbPath];
        [self createTables];
    }
    return self;
}
// 3. 创建数据表
/*
 applicantUsername;
 @property (nonatomic, strong) NSString * applicantNick; 申请人的状态
 @property (nonatomic, strong) NSString * reason; 申请理由
 @property (nonatomic, strong) NSString * receiverUsername; 接收人的用户名
 @property (nonatomic, strong) NSString * receiverNick; 接收人的状态
 @property (nonatomic, strong) NSNumber * style; 类型
 @property (nonatomic, strong) NSString * groupId; 组的id
 @property (nonatomic, strong) NSString * groupSubject; 组名称
 )"

 */
- (void)createTables {
    [self.queue inTransaction:^(FMDatabase *db, BOOL *rollback) {
        
        BOOL result = NO;
        result = [db executeUpdate: @"CREATE TABLE IF NOT EXISTS T_Friend ("
                  "friendID integer PRIMARY KEY AUTOINCREMENT,"
                  "applicantUsername text not null,"
                  "receiverUsername text,"
                  "reason text,"
                  "applicantNick text,"
                  "receiverNick text,"
                  "style text,"
                  "groupId text,"
                  "groupSubject text,"
                  "create_date timestamp default current_timestamp"
                  ");"];
        if (!result) {
            NSLog(@"创建数据表失败");
            *rollback = YES;
            return ;
        }
        NSLog(@"创建数据表完成");
    }];
}

@end
