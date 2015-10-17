#include <stdio.h>

int main(int argc, char *argv[])
{
     int i = 0,n = 0,m = 3;
     while(++i < 10)
	  printf ("%d\t",i);
     printf ("\n");
     while(n++ < 10)
	  printf ("%d\t",n);
     printf ("\n");
     
     printf ("%d\n",(2+m++)*6);
     return 0;
}


