#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

#include <iostream>
#include <string>

#include "message/proto/User.pb.h"
#include "message/proto/Messages.pb.h"

#define MAXLINE 4096

using namespace std;

int main (int argc, char ** argv)
{
  int    sockfd;
  //char   recvbuf[MAXLINE];
  struct sockaddr_in servaddr;
  Users user;
  Messages::Message mmsg;
  
  if (argc != 2)
    {
      printf ("usage: %s <ip address>.\n", *argv);
      exit (1);
    }

  if ((sockfd = socket (AF_INET, SOCK_STREAM, 0)) < 0)
    {
      perror ("socket");
      exit (1);
    }

  memset (&servaddr, 0x00, sizeof (servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port   = htons (1300);
  if (::inet_pton (AF_INET, *(argv+1), &servaddr.sin_addr.s_addr) < 0) {
    perror ("inet_pton");
    exit (1);
  }

  if ((connect (sockfd, (struct sockaddr *) &servaddr, sizeof (servaddr))) < 0) {
    perror ("connect");
    exit (1);
  }

  // send
  char sSendBuffer[MAXLINE];
  (void) memset (sSendBuffer, 0x00, sizeof (sSendBuffer));
  user.set_id(1);
  user.set_username("demo");
  user.set_mobile("110");
  user.set_email("demo@secdomain.com");
  string sStr,sendStr;
  user.SerializeToString (&sStr);
  mmsg.set_type(Messages::HOME);
  mmsg.set_msgbody(sStr); 
  mmsg.SerializeToString (&sendStr);
  (void) memcpy (sSendBuffer, sendStr.c_str(), sendStr.size());
  write (sockfd, sSendBuffer, sizeof (sSendBuffer));

  close(sockfd);
  return 0;
}
