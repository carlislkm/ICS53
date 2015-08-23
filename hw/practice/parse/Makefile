OBJS = my_shell.o
CC = gcc
CC_FLAGS = -ggdb -Wall -c 

my_shell: ${OBJS}
	${CC} ${OBJS} -o my_shell

my_shell.o: my_shell.c
	${CC} ${CC_FLAGS} my_shell.c

clean:
	rm -rf ${OBJS} my_shell

strip:
	strip -g -s -d my_shell
