#include "mpi.h"
#include <stdio.h>
#include <math.h>
#define MAXSIZE 10
void main(int argc, char* argv[])
{
	int myid, nproc;
int j=0;
	int data[MAXSIZE], i, x, low, high, myresult=0, result=0,k;
	char fn[255];
	char *fp;
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&nproc);
	MPI_Comm_rank(MPI_COMM_WORLD,&myid);
	x = MAXSIZE/nproc; /* Add my portion Of data */
	int recbuf[5];
	int recbuf0[10];
	if (myid == 0)
	 {  /* Open input file and initialize data */
		for(j=0;j<MAXSIZE;j++)
		data[j]=j;	
	}
//array of elements that need to send part of it for each proc
// count of elements for each proc 
//data type of send elements
//array to receve data from master
//size of elements that receve it from master
//data type of receve elements
	MPI_Scatter(data,x,MPI_INT,recbuf,x,MPI_INT,0,MPI_COMM_WORLD); 
//array of data that need to resend it to master
//size of array of data that need to send it to master
//data type
//array to receve data from all proc 
//size of data from 1 proc, "size of array must be numProc*the_value_of_this_argument"
//data type
	MPI_Gather(&recbuf,x,MPI_INT, &recbuf0,x, MPI_INT, 0, MPI_COMM_WORLD);
	if (myid == 0) 
		for( k=0;k<10;k++)
		printf("%d\n",recbuf0[k]);
	MPI_Finalize();
}
