#include <stdio.h>
#include <math.h>
#include "arith.h"

void test_multiply_simple( void ) {
    long long result = multiply_simple(121, 32);
    printf("result: %lld\n", result);
}


void test_multiply_big( void ) {
    long long result = multiply_large(1000320001, 1000000455);
    printf("result: %lld\n", result);
}

void test_multiply_neg( void ) {
    long long result = multiply_large(-1000320001, 1000000455);
    printf("result: %lld\n", result);
}

void test_division( void ) {
    double result = divide_simple(55, 5);
    printf("result: %lf\n", result);
}

void test_division_neg( void ) {
    double result = divide_simple(-55, 5);
    printf("result: %lf\n", result);
}

int main(void) {
    test_multiply_simple();
    test_multiply_big();
    test_multiply_neg();
    test_division();
    test_division_neg();
    return 0;
}
