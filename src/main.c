#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "calculator.h"

/**
*@file main.c
*@date 2021/12/01
*@author Choi S.W
*@version 1.0
*@brief main function of program. parse data from typed arguments on the prompt.
*/


#define MAX_ARGS 10
#define MAX_DATA 1024
#define MAX_CHAR 128

int get_data(char*, char**, int*);
char engine_state(char*);

/**
 *@fn int main(int argc, char* argv[]) 
 *@brief a main code. it handles user input data passed to the function as arguments.
 *@param argc, *argv[]
 *@return if code successfuly runs, returns 0 
 * otherwise, returns -1
 */
int main(int argc, char* argv[]) {
    int integrity_state = 0;
    int mode = 0; // 1 is numeric list mode
    int arg_len = argc - 2;
    int data_len[MAX_ARGS] = {0,};
    char *engine_name;
    char *arg_str[MAX_ARGS];
    char ***data_str =(char***)malloc(MAX_ARGS * sizeof(char**));
    // dynamic allocation of data strings
    for (int i = 0; i < MAX_ARGS; ++i) {
        data_str[i] = (char**)malloc(MAX_DATA * sizeof(char*));
            for (int j = 0; j < MAX_CHAR; ++j) {
                data_str[i][j] = (char*)malloc(MAX_CHAR * sizeof(char));
            }
    }

    if (argc > 2) {
        engine_name = argv[1];
        int j = 0;
        for (int i = 2; i < argc; ++i, ++j) {
            arg_str[j] = argv[i];
        }
        // check every case
        for (int k = 0; k < arg_len; ++k) {
            if((get_data(arg_str[k], data_str[k], &data_len[k]))){
                calc(data_str[k], data_len[k], engine_state(engine_name));
                integrity_state = 1;
            } 
            else if (!is_numeric(arg_str[k])){
                printf("Error: File not exists. Input must be entirely <file_list>, or <list of integers>\n"); 
                return -1;
            } 
            else if (integrity_state && is_numeric(arg_str[k])) {
                printf("Error: Input must be entirely <file_list>, or <list of integers>\n"); 
                return -1;
            }
            else if (arg_len == 1) {
                printf("Error: Two or more input needed, in list of integer mode\n"); 
            }
            else {
                mode = 1;
            }
        }
        
        if (mode == 0) return -1;
        calc(arg_str, arg_len, engine_state(engine_name));

    }
    else {
        printf("Error: Wrong arguments, usage: calc <engine_name> <file_list> or <list of integers>\n");
        return -1;
    }
    return 0;
}

/**
 *@fn int get_data(char *file_strings, char **data_strings, int  *data_length)
 *@brief gets data from input arguments of main code.
 *return 0 or 1, the value designed to decide calculation modes.
 *@param file_strings strings considered file names.
 *@param data_strings destination to store lists of numbers
 *@param data_length length of data_strings
 *@return returns 1 if there exists files contains list of numbers. 
 * otherwise, returns 0 
 */
int get_data(char *file_strings, char **data_strings, int  *data_length) {
    FILE *fp;
    char *suffix = ".txt";
    char file_name[1024];
    char line[256];
    if (strstr(file_strings, suffix) == NULL) {
        sprintf(file_name, "%s.txt", file_strings);
        fp = fopen(file_name, "r");
    } else { 
        fp = fopen(file_strings, "r");
    }
    if (fp == NULL) {
        // if there's no file with same name, return 0
        return 0;
    }

    int nl_count = 0;
    while (fgets(data_strings[nl_count], MAX_CHAR, fp)) {
        data_strings[nl_count][strlen(data_strings[nl_count]) - 1] = '\0';
        ++nl_count;
    }
    
    *data_length = nl_count;
    fclose(fp);
    return 1;
}

/**
 *@fn char engine_state(char* engine_name) {
 *@brief function for switch statement in calc function, input engine_name is converted to a simple char value.
 *@param engine_name engine name extracted from argv[1] in main.
 *@return returns '*', '/', mapped to engine names multiplier and divider respectively.
 */
char engine_state(char* engine_name) {
    if (!strcmp(engine_name, "multiplier")) 
        return '*';
    else if (!strcmp(engine_name, "divider")) 
        return '/';
    return -1;
}
