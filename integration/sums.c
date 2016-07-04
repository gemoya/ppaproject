#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

double h;
double result;
int N;
double step;
//double *results;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

double f(double x){

	return x*x;
}


// Partition a interval with N points
// apply trapezoid rule on this interval
// then add result 
void *partialTrapezoid(void *inter){

	double *interval = ((double *) inter);
	int i;
	double x_i;
	double a = interval[0];
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

	pthread_mutex_lock(&mutex);
	result = result + h*0.5*temp;
	pthread_mutex_unlock(&mutex);
	//

}




int main(int argc, char **argv){
	int a,b, threads;
	int i;

	pthread_t *threads_tab;
	double *thread_args;

	a = atoi(argv[1]);
	b = atoi(argv[2]);
	threads = atoi(argv[3]);

	N = (b-a)/threads;


	threads_tab = (pthread_t *)malloc((threads)*sizeof(pthread_t));

	thread_args = (double *)malloc(sizeof(double)*threads);


	pthread_mutex_init(&mutex, NULL);
	for( i = 0; i<threads; i++){
		thread_args[i]=i*N;
		pthread_create(&threads_tab[i], NULL, partialTrapezoid, (void *) &thread_args[i]);
	}

	for(i=0; i<threads; i++) pthread_join(threads_tab[i], NULL);

	result+=f(b);
	//results = malloc(n*sizeof(double));
	// h = (b-a)/(n-1);
	// result = 0;

	// pthread_mutex_init(&mutex, NULL);

	// // x_0 to x_n 
	// for(i = 0; i<(n); i++){
	// 	x_i = a + i*h;
	// 	pthread_create(&threads_tab[i], NULL, integration, (void *) &x_i);

	// }

	// for(i=0; i<n; i++) pthread_join(threads_tab[i], NULL);

	// pthread_mutex_destroy(&mutex);
	// result = h*0.5*result;



		
	printf("El resultado final es %f\n", result );

	free(threads_tab);
	return 0;
}