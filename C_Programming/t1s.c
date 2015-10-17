#include <stdio.h>
int main(int argc, char *argv[])
{
     int div,num = 144;
     for (div = 0; (div * div) <= num; div++)
     {
	  if (num % div == 0)
	  {
	       if (div * div != num)
		    printf ("%d is divisible by %d and %d.\n",
			    num,div,num / div);
	       else
		    printf ("%d is divisible by %d.\n",num,div);
	  }
     }
     return 0;
}

