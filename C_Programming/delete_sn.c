#include <stdio.h>
#define LEN 81
int drop_space(char * s);
int main(void)
{
     char orig[LEN];
     while (gets(orig) && orig[0] != '\0')
     {
	  drop_space(orig);
	  puts(orig);
     }
     puts("Bye!");
     return 0;
}
int drop_space(char * s)
{
     int ct = 0;
     char * pos;
     while (*s)
/* or while (*s != '\0') */
     {
	  if (*s == ' ')
	  {
	       pos = s;
	       do
	       {
		    *pos = *(pos + 1);
		    pos++;
	       } while (*pos);
	  }
	  else
	       s++;
     }
}
