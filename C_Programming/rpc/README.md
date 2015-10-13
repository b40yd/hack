## Compiler RPC

gcc -Wall -o test_server test_clnt.c test_srv_func.c test_svc.c
gcc -Wall -o test_client test_clnt_func.c test_clnt.c 

###error
fisrt start rpcbind.if not installed it.
you can `apt-get install rpcbind`

###INFO
Linux manual: man rpcgen.

