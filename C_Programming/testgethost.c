#include <netdb.h>
#include <sys/socket.h>
int main(int argc, char **argv)
{
	char *ptr,**pptr;
	struct hostent *hptr;
	char str[32];
	/* 取得命令后第一个参数，即要解析的域名或主机名 */
	ptr = argv[1];
	/* 调用gethostbyname()。调用结果都存在hptr中 */
	if( (hptr = gethostbyname(ptr) ) == NULL )
	{
	printf("gethostbyname error for host:%s\n", ptr);
	return 0; /* 如果调用gethostbyname发生错误，返回1 */
	}
	/* 将主机的规范名打出来 */
	printf("official hostname:%s\n",hptr->h_name);
	/* 主机可能有多个别名，将所有别名分别打出来 */
	for(pptr = hptr->h_aliases; *pptr != NULL; pptr++)
	printf(" alias:%s\n",*pptr);
	/* 根据地址类型，将地址打出来 */
	switch(hptr->h_addrtype)
	{
	case AF_INET:
	case AF_INET6:
	pptr=hptr->h_addr_list;
	/* 将刚才得到的所有地址都打出来。其中调用了inet_ntop()函数 */
	for(;*pptr!=NULL;pptr++)
	printf(" address:%s\n", inet_ntop(hptr->h_addrtype, *pptr, str, sizeof(str)));
	break;
	default:
	printf("unknown address type\n");
	break;
	}
	return 0;
} 