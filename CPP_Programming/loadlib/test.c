#include <stdio.h>
#include "libtest.h"

int main(int argc, char **argv)
{
	printf("loading shared lib.\n");
	char *name;
	name  = "test name";
	setname(name);
	char *s;
	s = getName();
	printf("name:\t%s\n%s\n",s,name);
	return 0;
}
