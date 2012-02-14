/**
 * 嵌套循环 使用const 代替#define
 * 打印各种图形
 */
#include <stdio.h>
/**
 * 方形的99乘法表 完全显示
 *
 */

int maths(void){
     const int N = 9, M = 9;
     int i,j;
     int n = 0;
     for (i = 1; i <= N; i++){
	  for (j = 1; j <= M; j++)
	       printf ("%d \t", i * j);
	  printf ("\n");
     }
     return 0;

}
/**
 * 梯形99乘法表
 * 判断i/j!=0 显示从左高到低 y轴显示乘法表
 */

int x_maths(void){
     const int N = 9, M = 9;
     int i,j;
     int n = 0;
     for (i = 1; i <= N; i++){
	  for (j = 1; j <= M; j++){
	       if (i/j!=0)
	       {
		    printf ("%d \t", i * j);
	       }
	  }
	  printf ("\n");
     }
     return 0;

}
/**
 * 梯形99乘法表 
 * x轴 进行乘法表显示
 */

int xx_maths(void){
     const int N = 9, M = 9;
     int i,j;
     int n = 0;
     for (i = 1; i <= N; i++){
	  for (j = 1; j <= M; j++){
	       if (j/i!=0)
	       {
		    printf ("%d \t", i * j);
	       }
	  }
	  printf ("\n");
     }
     return 0;

}

/**
 * 显示99乘法表 
 * 9*9开始显示递减到<=1
 */


int xxx_maths(void){
     //const int N = 9, M = 9;
     int i,j;
     //int n = 0;
     for (i = 9; i >= 1; i--){
	  for (j = 9; j >= 1; j--){
	       if (j/i!=0)
		    printf ("%d \t", i * j);
	       
	  }
	  printf ("\n");
     }
     return 0;

}

/**
 * 显示99乘法表 
 * 9*9开始显示递减到<=1
 */


int xxxx_maths(void){
     //const int N = 9, M = 9;
     int i,j;
     //int n = 0;
     for (i = 9; i >= 1; i--){
	  for (j = 9; j >= 1; j--){
	       if (i/j!=0)
		    printf ("%d \t", i * j);
	       
	  }
	  printf ("\n");
     }
     return 0;

}

int main(int argc, char *argv[])
{
     maths();
     x_maths();
     xx_maths();
     xxx_maths();
     xxxx_maths();
     return 0;
}

