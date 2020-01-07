#include "mpi.h"
#include <stdio.h>
#include <math.h>
#define MAXSIZE 4
//nproc 4
void main(int argc, char* argv[])
{
	int myid, nproc;
	int j=0;
	int i, x, low, high, myresult=0, result=0,k;

	int data[4];
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&myid);
	MPI_Comm_size(MPI_COMM_WORLD,&nproc);
	int size[nproc];
	//each proc return one value
	for(i=0;i<nproc;i++)
		size[i]=1;
	for(i=0;i<nproc;i++)
		data[i]=i;
	int recbuf;
	MPI_Reduce_scatter(&data,&recbuf,size,MPI_INT,MPI_SUM, MPI_COMM_WORLD);
	//data : is a one dimention array 
	//recbuf : to store the value of "reduce", so the size of it 1 "int"
	//size :  number of elements that receve from each proc {size_proc0,size_proc1,.....} ,
	//dependent on size of receve buffer
	MPI_Gather(&recbuf,1,MPI_INT, &data,1, MPI_INT, 0, MPI_COMM_WORLD);
	//you can solve it without gather,and print the value of recbuf,but the printf statments do not 
	//work in order
	//printf("proc number %d\n sum=%d\n",myid,recbuf);
	if(myid==0)
		for(i=0;i<nproc;i++)
		{
			printf("proc%d\n%d",i,i);
			for(j=1;j<nproc;j++)
				printf("+%d",i);
			printf("=%d\n",data[i]);
		}
	MPI_Finalize();
}
//ex:
//nproc=4
//data=[0,1,2,3];
//send 4 0's to proc0 then find the sum of it and store it in recbuf
//send 4 1's to proc1 then find the sum of it and store it in recbuf
//......

