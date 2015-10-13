#include "global.h"  
#include "thread_pool.h"  
#include <errno.h>  

static int thpool_keepalive = 1;  

/* 创建互斥量，并初始化 */  
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; /* used to serialize queue access */  

thpool_t*  thpool_init(int threadN)  
{  
	thpool_t* thpool;  
	if(!threadN || threadN < 1)  
		threadN = 1;  
	///分配线程池内存  
	thpool = (thpool_t*) malloc(sizeof(thpool_t));  
	if(thpool ==NULL)  
	{  
		printf("malloc thpool_t error");  
		return NULL;  
	}  
	//分配线程数  
	thpool->threadsN = threadN;  
	thpool->threads =(pthread_t*) malloc(threadN*sizeof(pthread_t));  
	if(thpool->threads == NULL)  
	{  
		printf("malloc thpool->threads error");  
		return NULL;  
	}  
	if(thpool_jobqueue_init(thpool))  
		return NULL;  

	thpool->jobqueue->queueSem =(sem_t*)malloc(sizeof(sem_t));  
	sem_init(thpool->jobqueue->queueSem,0,1);  
	int t;  
	for(t = 0;t< threadN ;t++)  
	{  
		pthread_create(&(thpool->threads[t]),NULL,(void *)thpool_thread_do,(void*)thpool);  
	}  
	  
	return thpool;  
}  

void thpool_destroy(thpool_t* tp_p)  
{  
	int i ;  
	thpool_keepalive = 0;  
	  
	for(i = 0;i < (tp_p->threadsN); i++)  
	{  
		if(sem_post(tp_p->jobqueue->queueSem))  
		{  
			fprintf(stderr, "thpool_destroy(): Could not bypass sem_wait()\n");  
		}  

	}  
	if(sem_post(tp_p->jobqueue->queueSem)!=0)  
	{  
		fprintf(stderr, "thpool_destroy(): Could not destroy semaphore\n");  
	}  
	for(i = 0;i < (tp_p->threadsN); i++)  
	{  
		pthread_join(tp_p->threads[i],NULL);  
	}  
	thpool_jobqueue_empty(tp_p);  
	  
	free(tp_p->threads);  
	free(tp_p->jobqueue->queueSem);  
	free(tp_p->jobqueue);  
	free (tp_p);  
  
}  
////对双向队列初始化  
/* Initialise queue */  
int thpool_jobqueue_init(thpool_t* tp_p){  
	tp_p->jobqueue=(thpool_jobqueue*)malloc(sizeof(thpool_jobqueue));      /* MALLOC job queue */  
	if (tp_p->jobqueue==NULL) return -1;  
	tp_p->jobqueue->tail=NULL;  
	tp_p->jobqueue->head=NULL;  
	tp_p->jobqueue->jobN=0;  
	return 0;  
}  

////  
void thpool_thread_do(thpool_t* tp_p)  
{  
while(thpool_keepalive ==1)  
{  
	if(sem_wait(tp_p->jobqueue->queueSem)) ///线程阻塞,等待通知 直到消息队列有数据  
	{  
		perror("thpool_thread_do(): Waiting for semaphore");  
		exit(1);  
	}  
	if(thpool_keepalive)  
	{ 
		printf("testing...\n"); 
		//(void*)(*function)(void *arg);  
		FUNC function;  
		void* arg_buff;  
		thpool_job_t*  job_p;  
		  
		pthread_mutex_lock(&mutex);  
		 job_p = thpool_jobqueue_peek(tp_p);  
		function = job_p->function;  
		arg_buff = job_p->arg;  
		if(thpool_jobqueue_removelast(tp_p))  
			return ;  
		pthread_mutex_unlock(&mutex);  
		function(arg_buff);   //运行 你的方法。  
		//free(job_p);         ////释放掉。  
	}  
	else  
	{  
		return ;  
	}  
		  
}  
return ;  
}  

//得到第一个队列的一个节点  
thpool_job_t* thpool_jobqueue_peek(thpool_t* tp_p)  
{  
	return tp_p->jobqueue->tail;  
}  
/////删除队列的最后一个节点  
int thpool_jobqueue_removelast(thpool_t* tp_p)  
{  
	if(tp_p ==NULL)  
		return -1;  
	thpool_job_t* theLastJob;  
	theLastJob = tp_p->jobqueue->tail;  
	switch(tp_p->jobqueue->jobN)  
	{  
		case 0:  
			return -1;  
		case 1:  
			tp_p->jobqueue->head =NULL;  
			tp_p->jobqueue->tail =NULL;  
			break;  
		default:  
			theLastJob->prev->next = NULL;  
			tp_p->jobqueue->tail = theLastJob->prev;  
				  
	}  
	(tp_p->jobqueue->jobN)--;  
	int reval;  
	sem_getvalue(tp_p->jobqueue->queueSem,&reval);  
	return 0;     
}  

void thpool_jobqueue_add(thpool_t* tp_p, thpool_job_t* newjob_p)  
	{  
	newjob_p->next = NULL;  
	newjob_p->prev = NULL;  
	thpool_job_t* oldFirstJob;  
	oldFirstJob = tp_p->jobqueue->head;  
	  
	switch(tp_p->jobqueue->jobN)  
	{  
		case 0:  
			tp_p->jobqueue->head = newjob_p;  
			tp_p->jobqueue->tail = newjob_p;  
			break;  
		default:  
			oldFirstJob->prev = newjob_p;  
			newjob_p->next = oldFirstJob;  
			tp_p->jobqueue->head = newjob_p;  
	  
	}  
	(tp_p->jobqueue->jobN)++;  
	sem_post(tp_p->jobqueue->queueSem);  
	  
	int reval;  
	sem_getvalue(tp_p->jobqueue->queueSem,&reval);  
	return;  
}  

/////将消息加入线程池  
int thpool_add_work(thpool_t* tp_p, void* (*function_p)(void*), void* arg_p)  
{  
	thpool_job_t* newjob;  
	newjob = (thpool_job_t*) malloc(sizeof(thpool_job_t));  
	  
	if(newjob ==NULL)  
	{  
		fprintf(stderr, "thpool_add_work(): Could not allocate memory for new job\n");  
		exit(1);  
	}  
	newjob ->function = function_p;  
	newjob ->arg      = arg_p;  
	pthread_mutex_lock(&mutex);  
	thpool_jobqueue_add(tp_p,newjob);  
	pthread_mutex_unlock(&mutex);       
	return 0;  
}  

///清空队列  
void thpool_jobqueue_empty(thpool_t* tp_p)  
{  
	thpool_job_t* curjob;  
	curjob = tp_p->jobqueue->tail;  
	  
	while(tp_p->jobqueue->jobN)  
	{  
		tp_p->jobqueue->tail = curjob->prev;  
		free (curjob);  
		curjob = tp_p->jobqueue->tail;  
		(tp_p->jobqueue->jobN)--;  
	}  
	tp_p->jobqueue->head = NULL;  
	tp_p->jobqueue->tail = NULL;  
}  
