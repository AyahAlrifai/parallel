#include "mpi.h"
#include <stdio.h>
#include <math.h>
#define MAXSIZE 8
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
	int A[MAXSIZE][MAXSIZE],B[MAXSIZE],C[MAXSIZE]={0,0,0,0},i,j,low, high, sum=0;
	
	char fn[255];
	char *fp;
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&nproc);
	MPI_Comm_rank(MPI_COMM_WORLD,&myid);
	int x=MAXSIZE/nproc;
	int recbuf[x][MAXSIZE], myresult[x];
	if(myid==0)
	{
		fillA(A);
		fillB(B);
		
	}
	MPI_Bcast(B, MAXSIZE, MPI_INT, 0, MPI_COMM_WORLD); 
	MPI_Scatter(A,x*MAXSIZE,MPI_INT,recbuf,x*MAXSIZE,MPI_INT,0,MPI_COMM_WORLD);
	for(i=0;i<x;i++)
	{
		myresult[i]=0;	
		for(j=0;j<MAXSIZE;j++)
		{
			myresult[i]+=recbuf[i][j]*B[j];
		}
		

	}
	MPI_Gather(&myresult,x,MPI_INT, &C,x, MPI_INT, 0, MPI_COMM_WORLD);
	if(myid==0)
		{
printf("result=\n");
printC(C);
}
	MPI_Finalize();
}


























