#include <unistd.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
  int p_pid[2];
  char buf[80];
  pid_t p_id;
  int read_buf;
  memset(buf,0,sizeof(buf));
  if(pipe(p_pid)<0){
    printf("create pipe error!");
    return -1;
  }

  if((p_id = fork())== 0){
    printf ("\n");
    close(p_pid[1]);
    sleep(2);
    if ((read_buf=read(p_pid[0],buf,80))>0) {
      printf ("%d %s\n",read_buf,buf);
    }
    close(p_pid[0]);
    exit(0);
  }else if (p_pid>0){
    close(p_pid[0]);
    if(write(p_pid[1],"Wo cao!",10)!=-1)
      printf ("Wo cao!Writing done!\n");
    close(p_pid[1]);
    sleep(3);
    waitpid(NULL);
    exit(0);
  }
  return 0;
}

