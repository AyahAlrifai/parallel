#include "mpi.h"
#include <stdio.h>
#include <math.h>
#define MAXSIZE 5

void main(int argc, char* argv[])
{
	int myid, nproc;
int j=0;
	int i, x, low, high, myresult=0, result=0;
	char data[]="Hello";
	char fn[255];
	char *fp;
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&nproc);
	MPI_Comm_rank(MPI_COMM_WORLD,&myid);
//count of data is 6 because there is element with null value with each string
	if(myid==0)
		MPI_Bcast(data,6, MPI_CHAR, 0, MPI_COMM_WORLD); /* broadcast data */
	
	printf("I got %s \n", data); /* Compute global sum */

	MPI_Finalize();
}
