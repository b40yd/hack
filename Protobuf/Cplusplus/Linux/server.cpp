#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <time.h>

#include <iostream>
#include <string>

#include "message/proto/User.pb.h"
#include "message/proto/Messages.pb.h"

#define MAXLINE 4096
using namespace std;
//using namespace Messages;

int main(int argc, char **argv)
{
  int    listenfd, connfd;
  socklen_t clilen;
  struct sockaddr_in servaddr, cliaddr;
  Users user;
  Messages::Message mmsg;

  if ((listenfd = socket (AF_INET, SOCK_STREAM, 0)) < 0)
    {
      perror ("socket");
      exit (1);
    }

  int opt = 1;
  setsockopt (listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof (opt));

  (void) memset (&servaddr, 0x00, sizeof (servaddr));
  servaddr.sin_family      = AF_INET;
  servaddr.sin_port        = htons (1300);
  servaddr.sin_addr.s_addr = htonl (INADDR_ANY);

  if (bind (listenfd, (struct sockaddr *) &servaddr, sizeof (servaddr)) < 0)
    {
      perror ("bind");
      exit (1);
    }

  listen (listenfd, 5);

  while (1)
    {
      clilen = sizeof (cliaddr);
      if ((connfd = accept (listenfd, (struct sockaddr *) &cliaddr, \
                            &clilen)) < 0)
        {
          perror ("accept");
          exit (1);
        }

      // recv
      char recvbuf[MAXLINE];
      int n;
      if ((n = read (connfd, recvbuf, sizeof (recvbuf))) > 0) {
        recvbuf[n] = 0x00;

        //int index_ = *(int*) recvbuf;
        //printf ("index = %i\n", index_);
        string sRecvStr;
        sRecvStr = recvbuf;
	mmsg.ParseFromString(sRecvStr);
	cout << "Msg Type:" << mmsg.type() << endl;
	cout << "Msg String:"<<mmsg.msgbody()<<endl;
	/*
	user.ParseFromString(sRecvStr);
        cout << "User Info:" << endl;
        cout << "ID:" << user.id() << endl;
        cout << "USERNAME:" << user.username() << endl;
        cout << "MOBILE:" << user.mobile() << endl;
        cout << "EMAIL:" << user.email() << endl;
     	*/
       }
      close(connfd);
    }
  close(listenfd);
  return 0;
}
