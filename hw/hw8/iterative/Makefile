all: client server
CC = gcc
CFLAGS = -ggdb 

client: client.c
	$(CC) $(CFLAGS) client.c -o client
server: server.c
	$(CC) $(CFLAGS) server.c -o server

.PHONY: clean
clean:
	rm -rf *.o client server
strip:
	strip -g -s -d client server

