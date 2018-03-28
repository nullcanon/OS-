/*************************************************************************
  > File Name   : test_sem.c
  > Author      : jack
  > Mail        : hansheng.jiayou@qq.com
  > Created Time: 2018年03月28日 星期三 12时27分08秒
 ************************************************************************/

//预期结果,A和B成对打印
//例如: AA BB 

#include<stdio.h>
#include<unistd.h>
#include"semaphore.h"
#include<sys/wait.h>

int main()
{
    int semid = CreateSemSet(1);
    InitSem(semid,0,1);
    pid_t id = fork();

    if(0 == id)
    {
        //child
        int _semid = GetSemSet(0);
        while(1)
        {
            P(_semid,0);
            printf("A");
            fflush(stdout);
            usleep(1000000);
            printf("A ");
            fflush(stdout);
            usleep(1000000);
            V(_semid,0);
        }
    }
    else
    {
        //father
        while(1)  
        {
            P(semid,0);
            printf("B");
            fflush(stdout);
            usleep(1000000);
            printf("B ");
            fflush(stdout);
            usleep(1000000);
            V(semid,0);
        }
        wait(NULL);
    }
    Destory(semid);
    return 0;
}

