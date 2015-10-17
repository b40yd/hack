#include "stdio.h"
int main(int argc, char *argv[])
{
     int arr[4][2]={
	  {1,2},{3,4},{5,6},{7,8}};
     int * p[2];//two pointer array..
     int (*p1)[2];//comprize two int value's array
     p[1] = &arr[2][1];
     printf ("*p = %d\n",*p[1]);
     return 0;
}


