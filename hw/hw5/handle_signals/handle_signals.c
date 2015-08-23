//Kevin Carlisle
//#82682616
//ICS 53 HW 5
//Problem 3
//Signal Handling

#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>


int C2 = 0;
int C3 = 0;
int C20 = 0;

void print_counts()
{
	printf("Interrupt: %d\n", C2);
	printf("Stop: %d\n", C3);
	printf("Quit: %d\n", C20);

}


void handle(int signum)
{

	switch(signum)
		{
		case 2:
			printf("\n I\n");
			fflush(stdout);
			++C2;
			break;
		case 3:
			printf("\n Q\n");
			fflush(stdout);
			++C3;
			break;
		case 20:
			printf("\n S\n");
			fflush(stdout);
			++C20;
			if(C20 >= 3)
			{
			print_counts();	
			fflush(stdout);
			exit(1);
			}
			raise(SIGSTOP);
			
			break;
		default:
			break;
		}
}


int main()
{
	
	signal(SIGINT, handle);	
	signal(SIGQUIT, handle);
	signal(SIGTSTP, handle);

	while(1)
		{
		printf("X");
		fflush(stdout);
		sleep(1);
		}

return 0;
}

