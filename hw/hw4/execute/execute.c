//Kevin Carlisle
//Execute



#include <stdio.h>
//#include <process.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>


void parse_ws_to_null(char* c, char* argv[])
{
	while(*c != '\0') 
	{
		while(*c == ' ' || *c == '\n' || *c == '\t')
		{
			*c = '\0';
			c++;
		}
		*argv = c;
		argv++;
		while(*c != '\0' && *c != ' ' && *c != '\t' && *c != '\n')
		{
			c++;
		}
	}
	*argv = '\0';
}

int main(int argc, char* argv[], char* envp[])
{

	char* argList[255];
	char stringToParse[255];
	gets(stringToParse);
	parse_ws_to_null(stringToParse,argList);

	execvpe(argList[0], argList, envp);

	return 0;
}