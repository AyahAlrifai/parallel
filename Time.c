#include "mpi.h"
#include <stdio.h>
#include <math.h>
#define MAXSIZE 1024

void main(int argc, char* argv[])
{
	int myid, nproc;
	int j=0;
	int data[MAXSIZE], i, x, low, high, myresult=0, result=0;
	double t1=0,t2=0;
	char fn[255];
	char *fp;
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&nproc);
	MPI_Comm_rank(MPI_COMM_WORLD,&myid);
	x = MAXSIZE/nproc; /* Add my portion Of data */
	int recbuf[MAXSIZE];
	if(myid==1)
	{
		for(i=0;i<MAXSIZE;i++)
		data[i]=i;
	}
	t1=MPI_Wtime();
	while(j<1000)
	{
	if(myid==1)
	MPI_Send(&data,MAXSIZE,MPI_INT,0,5,MPI_COMM_WORLD);
	else if(myid==0)
	MPI_Recv(&recbuf,MAXSIZE,MPI_INT,1,5,MPI_COMM_WORLD,MPI_STATUS_IGNORE);

	if(myid==0)
	MPI_Send(&recbuf,MAXSIZE,MPI_INT,1,4,MPI_COMM_WORLD);
	else if(myid==1)
	MPI_Recv(&data,MAXSIZE,MPI_INT,0,4,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
	
	j++; 
	}
	t2=MPI_Wtime();
	if(myid==0)
		printf("%f\n",(t2-t1));
	MPI_Finalize();
}
