#include <stdio.h>
int imin(int n,int m);
int main(int argc, char *argv[])
{
     int n,m;
     printf ("Enter a pair of integers(q to quit):\n");
     while(scanf("%d %d",&n,&m) ==2){
	  printf ("The lesser of %d and %d is %d.\n",n,m,imin(n,m));
	  printf ("Enter a pair of integers(q to quit):\n");
     }
     printf ("Bye.\n");
     return 0;
}

int imin(int n,int m){
     return n<m?n:m;
}
