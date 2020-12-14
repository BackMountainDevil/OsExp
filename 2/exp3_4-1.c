/*
    File:   exp3_4-1.c
  Author:   Kearney
   Email:   191615342@qq.com
 License:   GPL 3.0
 Version:   0.0.0
Encoding:   utf8
    Desc:   生产者
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define  KEY  77
#define  SIZE 1024
int main( )
{
    int  shmid, *p, i;
    char  *shmaddr;
    shmid=shmget(KEY,  SIZE,
                0777|IPC_CREAT);
    shmaddr=shmat(shmid,0, 0);
    p=(int *) shmaddr;
    for(i=0;i<10; i++)   {  // 产生十个随机数
        *p= rand()%100;
        printf("%d\n",*p);
        p++;  
        sleep(1);
    }
    sleep(5);  
    shmdt(shmaddr);  
    return 0;
}
