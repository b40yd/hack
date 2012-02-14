#include <stdlib.h>
#include <stdio.h>

#include "mysql.h"

int main(int argc, char *argv[])
{
  MYSQL my_connect;
  mysql_init(&my_connect);
  if (mysql_real_connect(&my_connect,"localhost",
			 "root","1","csql",0,NULL,0)){
    printf ("Connect success\n");
    mysql_close(&my_connect);
  }else{
    fprintf(stderr,"Connect failed\n");
    if (mysql_errno(&my_connect)){
      fprintf(stderr,"Connection error %d: %s\n",
	      mysql_errno(&my_connect),mysql_error(&my_connect));
    }
  }
  return EXIT_SUCCESS;
}


