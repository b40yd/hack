#include "stdio.h"
int main(int argc, char *argv[])
{
     int * p;
     int ar[4] = {100,200,300,400};
     p = ar;
     const int *p1 = &ar[3];
     p1 = &ar[2];
     printf ("ptr = %p , *ptr = %d,%d , &ptr = %p,%d\n",
	     p,*(++p),*p,&p,sizeof(double));
     printf ("%d\n",p1);
     return 0;
}


