#include "main.h"

const size_t N = 2048;

void RandomMatrix(double * A, size_t N)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            A[i * N + j] = (double) rand() / RAND_MAX;
        }
    }
}

void RandomVector(double * a, size_t N)
{
    for (int i = 0; i < N; i++)
    {
        a[i] = (double) rand() / RAND_MAX;
    }
}

int main()
{
    int NRuns = 5;
    size_t i, j, k;

    double *runtimes;
    double *A, *B, *C, *a, *b;
    
    A = (double *) malloc(N * N * sizeof(double));
    B = (double *) malloc(N * N * sizeof(double));
    C = (double *) malloc(N * N * sizeof(double));
    a = (double *) malloc(N * sizeof(double));
    b = (double *) malloc(N * sizeof(double));
    runtimes = (double *) malloc(NRuns * sizeof(double));

    RandomMatrix(&A[0], N);
    RandomMatrix(&B[0], N);
    RandomVector(&a[0], N);

    // Mat On Mat Mul
    double average_runtime = 0.0;
    for(int n=0; n<NRuns; n++)
    {
        runtimes[n]=CalcMatOnMAtMulTime(&A[0], &B[0], &C[0], N);
        printf("runtime %lf seconds\n", runtimes[n]);
        average_runtime += runtimes[n]/NRuns;
    }
    printf("average runtime Mat On Mat Mul %lf seconds\n", average_runtime);
    printf("---------------------------------\n");
    
    /*
    for (int i=0; i<N; i++)
    {
        for (int j=0; j<N; j++)
        {
            printf("%f\t", A[i * N + j]);
        }
        printf("\n");
    } printf("\n");
    for (int i=0; i<N; i++)
    {
        for (int j=0; j<N; j++)
        {
            printf("%f\t", B[i * N + j]);
        }
        printf("\n");
    } printf("\n");
    for (int i=0; i<N; i++)
    {
        for (int j=0; j<N; j++)
        {
            printf("%f\t", C[i * N + j]);
        }
        printf("\n");
    } printf("\n");*/

    // Mat On Vec Mul
    average_runtime = 0.0;
    for(int n=0; n<NRuns; n++)
    {
        runtimes[n]=CalcMatOnVecMulTime(&A[0], &a[0], &b[0], N);
        printf("runtime %lf seconds\n", runtimes[n]);
        average_runtime += runtimes[n]/NRuns;
    }
    printf("average runtime Mat On Vec Mul %lf seconds\n", average_runtime);
    printf("---------------------------------\n");
    /*
    for (int i=0; i<N; i++)
    {
        for (int j=0; j<N; j++)
        {
            printf("%f\t", A[i * N + j]);
        }
        printf("\n");
    } printf("\n");
    for (int i=0; i<N; i++)
    {
        printf("%f\t", a[i]);
        
    } printf("\n");
    for (int i=0; i<N; i++)
    {
        printf("%f\t", b[i]);
        
    } printf("\n");*/



    free(A); 
    free(B);
    free(C);
    free(a);
    free(b);
    free(runtimes);
    return 0;
}