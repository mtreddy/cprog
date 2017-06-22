#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/sem.h>
#include<sys/ipc.h>

#ifndef _SEM_COMMON_H__
#define _SEM_COMMON_H__
struct crit{
    int crit;
};
int semid;
short initarray[2], outarray[2];
struct sembuf pbuf, vbuf;
int first ;
int second ;
#define TEST_KEY    123456
void cleanup(int semid);
int sem_init(void);
int sem_lock(int semid);
int sem_unlock(int semid);
#endif
