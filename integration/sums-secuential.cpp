#include <stdio.h>
#include <stdlib.h>

double result;
double h;
int N;
double f(double x){

	return x*x;
//	return x*x*x + 25*x + 31 + (1/x*2);
}

void trapezoidRule(double *starto){

	int i;
	double x_i;
	double a =  *starto;
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
	result = result + h*0.5*temp;

}




int main(int argc, char **argv){
	int a,b,n;
	int i;
	double starto;

	a = atoi(argv[1]);
	b = atoi(argv[2]);
	n = atoi(argv[3]);

	N=(b-a)/(n);




	for(i = 0; i<n; i++){
		starto = i*N;
		trapezoidRule(&starto);
	}
	result+=f(b);

	printf("El resultado final es %f\n", result );

	return 0;



}
