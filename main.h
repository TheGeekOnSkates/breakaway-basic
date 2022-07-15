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
#define INPUT_BUFFER_SIZE 128

/** The actual size of the input buffer, 2 KB (8 times the size of INPUT_BUFFER_SIZE) */
#define BUFFER_MAX 1024

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

/** Max size of a BASIC program (1K of pointers * 256 bytes max per line = about 15 MB) */
#define PROGRAM_MAX 65536

#define NO_ERROR     0
#define SYNTAX_ERROR 1
#define MEMORY_ERROR 2


/************************************************************************/
/* DATA STRUCTURES                                                      */
/************************************************************************/




/************************************************************************/
/* PROGRAM MEMORY MANAGEMENT FUNCTIONS (defined in Program.c)           */
/************************************************************************/

/**
 * Replaces part of a string (like a find-&-replace)
 * @param[in, out] The string to be edited
 * @pparam[in] Position of the beginning of the string to be replaced
 * @pparam[in] Position of the end of the string to be replaced
 * @pparam[in] The string to put there instead
 */
void ReplaceWithString(char* line, uint16_t start, uint16_t end, char* replacement);

/**
 * Replaces part of a string with a float (for i.e.
 * replacing a variable name with its value, or an
 * equation with its result - i.e. turn "2.7 + 1.3"
 * into "4").  Note that this BASIC stores all its
 * numbers as floats, so this is highly reusable.
 * @param[in, out] The string to be edited
 * @pparam[in] Position of the beginning of the string to be replaced
 * @pparam[in] Position of the end of the string to be replaced
 * @pparam[in] The float to put there instead
 */
void ReplaceWithFloat(char* line, uint16_t from, uint16_t to, float value);

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

/**
 * Turns blocking getchar on or off
 * @param[in] True to turn blocking on, false to turn it off
 * @remarks Used for checking for the Escape key, and probably
 * in GET (once I've done that)
 */
void SetBlocking(bool setting);

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

/** Runs or continues the current program */
void RunOrContinue(void);

/** Prints "?SYNTAX ERROR" (and the line number if running)  on the screen */
void SyntaxError(void);

/** Prints "?MEMORY ERROR" (and the line number if running)  on the screen */
void MemoryError(void);

/**
 * Checks if every "(" character has a closing ")"
 * @param[in] The user's code
 * @returns True if so, false if not
 */
bool ParensMatch(char* string);

#endif
