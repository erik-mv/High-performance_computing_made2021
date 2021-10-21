#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

const size_t N = 1e10;


void seedThreads(unsigned int* seeds) 
{
    int my_thread_id;
    unsigned int seed;
    #pragma omp parallel private (seed, my_thread_id)
    {
        my_thread_id = omp_get_thread_num();
        unsigned int seed = (unsigned) omp_get_wtime();
        seeds[my_thread_id] = (seed & 0xFFFFFFF0) | (my_thread_id + 1);
    }
}


float monte_carlo_pi(const size_t n, unsigned int* seeds) {
    size_t cnt = 0;
    int tid;
    unsigned int seed;

    #pragma omp parallel num_threads(omp_get_max_threads()) \
        default(none) \
        private(tid, seed) \
        shared(n, seeds) \
        reduction(+:cnt)
    {
        tid = omp_get_thread_num();
        seed = seeds[tid];
        srand(seed);

        /*
        Я думаю разницы нет как сделать:
        вписать в единичный квадрат окружность радиусом 0.5 или
        вписать в единичный квадрат четверть окружности радиуса 1.
        Второй вариант более простой и экономичный, поэтому его и сделал
        */
        #pragma omp for
        for (size_t i = 0; i < n; ++i) 
        {
            float x = (float)rand_r(&seed) / RAND_MAX;
            float y = (float)rand_r(&seed) / RAND_MAX;
            if (x * x + y * y <= 1.) 
            {
                ++cnt;
            }
        }
    }

    return cnt * 4.0 / n;
}


int main() 
{
    unsigned int *seeds;
    seeds = (unsigned int *) malloc(omp_get_max_threads() * sizeof(unsigned int));
    seedThreads(&seeds[0]);

    float time = omp_get_wtime();
    printf("pi = %.8f\n", monte_carlo_pi(N, &seeds[0]));
    printf("runtime: %.3fs\n", omp_get_wtime() - time);
    printf("number of threads: %d\n", omp_get_max_threads());
    printf("number of points: %ld\n", N);

    free(seeds); 
    return 0;
}