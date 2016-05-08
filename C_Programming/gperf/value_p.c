#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "lex.h"

typedef unsigned long VALUE;

typedef struct pleb_value_s {
	VALUE value;
} pleb_value_t;


int main(){
	VALUE value;
	pleb_value_t *pvalue;
	pvalue = (pleb_value_t *)malloc(sizeof(pleb_value_t));
	pvalue->value = 0x0001;
	value = (VALUE)pvalue;
	printf("%ld\n",value);
	
	pleb_value_t *pleb_value = ((pleb_value_t *)value);
	
	printf("pleb_value->value:\t%ld\n",pleb_value->value);
	
	printf("1<<1%d\n",0x01<<1);
	printf("2<<1%d\n",0x02<<1);
	printf("3<<1%d\n",0x03<<1);
	printf("4<<1%d\n",0x04<<1);
	printf("5<<1%d\n",0x05<<1);
	printf("6<<1%d\n",0x06<<1);
	printf("7<<1%d\n",0x07<<1);
	const struct kwtable *kwt;
	kwt = rb_reserved_word("while",strlen("while"));
	if(kwt)
		printf("kwt:\t%d\n",kwt->name);
	free(pvalue);
	
}
