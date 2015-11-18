#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main()
{
	int max=5000;
	double sum = 0.0;
	double a[10];
	srand((int)time(NULL));
	for(int i=0; i<10; i++)
	{
		a[i] = (rand()%max)+10;
		sum = sum + a[i];
	}
	for(int i=0; i<10; i++)
		a[i] = a[i]/sum;
	for(int i=0; i<10; i++)
		printf("%lf ", a[i]);
	printf("\n");
	return 0;
}