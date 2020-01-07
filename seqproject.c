#include "mpi.h"
#include <stdio.h>
#include <math.h>
#define MAXSIZE 10
#define bagWeight 100
//number of things equal 10 ,so you have to array each one have size 10 for wight and price
//you have 2^10=1024 case and 8 proc ,so each proc have 128 case
void binary(int *arr,int num)
{
	int j=0;
	for(;j<10;j++)
	{
		arr[j]=num%2;
		num=num/2;
	}
}
void main(int argc, char* argv[])
{
	int myid, nproc;
	int w[MAXSIZE],v[MAXSIZE];
	int bin[MAXSIZE],i,j,low,high;
	int best_sol=0,max_v=0,current_v=0,current_w=0;

	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&nproc);
	MPI_Comm_rank(MPI_COMM_WORLD,&myid);
	int max,max_value[nproc],best_solution[nproc];
	if(myid==0)
	{

		for(i=0;i<MAXSIZE;i++)
		{
			w[i]=rand()%(bagWeight+50)+1;
			v[i]=rand()%(bagWeight*5)+1;
		}
		max_v=0;
		best_sol=low;
		for(j = 0; j < pow(2,MAXSIZE); j++)
		{
			binary(bin,j);
			for(i=MAXSIZE-1;i>=0;i--)
			{
				current_v+=v[i]*bin[i];
				current_w+=w[i]*bin[i];
			}
			if(current_v>max_v && current_w<=bagWeight)
				{
					best_sol=j;
					max_v=current_v;
				}
			current_v=0;
			current_w=0;		
		}
		printf("W\t");
		for(i=0;i<MAXSIZE;i++)
			printf("%d\t",w[i]);
		printf("\nv\t");	
		for(i=0;i<MAXSIZE;i++)
			printf("%d\t",v[i]);
		printf("\nS\t");	
		binary(bin,best_sol);
		for(i=0;i<MAXSIZE;i++)
			printf("%d\t",bin[i]);
		printf("\n");	
	}

	MPI_Finalize();
}
