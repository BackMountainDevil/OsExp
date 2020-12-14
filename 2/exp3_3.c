/*
    File:   exp3_3.c
  Author:   Kearney
   Email:   191615342@qq.com
 License:   GPL 3.0
 Version:   0.0.0
 Encoding:   utf8
    Desc:   getppid
*/
#include <stdio.h>
#include <unistd.h>     //fork()
#include <stdlib.h>     //sleep()

int main(){
    char name[10] = "易才润";
    char sid[20] = "2018308160239";

    if( fork() == 0){   // 子进程1
        for (int i = 0; i < 20; i++) // 避免while(1)的死循环
        {
            printf("子进程1 : 进程号 = %d , 父进程号 = %d\n", getpid(), getppid());
            sleep(2);
        }
    }else{
         //父进程
            printf("父进程 : 进程号 = %d , 父进程号 = %d\tSID : %s\tName : %s\n", getpid(), getppid(), name, sid);
            execlp("./exp3_2for",0);
            sleep(3);   // 如果父进程死的比子进程要早，子进程的父进程号会为1
    }

    // 父进程和子进程都执行的部分
    printf("父进程和子进程都执行的部分, pid = %d\n", getpid());
    return 0;
}