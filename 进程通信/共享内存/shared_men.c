/*************************************************************************
  > File Name   : shared_men.c
  > Author      : jack
  > Mail        : hansheng.jiayou@qq.com
  > Created Time: 2018年03月27日 星期二 13时23分13秒
 ************************************************************************/

#include"shared_men.h"

static int commShm(int size,int flags)
{
    key_t key = ftok(PATHNAME,PROJ_ID);
    if(key < 0)
    {
        perror("ftok");
        return -1;
    }
    int shmid = 0;
    if((shmid = shmget(key,size,flags)) < 0)
    {
        perror("shmget");
        return -2;
    }
    return shmid;
}

int CreateShm(int size)
{
    return commShm(size,IPC_CREAT|IPC_EXCL|0666);
}

int GetShm(int size)
{
    return commShm(size,IPC_CREAT);
}

int DestoryShm(int shmid)
{
    if(shmctl(shmid,IPC_RMID,NULL) < 0)
    {
        perror("shmctl");
        return -1;
    }
    return 0;
}
