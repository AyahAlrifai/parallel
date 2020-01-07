#include "mpi.h"
#include <stdio.h>
#include <math.h>
#define MAXSIZE 100
//nproc%10==0
//sum(1:100)=5050
void main(int argc, char* argv[])
{
	int myid, nproc;
	int j=0;
	int data[MAXSIZE], i, x, low, high, myresult=0, result=0;

	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&nproc);
	MPI_Comm_rank(MPI_COMM_WORLD,&myid);
	x = MAXSIZE/nproc; 
	low = myid * x;
	high = low + x;
	if (myid == 0) 
	{ 
		for(j=0;j<MAXSIZE;j++)
			data[j]=j+1;
		
	}
	MPI_Bcast(data, MAXSIZE, MPI_INT, 0, MPI_COMM_WORLD); 
	for(i = low; i < high; i++)
		myresult += data[i];
	printf("I got %d from %d\n", myresult, myid); 
	MPI_Reduce(&myresult, &result, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	if (myid == 0) 
		printf("The sum is %d.\n", result);
	MPI_Finalize();
}
