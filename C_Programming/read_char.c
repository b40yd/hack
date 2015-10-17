#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

#define STOP '|'
int main(int argc, char *argv[])
{
     char c,prev;//C读取字符 前一个读入字符
     long n_chars = 0L;//字符数
     int n_lines = 0,n_words = 0,p_lines = 0; //行数，单词数，不完整的行数
     bool inword = false;//如果c在一个单词中，则inword等于true
     printf ("Enter text to be analyzed (| to terminate):\n");
     prev = '\n';
     while((c=getchar())!=STOP){
	  n_chars++;
	  if (c == '\n')
	       n_lines++;
	  if (isspace(c) && !inword)
	  {
	       inword = true;
	       n_words++;
	  }
	  if (isspace(c) && inword)
	       inword = false;
	  prev = c;
     }
     if(prev != '\n')
	  p_lines=1;
     printf ("characters = %ld,word = %d,lines = %d,\n",n_chars,n_words,n_lines);
     printf ("partial lines = %d\n",p_lines);
     return 0;
}


