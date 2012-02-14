#include<stdio.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
     char ch;
     while((ch=getchar())!='#'){
	  ch = toupper(ch);
	  switch(ch){
	  case 'A':
	       printf ("helloword\n");break;
	  default:break;
	  }
     }
     return 0;
}

