#include "arith.h"
/**
*@file arith.c
*@date 2021/12/01
*@author Choi S.W
*@version 1.0
*@brief defines functions perform calculation of provided input data.
*/

/**
 *@fn int get_ndigits(long long num)
 *@brief gets a number of digits of input number.
 * in calculation, log base 10 is applied to an absolute value of input. 
 *@param num an input number to get a number of digits.
 *@return a number of digits of an input.
 */
int get_ndigits(long long num) {
    return floor(log10((double)llabs(num))) + 1;
}

/**
 *@fn int64_t multiply_simple(int64_t x1, int64_t x2, int* is_overflow)
 *@brief multiplies two input values x1 and x2. 
 * checking process exists for passed overflow checking flag.
 *@param x1, x2 input values to calculate.
 *@param is_overflow reference of overflow checking flag.
 *@return if it is not overflowed, function returns multiplied together.
 * if overflow happens, function returns x1 value. (designed for printing the last value before overflow)
 */
int64_t multiply_simple(int64_t x1, int64_t x2, int* is_overflow){
    int64_t result = x1 * x2;
    //printf("%"PRId64" * %"PRId64" = %"PRId64"\n", x1, x2, result);
    //printf("%"PRId64" / %"PRId64" = %"PRId64"\n", result, x1, x2);
    //overflow check
    if (x1 != 0 && ((result/x1) != x2)) {
        //printf("overflow\n");
        *is_overflow = 1;
        printf("Runtime error: signed integer overflow at %"PRId64" * %"PRId64"\n", x1, x2);
        printf("Returning with the last value\n");
        return x1;
    }
    return result;
}

/**
 *@fn long long multiply_simple_ll(long long x1, long long x2, int* is_overflow)
 *@brief multiplies two input values x1 and x2, as long long type.
 * checking process exists for passed overflow checking flag.
 *@param x1, x2 input values to calculate.
 *@param is_overflow reference of overflow checking flag.
 *@return if it is not overflowed, function returns multiplied together.
 * if overflow happens, function returns x1 value. (designed for printing the last value before overflow)
 */
long long multiply_simple_ll(long long x1, long long x2, int* is_overflow){
    long long result = x1 * x2;
    printf("%llu * %llu = %llu\n", x1, x2, result);
    printf("%llu / %llu = %llu\n", result, x1, x2);
    //overflow check
    if (x1 != 0 && ((result/x1) != x2)) {
        printf("overflow\n");
        *is_overflow = 1;
        printf("overflow\n");
        return x1;
    }
    return result;
}

/**
 *@fn long long multiply_large(long long x1, long long x2)
 *@brief multiplies two large input values x1 and x2. For faster computation, Karatsuba algorithm which uses divide and conquer approach is applied.
 *The function has a recursive call.
 *@param x1, x2 input values to calculate.
 *@return returns a value of x1, x2 multiplied together
 */
long long multiply_large(long long x1, long long x2) {
    //overflow check
    int n1 = get_ndigits(x1);
    int n2 = get_ndigits(x2);
    int *is_of  = 0;
    if (n1 < 10 || n2 < 10) {
        return multiply_simple_ll((int)x1, (int)x2, is_of);
    }
    // Karatsuba algorithm
    int n = (int) fmax(n1, n2);
    //printf("n digits %d\n", n);
    n = (n / 2) + (n % 2);

    long long E = powl(10, n);

    long long b = x1 / E;
	long long a = x1 - (b * E);
	long long d = x2 / E;
	long long c = x2 - (d * E);

	long long z0 = multiply_large(a, c);
	long long z1 = multiply_large(a + b, c + d);
	long long z2 = multiply_large(b, d);

    return z0 + ((z1 - z0 - z2) * E) + (z2 * (long long)(pow(10, 2 * n)));
}

/**
 *@fn double divide_simple(double x1, double x2)
 *@brief divides the value x1 by x2. This function does not returns remainder. 
 *returns a value consists of integer and fractional parts in decimal expression(double type). be careful about the order : x1/x2.
 *@param x1, x2 input values to calculate division.
 *@return returns a value of x1 divided by x2
 */
double divide_simple(double x1, double x2) {
    return x1 / x2;
}
