#include <unistd.h>
#include <signal.h>
#include <sys/param.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>

void init_daemon(void)
{
    int pid;
    int i;
    if(pid=fork()){
        printf("parent: %d\n", pid);
        exit(0);        //是父进程，结束父进程
    }
    else if(pid< 0){
        printf("%d\n", pid);
        exit(1);        //fork失败，退出
    }
    //是第一子进程，后台继续执行
    printf("%d\n", getdtablesize());
    setsid();           //第一子进程成为新的会话组长和进程组长
    for (i = 0; i < getdtablesize(); i++)
    {
        /* code */
        printf("%d\n", i);
        close(i);
    }

    //并与控制终端分离
    // if(pid=fork()){
    //     printf("first child: %d\n", pid);
    //     exit(0);        //是第一子进程，结束第一子进程
    // }
    // else if(pid< 0){
    //     printf("%d\n", pid);
    //     exit(1);        //fork失败，退出
    // }
    // //是第二子进程，继续
    // //第二子进程不再是会话组长
    // for(i=0;i< NOFILE;++i){  //关闭打开的文件描述符
    //     //printf("NOFILE: %d - %d\n", NOFILE, i);
    //     close(i);
    // }
    // printf("The child process PID is %d.\n",getpid());
    // printf("The Group ID is %d.\n",getpgrp());
    chdir("/tmp");      //改变工作目录到/tmp
    umask(0);           //重设文件创建掩模
    return;
}

