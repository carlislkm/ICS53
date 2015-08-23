#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<string.h>

char MDA[256][256][256];
int PIPE_NUM = 0;

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

void check_exit()
{
        if (strcmp(MDA[0][0],"q") ==0 )
		{
			exit(0);
		}
}

void redirInput(int i, int j)
{
	char iFile[64];
	strcpy(iFile, MDA[i][j]);
        int fRead   = open(iFile, O_RDONLY);
        dup2(fRead, 0);
}

void redirOutput(int i, int j)
{
	char oFile[64];	
	strcpy(oFile, MDA[i][j]);
        int fWrite  = open(oFile, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
        dup2(fWrite, 1);
}

int redirect(int i)
{
	printf("CHECKING REDIRECT FUNC\n");
        int flag = 0;
        int j = 0;
        while(strcmp(MDA[i][j], "\0") != 0)
        {
	printf("INSIDE LOOP\n");
                if(strcmp(MDA[i][j], "<") == 0)
                {
			printf("INSIDE IF\n");
                        redirInput(i,j);
			break;
                }
                else if (strcmp(MDA[i][j], ">") == 0)
                {
			printf("INSIDE ELSE IF\n");
                        redirOutput(i,j);
			break;
                }
                j++;
        }
	flag = j;
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
			PIPE_NUM = PIPE_NUM +1;
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
        	printf("---------%%: ");
        	gets(stringToParse);
        	parse_ws_to_null(stringToParse, argList);
		parse_to_MDA(argList);
		
		print_MDA();
		check_exit();

		int pcw = 0;
		
		int i;
		for(i = 0; i <= PIPE_NUM; i++)
		{

			//char* exe_arg[256];
			int p[2];
			pipe(p);
		
			pid_t pid = fork();
               	        int status;

			if (pid == 0)
			{
				printf("CHECKING CHILD BEFORE IF/ELSE\n");
				int num_args = 0;
				num_args = redirect(i);
				printf("NUM ARGS[%d]\n", num_args);
				printf("CHECKING AFTER REDIRECT\n");
				int x = 0;
				char* temp[256];
				while(x < num_args )
				{
					printf("_______[%s]\n", MDA[i][x]);
					strcpy(temp[x], MDA[i][x]);
					
					x++;
				}
				strcpy(temp[x], "\0");
				
				int y = 0;
				while(strcmp(temp[y],"\0") != 0)
				{
					printf("  --[%s]\n", temp[y]);
					y++;
				}	
				
				execvpe(temp[0], temp, envp);
				
				//printf("Child Run--> execpe\n");
				//char* test[] = {MDA[0][0],MDA[0][1], NULL};
				//execvpe(test[0], test, envp);
				printf("Child Failed----\n");
				exit(0);
			}
			 else if ( pid > 0)
        	        { 
				printf("\nParent PROCESS\n\n");
				wait(&status);
        	        }
        	        else if (pid <= -1)
        	        {
        	                printf("PID ERROR\n");
        	                exit(1);
        	        }
		}
	}

        return 0;
}

