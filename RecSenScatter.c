#include "mpi.h"
#include <stdio.h>
#include <math.h>
#define MAXSIZE 12
void main(int argc, char* argv[])
{
	int myid, nproc;
	int j=0;
	int data[MAXSIZE], i, x, low, high, myresult=0, result=0;
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&nproc);
	MPI_Comm_rank(MPI_COMM_WORLD,&myid);
	x = MAXSIZE/nproc;
	int recbuf[x];
	if(myid==0)
	{ 
		for(i=0;i<MAXSIZE;i++)
		{
			data[i]=i;
		}
		for(i=1;i<nproc;i++)
		{
			low = i * x;
			for(j=0;j<x;j++)
				recbuf[j]=data[low+j];
			MPI_Send(&recbuf,x,MPI_INT,i,i,MPI_COMM_WORLD);
	
		}
		for(j=0;j<x;j++)
			recbuf[j]=data[j];
	}
	else
		MPI_Recv(&recbuf,x,MPI_INT,0,myid,MPI_COMM_WORLD,MPI_STATUS_IGNORE); 
	
	for(i=0;i<nproc;i++)
	{
		printf("\n");
		if(i==myid)
		{
			printf("i am a proc %d and i received",myid); 
			for(i=0;i<x;i++)
				printf("\n%d",recbuf[i]);
		}
	}	
	MPI_Finalize();
}
