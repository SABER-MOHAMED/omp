#include <omp.h>
#include <stdio.h>
#define N 500

float A[N][N], B[N][N], C[N][N];

void initialize() {
    for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
            A[i][j] = i + j;
            B[i][j] = i - j;
            C[i][j] = 0;
        }
    }
}

int main() {
    initialize();
    
    double start = omp_get_wtime();
    
    #pragma omp parallel for collapse(2)
    for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
            float sum = 0;
            for(int k=0; k<N; k++) {
                sum += A[i][k] * B[k][j];
            }
            C[i][j] = sum;
        }
    }
    
    double end = omp_get_wtime();
    printf("Time taken: %f seconds\n", end - start);
    
    return 0;
}