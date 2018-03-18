/*************************************************************************
	> File Name: message.h
	> Author: jack
	> Mail: hansheng.jiayou@qq.com 
	> Created Time: 2018-03-18 16:41:36
 ************************************************************************/

#pragma once
#include<sys/types.h>
#include<sys/msg.h>
#include<sys/ipc.h>
#include<stdio.h>
#include<string.h>

#define SNDTYPE 1 //发送类型
#define RCVTYPE 0 //接收类型

#define PATHNAME "."
#define PROJ_ID 01

typedef struct msBuf
{
    long m_type;
    char m_text[1024];
}msBuf;

/**
 * @brief creatMQ 创建一个消息队列
 *
 * @return 成功返回msgid,失败返回-1
 */
int creatMQ();

/**
 * @brief openMQ 打开一个消息队列
 *
 * @return 成功返回msgid,失败返回-1
 */
int openMQ();

/** * @brief destroyMQ 销毁消息队列 
 *
 *
 * @return 成功返回0，失败返回-1
*/ 
int destroyMQ(int msgid); 

/** * @brief sendMQ 通过消息队列发送消息
 *
 * @return 成功返回0，失败返回-1
 */
int sendMQ(int msgid,int send_type,char* msg);

/**
 * @brief recvMQ 从消息队列中接受信息
 * @参数 out 存储接受到的字符串
 * @return 成功返回0，失败返回-1
 */
int recvMQ(int msgid,int rec_type,char out[]);
