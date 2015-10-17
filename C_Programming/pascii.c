#include <stdio.h>

/*
 * ascii()函数打印26个字幕
 * pascii()函数 输入对应的ASCII对应的值，并将其打印输出。
 * sound()编写一个发出警告声音，并打印字符串
 */
int ascii(void){
     int i = 0,a = 65;
     for (i = 0; i < 26; ++i)
     {
	  printf ("%c\t",a);
	  a++;
	  if (i==25)
	  {
	       printf ("\n");
	  }
     }
     //return 1;
}
int pascii(void){
     int a;
     scanf("%d",&a);
     printf ("%c\n",a);
     //return 1;
}
int main(int argc, char *argv[])
{
     ascii();
     pascii();
     printf ("\007Startled by the sodden sound,Sally shouted,\"By the Great Pumpkin,what was that!\"\n");
     return 0;
}


