#include <malloc.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <sys/time.h>


int main(int argc, char* argv[])
{
    if(argc != 4)
    {
        printf("apelati cu %s <step_size> <vector_size> <iterations>\n", argv[0]);
        return -1;
    }

    int64_t l = atoi(argv[1]);  // pasul
    int64_t n = atoi(argv[2]);  // dimensiunea vectorului
    int64_t c = atoi(argv[3]);  // numarul de iteratii

    // TODO alocari si initializari
    int64_t step, i;
    char* a = malloc(n * sizeof(*a));
    if (a == NULL) {
        printf("cannot allocate\n");
        return -1;
    }

    struct timeval start, end;
    gettimeofday(&start, NULL);

    // TODO bucla de test
    for (step = 0; step < c; ++step) {
		for (i = 0; i < n; i += l) {
			a[i] += 1;
        }
	}

    // in variabila ops calculez numarul de operatii efectuate
    int64_t ops =  c * n / l;

    gettimeofday(&end, NULL);

    float elapsed = ((end.tv_sec - start.tv_sec)*1000000.0f + end.tv_usec - start.tv_usec)/1000000.0f;
    printf("%12ld, %12ld, %12f, %12g\n", l, ops, elapsed, elapsed/ops);

    free(a);

    return 0;
}

