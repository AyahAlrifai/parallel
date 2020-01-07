#include "mpi.h"
#include <stdio.h>
#include <math.h>
//proc 0 send to proc 1
// nproc>=2
void main(int argc, char* argv[])
{
	int myid, nproc;
	int j=0;
	int data, i, x, low, high, myresult=0, result=0;

	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&nproc);
	MPI_Comm_rank(MPI_COMM_WORLD,&myid);
	int recbuf;
	data=myid;	
	if(myid==0)
		MPI_Send(&data,1,MPI_INT,1,5,MPI_COMM_WORLD);
	else if(myid==1)
		MPI_Recv(&recbuf,1,MPI_INT,0,5,MPI_COMM_WORLD,MPI_STATUS_IGNORE); 
	
	if(myid==0)
		printf("i am a proc%d and i am a sender,i sent %d \n",myid,myid); 
	else if(myid==1)
		printf("i am a proc%d and i am a reciver,i received %d \n",myid,recbuf); 
	else
		printf("i am a proc%d and i am not a reciver or sender\n",myid); 
	MPI_Finalize();
}
