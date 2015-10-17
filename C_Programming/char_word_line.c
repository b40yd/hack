#include <stdio.h>
int main(void)
{
     char ch;
     int sp_ct = 0;
     int nl_ct = 0;
     int other = 0;
     while ((ch = getchar()) != '#')
     {
	  if (ch == ' ')
	       sp_ct++;
	  else if (ch == '\n')
	       nl_ct++;
	  else
	       other++;
     }
     printf("spaces: %d, newlines: %d, others: %d\n", sp_ct, nl_ct, other);
     return 0;
}
