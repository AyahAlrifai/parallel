#include "mpi.h"
#include <stdio.h>
#include <math.h>
#define MAXSIZE 6
void fill(int A[MAXSIZE][MAXSIZE])
{
	int i=0;
	int j=0;
	for(i=0;i<MAXSIZE;i++)
	{		
	for(j=0;j<MAXSIZE;j++)
			{
				A[i][j]=4*i+j;
				printf("%d\t",A[i][j]);
			}
			printf("\n");
	}
			printf("\n");
}
void fillZero(int A[MAXSIZE][MAXSIZE])
{
	int i=0;
	int j=0;
	for(i=0;i<MAXSIZE;i++)
	{		
	for(j=0;j<MAXSIZE;j++)
			{
				A[i][j]=0;

			}
	}
}
void print(int C[MAXSIZE][MAXSIZE])
{
	int i=0;
	int j=0;
	for(i=0;i<MAXSIZE;i++)
	{		
	for(j=0;j<MAXSIZE;j++)
			{
				printf("%d\t",C[i][j]);
			}
			printf("\n");
	}
	printf("\n");
}


void main(int argc, char* argv[])
{
	
	int myid, nproc;
	int n=0,m=0;
	int A[MAXSIZE][MAXSIZE],B[MAXSIZE][MAXSIZE],C[MAXSIZE][MAXSIZE],i,j,k,low, high, myresult=0, sum=0;
	char fn[255];
	char *fp;
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&nproc);
	MPI_Comm_rank(MPI_COMM_WORLD,&myid);
	fill(A);
	fill(B);
	fillZero(C);
	for(i=0;i<MAXSIZE;i++)
		for(j=0;j<MAXSIZE;j++)
			for(k=0;k<MAXSIZE;k++)
			{
				C[i][j]+=A[i][k]*B[k][j];
			}
	print(C);
	MPI_Finalize();
}


























