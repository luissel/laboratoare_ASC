#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
 
void BMMultiply(int n, double* a, double* b, double* c)
{
    int bi = 0;
    int bj = 0;
    int bk = 0;
    int i = 0;
    int j = 0;
    int k = 0;

    // set block dimension
    int blockSize = 100; 

    for(bi = 0; bi < n; bi += blockSize)
        for(bj = 0; bj < n; bj += blockSize)
            for(bk = 0; bk < n; bk += blockSize)
                for(i = 0; i < blockSize; ++i)
                    for(j = 0; j < blockSize; ++j)
                        for(k = 0; k < blockSize; ++k)
                            c[(bi + i) * n + bj + j] += a[(bi + i) * n + bk + k] *
										                b[(bk + k) * n + bj + j];
}
 
int main(void)
{
    int n, doubleN;
    double* A;
    double* B;
    double* C;
    int numreps = 10;
    int i = 0;
    struct timeval tv1, tv2;
    struct timezone tz;
    double elapsed;

    // set matrix dimension n
    n = 1500;
    doubleN = n * n;
    // allocate memory for the matrices
    A = malloc(doubleN * sizeof(*A));
    B = malloc(doubleN * sizeof(*B));
    C = calloc(doubleN, sizeof(*C));

    // allocate matrices A, B & C
    // Initialize matrices A & B
    for (i = 0; i < doubleN; ++i)
	{
		A[i] = 1.0;
		B[i] = 2.0;
	}
 
    //multiply matrices
    printf("Multiply matrices %d times...\n", numreps);
    for (i = 0; i < numreps; ++i)
    {
        gettimeofday(&tv1, &tz);
        BMMultiply(n, A, B, C);
        gettimeofday(&tv2, &tz);
        elapsed +=  (double) (tv2.tv_sec-tv1.tv_sec) + (double) (tv2.tv_usec-tv1.tv_usec) * 1.e-6;
    }

    printf("Time  =  %lf \n", elapsed);
 
    //deallocate memory for matrices A, B & C
    free(A);
    free(B);
    free(C);
 
    return 0;
}