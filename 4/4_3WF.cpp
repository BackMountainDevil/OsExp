/*
    File:   4_3WF.cpp
  Author:   Kearney
   Email:   191615342@qq.com
 License:   GPL 3.0
 Version:   0.0.0
Encoding:   utf8
    Desc:   操作系统 - 最坏适应算法
    ref:    https://blog.csdn.net/qq_39382769/article/details/80486072?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522160792813219721940235088%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=160792813219721940235088&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~blog~sobaiduend~default-1-80486072.pc_v2_rank_blog_default&utm_term=%E6%9C%80%E5%9D%8F%E9%80%82%E5%BA%94%E7%AE%97%E6%B3%95c&spm=1018.2118.3001.4450
*/
#include<bits/stdc++.h>
using namespace std;

#define MEMSIZE 100 /*定义内存的大小为100*/
#define MINSIZE 2   /*如果小于此值，将不再分割内存*/

/*内存分区空间表结构*/
typedef struct _MemoryInfomation
{   
    int start;  /*起始地址*/
    int Size;   /*大小*/
    char status;    /*状态 F:空闲(Free) U:占用(Used) E 结束(End)*/
} MEMINFO;

MEMINFO MemList[MEMSIZE];   // 内存空间信息表

// 显示内存状态
void Display()
{
    int i,used=0;//记录可以使用的总空间量
    printf("\n---------------------------------------------------\n");
    printf("%5s%15s%15s%15s\n","Number","start","size","status");
    printf("---------------------------------------------------\n");
    for(i=0; i<MEMSIZE && MemList[i].status!='e'; i++)
    {
        if(MemList[i].status=='u')
        {
            used+=MemList[i].Size;
        }
        printf("%5d%15d%15d%15s\n",i,MemList[i].start,MemList[i].Size,MemList[i].status=='u'?"USED":"FREE");
    }
    printf("---------------------------------------------------\n");
    printf("Totalsize:%-10d Used:%-10d Free:%-10d\n",MEMSIZE,used,MEMSIZE-used);
}

// 初始化所有变量
void InitMemList()
{
    int i;
    MEMINFO temp= {0,0,'e'};
    //初始化空间信息表
    for(i=0; i<MEMSIZE; i++)
    {
        MemList[i]=temp;
    }
    //起始地址为0
    MemList[0].start=0;
    //空间初始为最大
    MemList[0].Size=MEMSIZE;
    //状态为空闲
    MemList[0].status='f';
}


// 最坏适应算法
void WorstFit_alloc()
{
    int i,j,k,flag,request;
    printf("WorstFit_alloc: How Many MEMORY requir?\n");
    scanf("%d",&request);
    j=0;
    flag=0;
    k=0;
    //保存满足要求的最大空间
    for(i=0;i<MEMSIZE-1&&MemList[i].status!='e';i++)
    {
        if(MemList[i].Size>=request&&MemList[i].status=='f')
        {
            flag=1;
            if(MemList[i].Size>k)
            {
                k=MemList[i].Size;
                j=i;
            }
        }
    }
    i=j;
    if(flag==0)
    {
        printf("Not Enough Memory!\n");
        j=i;
    }else if(MemList[i].Size-request<=MINSIZE)
    {
        MemList[i].status='u';
    }else
    {
        for(j=MEMSIZE-2;j>i;j--)
        {
            MemList[j+1]=MemList[j];
        }
        MemList[i+1].start=MemList[i].start+request;
        MemList[i+1].Size=MemList[i].Size-request;
        MemList[i+1].status='f';
        MemList[i].Size=request;
        MemList[i].status='u';
    }
    Display();
}


//释放一块内存
void setfree()
{
    int i,number;
    printf("\nplease input the NUMBER you want stop:\n");
    scanf("%d",&number);
    //输入的空间是使用的
    if(MemList[number].status=='u')
    {
        MemList[number].status='f';//标志为空闲
        if(MemList[number+1].status=='f')//右侧空间为空则合并
        {
            MemList[number].Size+=MemList[number].Size;//大小合并
            for(i=number+1; i<MEMSIZE-1&&MemList[i].status!='e'; i++) //i后面的空间信息表元素后移
            {
                if(i>0)
                {
                    MemList[i]=MemList[i+1];
                }
            }
        }
        //左测空间空闲则合并
        if(number>0&&MemList[number-1].status=='f')
        {
            MemList[number-1].Size+=MemList[number].Size;
            for(i=number; i<MEMSIZE-1&&MemList[i].status!='e'; i++)
            {
                MemList[i]=MemList[i+1];
            }
        }
    }
    else
    {
        printf("This Number is Not Exist or is Not Used！\n");
    }
    Display();
}

// 主函数
int main()
{
    int x;
    InitMemList();//变量初始化
    while(1)
    {
        printf("\n=================================================\n");
        printf("         1.Get a block use the WorstFit method\n");
        printf("         2.Free a block\n");
        printf("         3.Dispaly Mem info \n");
        printf("         4.Exit \n");
        printf("=================================================\n");
        scanf("%d",&x);
        switch(x)
        {
            case 1:
                WorstFit_alloc();   //最坏适应算法
                break;
            case 2:
                setfree();    //释放在使用的空间
                break;
            case 3:
                Display();  //显示内存分配情况
                break;
            case 4:
                exit(0);    //结束程序
        }
    }
    return 0;
}