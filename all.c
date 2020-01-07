#include "mpi.h"
#include <stdio.h>
#include <math.h>
#define MAXSIZE 12
void main(int argc, char* argv[])
{
	int myid, nproc;
	int j=0;
	int data[MAXSIZE], i, x, low, high, result=0;

	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&nproc);
	MPI_Comm_rank(MPI_COMM_WORLD,&myid);
	x = MAXSIZE/nproc;
	int recbuf[x],myresult;

	if (myid == 0)
	 { 
	for(j=0;j<MAXSIZE;j++)
		data[j]=j+1;	
	}
	MPI_Scatter(data,x,MPI_INT,recbuf,x,MPI_INT,0,MPI_COMM_WORLD); /* broadcast data */
	
	if(myid==1)
	{
	for(i=0;i<x;i++)
		result+=recbuf[i];
	MPI_Send(&result,1,MPI_INT,0,myid,MPI_COMM_WORLD);

	}
	else if(myid==2)
	{
	result=recbuf[0];
	for(i=0;i<x;i++)
		if(recbuf[i]<result)
			result=recbuf[i];
	MPI_Send(&result,1,MPI_INT,0,myid,MPI_COMM_WORLD);
	}
	else if(myid==3)
	{
	result=recbuf[0];
	for(i=0;i<x;i++)
		if(recbuf[i]>result)
			result=recbuf[i];
	MPI_Send(&result,1,MPI_INT,0,myid,MPI_COMM_WORLD);

	}
	else if(myid==0)
	{
	result=1;
	for(i=0;i<x;i++)
		result*=recbuf[i];

	}

	if(myid==0)
	{
	printf("prod=%d \n",result); 
	MPI_Recv(&myresult,1,MPI_INT,1,1,MPI_COMM_WORLD,MPI_STATUS_IGNORE); 
	printf("sum=%d \n",myresult); 
	MPI_Recv(&myresult,1,MPI_INT,2,2,MPI_COMM_WORLD,MPI_STATUS_IGNORE); 
	printf("min=%d \n",myresult); 
	MPI_Recv(&myresult,1,MPI_INT,3,3,MPI_COMM_WORLD,MPI_STATUS_IGNORE); 
	printf("max=%d \n",myresult); 
	}

	MPI_Finalize();
}
