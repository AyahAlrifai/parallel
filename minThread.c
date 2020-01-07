#include<stdio.h>
#include<pthread.h>
#define array_size 1000
#define num_threads 10

int a[array_size];
int global_index =0;
int min=0;
pthread_mutex_t mutex1;

void *slave(void *ignored)
{
int local_index;
do

  {
   	pthread_mutex_lock(&mutex1);
	local_index=global_index++;
	pthread_mutex_unlock(&mutex1);

	if (local_index<array_size)
		if(a[local_index]<min)
		{
			pthread_mutex_lock(&mutex1);
			min=a[local_index];
			pthread_mutex_unlock(&mutex1);
		}

   }while (local_index< array_size);
}


void main(){
int i;
pthread_t thread[num_threads];
pthread_mutex_init(&mutex1,NULL);

for(i=0;i<array_size;i++)
a[i]=i+10;
min=a[0];

for(i=0;i<num_threads;i++)
if(pthread_create(&thread[i],NULL,slave,NULL)!=0)
perror ("pthread_create fails");

for(i=0;i<num_threads;i++)
if(pthread_join(thread[i],NULL)!=0)
perror ("pthread_join fails");

printf("the min of 1 to %i is %d\n",array_size,min);


}

