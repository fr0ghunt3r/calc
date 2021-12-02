#include "calculator.h"
#include "arith.h"
#include <stdint.h>


/**
*@file calculator.c
*@date 2021/12/01
*@author Choi S.W
*@version 1.0
*@brief defines functions related to calculation engine. calculation engine calls arithmetic functions in arith.c, using a switch statement.
*/

/**
 *@fn int is_numeric(char* string)
 *@brief checks whether input string is number or not.
 *@param string input string to check whether numeric or not.
 *@return returns 1 if the input is numeric string.
 * otherwise, returns 0 
 */
int is_numeric(char *string) {
    char *end_ptr = NULL;
    int extracted_num = 0;
    extracted_num = strtol(string, &end_ptr, 10);
    if (end_ptr == string) {
        return 0;
    } else if (errno == 0 && extracted_num && (*end_ptr != 0)) {
        return 0;
    }
    return 1;
}

/**
 *@fn int calc(char** num_strings, int length_str, char operation)
 *@brief implements operation based on input data using switch statement.
 *@param num_strings series of string data. It only consists of numeric values.
 *@param length_str the length of numbers, the numbers which is not null in num_strings array.
 *@param operation specific engine_name.
 *@return returns 0 if there exists no problem.
 */
int calc(char** num_strings, int length_str, char operation) {
    int64_t result = 0;
    int is_of = 0;

    switch(operation) {
        case '*':
            result = (int64_t) atoi(num_strings[0]);
            for (int i = 1; i < length_str; ++i) {
                result = multiply_simple(result, (int64_t)atol(num_strings[i]), &is_of);
            }
            printf("%"PRId64"\n", result);
            break;

        case '/':
            ;
            double result_d = (double) atoi(num_strings[0]);
            for (int i = 1; i < length_str; ++i) {
                int denom = atoi(num_strings[i]);
                if (denom == 0) {
                    printf("Error: Attempted to divide by zero!\n");
                    return -1;
                }
                result_d = divide_simple(result_d, (double)denom);
            }
            printf("%.10e\n", result_d);
            break;

        // add another functions here !!


        //
        default :
            printf("Error: Type engine properly\n");
    }
    return 0;
}
