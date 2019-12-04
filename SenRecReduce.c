#include "mpi.h"
#include <stdio.h>
#include <math.h>
#define MAXSIZE 10
void main(int argc, char* argv[])
{
	int myid, nproc;
	int j=0;
	int  i, x, low, high, sum=0,prod=1,min,max;
	char fn[255];
	char *fp;
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&nproc);
	MPI_Comm_rank(MPI_COMM_WORLD,&myid);
	x = MAXSIZE/nproc; /* Add my portion Of data */
	int myresult=myid+1;
	int data[nproc];
	if(myid!=0)
		MPI_Send(&myresult,1,MPI_INT,0,myid,MPI_COMM_WORLD);
	if(myid==0)
	{	
		data[myid]=myresult;
		for(i=1;i<nproc;i++){
			MPI_Recv(&data[i],1,MPI_INT,i,i,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		}
		min=data[0];
		max=data[0];
		for(i=0;i<nproc;i++)
		{
			//sum
			sum+=data[i];
			//prod
			prod*=data[i];
			//min
			min=data[i]<min?data[i]:min;
			//max
			max=data[i]>max?data[i]:max;
		}
		printf("sum=%d\nprod=%d\nmin=%d\nmax=%d\n",sum,prod,min,max);
	}
	
	

	MPI_Finalize();
}
