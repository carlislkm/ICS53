//Kevin Carlisle
//82682616

#include <stdio.h>
#include <stdlib.h>

void print_array(int input_array[])
{
	int i = 0;
	while(input_array[i] != 0)
	{
		printf("[%d] ", input_array[i]);
		i++;
	}
	printf("\n\n");
}
void process_array(int input_array[], int pre_array[], int post_array[], int size)
{

	pre_array[0] = 1;
	int i;
	for (i = 1; i < size; i++)
	{
		pre_array[i] = input_array[i-1]* pre_array[i-1];
	}

	post_array[size-1] = 1;
	post_array[size] = '\0';

	for(i = size -2; i >= 0; i--)
	{
		post_array[i] = input_array[i+1]* post_array[i+1];
	}
}
void print_result_arrays( int pre_array[], int post_array[], int size)
{
	int i;
	for(i = 0; i < size; i++)
	{
		printf("%d\n", pre_array[i]*post_array[i]);
	}

}

int main()
{

	int input_array[256] = {0};
	int pre_array[256];
	int post_array[256];
	int size = 0;

	int c;
	int i = 0;
	while(scanf("%d", &c) ==1)
	{
		input_array[i] =c;
		i++;
	}
	size = i;
	
	//print_array(input_array);

	process_array(input_array, pre_array, post_array, size);

	print_result_arrays(pre_array, post_array, size);

	return 0;
}
