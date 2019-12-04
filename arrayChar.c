#include "mpi.h"
#include <stdio.h>
#include <math.h>
#define MAXSIZE 10
void main(int argc, char* argv[])
{
	int myid, nproc;
	int j=0;
	int i, x, low, high, myresult=0, result=0;
	char data[]="Hello";
	char fn[255];
	MPI_Status state;
	char *fp;
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&nproc);
	MPI_Comm_rank(MPI_COMM_WORLD,&myid);
	if(myid==0)
	{	
		for(i=1;i<nproc;i++)
			MPI_Send(&data,6,MPI_CHAR,i,i,MPI_COMM_WORLD);
	}
	if(myid!=0)
		MPI_Recv(&data,6,MPI_CHAR,0,myid,MPI_COMM_WORLD,&state);

	printf("i am a proc %d and data equal %s \n",myid,data); 

	MPI_Finalize();
}
