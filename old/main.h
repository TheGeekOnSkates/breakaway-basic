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

/**
 * Checks if the first string contains the second string
 * @param[in] The first string
 * @param[in] The second string
 * @returns True if it does, false if it doesn't
 */
#define STRING_CONTAINS(a, b) (strstr(a, b) != NULL)


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
	ILLEGAL_DIRECT_ERROR,	/* The instruction only runs in program mode */
	SYSTEM_ERROR,		/* Something outside Breakaway BASIC failed */
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
/* INTERPRETER FUNCTIONS (defined in interpreter.c                      */
/************************************************************************/

/**
 * Replaces variables with their values, does math etc.
 * @param[in, out] The string
 */
void Eval(char* line);

/** Runs the NEW instruction */
void RunNEW(void);

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
 * Checks if the line is a variable assignment (i.e. "X = 7")
 * @param[in] The line to look at
 * @returns True if it is, false if it isn't
 */
bool IsAssignment(char* line);

/**
 * Creates a copy of a substring
 * @param[in] The string to get a substring from
 * @param[in] A pointer greater than from (for example, from strstr)
 * @returns The substring (on the heap) or NULL if it fails
 */
char* CopySubstring(char* from, char* to);

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



/************************************************************************/
/* MATH FUNCTIONS (defined in Math.c                                    */
/************************************************************************/

/**
 * Checks if a character is a digit
 * @param[in] The character to be tested
 * @returns True if it is, false if it isn't
 */
static inline bool IsNumeric(char ch) {
	return ch >= '0' && ch <= '9';
}

/**
 * Replaces math equations with their results
 * @param[in] The string to be updated
 */
void EvalMath(char* line);

/**
 * Replaces the text "PI" with 3.1415926whatever
 * @param[in] The string to be updated
 */
void ReplacePI(char* line);

/**
 * Replaces exponents (i.e. 2^3) with their values (i.e. 16)
 * @param[in] The string to be updated
 */
void Exponent(char* line);

/**
 * Replaces addition problems with their solutions
 * @param[in] The string to be updated
 */
void Add(char* line);

/**
 * Replaces subtraction problems with their solutions
 * @param[in] The string to be updated
 */
void Subtract(char* line);

/**
 * Replaces multiplication problems with their solutions
 * @param[in] The string to be updated
 */
void Multiply(char* line);

/**
 * Replaces division problems with their solutions
 * @param[in] The string to be updated
 */
void Divide(char* line);



/************************************************************************/
/* ERROR HANDLERS (defined in errors.c)                                 */
/************************************************************************/

/** Prints the last error */
void PrintLastError(void);

/** Prints "?SYNTAX ERROR" (and the line number if running)  on the screen */
void SyntaxError(void);

/** Prints "?MEMORY ERROR" (and the line number if running)  on the screen */
void MemoryError(void);



/************************************************************************/
/* BASIC FUNCTIONS (defined in functions.c)                             */
/************************************************************************/

void ReplaceFunctions(char* buffer);
void ReplaceCHR(char* buffer);



/************************************************************************/
/* STRING VALIDATION FUNCTIONS (defined in validation.c)                */
/************************************************************************/

/**
 * Checks if a string is a whole number (negatives okay)
 * @param[in] The string to be tested
 * @returns True if it is, false if it isn't
 */
bool StringIsInt(char* string);

/**
 * Checks if a string is a positive whole number
 * @param[in] The string to be tested
 * @returns True if it is, false if it isn't
 */
bool StringIsUInt(char* string);

/**
 * Checks if a string is a number (negatives and ecimals okay)
 * @param[in] The string to be tested
 * @returns True if it is, false if it isn't
 */
bool StringIsFloat(char* string);

/**
 * Checks if a string is a string literal (in quotes)
 * @param[in] The string to be tested
 * @returns True if it is, false if it isn't
 */
bool IsStringLiteral(char* string);

/**
 * Checks if a string is a Breakaway BASIC keyword
 * @param[in] The string to be tested
 * @returns True if it is, false if it isn't
 */
bool IsKeyword(char* string);



/************************************************************************/
/* FUNCTIONS THAT MAKE "IF" WORK (defined in if.c)                      */
/************************************************************************/

/**
 * Handles the THEN <line number> [ELSE <line number>] part
 * @param[in] The user's code
 * @param[in] If true, go to THEN; if not, go to ELSE if there is one
 */
void then(char* line, bool answer);



#endif
