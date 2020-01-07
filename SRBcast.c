#include "mpi.h"
#include <stdio.h>
#include <math.h>
#define MAXSIZE 10
void main(int argc, char* argv[])
{
	int myid, nproc;
	int j=0;
	int data[MAXSIZE], i, x, low, high, myresult=0, result=0;
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&nproc);
	MPI_Comm_rank(MPI_COMM_WORLD,&myid);
	x = MAXSIZE/nproc;
	if(myid==0)
	{	
		for(i=0;i<MAXSIZE;i++)
			data[i]=i;
		for(i=1;i<nproc;i++)
			MPI_Send(&data,MAXSIZE,MPI_INT,i,i,MPI_COMM_WORLD);
	}
	if(myid!=0)
		MPI_Recv(&data,MAXSIZE,MPI_INT,0,myid,MPI_COMM_WORLD,MPI_STATUS_IGNORE);

	for(j=0;j<nproc;j++)
		if(j==myid)
			{
				for(i=0;i<MAXSIZE;i++)
					printf("data[%d]=%d \n",i,data[i]); 
				printf("*********************\n");
			}
	
	MPI_Finalize();
}
