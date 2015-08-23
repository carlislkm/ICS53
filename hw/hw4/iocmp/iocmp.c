//Kevin Carlisle 
// iocmp
//ICS 53 Hw 4

//*
// Compare the difference in performance 
// between C library functions and System Calls.
//*


/*
UNIX I/O Exercise: The purposes of this assignment are (1) to become familiar with 
UNIX I/O system calls and (2) to see the difference in performance between C library 
functions and system calls.  The program you write should do the following.
Contain a main program that prints out the time to copy the file using each of 
three methods.  The name of the input file and the name of the output file should
 come from the command line arguments to your program (via argv).
Method 1: Implement a function that uses fopen(), fgetc() and fputc(), 
then fclose() to copy the input file to the output file one character at a time.
 Each loop iteration will read and write a single character but I/O will be buffered
  by the stdio library routines which make system calls read() and write() to fill or 
  flush the stdio buffers.
Method 2: Implement a function that uses the system calls open(), read() and write(), 
then close() to copy the input file to the output file one character at a time. Each 
loop iteration will read and write just a single character.  There will be no buffering 
because you will be making system calls to read and write each character.
Method 3: Implement a function that uses the system calls open(), read() 
and write(), then close() to copy the input file to the output file one buffer at a 
time (the buffer should be of size "BUFSIZ", which is declared in the <stdio.h> include
 file and each read or write should write as many characters as possible per loop 
 iteration up to BUFSIZ).
Once these functions are implemented, test them out by having them perform 
their work N times each (where N is a command-line argument).  Display the 
amount of wallclock, user, and system time it takes for each of the three 
method functions to execute.
Use a Timer to measure the performance of each of the three approaches to 
copying a file.  Use /usr/share/dict/linux.words for the input file to copy.

Your program will take three arguments: argv[1] will be a number 1, 2, or 3 
indicating which of the above methods your program should use to make the copy;
 argv[2] will be the input file name; argv[3] will be the output file name. 
 A given invocation of your program should make one copy using the method passed 
 in for argv[1].  The output should be just the time required to make the copy. 
  To ensure you measure just the file copy in each case, start the timer 
  (with Timer_init()) right before you start the copy but after you have open()ed 
  the files and stop the timer (or get the elapsed user time) just after you have
   copied the last item from the file but before close()ing of the files.  
   Print the elapsed user time(to stdout) after you close the output files.

*/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "Timer.h"

void method1(char* iFile, char* oFile)
{
	FILE* fRead;
	FILE* fWrite;
	int n = 0;
	int c;
	double time;

	Timer_start();

	fRead =  fopen(iFile, "r");
	fWrite = fopen(oFile, "w");

	while( (c = fgetc(fRead)) != EOF)
	{
		fputc(c, fWrite);
	}
	Timer_elapsedUserTime(&time);
	fclose(fRead);
	fclose(fWrite);
	printf("Time Method 1: %g\n", time);

}

void method2(char* iFile, char* oFile)
{	
		int fRead   = open(iFile, O_RDONLY);
		int fWrite  = open(oFile, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);//O_CREAT |

		char c;
		double time;

		Timer_start();

		while(read(fRead, &c, 1)==1)
		{
			write(fWrite, &c, 1);
		}

		Timer_elapsedUserTime(&time);
		close(fRead);
		close(fWrite);
		printf("Time Method 2: %g\n", time);
}

void method3(char* iFile, char* oFile)
{	
		int fRead   = open(iFile, O_RDONLY);
		int fWrite  = open(oFile, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);//O_CREAT |
		double time;

		Timer_start();

		char buffer[BUFSIZ];
		int read_size;

		while((read_size = read(fRead, buffer, BUFSIZ))>0)
		{
			write(fWrite, buffer, read_size);
			//printf("-%s-\n", buffer);
		}

		Timer_elapsedUserTime(&time);

		close(fRead);
		close(fWrite);
		printf("Time Method 3: %g\n", time);
}

int main(int argc, char* argv[])
{


	
	if (atoi(argv[1]) == 1)
	{
		method1(argv[2], argv[3]);
	}
	else if (atoi(argv[1]) == 2)
	{
		method2(argv[2], argv[3]);
	}
	else if (atoi(argv[1]) == 3)
	{
		method3(argv[2], argv[3]);
	}

	return 0;
	
	
}