#include "mpi.h"
#include <stdio.h>
#include <math.h>
#define MAXSIZE 10
void main(int argc, char* argv[])
{
	int myid, nproc;
	int j=0;
	int  i, x, low, high, myresult=0, result=0;
	char fn[255];
	char *fp;
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&nproc);
	MPI_Comm_rank(MPI_COMM_WORLD,&myid);
	x = MAXSIZE/nproc; /* Add my portion Of data */
	myresult=myid;
	int data[nproc];
	if(myid!=0)
		MPI_Send(&myresult,1,MPI_INT,0,myid,MPI_COMM_WORLD);
	if(myid==0)
	{	
		data[myid]=myid;
		printf("%d ",data[myid]);
		for(i=1;i<nproc;i++){
			MPI_Recv(&data[i],1,MPI_INT,i,i,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			printf("%d ",data[i]);
		}
		
	}
	printf("\n");
	

	MPI_Finalize();
}
