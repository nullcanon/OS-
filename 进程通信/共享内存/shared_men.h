/*************************************************************************
  > File Name   : shared_men.h
  > Author      : jack
  > Mail        : hansheng.jiayou@qq.com
  > Created Time: 2018年03月27日 星期二 13时18分14秒
 ************************************************************************/

#ifndef _SHARED_MEN_H
#define _SHARED_MEN_H

#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdio.h>

#define PATHNAME "."
#define PROJ_ID 0x1

//创建共享内存
//size-共享内存的大小
//成功返回shmid,失败返回小于0的数
int CreateShm(int size);

//销毁共享内存
//shmid-共享内存标识id
//成功返回0,失败返回-1
int DestoryShm(int shmid);

//获得一段共享内存
//size-大小
//成功返回shmid,失败返回小于0的数
int GetShm(int size);

#endif
