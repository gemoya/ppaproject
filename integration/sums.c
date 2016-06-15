#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

double h;
double result = 0;
//double *results;

double f(double x){

	return x*x;
}

void *integration(void *inter){

	double x_k = (double *) inter;
	result = result + f(x_k);
	//results[]


}





int main(int argc, char **argv){

	int step;
	int a,b, n;

	int i,j;

	pthread_t *threads_tab;
	double x_i;

	a = atoi(&argv[1]);
	b = atoi(&argv[2]);
	n = atoi(&argv[3]);

	threads_tab = (pthread_t *)malloc((n)*sizeof(pthread_t));
	//results = malloc(n*sizeof(double));

	h = (b-a)/(n-1);



	// x_0 to x_n == x_1 to x_1
	for(i = 0; i<(n); i++){

		x_i = a + i*h;
		pthread_create(&threads_tab[i], NULL, integration, (void *) x_i);

	}

	for(i=0; i<threads; i++) pthread_join(threads_tab[i], NULL);

	printf("El resultado final es %ld\n", result );

	return 0;
}