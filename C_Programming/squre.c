#include <stdio.h>

int squre(int n);

int main(int argc, char *argv[])
{
     int arr[6] = {1,2,3,4,5,6};
     int i = 0,m = 0;
     for (i = 0; i < 6; i++)
	  m += squre(arr[i]);
     printf ("%d\n",m);
     return 0;
}

int squre(int n){
     return n*n;
}
