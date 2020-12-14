/*
    File:   exp3_1.c
  Author:   Kearney
   Email:   191615342@qq.com
 License:   GPL 3.0
 Version:   0.0.0
 Encoding:   utf8
    Desc:   使用fork创建进程
*/
#include <stdio.h>
#include <unistd.h>     //fork(), execlp()
#include <stdlib.h>     //sleep()

int main(){

    int x = 0;
    char name[10] = "易才润";
    char sid[20] = "2018308160239";

    if( fork() == 0){   // 子进程1
        printf("子进程1 : 进程号 = %d , 父进程号 = %d\tx = %d\n", getpid(), getppid(), x);
        for(int i = 0; i < 4; i++){
                printf("x = %d\n", x);
                x = x + 2;
        }
        
    }else{
        if( fork() == 0){  //子进程2
            // printf("子进程2！: 进程号 = %d, 父进程号 = %d\tx = %d\n", getpid(), getppid(), x);
            // for(int i = 0; i < 4; i++){
            //     printf("x = %d\n", x);
            //     x = x + 2;
            // }
        
            if( fork() == 0){   //子进程3
                printf("子进程3: 进程号 = %d, 父进程号 = %d\tx = %d\n", getpid(), getppid(), x);
                for(int i = 0; i < 4; i++){
                    printf("x = %d\n", x);
                    x = x + 2;
                }
            }
            else // 放在前后没有区别?执行的先后顺序不同
            {
                printf("子进程2: 进程号 = %d, 父进程号 = %d\tx = %d\n", getpid(), getppid(), x);
                for(int i = 0; i < 4; i++){
                    printf("x = %d\n", x);
                    x = x + 2;
                }
            }
        }else{  //父进程
            printf("父进程 : 进程号 = %d , 父进程号 = %d\tSID : %s\tName : %s\tx = %d\n", getpid(), getppid(), name, sid, x);
            for(int i = 0; i < 4; i++){
                printf("x = %d\n", x);
                x = x + 2;
            }
            sleep(3);   // 如果父进程死的比子进程要早，子进程的父进程号会为1
        }
    }

    // 父进程和子进程都执行的部分
    printf("父进程和子进程都执行的部分\n");
    return 0;
}
// 10.2.172.107
// 2019stu20
// 123456