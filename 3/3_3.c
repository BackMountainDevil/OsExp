/*
    File:   
  Author:   Kearney
   Email:   191615342@qq.com
 License:   GPL 3.0
 Version:   0.0.0
Encoding:   utf8
    Desc:   操作系统 - 动态优先级调度
    ref:    https://blog.csdn.net/xyisv/article/details/80467647
            https://blog.csdn.net/weixin_30414155/article/details/96830278
*/

#include<stdio.h>
#include<stdlib.h>

typedef struct pcb   //进程控制块定义
{
    int PID;         //进程号
    char state;     //进程状态，R表示运行ing，W表示处于就绪队列中
    int priority;   //进程优先级数，数越小，优先级越高
    int runTime;    //所需运行时间
    int workTime;   //已经运行了多长时间
    struct PCB *next;   //链接指针
}PCB;

PCB *ready=NULL,*p;//ready就绪队列头指针，p运行进程指针
int N;    //进程总数

//对就绪队列按优先级进行排序
void PCBsort(){
    PCB *first,*second;
    int flag=0;
    if((ready==NULL)||((p->priority)<(ready->priority)))    //ready空或者比头还要优先
    {
        p->next=ready;  //插在最前头
        ready = p;
        // printf("\n  -ready PID: %d\n", ready->PID);
    }else{  //优先数<=头
        first=ready;
        // printf("\n  +ready PID: %d\n", ready->PID);
        second=first->next;
        while(second!=NULL)
        {
            if((p->priority)<(second->priority))    //p优先数较小插在first和second之间
            {
                p->next=second;
                first->next=p;
                second=NULL;
                flag=1; 
            }else{  //优先数比当前大，继续往后遍历
                first=first->next;
                second=second->next;
            }
        }
        if(flag==0){    //未插入，优先级相同，运行完当前的切换到下一个优先级和自己一样的
            first->next=p;
            // printf("flag\n");
        }
            
    }
}

//建立进程，输入各个进程信息，并建立链表;
void inputProcess()
{
    int i;
    printf("输入%d个进程的信息（PID、优先数、运行时间）如 2 4 6\n",N);
    for(i=0;i<N;i++){
        p=(PCB*)malloc(sizeof(PCB));
        scanf("%d %d %d",&p->PID,&p->priority,&p->runTime);
        p->workTime=0;
        p->state='W';   //默认等待状态
        p->next=NULL;   //后继进程为空
        PCBsort();  //排序
    }
}
// 求就绪队列的进程数
int space()
{
    int k=0;
    PCB* pr=ready;
    while(pr!=NULL){
        k++;
        pr=pr->next;
    }
    // printf("k= %d\n",k);
    return k;
}

//显示每个进程状态
void showInfo(PCB *pr){
    printf("\nPID\t状态\t优先数\t运行时间\t剩余时间\n");
    printf("——————————————————————————————————————\n");
    printf(" %d\t",pr->PID);
    printf(" %c\t",pr->state);
    printf("%d\t",pr->priority);
    printf("%d\t\t",pr->runTime);
    printf("%d\t",pr->runTime-pr->workTime);
    printf("\n");
}

//运行进程调度的函数；
void priorityRun()
{
    int len,h=0;
    double tzz,tdqzz;
    tzz = 0;    //总周转时间
    tdqzz = 0;  //总带权周转时间
    char ch;
    inputProcess();
    len=space();
    while((len!=0)&&(ready!=NULL)) //就绪队列不为空
    {
        h++;
        printf("\n 运行时间:%d \n",h);
        p=ready;
        ready=p->next;
        p->next=NULL;
        p->state='R';   //更新进程状态
        PCB* pr;
        showInfo(p);    //显示当前进程信息
        pr=ready;
        while(pr!=NULL){    //显示就绪队列进程信息
            showInfo(pr);
            pr=pr->next;
        }
        (p->workTime)++;
        if(p->workTime==p->runTime){    //对比时间,判断是否结束
            printf("\n 进程%d 已结束。\t周转时间： %2d\t带权周转时间： %2.2lf\n",p->PID, h, (double)h/(double)(p->runTime));
            tzz += (double)h;
            tdqzz += (double)h/(double)(p->runTime);
            free(p);    //释放内存
        }
        else{
            (p->priority)++;    //优先数加一，优先级减1
            p->state='W';   //更新进程状态
            PCBsort();      //排序
        }
        // printf("按任意键继续 ......\n");
        // ch=getchar();   //按一下键盘运行一个时间片
    }

    printf("平均周转时间：%2.2lf\n",tzz/(double)N);
    printf("平均带权周转时间：%2.2lf\n",tdqzz/(double)N);
    printf("\n\n 所有进程已经完成,按任意键结束\n");
    ch=getchar();
}

//主函数，输入进程数目N
int main()
{
    printf("—————————————————优先级调度算法—————————————————\n");
    printf("输入进程数目：");
    scanf("%d",&N);
    priorityRun();
}