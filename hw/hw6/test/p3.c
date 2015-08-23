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

        printf("Enter string to parse: ");
        gets(stringToParse);
        parse_ws_to_null(stringToParse, argList);
	parse_to_MDA(argList);
	
	print_MDA();






        return 0;
}

