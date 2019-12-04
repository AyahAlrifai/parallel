#include "mpi.h"
#include <stdio.h>
#include <math.h>
#define MAXSIZE 16
float fact(int x)
{
float res=1;
float i;
for(i=1;i<=x;i++)
	res*=i;
return res;
}
float power (int x,int y)
{
float res=1;
int i=1;
for(i=1;i<=y;i++)
res*=x;
return res;

}
void main(int argc, char* argv[])
{
	int myid, nproc;
int j=0;
	int data[MAXSIZE], i, x, low, high;
	float myresult=0, result=0;
	char fn[255];
	char *fp;
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&nproc);
	MPI_Comm_rank(MPI_COMM_WORLD,&myid);
	x = MAXSIZE/nproc; /* Add my portion Of data */
	low = myid * x;
	high = low + x;
	for(i=low ;i<high;i++)
	{
	myresult+=power(2,i)/fact(i);

	}
	MPI_Reduce(&myresult, &result, 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);
	if (myid == 0) 
		printf("The sum is %f.\n", result);
	MPI_Finalize();
}
