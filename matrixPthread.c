#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include<math.h>
#define matrixSize 4

  double      arraya[matrixSize][matrixSize];  
  double      arrayb[matrixSize][matrixSize]; 
  double      arrayc[matrixSize][matrixSize]; 
  double      sum=0; 

#define numberofthreads 4
pthread_t thread_id_no[numberofthreads];  
pthread_mutex_t sum1;       

void *product(void *arg) {
  int i,k, start, end, len ;
  long int offset_thread;
  double my_each_sum;

  offset_thread = (long int)arg;  
  start = offset_thread;      

  my_each_sum = 0.0;
  for (i=0; i<numberofthreads ; i++) {
  my_each_sum = 0.0;
	for(k=0;k<numberofthreads;k++)
    		my_each_sum += (arraya[start][i] * arrayb[i][k]);
  	arrayc[start][i]=my_each_sum;                

  }
  
}

void  main (int argc, char *argv[]) {
  long int i,j;
  for (i=0; i<numberofthreads; i++) {
	for (j=0; j<numberofthreads; j++) {
    arraya[i][j]=1.0;
    arrayb[i][j]=2.0;
}
  }
  
  sum=0.0;
  pthread_mutex_init(&sum1, NULL);
  for(i=0;i<numberofthreads;i++) {
    pthread_create(&thread_id_no[i], NULL, product, (void *)i); 
  }
  

  for(i=0;i<numberofthreads;i++) {
    pthread_join(thread_id_no[i], NULL);
  }
  for (i=0; i<numberofthreads; i++) {
	for (j=0; j<numberofthreads; j++) {
    		  printf ("%f\t", arrayc[i][j]);
}
printf("\n");
  }

  pthread_exit(NULL);
}  



