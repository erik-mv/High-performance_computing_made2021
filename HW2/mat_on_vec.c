#include "main.h"

void ZeroVector(double * a, size_t N)
{
    for(size_t i=0; i<N; i++)
    {
        a[i] = 0.0;
    }
}

double CalcMatOnVecMulTime(double * A, double * a, double * b, size_t N)
{
    struct timeval start, end;
    double r_time = 0.0;
    size_t i, j, k;

    size_t dummy = 0;
    size_t dummy_j = 0;
    size_t dummy_k = 0;
    size_t dummy_kn = 0;

    ZeroVector(&b[0], N);

    gettimeofday(&start, NULL);
    
    for (i = 0; i < N; i++)
    {
        for(j = 0; j < N; j++)
        {
            b[i] = b[i] + A[i * N + j] * a[j];
        }
    }
    gettimeofday(&end, NULL);
    
    r_time = end.tv_sec - start.tv_sec + ((double) (end.tv_usec - start.tv_usec)) / 1000000;
    
    return r_time;
}