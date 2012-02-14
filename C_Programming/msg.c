#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct msg{
	int mtype;
	char data[255];
};

int main(int argc,int *argv[]){
	key_t key;
	int msgid;
	int ret;
	struct msg msgbuf;
	key = ftok("/tmp/1",'a');
	
	msgid = msgget(key,IPC_CREAT|IPC_EXCL|0666);
	if(msgid==-1)
		printf("get msgid error!");
	msgbuf.mtype = getpid();
	strcpy(msgbuf.data,"wowowowowowow");
	ret = msgsnd(msgid,&msgbuf,sizeof(msgbuf.data),IPC_NOWAIT);
	if(ret ==-1)
	   printf("msgsnd error!");
	   
	 memset(&msgbuf,0,sizeof(msgbuf));
	 
	 ret = msgrcv(msgid,&msgbuf,sizeof(msgbuf.data),getpid(),IPC_NOWAIT);
	 if(ret == -1)
	 	printf("read msg error!");
	 printf("%s\n",msgbuf.data);
	
	return 0;	
}
