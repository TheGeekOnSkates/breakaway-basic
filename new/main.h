#ifndef _MAIN_H
#define _MAIN_H

/************************************************************************/
/**** DEPENDENCIES                                                   ****/
/************************************************************************/

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>



/************************************************************************/
/**** PRE-PROCESSOR MACROS                                           ****/
/************************************************************************/

/** Tell the OS-dependent code we're building for Linux */
#define Linux true

/** 80 chars per line */
#define LINE_SIZE 80

/** 6400 lines * 80 chars per line, 500 KB */
#define PROGRAM_SIZE 6400

/** Because for 0.1, names are letters A-Z */
#define VARIABLE_SIZE 26

/** Clears the screen */
#define CLEAR_SCREEN() printf("\033[H\033[J")

/** Resets the terminal */
#define RESET() printf("\033[0m")

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



/************************************************************************/
/**** TYPE DEFINITIONS                                               ****/
/************************************************************************/

typedef char Line[LINE_SIZE];
typedef Line Program[PROGRAM_SIZE];
typedef Line Variable;
typedef Variable VarList[26];	/* Again, that limit might not last long lol */



/************************************************************************/
/**** OS-DEPENDENT FUNCTIONS (defined in the "os- folder)            ****/
/************************************************************************/

#ifdef Linux
	#include <unistd.h>
	#include <fcntl.h>
	#include <termios.h>
	#include <sys/resource.h>
	#include <sys/ioctl.h>
	#include <readline/readline.h>
	#include <readline/history.h>
#endif

/**
 * For the "CD" command (which does the same thing as in most other OSes)
 * @param[in] The folder to go to
 */
bool GoToFolder(char* folder);

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



/************************************************************************/
/**** VALIDATION FUNCTIONS (defined in is.c)                         ****/
/************************************************************************/

/**
 * Checks if a line is a CD statement
 * @param[in] The line the user just typed
 * @returns True if it is, false if it isn't
 */
bool is_cd(Line line);

/**
 * Checks if a line is an ESC statement
 * @param[in] The line the user just typed
 * @returns True if it is, false if it isn't
 */
bool is_esc(Line line);

/**
 * Checks if a line is a valid expression
 * @param[in] The line the user just typed
 * @param[in, out] Pointer to the start of the string; when this function is
 * done, it will move the pointer to the first character AFTER the variable.
 * @returns True if it is, false if it isn't
 */
bool is_expr(Line line, char** position);

/**
 * All these check if the string is a GOSUB statement.
 * @param[in] The line to be tested
 * @returns True if it is, false if it isn't
 */
bool is_gosub(Line line);

/**
 * All these check if the string is a GOTO statement.
 * @param[in] The line to be tested
 * @returns True if it is, false if it isn't
 */
bool is_goto(Line line);

/**
 * All these check if the string is an IF statement.
 * @param[in] The line to be tested
 * @returns True if it is, false if it isn't
 */
bool is_if(Line line);

/**
 * All these check if the string is a SYS statement.
 * @param[in] The line to be tested
 * @returns True if it is, false if it isn't
 */
bool is_sys(Line line);

/**
 * All these check if the string is an INPUT statement.
 * @param[in] The line to be tested
 * @returns True if it is, false if it isn't
 */
bool is_input(Line line);

/**
 * All these check if the string is a LET statement.
 * @param[in] The line to be tested
 * @returns True if it is, false if it isn't
 */
bool is_let(Line line);

/**
 * All these check if the string is a LIST statement.
 * @param[in] The line to be tested
 * @returns True if it is, false if it isn't
 */
bool is_list(Line line);

/**
 * All these check if the string is a PRINT statement.
 * @param[in] The line to be tested
 * @returns True if it is, false if it isn't
 */
bool is_print(Line line);

/**
 * Checks if a line of code is a valid statement
 * @param[in] The line the user just typed
 * @returns True if it is, false if it isn't
 */
bool is_statement(Line line);

/**
 * Checks if a line is a valid variable name
 * @param[in] The line the user just typed
 * @param[in, out] Pointer to the start of the string; when this function is
 * done, it will move the pointer to the first character AFTER the variable.
 * @returns True if it is, false if it isn't
 * @remarks For version 1, variables are just one letter.  I thought about
 * having the first parameter be just one character, but decided against it
 * because eventually I'd like to add features like Commodore BASIC ($ and %
 * for type-checking, for example).  So I'm using the whole line to "future-
 * proof" this function.  Others might also fall into the same situation.
 */
bool is_var(Line line, char** position);

/**
 * Checks if a line of code is a number
 * @param[in] The line the user just typed
 * @returns True if it is, false if it isn't
 */
bool is_number(Line line, char** position);

static inline bool is_digit(char ch) {
	return ch >= '0' && ch <= '9';
}
static inline bool is_math_action(char ch) {
	return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}
bool is_string(Line line, char** position);
bool is_relop(Line line, char** position);
bool is_expr_list(Line line, char** position);
bool is_var_list(Line line, char** position);



/************************************************************************/
/**** FUNCTIONS THAT RUN CODE (defined in run.c)                     ****/
/************************************************************************/

/**
 * Runs the line the user just typed
 * @param[in] The memory where the user's code is stores
 * @param[in] The memory where variable valeus are stores
 * @param[in] The line the user just typed
 * @param[in] true if in program mode, false if in direct mode
 */
void run(Program program, VarList variables, Line line, bool running);

/**
 * Runs the user's program
 * @param[in] The memory where the user's code is stores
 * @param[in] The memory where variable valeus are stores
 * @param[in] true if in program mode, false if in direct mode
 */
void run_program(Program program, VarList variables) ;

void run_list(Program program, Line line);
void run_print(Program program, Line line);
void run_cd(char* line);
void run_esc(char* line);
void run_let(char* line, VarList variables);
void run_if(Program program, char* line, VarList variables, bool running);
void run_input(char* line, VarList variables);
void run_sys(char* line);


/************************************************************************/
/**** TO BE SORTED                                                   ****/
/************************************************************************/

/**
 * Parses a line of BASIC code
 * @param[in] The memory where the user's code is stores
 * @param[in] The memory where variables' values are stored
 * @param[in] The line the user just typed
 */
void parse(Program program, VarList variables, Line line);

/**
 * Adds a line of code to the program
 * @param[in] The memory where the user's code is stores
 * @param[in] The line the user just typed
 */
void set_line(Program program, Line line);

void eval_expr(Line line, VarList variables);
void print_centered(const char* string);
void shift_left(char* string, size_t start, size_t length);
void replace_with_float(char* line, size_t from, size_t to, float value);
void strip_spaces(char* string);
size_t get_start(char* line, size_t symbol);
size_t get_end(char* line, size_t symbol);
void replace_with_string(char* line, size_t start, size_t end, char* replacement);
size_t count_math_symbols(Line line, char symbol);
void multiply(char* line, size_t length);
void divide(char* line, size_t length);
void add(char* line, size_t length);
void subtract(char* line, size_t length);
void replace_vars_with_values(Line line, VarList variables);

#endif
