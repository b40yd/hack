#include <stdio.h>
/*
 *浮点数的上益
 */
int main(int argc, char *argv[])
{
     float toobig = 0.1234e-10/10.0f;
     printf ("%le\n",toobig);
     printf ("%lf\n",toobig);
     return 0;
}


