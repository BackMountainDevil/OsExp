/*
    File:   5_2.cpp
  Author:   Kearney
   Email:   191615342@qq.com
 License:   GPL 3.0
 Version:   0.0.0
Encoding:   utf8
    Desc:   实验任务2：用位示图管理磁盘空间实现磁盘块的分配与回收
*/
#include <iostream>
#include <stdio.h>
using namespace std;
#define CYLINDER 48 //柱面数
#define WORD 16 //字
struct BitMap		//用于存储位示图 
{
	int map[CYLINDER][WORD];	//位示图 
	int free;		//剩余的空闲块数
}bitmap;

typedef struct process		//用于存储文件信息
{
	int num;				//用数字替代文件名 
	int size;				//文件大小，几块 
	int *pagetable;			//文件对应的页表 
	struct process *next;	//下一文件 
	struct process *pre;	//上一文件 
}process;


void SetProcess(process *head)		//创立文件，生成页表 
{
	int setnum;
	int i=0,j=0,k=0,finish=0;
	process *temp = new process();
	cout<<endl<<"请输入文件序号(数字且不为0)：";
	cin>>setnum;
	
	if(setnum == 0)
	{
		cout<<endl<<"错误！不能创建0号文件！";
		delete temp;
		return;
	}
	
	temp->num = setnum;
	cout<<endl<<"请输入文件大小： ";
	cin>>temp->size;
	
	if(temp->size > bitmap.free)		//判断现有空间是否足够分配 
	{
		cout<<endl<<"当前内存没有足够的空间分配！";
		delete temp;
		return;
	}
	
	temp->next = head->next;	//头插法插入新文件 
	if(head->next != NULL)
		head->next->pre = temp;
	temp->pre = head;
	head->next = temp;
	
	temp->pagetable = new int [temp->size];	//创立页表数组 
	for(i=0; i<CYLINDER && finish == 0; i++)
	{
		for(j=0; j<WORD && finish == 0; j++)
		{
			if(bitmap.map[i][j] == 0)		//修改页表数据 
			{
				bitmap.map[i][j] = 1;
				bitmap.free --;
				temp->pagetable[k] = WORD*i + j;
				k++;
			}
			
			if(k == temp->size)		//用于结束循环 
				finish = 1;
		}
	} 
	
	cout<<endl<<"已装入文件，页表如下："<<endl;
    cout<<"页号 相对块号  柱面号  磁道号  扇区号"<<endl;
	k = temp->size;
	for(i=0; i<k; i++)
	{
		cout<<i<<'\t'<<temp->pagetable[i]<<'\t'<<temp->pagetable[i]/WORD<<'\t'<<temp->pagetable[i]%16/4<<'\t'<<temp->pagetable[i]%16%4<<endl;
	}
}


void RecProcess(process *head)		//回收文件，退还内存 
{
	int recnum;
	int i=0,j=0,k=0,l=0,found=0;
	process *temp = new process();
	cout<<endl<<"请输入回收文件序号(数字且不为0)：";
	cin>>recnum;
	
	if(recnum == 0)
	{
		cout<<endl<<"错误！不能删除0号文件！";
		return;
	}
	
	for(temp=head; temp != NULL; temp = temp->next)		//找到进程 
	{
		if(temp->num == recnum)
		{
			found = 1;
			k = temp->size;
			for(l=0; l<k; l++)		//删除数据 
			{
				i = temp->pagetable[l] / WORD;
				j = temp->pagetable[l] % WORD;
				bitmap.map[i][j] = 0;
				bitmap.free ++;
			}
			
			if(temp->pre != NULL)		//不允许删除头结点 
			{
				if(temp->next != NULL)		//不是尾结点 
				{
					temp->pre->next = temp->next;
					temp->next->pre = temp->pre;
					delete temp;
				}
				
				else						//是尾结点 
				{
					temp->pre->next = NULL;
					delete temp;
				}
			}
			
			cout<<endl<<"已找到并回收序号为"<<recnum<<"的文件。";
			cout<<endl<<"该文件大小为"<<k<<"。"<<endl;
			continue;
		}
	}
	
	if(found == 0)		//未找到进程 
	{
		cout<<endl<<"未找到该文件，返回。";
		return;
	}
	
	cout<<endl<<"完成回收，返回。";
	return;
}


void ShowBitMap()		//展示位示图 
{
	cout<<endl<<"当前位示图状态如下："<<endl;
    int i=0,j=0;
    for(i=0; i< WORD; i++)  // 列头
	{
        cout<<'\t'<<i;
    }
	cout<<endl;
	for(i=0; i< WORD; i++)
	{
        cout<<"________";
    }

	for(i=0; i< CYLINDER; i++)
	{
		cout<<endl<<i<<'\t';    //行头
		for(j=0; j< WORD; j++)
		{
			cout<<bitmap.map[i][j]<<'\t';
		}
	}
}


void ShowPageTable(process *head)		//展示页表 
{
	int shownum;
	int i=0,j=0,k=0,l=0,found=0;
	process *temp = new process();
	cout<<endl<<"请输入查看文件序号(数字且不为0)：";
	cin>>shownum;
	
	if(shownum == 0)
	{
		cout<<endl<<"错误！不能查看0号文件，返回。";
		return;
	}
	
	for(temp=head; temp != NULL; temp = temp->next)		//找到进程 
	{
		if(temp->num == shownum)
		{
			found = 1; 
			cout<<endl<<"序号为"<<shownum<<"的文件页表如下："<<endl;		//输出页表 
			k = temp->size;

			cout<<"页号 相对块号  柱面号  磁道号  扇区号"<<endl;
            k = temp->size;
            for(i=0; i<k; i++)
            {
                cout<<i<<'\t'<<temp->pagetable[i]<<'\t'<<temp->pagetable[i]/WORD<<'\t'<<temp->pagetable[i]%16/4<<'\t'<<temp->pagetable[i]%16%4<<endl;
            }
			cout<<"该文件大小为"<<k<<"。"<<endl;
			continue;
		}
	}
	
	if(found == 0)		//未找到进程 
	{
		cout<<endl<<"未找到该文件，返回。";
		return;
	}
	
	cout<<endl<<"完成文件页表展示，返回。"; 
}


int main()
{
	char choice;

	bitmap.map[CYLINDER][WORD] = 0; //初始化位示图
    bitmap.free = CYLINDER*WORD;
    for(int i = 0; i < WORD; i ++)  //第1个字为“1”
    {
        bitmap.map[0][i] = 1;
        bitmap.free -= 1;
    }
	
	process *head = new process();
	head->next = NULL;
	head->pre = NULL;
	head->num = 0;
	
	while(true)
	{
		cout<<endl<<"================菜 单===============";
		cout<<endl<<"   0\t退出程序";
		cout<<endl<<"   1\t创建新文件，并请求内存空间";
		cout<<endl<<"   2\t回收文件，并返回内存；";
		cout<<endl<<"   3\t展示位示图";
		cout<<endl<<"   4\t展示进程页表";
		cout<<endl<<"   5\t清空屏幕";
		cout<<endl<<"====================================="; 
		cout<<endl<<"**请输入指令对应的数字：";
		
		cin>>choice;
		
		switch(choice)
		{
            case '0':
                cout<<"程序已结束"<<endl; 
                exit(0);    //结束程序
                break;
			case '1':
				SetProcess(head);
				break;
			case '2':
				RecProcess(head);
				break;
			case '3':
				ShowBitMap();
				break;
			case '4':
				ShowPageTable(head);
				break;
			case '5':
				system("clear");    //linux 是 clear， windows 是 cls
				break;
			default:
				cout<<"输入错误！请重新输入指令代表的数字"<<endl; 
                break;
		}
	}
	
	return 0;
}
