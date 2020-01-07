#include "mpi.h"
#include <stdio.h>
#include <math.h>
#define MAXSIZE 1000

void main(int argc, char* argv[])
{
	
	int myid, nproc;
	int n=0,m=0;
	int x[MAXSIZE],y[MAXSIZE],a=7,i,z,low, high, all_sum=0, sum=0;

	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&nproc);
	MPI_Comm_rank(MPI_COMM_WORLD,&myid);
	double t1,t2;
	t1=MPI_Wtime();
	z = MAXSIZE/nproc;
	low = myid * z;
	high = low + z; 
	for(i=0;i<MAXSIZE;i++)
	{
		x[i]=i;
		y[i]=i*i;
	}
	for(n=low;n<high;n++)
		{
		float l=1;
		for(m=0;m<MAXSIZE;m++)
		{
		if(m!=n)
			l*=(a-x[m])/(x[n]-x[m]);
		}
		sum+=y[n]*l;
		
		}	
	MPI_Reduce(&sum, &all_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	if(myid==0)
{		t2=MPI_Wtime();
		printf("p(%d)=%d\ntime=%f\n", a, all_sum,(t2-t1)); /* Compute global sum */
}
	MPI_Finalize();
}
