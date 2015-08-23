#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/select.h>
#include <ctype.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>
#include <sys/stat.h>

#define PORT_NUM 3502


void execute_command(char* buf_recv, char* envp[], int client_socket)
{

	
	int fStat = fork();

	if(fStat == -1)
	{
		perror("FORK() FAIL\n");
		exit(1);
	}
	else if(fStat == 0)
	{
		dup2(client_socket, 1);
		//execvpe(temp[0], temp, envp);
		printf("FROM CHILD PROCESS\n");
	//	printf("ERROR IN CHILD -> EXECVPE() FAIL\n");
		exit(0);
	}
	else
	{
		wait(NULL);
//		printf("PARENT PROCESS\n");
		exit(0);
	}

}

int main(int argc, char* argv[], char* envp[])
{
	int client_socket;
	int receiving_socket; 
	int s_size; 
	int reuse_bool = 1; 

	//TEMP VALS
	int bind_check;
	int listen_check;


	char file_path[256]; 

	struct sockaddr_in server_address;
	struct sockaddr_in client_address;

	receiving_socket = socket(AF_INET, SOCK_STREAM, 0);

	//CHECK IF SOCKET() CALL WAS SUCESSFUL
	if(receiving_socket == -1)
	{
		perror("receiving_socket -> SOCKET() FAIL\n");
		exit(1);
	}
	else
	{
		printf("SOCKET() SETUP #\n");
	}

	setsockopt(receiving_socket, SOL_SOCKET, SO_REUSEADDR, &reuse_bool, sizeof(reuse_bool));

	//SET SERVER_ADDRESS STRUCT
	server_address.sin_family = AF_INET;
 	server_address.sin_port = htons(PORT_NUM);
    	server_address.sin_addr.s_addr = INADDR_ANY;
    	memset(&(server_address.sin_zero), 0, sizeof(server_address));

	
    //BIND
    bind_check = bind(receiving_socket, (struct sockaddr *)&server_address, sizeof(server_address));

   	//CHECK IF BIND() CALL WAS SUCESSFUL
   	if(bind_check == -1)
   	{
   		perror("bind_check -> BIND() FAIL\n");
   		exit(1);
   	}
   	else
   	{
   		printf("BIND() SETUP#\n");
   	}


   	//LISTEN 
   	listen_check = listen(receiving_socket, 20);

   	//CHECK IF LISTEN() CALL WAS SUCESSFUL
   	if(listen_check == -1)
   	{
   		perror("listen_checken -> LISTEN() FAIL\n");
   		exit(1);
   	}
   	else
   	{
   		printf("LISTEN() SETUP#\n");
   		printf("...............\n");
   	}
   	

   	s_size = sizeof(struct sockaddr_in);

   	client_socket = accept(receiving_socket, (struct sockaddr *)&client_address, (socklen_t *)&s_size);
	

	char buf_recv[1024] = {'\0'};
	read(client_socket, buf_recv, sizeof(buf_recv));

	execute_command(buf_recv, envp, client_socket);

	printf("CLOSING SERVER.....\n");	

   	return 0;

}
