#include "mpi.h"
#include <stdio.h>
#include <math.h>
#define MAXSIZE 4
void fillA(int A[MAXSIZE][MAXSIZE])
{
	int i=0;
	int j=0;
	printf("A=\n");
	for(i=0;i<MAXSIZE;i++)
	{		
	for(j=0;j<MAXSIZE;j++)
			{
				A[i][j]=4*i+j;
				printf("%d\t",A[i][j]);
			}
			printf("\n");
	}
}
void printC(int* C)
{
	int i=0;
	for(;i<MAXSIZE;i++)
			printf("%d\n",C[i]);
	printf("\n");
}
void fillB(int* B)
{
	int i=0;
	for(;i<MAXSIZE;i++)
		B[i]=1;
	printf("\nB=\n");
	printC(B);
}

void main(int argc, char* argv[])
{
	
	int myid, nproc;
	int n=0,m=0;
	int A[MAXSIZE][MAXSIZE],B[MAXSIZE],C[MAXSIZE]={0,0,0,0},i,j,low, high, myresult=0, sum=0;
	char fn[255];
	char *fp;
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&nproc);
	MPI_Comm_rank(MPI_COMM_WORLD,&myid);
	fillA(A);
	fillB(B);
	for(i=0;i<MAXSIZE;i++)
		for(j=0;j<MAXSIZE;j++)
		{
		C[i]+=A[i][j]*B[j];
		}
	printf("C=\n");
	printC(C);
	//printf("p(%d)=%d\ntime=%f\n", a, sum,(t2-t1)); /* Compute global sum */
	MPI_Finalize();
}


























