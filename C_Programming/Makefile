#ifneq ($(KERNELRELEASE),)

#obj-m := hellomod.o

#else

#KDIR := /lib/modules/2.6.35-22-generic/build

#all:
#	make -C $(KDIR) M=$(PWD) modules
#clean:
#	rm -f *.ko *.o *.mod.o *.mod.c *.symvers
#endif

# Use GCC, if you have it installed.
CC=gcc	
# Tell the C compiler where to find <libguile.h>
CFLAGS='guile-config compile'
# Tell the linker what libraries to use and where to find them.
LIBS='guile-config link'
simple-guile: simple-guile.o
	${CC} simple-guile.o ${LIBS} -o simple-guile
simple-guile.o: simple-guile.c
	${CC} -c ${CFLAGS} simple-guile.c
# compile daemon program
daemon:
	${CC} -g -o test_daemon init.c test_daemon.c