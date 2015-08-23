PORT = 6193
PROGRAMS = server client
S = -std=c99 -ggdb

both: $(PROGRAMS)

server: server.c
	gcc $S server.c -lpthread -o server

client: client.c Timer.c Timer.h
	gcc $S client.c Timer.c -lpthread -o client

test: both
	./server $(PORT) &
	echo Starting client
	./client `hostname` $(PORT)
	ls -lr Thread_*

clean:
	/bin/rm -rf $(PROGRAMS) Thread_*
