#ifndef _MAIN_H
#define _MAIN_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

/* 80 chars per line */
#define LINE_SIZE 80

/* 80 lines * 80 chars per line, 6.25 KB */
#define PROGRAM_SIZE 6400

/* Define some types for better readability and size-checking */
typedef char Line[LINE_SIZE];
typedef Line Program[PROGRAM_SIZE];

/**
 * Parses a line of BASIC code
 * @param[in] The memory where the user's code is stores
 * @param[in] The memory where variables' values are stored
 * @param[in] The line the user just typed
 */
void parse(Program* program, Program* variables, Line line);

#endif
