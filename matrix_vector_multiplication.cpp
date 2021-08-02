#include <iostream>
#include <omp.h>
#include <stdio.h>

#define M 5
#define N 8

int main()
{
	int y[M],x[N],z[M];
	int A[M * N];
	// y = Ax
	int i, j;
	for ( i = 0; i < N; i++)
	{
		x[i] = rand();
	}
	printf("X :\n");
	for (j = 0; j < M; j++)
	{
		printf("%d\t", x[j]);
	}
	printf("\n");
	printf("A :\n");
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < M; j++)
		{
			A[j + i * M] = rand();
		}
	}
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < M; j++)
		{
			printf("%d\t", A[j + i * M]);
		}
		printf("\n");
	}
#pragma omp parallel private(j,z)
	{
		for (j = 0; j < M; j++)
			z[j] = 0;
		#pragma omp for
		for (i = 0; i < N; i++)
		{
			for (j = 0; j < M; j++)
			{
				z[j] += A[j + i * M] * x[i];
			}
		}
		#pragma omp critical
		for (j = 0; j < M; j++)
		{
			y[j] += z[j];
		}
	}
	printf("\n");
	printf("Y :\n");
	for (j = 0; j < M; j++)
	{
		printf("%d\t",y[j]);
	}
	return 0;
}