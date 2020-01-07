#include "mpi.h"
#include <stdio.h>
#include <math.h>
#define N 1000
//WHEN INCREASE N DECREASE ERROR
//NPROC%5==0
void main(int argc, char* argv[])
{
	
	int myid, nproc;
	float a=1,b=4,low,high,k,j;
	float sum=0;
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&nproc);
	MPI_Comm_rank(MPI_COMM_WORLD,&myid);
	float x=N/nproc;
	float myresult=0;
	float h=(b-a)/N;
	low=myid*x;
	high=low+x;
	for(k=low;k<high;k++)
		myresult+=a+k*h;
	MPI_Reduce(&myresult,&sum,1,MPI_FLOAT,MPI_SUM,0,MPI_COMM_WORLD);
	sum=(h/2)*(2*sum+a+b);
	if(myid==0)
		printf("result=%f\n",sum);
	MPI_Finalize();
}


























