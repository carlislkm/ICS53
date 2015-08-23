//Kevin Carlisle
//#82682616
//Problem 4
//Command Shell

#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<fcntl.h>


void parse_ws_to_null(char* c, char* argv[])
{
        while(*c != '\0')
        {
                while(*c == ' ' || *c == '\n' || *c == '\t'|| *c == '<' || *c == '>')
                {
			if( *c == '<')
			{
				*argv = "<";
				argv++;
				*c = '\0';
				c++;

			}
			else if( *c == '>')
			{
				*argv = ">";
				argv++;
				*c = '\0';
				c++;

			}
			else
			{

                        	*c = '\0';
                        	c++;
			}
                }
                *argv = c;
                argv++;
                while(*c != '\0' && *c != ' ' && *c != '\t' && *c != '\n' && *c != '<' && *c != '>')
                {
                        c++;
                }
        }
        *argv = '\0';
}
void check_exit(char** argList)
{
	if (strcmp(argList[0],"QUIT") ==0 ){exit(0);}
}
void redirInput(char* iFile)
{
	int fRead   = open(iFile, O_RDONLY);
	dup2(fRead, 0);
}
void redirOutput(char* oFile)
{
	int fWrite  = open(oFile, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
	dup2(fWrite, 1);
}
int redirect(char* argList[])
{
	int flag = 0;
	int i = 0;
	while(argList[i] != NULL)
	{
		if(strcmp(argList[i], "<") == 0)
		{
			redirInput(argList[i+1]);
			flag = 1;
		}
		else if (strcmp(argList[i], ">") == 0)
		{
			redirOutput(argList[i+1]);
			flag = 1;
		}			
		i++;
	} 
	return flag;

}
int main(int argc, char* argv[], char* envp[])
{

	char* argList[255];
	char stringToParse[255];

	while(1)
	{	

		printf("%%");
		gets(stringToParse);
		parse_ws_to_null(stringToParse, argList);
		check_exit(argList);
		pid_t pid = fork();
		int status;
	
		if (pid == 0)
		{
			if(redirect(argList) == 1)
				{
				char* temp[] = {argList[0], argList[1], NULL};
				execvpe(temp[0], temp, envp);
				_exit(EXIT_FAILURE);
				}
			else
				{
				execvpe(argList[0], argList, envp);
				_exit(EXIT_FAILURE);
				}
		}
		else if ( pid > 0)
		{
			wait(&status);
		}
		else if (pid <= -1)
		{
			printf("PID ERROR\n");
			exit(1);		
		}
	}	



	return 0;
}

