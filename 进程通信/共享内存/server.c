/*************************************************************************
  > File Name   : server.c
  > Author      : jack
  > Mail        : hansheng.jiayou@qq.com
  > Created Time: 2018年03月27日 星期二 14时56分25秒
 ************************************************************************/

#include"shared_men.h"
#include<unistd.h>

int main()
{
    int shmid = CreateShm(4096);
    if(shmid < 0)
    {
       printf("CreateShm  error\n");
       _exit(1);
    }

    char* addr = (char*)shmat(shmid,NULL,0);
    while(1)
    {
        printf("[client]:%s\n",addr);
        sleep(1);
    }
    shmdt(addr);
    DestoryShm(shmid);
    return 0;
}
