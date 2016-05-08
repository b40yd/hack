CC=gcc
CFLAGS=-Wall -g
CORE_DEFS=value_p.c
CORE_OBJS=value_p.o
RM=rm

values:$(CORE_OBJS)
	$(CC) $(CFLAGS) -o $@ $<

lex.h:test.gperf
	gperf -C -P -p -G -o -t -N rb_reserved_word $< > lex.h

%.o:$(CORE_DEFS)
	@echo $(CORE_DEFS) compiling...
	$(CC) $(CFLAGS) -c $<

clean:
	$(RM) -rfv *.o values lex.h
