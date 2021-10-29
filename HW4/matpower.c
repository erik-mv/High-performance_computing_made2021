#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#include <string.h>


const size_t N = 4;
const size_t M = 7;


void print_matrix(int* A, size_t n)
{
    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = 0; j < n; ++j)
        {
            printf("%d ", A[i * n + j]);
        }
        printf("\n");
    }
    printf("\n");
}

void random_matrix(int* A, size_t n)
{
    srand(time(NULL));

    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = 0; j < n; ++j)
        {
            if (i == j)
            {
                A[i * n + j] = 0;
            }
            else
            {
                A[i * n + j] = rand() & 1;
            }
        }
    }
}

void zeroArray(int* C, size_t n)
{
    for (size_t i = 0; i < n; ++i)
        C[i] = 0;
}

void matmul(int* A, int* B, int* C, size_t n)
{
    int i, j, k, temp_index, tid;

    zeroArray(C, n * n);

    #pragma omp parallel \
        private(i, j, k, temp_index, tid) \
        shared(A, B,  C, n)
    {
        for (k = 0; k < n; k++)
        {
            for (i = 0; i < n; i++)
            {
                temp_index = i * n;
                #pragma omp for schedule(static)
                for (j = 0; j < n; j++)
                {
                    C[temp_index + j] += A[temp_index + k] * B[k * n + j];
                }
            }
        }

    }
    
}

void matpower_iter(int* A, int* B, int* C, size_t n, size_t power)
{
    if (power == 1)
    {
        return;
    }
    if (power == 2)
    {
        matmul(A, A, C, n);
        return;

    }
    else if (power % 2 == 1)
    {
        matpower_iter(A, C, B, n, power - 1);
        matmul(B, A, C, n);
    }
    else
    {
        matpower_iter(A, C, B, n, power / 2);
        matmul(B, B, C, n);
    }
}

void matpower(int* A, int* C, size_t n, size_t power)
{
    if (power == 0)
    {
        zeroArray(C, n * n);
        for (size_t i = 0; i < n; ++i)
            C[i * n + i] = 1;
        return;
    }
    else if (power == 1)
    {
        memcpy(C, A, n * n * sizeof(int));
        return;
    }

    int* B = (int*)malloc(n * n * sizeof(int));
    matpower_iter(A, B, C, n, power);
    free(B);
}

int main()
{
    int* A = (int*)malloc(N * N * sizeof(int));
    int* C = (int*)malloc(N * N * sizeof(int));

    random_matrix(A, N);
    print_matrix(A, N);

    printf("N = %ld\n", N);
    printf("M = %ld\n", M);

    float time = omp_get_wtime();
    matpower(A, C, N, M);
    printf("runtime: %.3fs\n", omp_get_wtime() - time);

    print_matrix(C, N);

    free(A);
    free(C);
    return 0;
}
