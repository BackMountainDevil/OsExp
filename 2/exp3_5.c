/*
    File:   exp3_5.c
  Author:   Kearney
   Email:   191615342@qq.com
 License:   GPL 3.0
 Version:   0.0.0
Encoding:   utf8
    Desc:   修改上面的程序。父进程从键盘上接受10个数据，对其求和sum1，子进程求这10个
    数平方和sum2，使用消息队列方式将结果传给父进程，父进程计算sum1+sum2，打印结果。
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
struct msgform
{  	long mtype;
	int myarray[10];
}msg;
int msgqid, i;

int main()
{
	int pid1;
	while((pid1=fork())==-1);
	if(pid1==0)
    {   // 子进程
		int mid,*q,*t;
		int sum2=0;
		struct msgform m;
		mid=msgget(KEY, 0777|IPC_CREAT);    //接收父进程数据
		msgrcv(mid,&m,sizeof(int)*10,123,0);
		for(i=0;i<10;i++){  // 求平方和
			sum2+=(m.myarray[i])*(m.myarray[i]);
		}

		m.mtype=321;
		m.myarray[0]=sum2;
		msgsnd(mid,&m,sizeof(int),0); //发送sum2给父
	}
	else
    {   //父进程
		int sum1=1,sum2;
		int msgid,*p,i,a[10];
 		struct msgform msg;
 		msgid=msgget(KEY, 0777|IPC_CREAT);
		

        msg.mtype=123;
        for(i=0;i<10;i++){  //输入生成10个数据
            // printf("Please input the %2d number: ",i+1);
            // scanf("%d: ",&msg.myarray[i]); 
            msg.myarray[i] = rand()%100;
        }
        printf("Array is : ");
        for(i=0;i<10;i++){  //输出10个数据，并求和sum1
            printf("%3d",msg.myarray[i]);
            sum1 = sum1 + msg.myarray[i];
        }
        printf("\n");
        
        msgsnd(msgid,&msg,sizeof(int)*10,0);    //发送数据给子进程

        sleep(2);   //等待子计算sum2

        msgrcv(msgid, &msg, sizeof(int), 321, 0);   //接收子进程发来的数据
        sum2=msg.myarray[0];
        printf("sum1 = %5d   sum2 = %5d   sum = %5d\n", sum1, sum2, (sum1+sum2));

	}
    return 0;
}
