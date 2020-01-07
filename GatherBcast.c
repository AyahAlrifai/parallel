#include "mpi.h"
#include <stdio.h>
#include <math.h>
#define MAXSIZE 10
//nproc=2 to show the result
void main(int argc, char* argv[])
{
	int myid, nproc;
	int j=0;
	int data[MAXSIZE], i, x, low, high, myresult=0, result=0,k;

	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&nproc);
	MPI_Comm_rank(MPI_COMM_WORLD,&myid);
	int recbuf[MAXSIZE*nproc];
	if (myid == 0)
	 {
		for(j=0;j<MAXSIZE;j++)
			data[j]=j;	
	}
	MPI_Bcast(data, MAXSIZE, MPI_INT, 0, MPI_COMM_WORLD); 
	MPI_Gather(&data,MAXSIZE,MPI_INT, &recbuf,MAXSIZE, MPI_INT, 0, MPI_COMM_WORLD);
	if (myid == 0) 
		for( k=0;k<MAXSIZE*nproc;k++)
			printf("%d\n",recbuf[k]);
	MPI_Finalize();
}
