#include <stdio.h>
int main(int argc, char *argv[])
{
     int i=0;
     char n;
     while((n = getchar())!='&'){
	  if(n=='\n')
	       continue;
	  else{
	       i++;
	       printf ("%d\n",n);
	  }
     }
     printf ("%d\n",i);
     return 0;
}

