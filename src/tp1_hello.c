#include <omp.h>
#include <stdio.h>
#define SIZE 1000000

float a[SIZE], b[SIZE], c[SIZE];

int main() {
    // Initialize arrays a and b
    for(int i = 0; i < SIZE; i++) {
        a[i] = i;
        b[i] = 2*i;
    }

    double start = omp_get_wtime();

    #pragma omp parallel for
    for(int i = 0; i < SIZE; i++) {
        c[i] = a[i] + b[i];
    }
    
    double end = omp_get_wtime();
    printf("Time taken: %f seconds\n", end - start);
    
    return 0;
}