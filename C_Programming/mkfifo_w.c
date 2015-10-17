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
  f = open(FIFO,O_WRONLY|O_NONBLOCK,0);
  if(f==-1)
    printf ("open fifo error!\n");
  strcpy(buf,argv[1]);
  if(write(f,buf,100) == -1)
    printf ("write data error!\n");
  printf ("your write data: %s\n",buf);
  return 0;
}
