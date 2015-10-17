#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

int mysignal(int sig_n){
  if(sig_n == SIGINT)
    printf ("SIGINT\n");
  if (sig_n==SIGQUIT){
    printf ("SIGQUIT\n");
  }
}

int main(int argc, char *argv[])
{
  signal(SIGINT,mysignal);
  signal(SIGQUIT,mysignal);
  pause();
  exit(0);
  return 0;
}



