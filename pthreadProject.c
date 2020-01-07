#include<stdio.h>
#include<pthread.h>
#include <math.h> 
#define MAXSIZE 10
#define bagWeight 100
#define numberofthreads 8

int w[MAXSIZE], v[MAXSIZE];
pthread_mutex_t sum1;
pthread_t thread_id_no[numberofthreads];
int max, max_value[numberofthreads], best_solution[numberofthreads];


void binary(int *arr,int num)
{
	int j=0;
	for(;j<10;j++)
	{
		arr[j]=num%2;
		num=num/2;
	}
}

void *knapsack(void *arg)
{
	int i, j,low,high;
	int  bin[MAXSIZE];
	long int offset_thread;
	int x = pow(2, MAXSIZE) / numberofthreads;
	offset_thread = (long int)arg;   /* Thread number */
	low = offset_thread * x;       /* Start of this threads slice of the vectors */
	high = low + x;      /* End of the slice */
	int best_sol = 0, max_v = 0, current_v = 0, current_w = 0;

	
	max_v = 0;
	best_sol = low;
	for (j = low; j < high; j++)
	{
		binary(bin, j);
		for (i = MAXSIZE - 1; i >= 0; i--)
		{
			current_v += v[i] * bin[i];
			current_w += w[i] * bin[i];
		}
		if (current_v > max_v && current_w <= bagWeight)
		{
			best_sol = j;
			max_v = current_v;
		}
		current_v = 0;
		current_w = 0;
	}

	max_value[offset_thread] = max_v;
		
	best_solution[offset_thread] = best_sol;



}
void main(int argc, char* argv[])
{

	int  bin[MAXSIZE];
	long int i;

	pthread_mutex_init(&sum1, NULL);

	for (i = 0; i < MAXSIZE; i++)
	{
		w[i] = rand() % (bagWeight + 50) + 1;
		v[i] = rand() % (bagWeight * 5) + 1;
	}


	for (i = 0; i < numberofthreads; i++) {
		pthread_create(&thread_id_no[i], NULL, knapsack, (void *)i);
	}



	max = 0;
	for (i = 0; i < numberofthreads; i++)
	{
		if (max_value[i] > max_value[max])
			max = i;
	}



	for (i = 0; i < numberofthreads; i++) {
		pthread_join(thread_id_no[i], NULL);
	}
  
	
	


	printf("W\t");
	for (i = 0; i < MAXSIZE; i++)
		printf("%d\t", w[i]);
	printf("\nv\t");
	for (i = 0; i < MAXSIZE; i++)
		printf("%d\t", v[i]);
	printf("\nS\t");
	binary(bin, best_solution[max]);
	for (i = 0; i < MAXSIZE; i++)
		printf("%d\t", bin[i]);
	printf("\n");

	pthread_exit(NULL);

}






