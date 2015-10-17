#include <stdio.h>

int main(int argc,int *args[]){
	FILE * f = NULL;
	char buf;
	f = fopen("db.scm","rb");
	buf=fgetc(f);
	while(buf!=EOF){
		putchar(buf);
		buf=fgetc(f);
	}
	fclose(f);
}
