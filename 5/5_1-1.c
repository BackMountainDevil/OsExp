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
            https://www.runoob.com/cprogramming/c-function-fopen.html
*/
#include<stdio.h>
 
int main ()
{
  FILE *fp;
  char name[20] = "";
  char no[10] = "";
  char class[10] = "";

  fp = fopen( "file.txt" , "w" );   //创建一个用于写入的空文件。同名则覆盖

  printf("Please input the Name, No, Class of std（Split with space） \nJust like: Kearney 7 D\n");
  for(int i = 0; i < 10; i++) //写入信息到文件
  {
    scanf("%s %s %s",&name, &no, &class);
    // printf("%s %s %s\n",name, no, class);
    fprintf(fp, "Name: %s\nNo: %s\nClass: %s\n",&name, &no, &class); // 相当于fwrite，把字符写入文件
  }
  fclose(fp); //关闭文件

  // 读取写入的内容
  fp = fopen( "file.txt" , "r" ); 
  while(1)
   {
      int c = fgetc(fp);
      if( feof(fp) )
      { 
          break ;
      }
      printf("%c", c);
   }
  fclose(fp);

  return 0;
}
