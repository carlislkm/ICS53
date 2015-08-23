//KEVIN CARLISLE
//82682616
//THIS VERSION RUNS BUT ONLY A FEW COMMANDS
//MY FAILED ATTEMPT IS IN MY_SHELL_FAILED_ATTEMPT.C
//IN WHICH I ATTEMPTED TO PIPE
//THIS VERSION DOES NOT SUPPORT < OR > AT THE MOMENT
//ALTHOUGH MY COMPLETED VERSION FROM LAST WEEK DOES
//


#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<string.h>

char MDA[256][256][256];


void parse_ws_to_null(char* c, char* argv[])
{
        while(*c != '\0')
        {
                while(*c == ' ' || *c == '\n' || *c == '\t'|| *c == '<' || *c == '>' || *c == '|')
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
			else if ( *c == '|')
			{
                                *argv = "|";
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
                while(*c != '\0' && *c != ' ' && *c != '\t' && *c != '\n' && *c != '<' && *c != '>' && *c != '|')
               	{
                        c++;
	        }
        }
        *argv = '\0';
}

//void check_exit(char** argList)
void check_exit()
{
        if (strcmp(MDA[0][0],"q") ==0 )
		{
			printf("EXIT CALL\n");
			exit(0);
		}
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

void parse_to_MDA(char* argv[])
{

	int i = 0;
	int j = 0;
	while(*argv != NULL)
	{
		if (strcmp(*argv, "|") == 0)
		 {
			strcpy(MDA[i][j], "\0");
			j = 0;
			i++;
		}
		else
		{
			strcpy(MDA[i][j], *argv);
			j++;
		}
		argv++;
	}	
	/* NULL TERMINATED ARRAY STRINGS ARE NOT NECESSARY 
 * 	BUT SHOULD BE FOR EXEC */
	
	//NULL TERMINATE LAST OF CURRENT ARRAY
	strcpy(MDA[i][j],"\0");
	//NULL TERMINATE LAST ARRAY
	strcpy(MDA[i+1][0],"\0");
}

void print_MDA()
{
	int i = 0;
	int j = 0;
	
	while((strcmp(MDA[i][j], "\0") != 0))
	{		
		while((strcmp(MDA[i][j], "\0") != 0))
		{
			printf("[%d]->[%s]\n",i,  MDA[i][j]);
			j++;
		}
		i++;
		j = 0;
	}

	printf("\n\n\n");
}

int main(int argc, char* argv[], char* envp[])
{

        char* argList[255];
        char stringToParse[255];
	
	int i;
	
	while(1)
	{
        	printf("%%: ");
        	gets(stringToParse);
        	parse_ws_to_null(stringToParse, argList);
		parse_to_MDA(argList);
		
	//	print_MDA();
		check_exit();
		pid_t pid = fork();
                int status;

		if (pid == 0)
		{
			char* test[] = {MDA[0][0],MDA[0][1], NULL};
			execvpe(test[0], test, envp);
			
			exit(0);
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

