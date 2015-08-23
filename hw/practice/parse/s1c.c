#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<ctype.h>
#include<fcntl.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<signal.h>

void print_info(char* temp[], char*  rd_input, char*  rd_output)
{

	printf("Testing\n\n");
	while(*temp != NULL)
	{
		printf("[%s]\n",*temp);
		temp++;
	}
	printf("[%s]\n", rd_input);
	printf("[%s]\n", rd_output);
	if(rd_input 


}

int main(int argc, char* argv[], char* envp[])
{


	char* c1[] = {"cat", NULL};
	char* rd_input = "exin";
	char* rd_output = "";

	char* c2[] = {"tee out1", NULL};
	char* rd_input2 = "";
	char* rd_output2 = "out2";


	print_info(c1, rd_input, rd_output);

	print_info(c2, rd_input2, rd_output2);

return 0;
}
