/*
    File:   exp3_2for.c
  Author:   Kearney
   Email:   191615342@qq.com
 License:   GPL 3.0
 Version:   0.0.0
 Encoding:   utf8
    Desc:   execl的子程序
*/
#include <stdio.h>
int main()
{
    printf("Tag:");
    int x = 0;
    for(int i = 0; i < 4; i++){
        printf("x = %d\n", x);
        x = x + 2;
    }
    return 0;
}