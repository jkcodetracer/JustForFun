#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE	1000

void swap(int *array, int src, int dst) 
{
	int tmp = array[src]; 
	array[src] = array[dst];
	array[dst] = tmp;
}

void quick_sort(int *array, int begin, int end)
{
	if (begin >= end) 
		return ;
	int i = 0;
	int last = begin;
	
	swap(array, begin, (begin+end)/2);
	for (i = begin; i < end; i++) {
		if (array[i] < array[begin]) 
			swap(array, ++last, i);
	}
	swap(array, last, begin);	

	quick_sort(array, begin, last);
	quick_sort(array, last+1, end);
}

int check(int *array, int size)
{
	int i = 0; 
	
	for(i = 0; i < size-1; i++) {
		if(array[i] > array[i+1])	
			return -1;
	}
	
	return 0;
}

int main(int argc, char *argv[])
{
	int i = 0, j = 0;
	int total = atoi(argv[1]);	
	int array[MAX_SIZE] = {0};

	//printf("total: %d\n", total);
	srand(time(NULL));	
	for(i = 0; i < total; i++) {
		//printf("[%d]\n", i);
		for (j = 0; j < MAX_SIZE; j++) {
			array[j] = rand()%10000;	
		}	

		quick_sort(array, 0, MAX_SIZE);
		if(check(array, MAX_SIZE) != 0) {
			printf("sort failed!\n");	
		}
	}

	return 0;
}
