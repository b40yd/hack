#include <time.h>
#include <stdio.h>

int main(int argc,int * argv[]){
	struct tm *local;
	time_t t;
	t=time(NULL);
	local = localtime(&t);
	printf("%d\n",local->tm_hour);
}
