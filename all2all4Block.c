#include "mpi.h"
#include <stdio.h>
#include <math.h>
#define MAXSIZE 8
void main(int argc, char* argv[])
{
	int myid, nproc;
	int j=0;
	int i, x, myresult=0, result=0,k;
	char fn[255];
	char *fp;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&myid);
	MPI_Comm_size(MPI_COMM_WORLD,&nproc);
	int data[nproc];
	int low=myid*nproc;
	for(i=0;i<MAXSIZE;i++)
		data[i]=i+low;
	int recbuf[nproc];
	MPI_Alltoall(&data,1,MPI_INT,&recbuf,1,MPI_INT,MPI_COMM_WORLD);
	for(k=0;k<nproc;k++)
			printf("%d\t",recbuf[k]);
		printf("\n");
	MPI_Finalize();
}
