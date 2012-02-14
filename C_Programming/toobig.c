#include <stdio.h>
/*
 * 打印 类型错误和格式类型
 * int i有符号整数类型 unsigned int j 无符号整数类型
 * long int n 长整型整数
 */
int fun(void);
int main(void)
{
     int i = 2147483647;
     unsigned int j = 42949667295;
     long int n = 1000000;
     
     printf ("%d %d %d\n",i,i+1,i+2);
     printf ("%u %u %u\n",j,j+1,j+2);
     printf ("%ld %lo \t %lx\n",n,n,n);
     printf ("%LD %LO \t %LX\n",n,n,n);
     printf ("%lD %lO \t %lX\n",n,n,n);//错误的格式符，
     fun();
     return 0;
}

int fun(void){
     int o;
     scanf("%d",&o);
     printf("%d",o);
     return 0;
}


