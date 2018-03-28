/*************************************************************************
  > File Name   : semaphore.h
  > Author      : jack
  > Mail        : hansheng.jiayou@qq.com
  > Created Time: 2018年03月27日 星期二 20时58分57秒
 ************************************************************************/

#ifndef _SEMAPHORE_H
#define _SEMAPHORE_H

#include<stdio.h>
#include<sys/ipc.h>
#include<sys/types.h>
#include<sys/sem.h>


#define PATHNAME "."
#define PROJ_ID 0x1


union semun 
{
    int              val;    /* Value for SETVAL */
    struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
    unsigned short  *array;  /* Array for GETALL, SETALL */
    struct seminfo  *__buf;  /* Buffer for IPC_INFO
                                (Linux-specific) */
};

int CreateSemSet(int nums);
int GetSemSet(int nums);
int InitSem(int semid,int nums,int initVal);
int Destory(int semid);
int P(int semid,int who);
int V(int semid,int who);

// struct semid_ds {
//     struct ipc_perm sem_perm;  /* Ownership and permissions */
//     time_t          sem_otime; /* Last semop time */
//     time_t          sem_ctime; /* Last change time */
//     unsigned long   sem_nsems; /* No. of semaphores in set */

// };

// struct ipc_perm {
//     key_t          __key; /* Key supplied to semget(2) */
//     uid_t          uid;   /* Effective UID of owner */
//     gid_t          gid;   /* Effective GID of owner */
//     uid_t          cuid;  /* Effective UID of creator */
//     gid_t          cgid;  /* Effective GID of creator */
//     unsigned short mode;  /* Permissions */
//     unsigned short __seq; /* Sequence number */

// };


#endif
