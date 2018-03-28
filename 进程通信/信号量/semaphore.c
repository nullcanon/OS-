/*************************************************************************
  > File Name   : semaphore.c
  > Author      : jack
  > Mail        : hansheng.jiayou@qq.com
  > Created Time: 2018年03月27日 星期二 20时59分10秒
 ************************************************************************/

#include"semaphore.h"

static int commSem(int nums,int flags)
{
    key_t key = ftok(PATHNAME,PROJ_ID);
    if(key < 0)
    {
        perror("ftok");
        return -1;
    }
    int semid = semget(key,nums,flags);
    if(semid < 0)
    {
        perror("semget");
        return -2;
    }
    return semid;
}

int CreateSemSet(int nums)
{
    return commSem(nums,IPC_CREAT|IPC_EXCL|0666);
}

int GetSemSet(int nums)
{
    return commSem(nums,IPC_CREAT);
}


int InitSem(int semid,int nums,int initVal)
{
    union semun _un;
    _un.val = initVal;
    if(semctl(semid,nums,SETVAL,_un) < 0)
    {
        perror("semctl");
        return -1;
    }
    return 0;
}

static int commPV(int semid,int who,int op)
{
    struct sembuf _sf;
    _sf.sem_num = who;
    _sf.sem_op = op;
    _sf.sem_flg = 0;
    if(semop(semid,&_sf,1) < 0)
    {
        perror("semop");
        return -1;
    }
    return 0;
}

int P(int semid,int who)
{
    return commPV(semid,who,-1);
}

int V(int semid,int who)
{
    return commPV(semid,who,1);
}
