#include "mpi.h"
#include <stdio.h>
#include <math.h>
#define MAXSIZE 4
void main(int argc, char* argv[])
{
	int myid, nproc;
	int j=0;
	int i, x, low, high, myresult=0, result=0,k;
	char fn[255];
	char *fp;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&myid);
	MPI_Comm_size(MPI_COMM_WORLD,&nproc);
	int data[nproc];
	for(i=0;i<nproc;i++)
		data[i]=i;
	int recbuf[nproc];
	MPI_Alltoall(&data,1,MPI_INT,&recbuf,1,MPI_INT,MPI_COMM_WORLD);
		for(k=0;k<nproc;k++)
			printf("%d ",recbuf[k]);
		printf("\n");
	MPI_Finalize();
}

//H:Befor   V:After
//   p0  p1   p2   p4

//p0  0   1    2    3

//p1  0   1    2    3

//p2  0   1    2    3

//p3  0   1    2    3


