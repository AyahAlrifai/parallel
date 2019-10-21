#include "mpi.h"
#include <stdio.h>
#include <math.h>
#define MAXSIZE 10
void main(int argc, char* argv[])
{
	int myid, nproc;
int j=0;
	int data[MAXSIZE], i, x, low, high, myresult=0, result=0,k;
	char fn[255];
	char *fp;
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&nproc);
	MPI_Comm_rank(MPI_COMM_WORLD,&myid);
	x = MAXSIZE/nproc; /* Add my portion Of data */
	int recbuf[10*nproc];
	if (myid == 0)
	 {  /* Open input file and initialize data */
		for(j=0;j<MAXSIZE;j++)
		data[j]=j;	
	}
	MPI_Bcast(data, MAXSIZE, MPI_INT, 0, MPI_COMM_WORLD); /* broadcast data */
	MPI_Gather(&data,10,MPI_INT, &recbuf,10, MPI_INT, 0, MPI_COMM_WORLD);
	if (myid == 0) 
		for( k=0;k<20;k++)
		printf("%d\n",recbuf[k]);
	MPI_Finalize();
}
