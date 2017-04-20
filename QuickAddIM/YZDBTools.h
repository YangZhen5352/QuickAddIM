//
//  YZDBTools.h
//  QuickAddIM
//
//  Created by edz on 2017/4/18.
//  Copyright © 2017年 edz. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "FMDB.h"
#import "FMDatabaseQueue.h"

@interface YZDBTools : NSObject

+ (instancetype)sharedDBTools;
@property (nonatomic, strong) FMDatabaseQueue *queue;
@end
