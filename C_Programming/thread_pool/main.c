#include "thread_pool.h"
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

void* work(void* arg)
{
    char *p = (char*) arg;
    printf("threadpool callback fuction : %s.\n", p);
    sleep(1);
}

int main(void)
{
    struct threadpool *pool = threadpool_init(10, 1000);
    int n;
    char s[255];
    //bzero(&s,0x00);
    for(n = 1;n<1000;n++){
	//itoa(n,s,4);
	printf("%d",n);
	sprintf(s,"%d",n);
	threadpool_add_job(pool, work, s);
    }

    sleep(5);
    threadpool_destroy(pool);
    return 0;
}
