#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

char buf1[16];
char buf2[16];

int main()

{

	int p[2];
	pipe(p);
	int pid = fork();

	if( pid == 0)
	{
		//CHILD PROCESS
		//strcpy(buf1, "HELLO PARENT!");
		//printf("IN CHILD PROCESS...\n");
		//write(p[1], buf1, sizeof(buf1));//write to parent
		//sleep(2);
		//read(p[0], buf1, sizeof(buf1));
		//printf("CHILD PROCESS RECIEVED: [%s]\n\n", buf1);
		//
		//

		printf("IN CHILD PROCESS...\n");
		close(p[0]);
		int current_out = dup(1);
		dup2(p[1], 1);
		printf("Print from child process 1...\n");
		printf("Print from child process 2...\n");
		printf("Print from child process 3...\n");
		//close(p[1]);
		dup2(current_out, 1);
		printf("END OF CHILD....\n\n");

	}
	else if (pid >0)
	{
		//PARENT PROCESS
		//sleep(1);
		printf("IN Parent PROCESS...\n\n");
		//read(p[0], buf1, sizeof(buf1));
		//printf("PARENT RECIEVED: [%s]\n\n", buf1);
		//strcpy(buf1, "HELLO CHILD!");
		//write(p[1], buf1, sizeof(buf1));

		int c;
		
		int status;
		wait(status);
		
		close(p[1]);
		dup2(p[0], 0);

		//while( (c = fgetc(stdin))>0)
		//{
		//	printf("-%c",c); 
		//}
		int r;	
		while((r= read(0, &c, 1)) == 1)
		{
			printf("-%c",c);
	
		}
		close(p[0]);

	
	}
	else
	{


	}


return 0;
}

