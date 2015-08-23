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

void parseLine(char * lineIn, int *numPipes, char pipedFinal[8][3][256])
{
	char c = 0;
	int readIn = 0;
	int positions[3] = {0, 0, 0};
	
	do
	{
		c = *lineIn++;
		if (!isspace(c))
		{
			if (c == '<')
			{
				while (pipedFinal[*numPipes][readIn][positions[readIn]-1] == ' ')
				{
					pipedFinal[*numPipes][readIn][--positions[readIn]] = 0;
				}
				readIn = 1;
			}
			else if (c == '>')
			{
				while (pipedFinal[*numPipes][readIn][positions[readIn]-1] == ' ')
				{
					pipedFinal[*numPipes][readIn][--positions[readIn]] = 0;
				}
				readIn = 2;
			}
			else if (c == '|')
			{
				while (pipedFinal[*numPipes][readIn][positions[readIn]-1] == ' ')
				{
					pipedFinal[*numPipes][readIn][--positions[readIn]] = 0;
				}
				for (int i=0; i<3; i++)
				{
					pipedFinal[*numPipes][i][positions[i]] = '\0';
					positions[i] = 0;
				}
				*numPipes = *numPipes + 1;
				readIn = 0;
			}
			else
				pipedFinal[*numPipes][readIn][positions[readIn]++] = c;
		}
		else
		{
			if (readIn == 0)
				if (positions[readIn] != 0)
					pipedFinal[*numPipes][readIn][positions[readIn]++] = ' ';
		}
	} while (c != '\0');
}

void parseCommand(char *c, char * argv[])
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

void mainloop(char *envp[])
{
	while(1)
	{
		int numPipes = 0;
		char lineIn[256];
		printf("%%");
		gets(lineIn);
		char  pipedFinal[8][3][256];
		parseLine(lineIn, &numPipes, pipedFinal);

		int curr = 0;
		for (int i=0; i<=numPipes; i++)
		{
			int p[2];
			pipe(p);
			char c;
			char * commands1[256];
			switch (fork())
			{
				case -1:
					perror("fork");
					exit(1);
				case 0:
					close(p[0]);
					if (curr != 0)
						dup2(curr, 0);
					if (strlen(pipedFinal[i][1]) > 1)
					{
						int readFile = open(pipedFinal[i][1], O_RDONLY);
						dup2(readFile, 0);
					}
					dup2(p[1], 1);
					if (strlen(pipedFinal[i][2]) > 1)
					{
						int writeFile = open(pipedFinal[i][2], O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
						dup2(writeFile, 1);
					}
					parseCommand(pipedFinal[i][0], commands1);
					execvpe(commands1[0], commands1, envp);
					exit(1);
				default:
					wait(NULL);
					close(p[1]);
					curr = p[0];
			}
		}
	}
}

int main(int argc, char *argv[], char *envp[])
{
	mainloop(envp);

	return 0;
}

