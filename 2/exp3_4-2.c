/*
    File:   exp3_4-2.c
  Author:   Kearney
   Email:   191615342@qq.com
 License:   GPL 3.0
 Version:   0.0.0
Encoding:   utf8
    Desc:   消费者
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <math.h>
#define  KEY  77
#define  SIZE 1024


int main( )
{
    int shmid,*q,*t,i;
    double x,x1;
    char * maddr;
    shmid=shmget(KEY,   SIZE,  0777);
    maddr=shmat(shmid,0,0);
    q=(double *) maddr;
    sleep(12);
    for(i=0;i<10;i++){
        x=sqrt(*q);
        x1=(*q)*(*q);
        printf("sqrt= %lf  ^2= %lf\n",x,x1);
        q++;
    }
    shmdt(maddr);
    shmctl(shmid,  IPC_RMID, 0);
    return 0;
}

