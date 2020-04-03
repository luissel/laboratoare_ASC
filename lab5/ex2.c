#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>

#define N 1500

double A[N][N];
double B[N][N];
double C[N][N];

int main(void)
{
	int i, j, k, sum;
	struct timeval start, end;

    // Initializam matricile
    for(i = 0; i < N; i++) {
        for(j = 0; j < N; j++) {
            A[i][j] = 1;
            B[i][j] = 2;
        }
    }

	gettimeofday(&start, NULL);
    
    /*
        i-j-k:  18.08s
        i-k-j:  1.58s
        j-i-k:  15.97s
        j-k-i:  16.41s
        k-i-j:  3.24s
        k-j-i:  31.69s
    */
    for (k = 0; k < N; k++) {
        for (j = 0; j < N; j++) {
            sum = B[k][j];

            for (i = 0; i < N; i++) {
                C[i][j] += A[i][k] * sum;
            }

        }
    }

	gettimeofday(&end, NULL);

    // calculam timpul
	double elapsed = (double) ((end.tv_sec - start.tv_sec) 
		                + (end.tv_usec - start.tv_usec) * 1.e-6) ;

	printf("Time for N = %d is %f seconds.\n", N, elapsed);

	return 0;
}