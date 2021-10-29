#include <stdio.h>
#include <stdlib.h>
#include <cblas.h>
#include <time.h>

//g++ -std=c++11 HW4/pagerank.c -o HW4/pagerank -lblas

const size_t N = 15;
const double EPS = 1e-8;
const double DUMP_FACTOR = 0.9;


void random_graph(double *A, size_t n) 
{
    srand(time(NULL));

    for (size_t i = 0; i < n; ++i) 
    {
        for (size_t j = 0; j < n; ++j) 
        {
            A[i * n + j] = A[i * n + j];
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

void col_sum(double *A, size_t n) 
{
    for (size_t j = 0; j < n; ++j) 
    {
        double sum = 0;
        for (size_t i = 0; i < n; ++i) 
        {
            sum += A[i * n + j];
        }
        for (size_t i = 0; i < n; ++i) 
        {
            if (A[i * n + j] != 0) 
            {
                A[i * n + j] /= sum;
            }
        }
    }
}

void ranking_naive(double *G, double *X, size_t n) 
{
    double all_sum = 0;
    for (size_t i = 0; i < n; ++i)
    {
        double sum = 0;
        for (size_t j = 0; j < n; ++j)
        {
            sum += G[i * n + j] > 0;
        }
        all_sum += sum;
        X[i] = sum;
    }
    for (size_t i = 0; i < n; ++i)
    {
        X[i] /= all_sum;
    }
}

void ranking_pagerank(double *G, double *X, int n, double dumping_factor, double eps) 
{
    double *Y = (double *) malloc(N * sizeof(double));
    double temp = 1.0 / n;
    for (size_t i = 0; i < n; ++i) 
    {
        X[i] = temp;
        Y[i] = 0;
    }

    double norm;
    temp = (1.0 - dumping_factor) / n;
    do 
    {
        cblas_dgemv(CblasRowMajor, CblasNoTrans, n, n, 1, G, n, X, 1, 0, Y, 1);
        norm = 0;
        for (size_t i = 0; i < n; ++i) 
        {
            Y[i] = dumping_factor * Y[i] + temp;
            norm += (Y[i] - X[i]) * (Y[i] - X[i]);
            X[i] = Y[i];
        }
    } while (norm > eps);

    free(Y);
}

void print_rang(double *X, size_t n)
{
    for (size_t i = 0; i < N; ++i) 
    {
        printf("%.3f ", X[i]);
    }
    printf("\n\n");
}

int main() 
{
    double dumping_factor = 0.9;
    double *G = (double * ) malloc(N * N * sizeof(double));
    double *rank_pagerank = (double * ) malloc(N * sizeof(double));
    double *rank_naive = (double * ) malloc(N * sizeof(double));

    random_graph(G, N);
    col_sum(G, N);

    ranking_pagerank(G, rank_pagerank, N, DUMP_FACTOR, EPS);
    printf("###### Rank PageRank ######\n");
    print_rang(rank_pagerank, N);

    ranking_naive(G, rank_naive, N);
    printf("###### Rank Naive ######\n");
    print_rang(rank_naive, N);

    free(G);
    free(rank_pagerank);
    free(rank_naive);
    return 0;
}
