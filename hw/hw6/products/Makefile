OBJS = products.o
CC = gcc
CC_FLAGS = -ggdb -Wall -c

products: ${OBJS}
	${CC} ${OBJS} -o products

products.o: products.c
	${CC} ${CC_FLAGS} products.c
clean:
	rm -rf ${OBJS} products
strip:
	strip -g -s -d products 
