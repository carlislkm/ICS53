#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<string.h>


void parse_ws_to_null(char* c, char (*argv)[255][255])
{
	int i = 0;
	int j = 0;
        while(*c != '\0')
        {
                while(*c == ' ' || *c == '\n' || *c == '\t'|| *c == '<' || *c == '>' || *c == '|')
                {
                        if( *c == '<')
                        {
				strcpy(**argv, "<");
                                *argv++;
                                *c = '\0';
                                c++;
                        }
                        else if( *c == '>')
                        {
				strcpy(**argv, ">");
                                *argv++;
                                *c = '\0';
                                c++;
                        }
			else if ( *c == '|')
			{
				strcpy(**argv, "|");
                                *argv++;
                                *c = '\0';
                                c++;
			
			}
                        else
                        {
                                *c = '\0';
                                c++;
                        }
                }
                strcpy(**argv, c);
                *argv++;
                while(*c != '\0' && *c != ' ' && *c != '\t' && *c != '\n' && *c != '<' && *c != '>' && *c != '|')
               	{
                        c++;
	        }
        }
        
	strcpy(**argv, '\0');
}


int main(int argc, char* argv[], char* envp[])
{

        char argList[255][255][255];
        char stringToParse[255];

        printf("Enter string to parse: ");
        gets(stringToParse);
        parse_ws_to_null(stringToParse, argList);

	int i;
	while(argList[0][i] != NULL)
	{
		printf("[%s]\n", argList[0][i]);
		i++;

	}

        return 0;
}

