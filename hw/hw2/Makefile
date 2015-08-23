OBJS=strlib.o strtest.o
CC=gcc
CFLAGS=-std=c99 -ggdb

all: strtest

strtest: ${OBJS}
	${CC} -o strtest ${OBJS}
	
.cpp.o: 
	${CC} -c $< -o $@

.PHONY: clean
clean:
	rm -rf ${OBJS} strtest
