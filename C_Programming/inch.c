#include <stdio.h>
/*
 *计算身高，把cm to inch
 *1inch equal 2.54cm
 */
int cm_to_inch(void){
     float high;
     scanf("%f",&high);
     printf ("%f\n",high);
     printf("1 inch == 2.54cm you enter high is %f ,inch equal %f\n",high,high/2.54);

}
/*
 *计算输入的夸脱水有多少分子
 */
int water(void){
     long double m,w = 3.0e-23;
     long int g = 950,n;
     scanf("%d",&n);
     m = n*g*w;
     printf ("water numbers = %d,hydrone = %f(%e)\n",n,m,m);
}
int main(int argc, char *argv[])
{
     int n;
     water();
     scanf("%d\n",&n);
     printf("age = %le",n*3.156e7);
     cm_to_inch();
     return 0;
}


