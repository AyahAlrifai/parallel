#include "mpi.h"
#include <stdio.h>
#include <math.h>
#define MAXSIZE 12
//nproc=4
void main(int argc, char* argv[])
{
	int myid, nproc;
	int j=0;
	int data[MAXSIZE], i, x, low, high, result=0;
	char fn[255];
	char *fp;
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&nproc);
	MPI_Comm_rank(MPI_COMM_WORLD,&myid);
	x = MAXSIZE/nproc; 
	int recbuf[x],myresult;
	//scatter data t0 4 proc,then each proc send the value of sum or prod or min or max
	if (myid == 0)
	 { 
	for(j=0;j<MAXSIZE;j++)
		data[j]=j+1;	
	}
	MPI_Scatter(data,x,MPI_INT,recbuf,x,MPI_INT,0,MPI_COMM_WORLD); 
	//p1 sum data[3:5]
	if(myid==1)
	{
	for(i=0;i<x;i++)
		result+=recbuf[i];
	MPI_Send(&result,1,MPI_INT,0,1,MPI_COMM_WORLD);

	}
	//p2 min data[6:8]
	else if(myid==2)
	{
	result=recbuf[0];
	for(i=0;i<x;i++)
		if(recbuf[i]<result)
			result=recbuf[i];
	MPI_Send(&result,1,MPI_INT,0,2,MPI_COMM_WORLD);
	}
	//p3 max data[9:11]
	else if(myid==3)
	{
	result=recbuf[0];
	for(i=0;i<x;i++)
		if(recbuf[i]>result)
			result=recbuf[i];
	MPI_Send(&result,1,MPI_INT,0,3,MPI_COMM_WORLD);

	}
	//p0 prod data[0:2]
	else if(myid==0)
	{
	result=1;
	for(i=0;i<x;i++)
		result*=recbuf[i];

	}

	if(myid==0)
	{
	for(i=0;i<3;i++)
		printf("%d,",data[i]); 
	printf("___prod=%d \n",result); 
	MPI_Recv(&myresult,1,MPI_INT,1,1,MPI_COMM_WORLD,MPI_STATUS_IGNORE); 
	for(i=3;i<6;i++)
		printf("%d,",data[i]);
	printf("___sum=%d \n",myresult); 
	MPI_Recv(&myresult,1,MPI_INT,2,2,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
	for(i=6;i<9;i++)
		printf("%d,",data[i]); 
	printf("___min= %d \n",myresult); 
	MPI_Recv(&myresult,1,MPI_INT,3,3,MPI_COMM_WORLD,MPI_STATUS_IGNORE); 
	for(i=9;i<12;i++)
		printf("%d,",data[i]);
	printf("___max=%d \n",myresult); 
	}

	MPI_Finalize();
}
