//Kevin Carlisle
//ICS 53 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void printChar(char letter, int count)
{
	int i = 0;
	while (i<count)
	{
		printf("%c", letter);
		fflush(stdout);
		i++;
	}
}

int GT(pid_t p)
{
	return (p>0);
}
int ET(pid_t p)
{
	return (p == 0);
}

int main(int argc, char* argv[])
{
	int count;
	if (argc > 1){count = atoi(argv[1]);}
	else{count = 10000;}

	pid_t p1 = fork();
	pid_t p2 = fork();
	
	//PRINT PROCEESS ID
	printf("[Process ID: %d]", getpid());
	fflush(stdout);
	sleep(1);



	if (GT(p1) && GT(p2))
	{
		printChar('A', count);
	}
	else if (GT(p1) && ET(p2))
	{
		printChar('B', count);
	}
	else if (ET(p1) && GT(p2))
	{
		printChar('C', count);
	}
	else if (ET(p1) && ET(p2))
	{
		printChar('D', count);
	}

	int Status;
	waitpid(p1, &Status, 0);
	waitpid(p2, &Status, 0);

	if (p1 > 0 && p2 > 0){printf("\n");}

	return 0;

}





