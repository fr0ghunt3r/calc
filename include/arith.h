#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>


int get_ndigits(long long num);

// multiplcation
int64_t multiply_simple(int64_t x1, int64_t x2, int* is_overflow);
long long multiply_simple_ll(long long x1, long long x2, int* is_overflow);
long long multiply_large(long long x1, long long x2);

// division
double divide_simple(double x1, double x2);
