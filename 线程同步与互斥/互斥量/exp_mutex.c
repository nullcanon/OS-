//////////////////////////////////////////////////////////////////////////////
// 互斥量接口:                                                              //
// 初始化互斥量:int pthread_mutex_init(pthread_mutex_t* restrict mutex,     //
//                          const pthread_mutexattr_t* restrict attr);      //
//              参数:mutex-要初始化的互斥量,attr-NULL                       //
// 销毁互斥量:int pthread_mutex_destroy(pthread_mutex_t* mutex);            //
// 加锁和解锁:int pthread_mutex_lock(pthread_mutex_t* mutex);               //
//            int pthread_mutex_unlock(pthread_mutex_t* mutex)              //
//////////////////////////////////////////////////////////////////////////////

#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>

#define PTHREADSIZE 2

pthread_mutex_t mutex;
int g_count = 0;

void* route(void* arg)
{
    (void)arg;
    int n = 50000;
    while(n--)
    {
        pthread_mutex_lock(&mutex);
        ++g_count;
        printf("%d\n",g_count);
        pthread_mutex_unlock(&mutex);
        usleep(123456);
    }
    return NULL;
}

int main()
{
    pthread_t t1,t2;
    pthread_mutex_init(&mutex,NULL);

    pthread_create(&t1,NULL,route,NULL);
    pthread_create(&t2,NULL,route,NULL);

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    pthread_mutex_destroy(&mutex);

    
    return 0;
}

