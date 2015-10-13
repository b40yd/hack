#ifndef _THREAD_POOL_  
#define _THREAD_POOL_  

#include "global.h"  
/** 
定义一个任务节点 
**/  
typedef void* (*FUNC)(void* arg);  


typedef struct _thpool_job_t{  
//  void* (*function)(void* arg);    //函数指针  
FUNC             function;  
void*                   arg;     //函数参数。  
struct _thpool_job_t* prev;     // 指向上一个节点  
struct _thpool_job_t* next;     //指向下一个节点  
} thpool_job_t;  

/** 
定义一个工作队列 
**/  

typedef struct _thpool_job_queue{  
thpool_job_t*    head;            //队列头指针   
thpool_job_t*    tail;             // 队列末尾指针  
int              jobN;                    //任务数  
sem_t*           queueSem;            //x信号量  
}thpool_jobqueue;   

/** 
线程池 
**/  

typedef struct _thpool_t{  
pthread_t*      threads;    ////线程指针数  
int             threadsN;    //// 线程数  
thpool_jobqueue* jobqueue;   // 指向队列指针  
}thpool_t;  

typedef struct thread_data{                              
pthread_mutex_t *mutex_p;  
thpool_t        *tp_p;  
}thread_data;  

//初始化线程池内部的线程数  
thpool_t*  thpool_init(int threadN);  

void thpool_thread_do(thpool_t* tp_p);  

int thpool_add_work(thpool_t* tp_p, void *(*function_p)(void*), void* arg_p);  

void thpool_destroy(thpool_t* tp_p);  



int thpool_jobqueue_init(thpool_t* tp_p);  



void thpool_jobqueue_add(thpool_t* tp_p, thpool_job_t* newjob_p);  

int thpool_jobqueue_removelast(thpool_t* tp_p);  

thpool_job_t* thpool_jobqueue_peek(thpool_t* tp_p);  

void thpool_jobqueue_empty(thpool_t* tp_p);  

#endif  