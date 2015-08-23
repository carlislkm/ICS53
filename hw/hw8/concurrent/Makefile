all: client server
CC = gcc
CFLAGS = -ggdb

client: client.c
	$(CC) $(FLAGS) client.c -o client
server: server.c
	$(CC) $(FLAGS) server.c -o server

clean: 
	rm -rf *.o client server
strip:
	strip -g -s -d client server

