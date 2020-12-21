/*
    File:   5_1-2.c
  Author:   Kearney
   Email:   191615342@qq.com
 License:   GPL 3.0
 Version:   0.0.1
Encoding:   utf8
    Desc:   实验任务1：编程从键盘中输入10个学生的有关数据，然后把他们转存到磁盘文件中。
            学生信息包括：学生姓名、学号、班级等；
            使用Linux的系统调用open、write等完成，在Linux环境下运行。
    ref:    https://www.cnblogs.com/Lxk0825/p/10216694.html
*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
int main ()
{
  char str[] = "1234567890";
  char line1[] = "\nName: ";
  char line2[] = "\nNo: ";
  char line3[] = "\nClass:  ";
  int fp = open( "file.txt" , O_RDWR | O_CREAT);  // 以可读写方式打开文件,文件不存在则创建
  // printf("%d",fp);
  // int n = write(fp, str,strlen(str));  // 返回写入的字节数，出错返回-1
  // printf("%d",n);
  for(int i = 0; i < 10; i++)
  {
    printf("Please input the name of std: ");
    scanf("%s",&str);
    write(fp, line1,strlen(line1));
    write(fp, str,strlen(str));
    printf("Please input the no of std: ");
    scanf("%s",&str);
    write(fp, line2,strlen(line2));
    write(fp, str,strlen(str));
    printf("Please input the class of std: ");
    scanf("%s",&str);
    write(fp, line3,strlen(line3));
    write(fp, str,strlen(str));
  }
  return 0;
}