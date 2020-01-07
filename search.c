#include "mpi.h"
#include <stdio.h>
#include <math.h>
#define MAXSIZE 1000000
//nproc%10==0
int isPrim(int x)
{
int i;
	if(x==0 || x==1)
		return 0;
	for(i=2;i<x;i++)
		if(x%i==0)
			return 0;
	return 1;
}
void main(int argc, char* argv[])
{
	int myid, nproc;
	int j=0;
	int data[MAXSIZE], i, x, low, high, result=0, count=0;

	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&nproc);
	MPI_Comm_rank(MPI_COMM_WORLD,&myid);
	x = MAXSIZE/nproc; 
	low = myid * x;
	high = low + x;
	for(i=low+1;i<=high;i++)
	{
		count+=isPrim(i);
	}
	MPI_Reduce(&count, &result, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	if(myid==0)
		printf("count of primary number is %d\n",result);
	MPI_Finalize();
}
