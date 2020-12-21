/*
    File:   5_1-1
  Author:   Kearney
   Email:   191615342@qq.com
 License:   GPL 3.0
 Version:   0.0.0
Encoding:   utf8
    Desc:   实验任务1：编程从键盘中输入10个学生的有关数据，然后把他们转存到磁盘文件中。
            学生信息包括：学生姓名、学号、班级等；使用库函数fopen、fwrite等函数完成；
      ref:  https://www.runoob.com/cprogramming/c-function-fwrite.html
*/
#include<stdio.h>
 
int main ()
{
  FILE *fp;
  char str[] = "                     ";
  char line1[] = "\nName: ";
  char line2[] = "\nNo: ";
  char line3[] = "\nClass:  ";
  fp = fopen( "file.txt" , "w" );

  for(int i = 0; i < 10; i++)
  {
    printf("Please input the name of std: ");
    scanf("%s",&str);
    fwrite(line1, sizeof(line1) , 1, fp );
    fwrite(str, sizeof(str) , 1, fp );
    printf("Please input the no of std: ");
    scanf("%s",&str);
    fwrite(line2, sizeof(line2) , 1, fp );
    fwrite(str, sizeof(str) , 1, fp );
    printf("Please input the class of std: ");
    scanf("%s",&str);
    fwrite(line3, sizeof(line3) , 1, fp );
    fwrite(str, sizeof(str) , 1, fp );
  }
  fclose(fp);
  return 0;
}
