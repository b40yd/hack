#
# makefile of test for protobuf
#

# set src, dst directory and flags for protobuf
PROTOC      = protoc
PBFLAGS     = --cpp_out
PBSRC       = ./proto
PBDST       = ./message

# which c plus plus compiler
CPP         = g++

# options for compiler
CFLAGS      = -Wall -Werror

# is debug? (for development)
CDEBUG      = -g

# libraries
LIB         = -lprotobuf

# objects

MESSAGEOBJS = message/proto/User.pb.o \
	message/proto/Messages.pb.o 
SERVEROBJS  = server.o 
CLIENTOBJS  = client.o 
OBJS        = $(MESSAGEOBJS) $(SERVEROBJS) $(CLIENTOBJS)

# binary
BIN	        = server client

# where are include files kept
INC	        = -I. -I./message 

# rock..
all: clean precompile_protobuf $(BIN)

precompile_protobuf:
	$(PROTOC) $(PBFLAGS)=$(PBDST) $(PBSRC)/*

server:$(SERVEROBJS) $(MESSAGEOBJS)
	$(CPP) $(CFLAGS) $(CDEBUG) -o $@ $(SERVEROBJS) $(MESSAGEOBJS) $(LIB)
client:$(CLIENTOBJS) $(MESSAGEOBJS)
	$(CPP) $(CFLAGS) $(CDEBUG) -o $@ $(CLIENTOBJS) $(MESSAGEOBJS) $(LIB)

%.o:%.cpp
	$(CPP) $(CFLAGS) $(CDEBUG) $(INC) -o $@ -c $<
%.o:%.cc
	$(CPP) $(CFLAGS) $(CDEBUG) $(INC) -o $@ -c $<

.PHONY: clean

clean:
	-rm -rf $(OBJS) $(BIN) ./message/proto *~

