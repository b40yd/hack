SRCS	=	$(wildcard *.c)  
  
OBJS	=	$(SRCS:.c=.o)  
  
CC	=	gcc  
  
INCLUDES	=	-I/  
  
LIBS	=	-L/ -lpthread  
  
CCFLAGS	=	-g -Wall -O0  
  
main:$(OBJS)  
	$(CC) $^ -o $@ $(INCLUDES) $(LIBS)  
  
%.o:%.cpp  
	$(CC) -c $<$(CCFLAGS)  
  
  
clean:  
	@rm -rfv *.o  
.PHONY:clean 
