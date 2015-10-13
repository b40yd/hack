OBJS	= test.o
CC	= ccache gcc
CFLAGS	= -Wall -Werror
CDEBUG	= -g
LIB	= -ltest

all:
	$(CC) -shared -fPIC -o libtest.so libtest.c
	$(CC) $(CFLAGS) $(CDEBUG) -o test test.c -L. $(LIB)
	$(CC) $(CFLAGS) $(CDEBUG) -o opentest opentest.c -ldl

clean:
	@rm -rfv *.so *.o test opentest
