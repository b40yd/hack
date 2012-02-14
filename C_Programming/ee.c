#include <stdio.h>

int main(int argc, char *argv[])
{
     float g = 1e21;
     int h = 44;
     char ch = 65;
     printf ("%f not %e\n",g,g);
     printf ("%d not %#ox\n",h,h);
     printf ("%c is %d\n",ch,ch);
     return 0;
}


