//
//  HNetworkManager.h
//  helpdesk_sdk
//
//  Created by afanda on 16/11/23.
//  Copyright © 2016年 hyphenate. All rights reserved.
//

#import <Foundation/Foundation.h>
@class LeaveMsgRequestBody;
@interface HLeaveMsgManager : NSObject

+(instancetype)shareInstance;


/*
 @method
 @brief 获取客服工作状态
 @param tenantId    客服tenantId
 */
- (void)getWorkStatusWithTenantId:(NSString *)tenantId
                       completion:(void(^)(BOOL isWork,NSError *error))completion;

/*
 @method
 @brief 创建一个留言
 @discussion 失败返回NSError,成功返回responseObject
 @param tenantId    客服tenantId
 @param projectId   留言的Project ID
 @param cname       im服务号
 @param requestBody 留言参数
 @result
 */
- (void)asyncCreateMessageWithTenantId:(NSString*)tenantId
                             projectId:(NSString*)projectId
                                 cname:(NSString *)cname
                           requestBody:(LeaveMsgRequestBody *)requestBody
                            completion:(void(^)(id responseObject,NSError *error))completion;
/*
 @method
 @brief 获取留言详情
 @discussion 失败返回NSError,成功返回responseObject
 @param tenantId    客服tenantId
 @param projectId   留言的Project ID
 @param cname       im服务号
 @param tickedId    留言ID
 @result
 */
- (void)asyncGetLeaveMessageDetailWithTenantId:(NSString*)tenantId
                                     projectId:(NSString*)projectId
                                         cname:(NSString *)cname
                                      ticketId:(NSString*)ticketId
                                    completion:(void(^)(id responseObject,NSError *error))completion;

/*
 @method
 @brief 获取留言下所有评论
 @discussion 失败返回NSError,成功返回responseObject
 @param tenantId    客服tenantId
 @param projectId   留言的Project ID
 @param cname       im服务号
 @param tickedId    留言ID
 @param page        参数
 @param pageSize    每页数据数目
 @result
 */
- (void)asyncGetLeaveMessageAllCommentsWithTenantId:(NSString*)tenantId
                                          projectId:(NSString*)projectId
                                              cname:(NSString *)cname
                                           ticketId:(NSString *)ticketId
                                               page:(NSUInteger)page
                                           pageSize:(NSUInteger)pageSize
                                         completion:(void(^)(id responseObject,NSError *error))completion;

/*
 @method
 @brief 给一个留言添加评论
 @discussion 失败返回NSError,成功返回responseObject
 @param tenantId    客服tenantId
 @param projectId   留言的Project ID
 @param cname       im服务号
 @param tickedId    留言ID
 @param requestBody  请求体
 @result
 */
- (void)asyncLeaveMessageCommentWithTenantId:(NSString*)tenantId
                                   projectId:(NSString*)projectId
                                       cname:(NSString *)cname
                              ticketId:(NSString *)ticketId
                            requestBody:(LeaveMsgRequestBody*)requestBody
                            completion:(void(^)(id responseObject,NSError *error))completion;


/*
 @method
 @brief 获取留言列表
 @discussion 失败返回NSError,成功返回responseObject
 @param tenantId    客服tenantId
 @param cname       IM 服务号
 @param projectId   留言的Project ID
 @param page        第几页
 @param pageSize    每页的数据
 @result
 */
- (void)asyncGetMessagesWithTenantId:(NSString*)tenantId
                           projectId:(NSString*)projectId
                               cname:(NSString *)cname
                                page:(NSInteger)page
                            pageSize:(NSInteger)pigeSize
                          completion:(void(^)(id responseObject,NSError *error))completion;


/*
 @method
 @brief 上传附件
 @discussion 失败返回NSError,成功返回responseObject
 @param tenantId    客服tenantId
 @param file        附件
 @param parameters  参数
 @result
 */
- (void)uploadWithTenantId:(NSString*)tenantId
                      File:(NSData*)file
                parameters:(NSDictionary*)parameters
                completion:(void(^)(id responseObject,NSError *error))completion;

/*
 下载文件
 */

- (void)downloadFileWithUrl:(NSString *)url completionHander:(void (^)(BOOL success,NSURL *filePath,NSError *error))completion;



@end


typedef NS_ENUM(NSUInteger, AttachmentType) {
    AttachmentTypeImage = 1,    //图片
    AttachmentTypeFile, //文件
    AttachmentTypeAudio,    //声音
};

@interface LeaveMsgAttachment : NSObject

@property (nonatomic, copy) NSString *name; //附件名称
@property (nonatomic, copy) NSString *url;  //附件url
@property (nonatomic, assign) AttachmentType type; //附件类型

- (NSDictionary *)getContent;

@end

@interface Creator : NSObject
@property (nonatomic,copy) NSString* name;   //访客名称
@property (nonatomic,copy) NSString* avatar; //访客头像【可选】
@property (nonatomic,copy) NSString* email;  //访客email
@property (nonatomic,copy) NSString* phone;  //访客电话
@property (nonatomic,copy) NSString* qq; //访客QQ
@property (nonatomic,copy) NSString* companyName; //公司
@property (nonatomic,copy) NSString* desc;   //备注

// - - - - - - - 回复评论特有 - - - - - - -
@property(nonatomic,copy) NSString *identity; //可选。创建这个评论的人的id

- (NSDictionary *)getContent;
@end

typedef enum : NSUInteger {
    Status_1=0, //未处理
    Status_2,    //处理中
    Status_3, //已处理
} Status;

@interface  LeaveMsgRequestBody: NSObject

@property(nonatomic,copy) NSString *subject;    //留言的主题 【可选】
@property(nonatomic,copy) NSString *content;    //留言的主要内容

//回复评论的时候,设置了这个属性的话, 可以在添加评论的时候同时设置这个ticket的状态, 只有agent(访客)能够调用
@property(nonatomic,assign) Status status;     //留言默认处理状态【可选】
@property(nonatomic,copy) NSString *priority;   //优先级别【可选】
@property(nonatomic,copy) NSString *category;   //类别【可选】

@property(nonatomic,strong) Creator *creator;   //创建者信息
@property(nonatomic,copy) NSArray <LeaveMsgAttachment *> *attachments; //附件 【可选】

//回复评论特有【可选项】
@property(nonatomic,copy) NSString *replyId; //回复那条评论的id

- (NSDictionary *)getContent;

@end







