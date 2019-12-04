#include "mpi.h"
#include <stdio.h>
#include <math.h>
#define MAXSIZE 10
//number of things eual 10 ,so you have to array each one have size 10 for wight and price
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
	int w[MAXSIZE]={10,20,30,78,50,60,79,80,90,10},v[MAXSIZE]={100,23,165,756,896,12,35,16,38,90};
	int bin[MAXSIZE],i,j,low,high;
	int max,max_value[8],max_solution[8];
	int max_sol=0,max_v=0,current_v=0,current_w=0;
	char fn[255];
	char *fp;
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&nproc);
	MPI_Comm_rank(MPI_COMM_WORLD,&myid);
	low = myid * 128;
	high = (myid+1)*128;
	MPI_Bcast(w, MAXSIZE, MPI_INT, 0, MPI_COMM_WORLD); 
	MPI_Bcast(v, MAXSIZE, MPI_INT, 0, MPI_COMM_WORLD); 
	max_v=0;
	max_sol=low;
	for(j = low; j < high; j++)
	{
		binary(bin,j);
		for(i=9;i>=0;i--)
		{
			current_v+=v[i]*bin[i];
			current_w+=w[i]*bin[i];
		}
		if(current_v>max_v && current_w<=100)
			{
				max_sol=j;
				max_v=current_v;
			}
		current_v=0;
		current_w=0;		
	}
	MPI_Gather(&max_v,1,MPI_INT, &max_value,1, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Gather(&max_sol,1,MPI_INT, &max_solution,1, MPI_INT, 0, MPI_COMM_WORLD);
	if(myid==0)
	{
		max=0;
		for(i=0;i<8;i++)
		{
			if(max_value[i]>max_value[max])
				max=i;
		}
		printf("W\t");
		for(i=0;i<10;i++)
			printf("%d\t",w[i]);
		printf("\nv\t");	
		for(i=0;i<10;i++)
			printf("%d\t",v[i]);
		printf("\nS\t");	
		binary(bin,max_solution[max]);
		for(i=0;i<10;i++)
			printf("%d\t",bin[i]);
		printf("\n");	
	}
	MPI_Finalize();
}
