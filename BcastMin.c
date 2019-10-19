#include "mpi.h"
#include <stdio.h>
#include <math.h>
#define MAXSIZE 10
void main(int argc, char* argv[])
{
	int myid, nproc;
int j=0;
	int data[MAXSIZE], i, x, low, high, myresult=0, result=0;
	char fn[255];
	char *fp;
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&nproc);
	MPI_Comm_rank(MPI_COMM_WORLD,&myid);

	MPI_Bcast(data, MAXSIZE, MPI_INT, 0, MPI_COMM_WORLD); /* broadcast data */
	x = MAXSIZE/nproc; /* Add my portion Of data */
	low = myid * x;
	high = low + x;
	if (myid == 0) {  /* Open input file and initialize data */
	for(j=0;j<MAXSIZE;j++)
		data[j]=j;
		
	}
	MPI_Bcast(data, MAXSIZE, MPI_INT, 0, MPI_COMM_WORLD); /* broadcast data */
	myresult=data[low];
	for(i = low; i < high; i++)
		if(data[i]<myresult)
			myresult=data[i];
	printf("I got %d from %d\n", myresult, myid); /* Compute global sum */
	MPI_Reduce(&myresult, &result, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);
	if (myid == 0) 
		printf("The min is %d.\n", result);
	MPI_Finalize();
}
