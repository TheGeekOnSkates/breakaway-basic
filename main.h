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

/** If true, print debug messages */
#define DEBUG_MODE 0

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



/************************************************************************/
/* ENUMERATIONS                                                         */
/************************************************************************/

/* BASIC error codes */
enum Errors {
	NO_ERROR,		/* There was no error */
	MEMORY_ERROR,		/* malloc/calloc/realloc failed */
	SYNTAX_ERROR,		/* The user entered invalid BASIC code */
	TYPE_MISMATCH_ERROR,	/* Code tries to add a string and a number */
	OVERFLOW_ERROR,		/* Happens in math functions */
	DIVISION_BY_SERO_ERROR,	/* Can't divide by zero */
	ILLEGAL_QTY_ERROR,	/* Number is too big or too small */
};



/************************************************************************/
/* DATA STRUCTURES                                                      */
/************************************************************************/

/* Stores a list of variables in memory */
typedef struct _var {
	
	/* The name of the variable */
	char* name;
	
	/* The value of the variable */
	char* value;
	
	/* Next one in the list */
	struct _var* next;
} Variable;



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
 * Gets the screen size
 * @param[out] The number of rows, in characters
 * @param[out] The number of columns, in characters
 */
void GetScreenSize(int* rows, int* columns);

/**
 * Gets the total free memory on the system
 * @returns The total bytes free (like on Commodore stuff)
 * @remarks This is just for laughs, of course; the PET, VIC, C64 etc.
 * all had memory in the KB, so this was a much bigger deal back then.
 * And today there's virtual memory, disk space vs. RAM, etc.  I have
 * long since forgotten what those system calls are getting, but I
 * think it's the RAM (cuz that's what it was on most 8-bit computers) :)
 */
uint64_t GetBytesFree(void);

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

/**
 * Replaces an alias with its value
 * @param[in, out] The user's code
 */
void ReplaceAliases(char* buffer);

/** Runs or continues the current program */
void RunOrContinue(void);

/** Clears program memory, and also variables */
void New(void);

/** Prints "?SYNTAX ERROR" (and the line number if running)  on the screen */
void SyntaxError(void);

/** Prints "?MEMORY ERROR" (and the line number if running)  on the screen */
void MemoryError(void);

/**
 * Loads a file into memory
 * @param[in] The file to load
 */
void LoadFile(char* name);

/**
 * Saves program memory to a file
 * @param[in] The file to save
 */
void SaveFile(char* name);

/**
 * Checks if every "(" character has a closing ")"
 * @param[in] The user's code
 * @returns True if so, false if not
 */
bool ParensMatch(char* string);



/***********************************************************************/
/* VARIABLES (defined in vars.c)                                       */
/***********************************************************************/

/**
 * Creates a variable in memory
 * @param[in] The un-parsed string (i.e. "test=123"
 */
Variable* CreateVariable(char* raw);

/**
 * Frees memory used by variables
 * @param[in] The first variable in the list
 */
void FreeVariables(Variable* v);

/**
 * Gets the value of a variable
 * @param[in] The name of the variable
 * @param[in] If true, get an alias instead
 * The variable, or NULL if no match was found
 */
Variable* GetVariable(char* name, bool isAlias);

/**
 * Sets/resets a variable's value
 * @param[in] The raw ("un-parsed") string the user entered
 * @param[in] If true, set an alias instead
 */
void SetVariable(char* raw, bool isAlias);



/************************************************************************/
/* STRING MANIPULATION FUNCTIONS (defined in strings.c)                 */
/************************************************************************/

/**
 * Strips spaces from a string (except inside strings)
 * @param[in, out] The string to be edited
 */
void StripSpaces(char* line);

/**
 * Deletes a character in a string by shifting
 * everything after it to the left 1 character
 * @param[in, out] The string to be edited
 * @param[in] Position of the char to be deleted
 * @param[in] Length of the string
 */
void ShiftLeft(char* string, size_t start, size_t length);

/**
 * "Adds" (joins) two strings connected by a plus sign
 * @param[in, out] The string to be edited (make sure
 * StripSpaces has been called on it first)
 * @example It turns "Awe"+"some" to "Awesome"
 */
void CombineStrings(char* line);

/**
 * Replaces variables with their values
 * @param[in] The first variable in the program's linked list
 * @param[in] The buffer to receive the replacements
 */
void ReplaceVariablesWithValues(char* buffer1);

/**
 * Prints text center-aligneded
 * @param[in] The string to print
 */
void PrintCentered(const char* string);



#endif
