#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#define FIFO "test"
 
int main(int argc, char *argv[])
{
  char buf[100];
  int f;
  if((mkfifo(FIFO,O_CREAT|O_EXCL)<0)&&(errno!=EEXIST))
    printf ("Cannot create fifoserver!\n");
  memset(buf,0,sizeof(buf));
  
  f = open(FIFO,O_RDONLY|O_NONBLOCK,0);
  if(f == -1){
    perror("fifo");
    exit(1);
  }
  
  while(1){
    memset(buf,0,sizeof(buf));
    if(read(f,buf,100) == -1)
      printf ("NO read data!\n");
    printf ("%s\n",buf);
    sleep(3);
  }
  pause();
  unlink(FIFO);
  return 0;
}



