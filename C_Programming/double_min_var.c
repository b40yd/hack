#include "stdio.h"
double min(double n,double m);
int main(int argc, char *argv[])
{
     double n,m;
     printf ("Enter two numbers (q to quit):\n");
     while(scanf("%lf %lf",&n,&m) == 2){
	  printf ("The smaller number is %f.\n",min(n,m));
	  printf ("Next two values (q to quit):\n");
     }
     printf ("Bye!\n");
     return 0;
}
double min(double n,double m){
     return n>m?n:m;
}


