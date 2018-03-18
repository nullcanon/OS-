/*************************************************************************
	> File Name: message.c
	> Author: jack
	> Mail: hansheng.jiayou@qq.com 
	> Created Time: 2018-03-18 16:53:31
 ************************************************************************/

#include"message.h"

/**
 * @brief Creat 公共使用的创建消息队列的函数
 *
 * @return 失败返回小于0的数,成功返回一个大于0的数 
 */
static int Creat(int flags)
{
    key_t key = ftok(PATHNAME,PROJ_ID);
    if(key < 0)
    {
        perror("ftok");
        return -1;
    }
    int msgid = msgget(key,flags);    
    if(msgid < 0)
    {
        perror("msgget");
    }
    return msgid;
}


int creatMQ()
{
   return Creat(IPC_CREAT|IPC_EXCL|0666); 
}

int openMQ()
{
    return Creat(IPC_CREAT);
}

int destroyMQ(int msgid)
{
    if(msgctl(msgid,IPC_RMID,NULL)<0)
    {
        perror("msgctl");
        return -1;
    }
    return 0;
}

int sendMQ(int msgid,int send_type,char* msg)
{
   msBuf buf;
   buf.m_type = send_type;
   strcpy(buf.m_text,msg);
   if(msgsnd(msgid,(void*)&buf,sizeof(buf.m_text),0) < 0)
   {
       perror("msgsnd");
       return -1;
   }
   return 0;
}

int recvMQ(int msgid,int rec_type,char out[])
{
    msBuf buf;
    if(msgrcv(msgid,(void*)&buf,sizeof(buf.m_text),rec_type,0) < 0)
    {
        perror("msgrcv");
        return -1;
    }

    strcpy(out,buf.m_text);
    return 0;
}
