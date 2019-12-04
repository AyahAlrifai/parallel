#include "mpi.h"
#include <stdio.h>
#include <math.h>
#define MAXSIZE 10
void main(int argc, char* argv[])
{
	int myid, nproc;
	int j=0;
	int data1[MAXSIZE],data2[MAXSIZE],data3[MAXSIZE], i, x, low, high, myresult=0, result=0;
	char fn[255];
	char *fp;
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&nproc);
	MPI_Comm_rank(MPI_COMM_WORLD,&myid);
	x = MAXSIZE/nproc; /* Add my portion Of data */
	int recbuf1[x];
	int recbuf2[x];
	int res[x];
	if(myid==0)
	{
		for(i=0;i<MAXSIZE;i++)
		{
			data1[i]=i;
			data2[i]=i;
		}
				
	}
	MPI_Scatter(&data1,x,MPI_INT,&recbuf1,x,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Scatter(&data2,x,MPI_INT,&recbuf2,x,MPI_INT,0,MPI_COMM_WORLD);
	for(i=0;i<x;i++)
	{
		
		res[i]=recbuf1[i]*recbuf2[i];

	}

	MPI_Gather(&res,x,MPI_INT, &data3,x, MPI_INT, 0, MPI_COMM_WORLD);
	if(myid==0)
	{
		for(i=0;i<MAXSIZE;i++)
			printf("%d\n",data3[i]);
	}
	MPI_Finalize();
}
