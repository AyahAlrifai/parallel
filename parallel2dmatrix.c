#include "mpi.h"
#include <stdio.h>
#include <math.h>
#define MAXSIZE 4
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

void printScat(int C[2][MAXSIZE])
{
	int i=0;
	int j=0;
	for(i=0;i<2;i++)
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
	int A[MAXSIZE][MAXSIZE],B[MAXSIZE][MAXSIZE],C[MAXSIZE][MAXSIZE],i,j,k,low, high,sum=0;
	char fn[255];
	char *fp;
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&nproc);
	MPI_Comm_rank(MPI_COMM_WORLD,&myid);
	int x=MAXSIZE/nproc;
	int recbuf[x][MAXSIZE], myresult[x][MAXSIZE];
	if(myid==0)
	{
	fill(A);
	fill(B);
	fillZero(C);
	}
	fillZero(myresult);
	MPI_Bcast(B, MAXSIZE*MAXSIZE, MPI_INT, 0, MPI_COMM_WORLD); 
	MPI_Scatter(A,x*MAXSIZE,MPI_INT,recbuf,x*MAXSIZE,MPI_INT,0,MPI_COMM_WORLD);

	for(i=0;i<x;i++)
		for(j=0;j<MAXSIZE;j++)
			for(k=0;k<MAXSIZE;k++)
			{
				myresult[i][j]+=recbuf[i][k]*B[k][j];
				//printf("recbuf[%d][%d]=%d  B[%d][%d]=%d myresult[%d][%d]=%d\n",i,k,recbuf[i][k],k,j,B[k][j],i,j,myresult[i][j]);
			}
	
	MPI_Gather(&myresult,x*MAXSIZE,MPI_INT, &C,x*MAXSIZE, MPI_INT, 0, MPI_COMM_WORLD);
	if(myid==0)
	print(C);
	MPI_Finalize();
}


























