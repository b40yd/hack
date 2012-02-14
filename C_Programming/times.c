#include <stdio.h>
//#define TIMES 60
/*
 *将分钟转换成小时和分钟表示的时间，输入小于或等于0退出
 *使用#define or const 定义常量，使用while循环 
 */
int main(int argc, char *argv[])
{
     const int minute = 60;
     int t,n;
     printf ("Please enter minute:\n");
     scanf("%d",&t);
     while(t != 0){
	  n = 0;
	  while(t >= minute){
	       t = t - minute;
	       n++;
	  }
	  printf ("%d hour %d minute\n",n,t);
	  printf ("Please enter minute:\n");
	  scanf("%d",&t);
     }
     printf ("Done!\n");
     return 0;
}


