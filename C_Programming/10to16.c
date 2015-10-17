#include "stdio.h"

char tos(char *p);

int main(int argc, char *argv[])
{
 
     char arr[5] = {111,222,333,444,235};
     char * p = arr;
     tos(arr);
     return 0;
}

char tos(char *p){
     int i,j,var,new;
     char ff[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
     for (i = 0; i < 5; i++)
     {
	  var=p[i]/16;
	  printf ("%d\n",ff[var]);
	  while(var>=16)
	       new=var/16;
	  printf ("%d",new);
	  //printf ("%c",ff[new]);
     }
     putchar('\n');
}
