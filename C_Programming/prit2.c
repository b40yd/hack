#include <stdio.h>
/*
 * 测试 无符号整数类型，short整数类型，long整数类型，long long 整数类型
 * 分别显示正确与错误的格式说明符
 */
int main(int argc, char *argv[])
{
     unsigned int nu = 3000000000; //int 为32位
     short end = 200;//和short为16位的整数
     long big = 65537; 
     long long verybig = 12345678908642;
     printf ("nu = %u and not %u\n",nu,nu);
     printf ("end = %hd and %d\n",end,end);
     printf ("hig = %ld and not %hd\n",big,big);
     printf ("verybig = %lld and not %ld\n",verybig,verybig);
     return 0;
}


