iocmp: iocmp.o Timer.o 
	gcc -ggdb iocmp.o Timer.o -o iocmp

iocmp.o: iocmp.c Timer.h
	gcc -ggdb -c iocmp.c

Timer.o: Timer.c Timer.h
	gcc -ggdb -c Timer.c

clean:
	rm iocmp.o Timer.o iocmp
