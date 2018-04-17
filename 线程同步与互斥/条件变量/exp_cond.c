//////////////////////////////////////////////////////////////////////////
// 条件变量函数:                                                        //
// 初始化:int pthread_cond_init(pthread_cond_t* restrict cond,          //
//                      const pthread_condattr_t* rest);                //
// 销毁:int pthread_cond_destroy(pthread_cond_t* cond);                 //
// 等待满足条件:int pthread_cond_wait(pthread_cond_t* restrict cond,    //
//                                  pthread_mutex_t* restrict mutex);   //
// 唤醒等待:int pthread_cond_broadcast(pthread_cond_t* cond);           //
//          int pthread_cond_signal(pthread_cond_t* cond);              //
//////////////////////////////////////////////////////////////////////////


#include<stdio.h>
#include<pthread.h>
#include<unistd.h>

pthread_cond_t cond;
pthread_mutex_t mutex;
int g_count;

void* r1(void* arg)
{
    (void)arg;
    while(1)
    {
        pthread_cond_wait(&cond,&mutex);
        g_count--;
        printf("g_count = %d\n",g_count);
        usleep(123456);
    }
    return NULL;
}

void* r2(void* arg)
{
    (void)arg; 
    while(1)
    {
        g_count++;
        printf("g_count = %d\n",g_count);
        usleep(123466);
        pthread_cond_signal(&cond);
    }
    
    return NULL;

}


int main()
{
    pthread_t t1,t2;

    pthread_cond_init(&cond,NULL);
    pthread_mutex_init(&mutex,NULL);


    pthread_create(&t1,NULL,r1,NULL);
    pthread_create(&t2,NULL,r2,NULL);
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);

    return 0;
}
