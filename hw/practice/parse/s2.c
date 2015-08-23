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
#include<ctype.h>
#include<string.h>

void parse_by_bar(char* c, char* argv[], int* pipecount)
{
        while(*c != '\0')
        {
                while(*c == '|')
                {
            if(*(c-1) == ' ')
            {
                *(c-1) = '\0';
            }
                          *c = '\0';
                           c++;
            (*pipecount)++;
            if (*c == ' ')
                {
                    *c = '\0';
                    c++;
                }
            
                }
                *argv = c;
                argv++;
                while(*c != '\0' && *c != '|')
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
    int stat = dup2(fWrite, 1);
}


void redirect_and_parse(char* c, char* argv[])
{
    char redir_type = '\0';
    int len = 0;

    char inputfile[256] = {0};
    char outputfile[256] = {0};
    char temp[256] = {0};

    char* ip = inputfile;
    char* op = outputfile;
    char* tp = temp;

    int flag = 0;
    int i = 0;
	while(*c != '\0')
	{
		if ( *c != ' ' && *c != '\n' && *c != '\t')
		{
			*tp = *c;
			tp++;
				

			
		}
		else
		{

			*tp = '\0';
			printf("TEST: [%s]\n", temp);
			*argv = temp;
			argv++;
			memset(temp, 0, sizeof(temp));
			tp = temp;
		}

		c++;
	}
	*tp = '\0';
	printf("TEST: [%s]\n", temp);
	tp = temp;
	*argv = temp;
	argv++;
	memset(temp, 0, sizeof(temp));
	tp = temp;



	*argv = '\0';
	printf("INPUT: [%d]\n", *inputfile);
	printf("OUTPUT: [%d]\n", *outputfile);
	printf("ARGV: [%s]\n", argv[0]);

}

int main(int argc, char* argv[], char* envp[])
{

    char* argList[255];
    char stringToParse[255];


    while(1)
    {    

        int pipecount = 0;
        printf("%%");
        gets(stringToParse);
        parse_by_bar(stringToParse, argList, &pipecount);
        check_exit(argList);

        int pipe_ref = 0;
        int i;
        for(i = 0; i <= pipecount; i++)
        {
            int p[2];
            pipe(p);
                
            pid_t pid = fork();
            int status;
        
            if (pid == 0)
            {

            char* temp[256];
            redirect_and_parse(argList[i], temp);

            int k;
            for(k=0; k<15; k++)
                printf("%i ", temp[0][k]);
            for(k = 0; temp[k] != '\0'; ++k)
                printf("Arg %d: {%s}\n", k, temp[k]);

                execvpe(temp[0], temp, envp);

                exit(1);
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
    }    



    return 0;
}

