#include <stdio.h>

int sum(int * p,int (fun)(int));
int square(int n);


int main(int argc, char *argv[])
{
     int arr[10]={0};
     int *ptr = arr;
     printf ("Please enter your numbers:\n");
     while(scanf("%d",ptr) &&
	   (*ptr++) != 0){
	  
     }

     printf ("%d\n",sum(arr,square));
     return 0;
}

int sum(int * p,int (fun)(int)){     
     int n = 0;
     int i = 0;
     
     for (; p[i]!=0 ; ++i)
     {
	  n += fun(p[i]);
     }
     return n;
}

int square(int n){
     return n*n;
}

