CC	=	gcc
CFLAG	= 	-Wall -g
CORE_DEPS	=	main.o thread_pool.o
LIB	=	-lpthread
test:$(CORE_DEPS)
	${CC} -Wall -g ${LIB} -L. $(CORE_DEPS) -o $@

clean:
	@rm -rfv test *.o
