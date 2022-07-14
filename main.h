#ifndef _MAIN_H
#define _MAIN_H

/************************************************************************/
/* DEPENDENCIES                                                         */
/************************************************************************/

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>



/************************************************************************/
/* MACROS                                                               */
/************************************************************************/

/**
 * Max size of user input buffer
 * @todo Find out if there is a way to check what
 * the user's terminal has as its max buffer size.
 * I know Windows has one; Linux...?
 */
#define INPUT_BUFFER_SIZE 256

/**
 * Checks if two strings contain the same text
 * @param[in] The first string
 * @param[in] The second string
 * @returns True if they do, false if they don't
 */
#define STRING_EQUALS(a, b) (strcmp(a, b) == 0)

#define STRING_STARTS_WITH(a, b) (strstr(a, b) == a)




/************************************************************************/
/* OS-DEPENDENT FUNCTIONS (defined in the "os-dependent" folder)        */
/* Note that OS-dependent headers (i.e. Windows.h) are included there.  */
/************************************************************************/

/* Just Linux for now, but eventually might support Windows */
#define Linux true

/** Prints a new line (\n on Linux, \r\n on Windows/DOS, etc.) */
void NewLine(void);



/************************************************************************/
/* INTERPRETER FUNCTIONS (defined in interpreter.c                      */
/************************************************************************/

/**
 * Interprets a single line of BASIC code
 * @param[in] The user's code
 * @remarks called in the main event loop
 */
void Interpret(char* buffer);

#endif
