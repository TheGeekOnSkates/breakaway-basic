#ifndef _MAIN_H
#define _MAIN_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

/* 80 chars per line */
#define LINE_SIZE 80

/* 6400 lines * 80 chars per line, 500 KB */
#define PROGRAM_SIZE 6400

/**
 * Checks if two strings contain the same text
 * @param[in] The first string
 * @param[in] The second string
 * @returns True if they do, false if they don't
 */
#define STRING_EQUALS(a, b) (strcmp(a, b) == 0)

/**
 * Checks if the first string starts with the second string
 * @param[in] The first string
 * @param[in] The second string
 * @returns True if it does, false if it doesn't
 */
#define STRING_STARTS_WITH(a, b) (strstr(a, b) == a)

/**
 * Checks if the first string contains the second string
 * @param[in] The first string
 * @param[in] The second string
 * @returns True if it does, false if it doesn't
 */
#define STRING_CONTAINS(a, b) (strstr(a, b) != NULL)

/* Define some types for better readability and size-checking */
typedef char Line[LINE_SIZE];
typedef Line Program[PROGRAM_SIZE];

/**
 * Parses a line of BASIC code
 * @param[in] The memory where the user's code is stores
 * @param[in] The memory where variables' values are stored
 * @param[in] The line the user just typed
 */
void parse(Program program, Program variables, Line line);

/**
 * Adds a line of code to the program
 * @param[in] The memory where the user's code is stores
 * @param[in] The line the user just typed
 */
void set_line(Program program, Line line);

/**
 * Checks if a line of code is a valid statement
 * @param[in] The line the user just typed
 * @returns True if it is, false if it isn't
 */
bool is_statement(Line line);

#endif
