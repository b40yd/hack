OBJS	=	libtest.o
CPP	=	ccache g++
STATIC	=	ar 
# options for compiler
CFLAGS      = -Wall -Werror

# is debug? (for development)
CDEBUG      = -g

STATIC_LIBNAME	=	libtest.a
SHARED_LIBNAME	=	libtest.so

all:
	@echo "make static"	
static:$(OBJS)
	$(STATIC) -crv $(STATIC_LIBNAME) $(OBJS)
shared:
	$(CPP) -shared -o $(SHARED_LIBNAME) -fPIC libtest.cpp

%.o:%.cpp
	$(CPP) $(CFLAGS) $(CDEBUG) -o $@ -c $<
%.o:%.cc
	$(CPP) $(CFLAGS) $(CDEBUG) -o $@ -c $<
%.o:%.c
	$(CPP) $(CFLAGS) $(CDEBUG) -o $@ -c $<

.PHONY: clean

clean:
	@rm -rfv $(OBJS) $(STATIC_LIBNAME) $(SHARED_LIBNAME)
