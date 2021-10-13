#include "main.h"

void ZeroMatrix(double * A, size_t N)
{
    for(size_t i=0; i<N; i++)
    {
        for(size_t j=0; j<N; j++)
        {
            A[i * N + j] = 0.0;
        }
    }
}

double CalcMatOnMAtMulTime(double * A, double * B, double * C, size_t N)
{
    struct timeval start, end;
    double r_time = 0.0;
    size_t i, j, k;

    size_t dummy = 0;
    size_t dummy_j = 0;
    size_t dummy_k = 0;
    size_t dummy_kn = 0;

    ZeroMatrix(&C[0], N);

    gettimeofday(&start, NULL);
    
    for (k = 0; k < N; k++)
    {
        dummy_kn = k * N;
        for(i = 0; i < N; i++)
        {
            dummy = i * N;
            dummy_k = dummy + k; 
            for(j = 0; j < N; j++)
            {
                dummy_j = dummy + j;
                C[dummy_j] = C[dummy_j] + A[dummy_k] * B[dummy_kn + j];
            }
        }
    }
    gettimeofday(&end, NULL);
    
    r_time = end.tv_sec - start.tv_sec + ((double) (end.tv_usec - start.tv_usec)) / 1000000;
    
    return r_time;
}