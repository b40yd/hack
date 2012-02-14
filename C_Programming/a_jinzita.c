#include <stdio.h>
int main(int argc, char *argv[])
{
     int i,j,n;
     char m;
     printf ("Please enter a number and char:\t");
     scanf("%d %c",&n,&m);
     for (i = 0; i < n; i++)
     {
	  for (j = 0; j < (n-i); j++)
	       putchar (' ');
	  for (j = 0; j < i; j++)
	       putchar (m+j);
	  while(j>=0)
	       putchar (m+(j--));
	  printf ("\n");
     }
     return 0;
}

