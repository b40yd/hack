#include <stdio.h>

struct command_s {
    char	*name;
    int		type;
    char	*set;
    int		conf;
    int		offset;
    void	*post;
};

typedef struct command_s command_t;
int main()
{
	command_t commands[] = {
		{"first",1,"a",1,1,NULL},
		{"mid",2,"b",2,2,NULL},
		{"last",3,"c",3,3,NULL}
	};
	
	int n = sizeof(commands)/sizeof(commands[0]);
	printf("array length:%d\n",n);
	
	for(int i = 0;i<3;i++){
		printf("name:%s type:%d set:%s conf:%d offset:%d post:%s\n",
			commands[i].name,
			commands[i].type,
			commands[i].set,
			commands[i].conf,
			commands[i].offset,
			commands[i].post
			);
	}
	
	return 0;
}
