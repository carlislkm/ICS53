#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void* thread1()
{
	int num = 1000;

	while(num >0)
	{
		printf("1");
		num--;
	}
}

void* thread2()
{
	int num = 1000;
	while(num > 0)
	{
		printf("0");
		num--;
	}

}

int main()
{
	int status;
	pthread_t tid1;
	pthread_t tid2;

	pthread_create(&tid1, NULL, thread1, NULL);
	pthread_create(&tid2, NULL, thread2, NULL);

	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	
	printf("\n");

	return 0;
}

