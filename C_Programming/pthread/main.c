#include "global.h"  
#include "thread_pool.h"  
  
void* task1()  
{  
	printf("# Thread working: %u\n", (int)pthread_self());  
	printf("  Task 1 running..\n");  
}  


/* Some arbitrary task 2 */  
void* task2(int a)  
{  
	printf("# Thread working: %u\n", (int)pthread_self());  
	printf("  Task 2 running..\n");  
	printf("%d\n", a);  
}  
int main()  
{  
    printf("~~~~~~~~~~~");  
    thpool_t* thpool;  
    int i;  
    thpool = thpool_init(5);  
    puts("Adding 20 tasks to threadpool");  
    //int a=54;  
    for (i=0; i<20; i++){  
        thpool_add_work(thpool, (void*)task1, NULL);  
        thpool_add_work(thpool, (void*)task2, NULL);  
    };  
  
  
    puts("Will kill threadpool");  
    thpool_destroy(thpool);  
      
}
