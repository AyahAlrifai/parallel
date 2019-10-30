#include "mpi.h"
#include <stdio.h>
#include <math.h>
#define MAXSIZE 10
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
	int recbuf;
	data=myid;	
	if(myid==3)
	MPI_Send(&data,1,MPI_INT,2,5,MPI_COMM_WORLD);
	else if(myid==2)
	MPI_Recv(&recbuf,1,MPI_INT,3,5,MPI_COMM_WORLD,MPI_STATUS_IGNORE); 
	
	if(myid==2)
			printf("i am a proc %d and i am a slave and i received %d \n",myid,recbuf); 
	else
			printf("i am a proc %d and i am  not a slave \n",myid); 
	MPI_Finalize();
}
