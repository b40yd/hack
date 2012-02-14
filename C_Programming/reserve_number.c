#include <stdio.h>
#include<stdlib.h>
#include<math.h>
int reserve(int n,int rlt);
int main(int argc, char *argv[])
{
  char str[16]={0};
  int n=0;
  sscanf("abcdef, 10","%s%d",str,&n);
  printf ("%s%d\n%d\n",str,n,reserve(123,0));
  
  return 0;
}

int reserve(int n,int rlt)
{
    if(n<10)
    {
      rlt = rlt*10+n;
      return rlt;
    }    
    else
    {
      reserve(n/10,rlt*10+n%10);
    }    
} 

