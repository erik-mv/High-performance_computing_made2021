#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

double CalcMatOnMAtMulTime(double * A, double * B, double * C, size_t N);
double CalcMatOnVecMulTime(double * A, double * a, double * b, size_t N);