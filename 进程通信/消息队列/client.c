/*************************************************************************
	> File Name: client.c
	> Author: jack
	> Mail: hansheng.jiayou@qq.com 
	> Created Time: 2018-03-18 19:26:40
 ************************************************************************/

#include<stdio.h>
#include"message.h"
#include<unistd.h>
#include<stdlib.h>

int main(int argc, const char *argv[])
{
    
    int msgid = openMQ();
    if(msgid < 0)
    {
        printf("打开消息队列失败\n");
        exit(1);
    }
    char buf[1024];
    char out[2048];
    while(1)
    {
        printf("[client]:");
        fflush(stdout);
        ssize_t read_size = read(0,buf,sizeof(buf)-1);
        if(read_size < 0)
        {
            perror("read");
            continue;
        }
        else
        {

            buf[read_size] = '\0';
            if(sendMQ(msgid,SNDTYPE,buf) < 0)
            {
                printf("发送消息失败\n");
                continue;
            }
        }
        if(recvMQ(msgid,RCVTYPE,out) < 0)
        {
            printf("接受消息失败\n");
            continue;
        }
        else
            printf("[server]:%s\n",out);
    }
    return 0;
}
