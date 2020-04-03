#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>

#define N 1500

double A[N][N];
double B[N][N];
double C[N][N];
double D[N][N];

int main(void)
{
    double *orig_pa, *pa, *pb;
	int i, j, k;
	int numMatrixElems = N * N;
	struct timeval start, end;

	pa = A[0];
	pb = B[0];

	for (i = 0; i != numMatrixElems; ++i, ++pa, ++pb)
	{
		*pa = 1.0;
		*pb = 2.0;
	}

	gettimeofday(&start, NULL);

    /* Tinem cont de pozitia in care ne aflam in cadrul vectorului */
    for (i = 0; i < N; ++i)
    {
        /* linia i din A */
        orig_pa = A[i];

        for (j = 0; j < N; ++j)
        {
            /* coloana j din B */
            pb = &B[0][j];
            pa = orig_pa;

            register double sum = 0.0;
            
            /* pentru a trece la urmatoarea coloana, adunam N pointer-ului */
            for (k = 0; k < N; ++k, ++pa, pb += N)
            {
                sum += *pa * *pb;
            }

            C[i][j] = sum;
        }
    }

	gettimeofday(&end, NULL);

    // calculam timpul
	double elapsed = (double) ((end.tv_sec - start.tv_sec) 
		                + (end.tv_usec - start.tv_usec) * 1.e-6) ;

	printf("Time for N = %d is %f seconds.\n", N, elapsed);

	return 0;
}