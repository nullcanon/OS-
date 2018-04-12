#include<string.h>
#include<pthread.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

/**********************************创建线程************************************/

//创建一个新的线程
//int pthread_create(phread_t *thread,const ohread_attr_t,void*(*start_routine)(void*),void *arg)
//thread-返回线程id     attr-设置线程的属性,NULL表示默认属性
//start_routine-是个函数地址,线程启动后要执行的函数     arg-传给线程启动函数的参数


void *rout(void *arg)
{
    (void)arg;
    for(;;)
    {
        printf("I am thread 1\n");
        sleep(1);
    }
}

void Test1()
{
    pthread_t tid;
    int ret;
    if((ret=pthread_create(&tid,NULL,rout,NULL)) != 0)
    {
       fprintf(stderr,"pthread_create:%s\n",strerror(ret));
       _exit(1);
    }

    for(;;)
    {
        printf("I am main thread\n");
        sleep(1);
    }
}
/*********************************线程终止****************************************/
//进程终止有三个方法:
//1.从线程函数return。主线程的话直接从main函数返回
//2.线程可以调用pthread_exit终止自己
//3.一个线程可以调用pthread_cancel终止同一进程中的另一个进程
//void pthread_exit(void* value_ptr)--value_ptr不要指向它的局部变量
//int pthread_cancel(pthread_t thread)--thread线程id

void *rout1(void *arg)
{
    (void)arg;
    int i = 5;
    for(;i--;)
    {
        printf("I am thread 1\n");
        sleep(1);
    }
    return NULL;
}


void Test2()
{
    pthread_t tid;
    int ret;
    if((ret=pthread_create(&tid,NULL,rout1,NULL)) != 0)
    {
       fprintf(stderr,"pthread_create:%s\n",strerror(ret));
       _exit(1);
    }

    for(;;)
    {
        printf("I am main thread\n");
        sleep(1);
    }

}

/***************************************线程等待**********************************/
//已经退出的线程所申请的资源并没有释放
//创建新的线程不会复用原线程的空间
//通过线程等待来释放相应的资源
//int phread_join(pthread_t pthread,void** value_ptr)--value_ptr:指向一个指针，后者指向线程的返回值

void* thread1(void* arg)
{
    (void)arg;
    printf("Thread1 is runing\n");
    int* p = (int*)malloc(sizeof(int));
    *p = 1;
    return (void*)p;
}

void* thread2(void* arg)
{
    (void)arg;
    printf("Thread2 is runing\n");
    int* p = (int*)malloc(sizeof(int));
    *p = 2;
    pthread_exit((void*)p);
}

void* thread3(void* arg)
{
    (void)arg;
    while(1)
    {
        printf("Thread3 is runing\n");
        sleep(1);
    }
    return NULL;
}

void Test3()
{
    pthread_t tid;
    void* ret;

    //thread1 return
    pthread_create(&tid,NULL,thread1,NULL);
    pthread_join(tid,&ret);
    printf("Thread1 return,return ID:%X,retrun code:%d\n",(unsigned int)tid,*(int*)ret);
    free(ret);

    //thread2 exit
    pthread_create(&tid,NULL,thread2,NULL);
    pthread_join(tid,&ret);
    printf("Thread2 return,return ID:%X,retrun code:%d\n",(unsigned int)tid,*(int*)ret);
    free(ret);

    //thread3 cancal by other
    pthread_create(&tid,NULL,thread3,NULL);
    sleep(3);
    pthread_cancel(tid);
    pthread_join(tid,&ret);
    if(ret == PTHREAD_CANCELED)
        printf("Thread3 return,return ID:%X,retrun code:PTHREAD_CANCELED\n",(unsigned int)tid);
    else
        printf("Thread3 return,return ID:%X,retrun code:NULL\n",(unsigned int)tid);

}
/***********************************线程分离**************************************/
//默认情况下，新创建的线程是joinable的，线程退出后，需要对其进行pthread_join操作，否则无法释放资源
//如果不关心返回值，join是一种负担，可以告诉操作系统，线程退出时，自动释放资源
//int pthread_detach(pthread_t pthread);

void* thread4(void* arg)
{
    (void)arg;
    pthread_detach(pthread_self());
    printf("%s\n",(char*)arg);
    return NULL;
}

void Test4()
{
    pthread_t tid;

    if(pthread_create(&tid,NULL,thread4,"thread4 run...") != 0)
    {
        printf("thread4 create error\n");
        return;
    }
    sleep(1);
    if(pthread_join(tid,NULL)==0)
        printf("pthread whit success\n");
    else
        printf("pthread whit failed\n");
}
/*********************************************************************************/
int main()
{
    // Test1();
    // Test2();
    // Test3();
    Test4();
    return 0;
}

