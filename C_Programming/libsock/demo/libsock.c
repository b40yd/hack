#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <errno.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "libsock.h"

#define BUFSIZE 1024

int connection(server *serv)
{
  int sockfd = 0;
  struct sockaddr_in server_addr;
  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 ) {
    return -1;
  };
  //set init value
  bzero(&server_addr, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(serv->port);
  //traslate IP addr to net addr
  if (inet_pton(AF_INET, serv->ip_addr, &server_addr.sin_addr) <= 0 ){
    return -2;
  };
  if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0){
    return -3;
  }
  return sockfd;
}

char *request(int sockfd, char *header,char *results)
{
  int ret = 0;
  fd_set   t_set;
  struct timeval  tv;
  if(strlen(header) == 0){
    close(sockfd);
	printf("header length eqval zero!\n");
    return results;
  }
  results = (char *)malloc(4089);
  ret = write(sockfd,header,strlen(header));
  if(ret > 0){
    FD_ZERO(&t_set);
    FD_SET(sockfd, &t_set);
    while(1){
	sleep(2);
      tv.tv_sec = 0;
      tv.tv_usec = 0;
      int handle = 0;
      handle = select(sockfd +1, &t_set,NULL,NULL,&tv);
      if(handle == 0){
	printf("server close..\n");
        break;
	}
      if(handle > 0){
        char * tmp_buf = NULL;
        tmp_buf = (char *)malloc(BUFSIZE);
        int read_num = 0;
        read_num = read(sockfd,tmp_buf,BUFSIZE);
        if(read_num == 0){
	  printf("Not readed data...\n");
          break;
        }
	printf(tmp_buf);
        strcat(results,tmp_buf);
	free(tmp_buf);
      }
    }
  }else{
	printf("write %d bytes",ret);
  }
  close(sockfd);
  return results;
}
