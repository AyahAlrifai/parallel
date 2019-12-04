#include "mpi.h"
#include <stdio.h>
#include <math.h>
#define MAXSIZE 1000

void main(int argc, char* argv[])
{
	
	int myid, nproc;
	int n=0,m=0;
	int x[MAXSIZE],y[MAXSIZE],a=7,i,low, high, myresult=0, sum=0;
	char fn[255];
	char *fp;
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&nproc);
	MPI_Comm_rank(MPI_COMM_WORLD,&myid);
	double t1,t2;
	t1=MPI_Wtime();
	for(i=0;i<MAXSIZE;i++)
	{
		x[i]=i;
		y[i]=i*i;
	}
	if (myid == 0) {  
	for(n=0;n<MAXSIZE;n++)
		{
		float l=1;
		for(m=0;m<MAXSIZE;m++)
		{
		if(m!=n)
			l*=(a-x[m])/(x[n]-x[m]);
		}
		sum+=y[n]*l;
		
		}	
	}
	t2=MPI_Wtime();
	printf("p(%d)=%d\ntime=%f\n", a, sum,(t2-t1)); /* Compute global sum */
	MPI_Finalize();
}
