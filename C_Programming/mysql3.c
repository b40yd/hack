#include <stdlib.h>
#include <stdio.h>
#include "mysql.h"

MYSQL  my_connects;
MYSQL_RES *res_ptr;
MYSQL_ROW sqlrow;

int main(int argc, char *argv[])
{
  int res;
  mysql_init(&my_connects);
  if(mysql_real_connect(&my_connects,"localhost","root","","csql",0,NULL,0)){
    printf ("Connection success!\n");
    res = mysql_query(&my_connects,"select * from user");
    if (res){
      printf ("SELECT error:%s\n",mysql_error(&my_connects));
    }else{
      res_ptr = mysql_store_result(&my_connects);
      if (res_ptr){
	printf ("Retrieved %lu rows\n",(unsigned long)mysql_num_rows(res_ptr));
	while((sqlrow=mysql_fetch_row(res_ptr))){
	  //printf ("fetch data ...\n");
	  printf ("%s\t %s\t %s\n",sqlrow[0],sqlrow[1],sqlrow[2]);
	}
	if (mysql_errno(&my_connects)){
	  fprintf(stderr,"Retrive error:%s\n",mysql_error(&my_connects));
	}
	mysql_free_result(res_ptr);	

      }
    }
    mysql_close(&my_connects);
  }else{
    fprintf(stderr,"Connection failed!\n");
    if(mysql_errno(&my_connects)){
      fprintf(stderr,"Connection error %d: %s\n",
	      mysql_errno(&my_connects),mysql_error(&my_connects));
    }
  }
  return EXIT_SUCCESS;
}
