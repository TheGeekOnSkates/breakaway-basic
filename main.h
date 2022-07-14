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

#define PROGRAM_MAX 65536
#define SYNTAX_ERROR 1


/************************************************************************/
/* DATA STRUCTURES                                                      */
/************************************************************************/




/************************************************************************/
/* PROGRAM MEMORY MANAGEMENT FUNCTIONS (defined in Program.c)           */
/************************************************************************/

/**
 * Sets up memory for PROGRAM_MAX lines of BASIC code
 * @returns An array of NULL pointers, or NULL if malloc fails
 */
char** CreateProgram(void);

/**
 * Frees memory used by a program, including users' code
 * @param[in] The program
 */
void FreeProgram(char** program);

/**
 * Adds a line of code to the user's program
 * @param[in] The program
 * @param[in] The code
 * @returns True if it works, false if it doesn't
 * @remarks If it fails, it will print an error message
 */
bool AddToProgram(char** program, char* line);

/**
 * Runs the LIST command
 * @param[in] The user's program
 * @param[in] The un-formatted string (in case there's a line number in it)
 */
void ListProgram(char** program, char* instruction);

/**
 * Checks if a line is empty
 * @param[in] The user's program
 * @param[in] The line number to check
 * @returns True if it is, false if it isn't
 */
static inline bool IsLineEmpty(char** program, uint16_t lineNumber) {
	return program[lineNumber] == NULL || program[lineNumber][0] == '\n';
}



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

/**
 * Checks if every "(" character has a closing ")"
 * @param[in] The user's code
 * @returns True if so, false if not
 */
bool ParensMatch(char* string);

#endif
