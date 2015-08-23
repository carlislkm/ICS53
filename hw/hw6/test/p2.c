#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<fcntl.h>

char** TDA[16];

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


int main(int argc, char* argv[], char* envp[])
{

        char* argList[255];
        char stringToParse[255];

        printf("Enter string to parse: ");
        gets(stringToParse);
        parse_ws_to_null(stringToParse, argList);

	int i;
	while(argList[i] != NULL)
	{
		printf("[%s]\n", argList[i]);
		i++;

	}

        return 0;
}

