#include <stdio.h>
#include <limits.h>
#include <float.h>

int main(int argc, char *argv[])
{
     printf ("Some number limits for this system: \n");
   
     printf ("int max var = %d\n",INT_MAX);
     printf ("int min var = %d\n",INT_MIN);
     printf ("long max var = %d\n",LONG_MAX);
     printf ("long min var = %d\n",LONG_MIN);
     printf ("unsigned long max var = %d\n",ULONG_MAX);
     printf ("long long max var = %d\n",LLONG_MAX);
     printf ("long long min var = %d\n",LLONG_MIN);
     printf ("unsigned long long max var = %d\n",ULLONG_MAX);

     return 0;
}



