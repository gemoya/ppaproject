#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int N;

double f(double x){

	return x*x;
}


void trapezoidRule(double *starto, double *result){

	int i;
	double x_i;
	double a =  *starto;
	printf("En trapezoidRule %f\n", a);
	//printf("a: %f\n", a);
	double b = a + N-1;
	//printf("b: %f\n", b);
	double h = (b-a)/(N-1);
	double temp = 0.0;

	temp = temp + f(a)+f(b);
	for(i = 1; i<(N-1); i++){
		x_i = a + i*h;
		temp = temp+ 2*f(x_i);
	}
	*result = *result + h*0.5*temp;

}


int main(int argc, char **argv){

	int i = 0;
	int rank, numprocs;
	int a,b;
	double resto;
	int x_i;

	double *sendbuffer, *recbuffer;

	a = atoi(argv[1]);
	b = atoi(argv[2]);

	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	double result;
	double final;

	N=(b-a+1)/numprocs;
	resto = (b-a+1)%numprocs;
	
	recbuffer = (double *)malloc(sizeof(int)*((b-a+1)/numprocs));

	sendbuffer = (double *)malloc(sizeof(int)*(b-a+1-resto));
	if (rank == 0){

		//sendbuffer = (double *)malloc(sizeof(int)*(b-a+1-resto));
		//fill buffer
		x_i = a;
		i=0;
		while(i<(b-a)+1-resto){

			x_i = a + i;
			sendbuffer[i] = x_i;
			i++;
		}
		// pasando todo el buffer tal vez es mejor sin pasar todo el buffer

	}
	//MPI_Scatter(sendbuffer,N,MPI_DOUBLE,recbuffer,N,MPI_DOUBLE,0,MPI_COMM_WORLD);
	MPI_Bcast(sendbuffer, (b-a)+1-resto, MPI_DOUBLE, 0, MPI_COMM_WORLD);

	double wea = rank*N;
	trapezoidRule( &wea, &result);

	MPI_Reduce(&result, &final, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

	if (rank ==0 ) printf("El resultado final es %f\n", final);
	
	free(sendbuffer);
	MPI_Finalize();


	return 0;
}