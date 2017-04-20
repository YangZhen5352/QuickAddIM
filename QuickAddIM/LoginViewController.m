//
//  LoginViewController.m
//  QuickAddIM
//
//  Created by edz on 2017/4/17.
//  Copyright © 2017年 edz. All rights reserved.
//

#import "LoginViewController.h"

#import "KeychainTool.h"
#import "HomeTabBarVC.h"

// 保存账户和密码的key
#define UsernameTextField @"usernameTextField"
#define PasswordTextField @"passwordTextField"

@interface LoginViewController ()<UITextFieldDelegate>

@property (weak, nonatomic) IBOutlet UITextField *usernameTextField;
@property (weak, nonatomic) IBOutlet UITextField *passwordTextField;
@property (weak, nonatomic) IBOutlet UIButton *registerButton;
@property (weak, nonatomic) IBOutlet UIButton *loginButton;

- (IBAction)doRegister:(id)sender;
- (IBAction)doLogin:(id)sender;
- (IBAction)doExit:(id)sender;


@end

@implementation LoginViewController

@synthesize usernameTextField = _usernameTextField;
@synthesize passwordTextField = _passwordTextField;
@synthesize registerButton = _registerButton;
@synthesize loginButton = _loginButton;


- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
}

// /Users/edz/Desktop/神灯房产_QuickAddIM/QuickAddIM/QuickAddIM/LoginViewController.m:42:51: No visible @interface for 'EMClient' declares the selector 'registerWithUsername:password:'
- (void)dismissRegister {
    [_usernameTextField resignFirstResponder];
    [_passwordTextField resignFirstResponder];
}
- (IBAction)doRegister:(id)sender
{
    [self dismissRegister];
    __weak typeof(self) weakself = self;
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
        [[EMClient sharedClient] registerWithUsername:weakself.usernameTextField.text password:weakself.passwordTextField.text completion:^(NSString *aUsername, EMError *aError) {
            if (!aError) {
                
                TTAlertNoTitle(@"注册成功！");
                // 保存账户和密码
                [KeychainTool saveKeychainValue:weakself.usernameTextField.text key:UsernameTextField];
                [KeychainTool saveKeychainValue:weakself.passwordTextField.text key:PasswordTextField];
                
            } else {
                switch (aError.code) {
                    case EMErrorServerNotReachable:
                        TTAlertNoTitle(NSLocalizedString(@"error.connectServerFail", @"Connect to the server failed!"));
                        break;
                    case EMErrorUserAlreadyExist:
                        TTAlertNoTitle(NSLocalizedString(@"register.repeat", @"You registered user already exists!"));
                        break;
                    case EMErrorNetworkUnavailable:
                        TTAlertNoTitle(NSLocalizedString(@"error.connectNetworkFail", @"No network connection!"));
                        break;
                    case EMErrorServerTimeout:
                        TTAlertNoTitle(NSLocalizedString(@"error.connectServerTimeout", @"Connect to the server timed out!"));
                        break;
                    case EMErrorServerServingForbidden:
                        TTAlertNoTitle(NSLocalizedString(@"servingIsBanned", @"Serving is banned"));
                        break;
                    default:
                        TTAlertNoTitle(NSLocalizedString(@"register.fail", @"Registration failed"));
                        break;
                }
            }
        }];
    });
}
- (IBAction)doLogin:(id)sender
{
    [self dismissRegister];
    
    __weak typeof(self) weakself = self;
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
//        EMError *error = [[EMClient sharedClient] loginWithUsername:username password:password];
        [[EMClient sharedClient] loginWithUsername:weakself.usernameTextField.text password:weakself.passwordTextField.text completion:^(NSString *aUsername, EMError *aError) {
            dispatch_async(dispatch_get_main_queue(), ^{
                
                if (!aError) {
                    //设置是否自动登录
                    [[EMClient sharedClient].options setIsAutoLogin:YES];
                    
                    // 登陆成功
                    TTAlertNoTitle(@"登陆成功");
                    [[MBProgressHUD alloc] showAnimated:YES];
                    // 跳转到首页控制器
                    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(2.0 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
                        
                        [[MBProgressHUD alloc] hideAnimated:YES];
                        UIWindow *window = [UIApplication sharedApplication].keyWindow;
                        HomeTabBarVC *mainVc = [[HomeTabBarVC alloc] init];
                        window.rootViewController = mainVc;
                    });
                    
                } else {
                    switch (aError.code)
                    {
                        case EMErrorUserNotFound:
                            TTAlertNoTitle(NSLocalizedString(@"error.usernotExist", @"User not exist!"));
                            break;
                        case EMErrorNetworkUnavailable:
                            TTAlertNoTitle(NSLocalizedString(@"error.connectNetworkFail", @"No network connection!"));
                            break;
                        case EMErrorServerNotReachable:
                            TTAlertNoTitle(NSLocalizedString(@"error.connectServerFail", @"Connect to the server failed!"));
                            break;
                        case EMErrorUserAuthenticationFailed:
                            TTAlertNoTitle(aError.errorDescription);
                            break;
                        case EMErrorServerTimeout:
                            TTAlertNoTitle(NSLocalizedString(@"error.connectServerTimeout", @"Connect to the server timed out!"));
                            break;
                        case EMErrorServerServingForbidden:
                            TTAlertNoTitle(NSLocalizedString(@"servingIsBanned", @"Serving is banned"));
                            break;
                        default:
                            TTAlertNoTitle(NSLocalizedString(@"login.fail", @"Login failure"));
                            break;
                    }
                }
            });
        }];
    });
}

- (IBAction)doExit:(id)sender {
    
    [[EMClient sharedClient] logout:YES completion:^(EMError *aError) {
        if (!aError) {
            TTAlertNoTitle(@"退出登陆成功");
        } else {
            
        }
    }];
}

#pragma mark - <UITextFieldDelegate>
- (void)textFieldDidEndEditing:(UITextField *)textField
{
    
}

@end
