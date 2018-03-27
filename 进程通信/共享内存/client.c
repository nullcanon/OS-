/*************************************************************************
  > File Name   : client.c
  > Author      : jack
  > Mail        : hansheng.jiayou@qq.com
  > Created Time: 2018年03月27日 星期二 14时56分46秒
 ************************************************************************/

#include"shared_men.h"
#include<unistd.h>

int main()
{
    int shmid = GetShm(4096);
    if(shmid < 0)
    {
       printf("GetShm  error\n");
       _exit(1);
    }
    char *addr = (char*)shmat(shmid,NULL,0);
    int i = 0;
    while(1)
    {
        addr[i] = 'A';
        addr[i+1] = '\0';
        ++i;
        sleep(1);
    }
    shmdt(addr);
    DestoryShm(shmid);
    return 0;
}



