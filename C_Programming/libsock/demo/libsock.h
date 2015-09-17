#ifndef __LIBSOCK_H_
#define __LIBSOCK_H_

typedef struct server_info{
  char *ip_addr;
  int port;
}server;

int connection(server *serv);

char *request(int sockfd, char *buf, char *results);

#endif
