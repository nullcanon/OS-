/*************************************************************************
	> File Name: server.c
	> Author: jack
	> Mail: hansheng.jiayou@qq.com 
	> Created Time: 2018-03-18 19:01:43
 ************************************************************************/
#include"message.h"
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main(int argc, const char *argv[])
{
    int msgid = creatMQ();
    if(msgid < 0)
    {
        printf("创建消息队列失败！\n");
        exit(1);
    }
    char buf[2048];
    while(1)
    {
       if( recvMQ(msgid,RCVTYPE,buf) < 0)
       {
           printf("接受消息失败\n");
           continue;
       }
       printf("[client]:%s\n",buf);

       ssize_t read_size = read(0,buf,sizeof(buf)-1);
       if(read_size > 0)
       {
            //服务器接受到消息后向客户端回复
            if(sendMQ(msgid,SNDTYPE,buf) < 0)
            {
                printf("回复消息失败\n");
                continue;
            }
        
       }
        printf("[server]:");
        fflush(stdout);
    }
    destroyMQ(msgid);
    return 0;
}
