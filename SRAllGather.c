#include "mpi.h"
#include <stdio.h>
#include <math.h>
#define MAXSIZE 12
void main(int argc, char* argv[])
{
	int myid, nproc;
	int j=0;
	int data, i, x, low, high, myresult=0, result=0;
	char fn[255];
	char *fp;
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&nproc);
	MPI_Comm_rank(MPI_COMM_WORLD,&myid);
	x = MAXSIZE/nproc; /* Add my portion Of data */
	data=myid;
	int recbuf[nproc];

	if(myid!=0)
	{
			MPI_Send(&data,1,MPI_INT,0,myid,MPI_COMM_WORLD);
	}

	if(myid==0)
	{ 
		recbuf[0]=myid;
		for(i=1;i<nproc;i++)
		{
			MPI_Recv(&recbuf[i],1,MPI_INT,i,i,MPI_COMM_WORLD,MPI_STATUS_IGNORE); 
		}
		for(i=1;i<nproc;i++)
			MPI_Send(&recbuf,nproc,MPI_INT,i,i,MPI_COMM_WORLD);
		
	}
	for(i=1;i<nproc;i++)
	{
		if(myid==i)
		{
			MPI_Recv(&recbuf,nproc,MPI_INT,0,myid,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			printf("my id %d\n",myid);
			for(j=0;j<nproc;j++)
				printf("%d\n",recbuf[j]);
		
		}
	}
	MPI_Finalize();
}
