CC=gcc
build-lib:
	${CC} -c libsock.c libsock.h
	ar -r libtest.a libsock.o libsock.h.gch

all:
	${CC} -Wall -g testsock.c -ltest -L. -o test

clear:
	rm -rfv libsock.o libsock.h.gch test
