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
 * @todo Make the function name lowercase; it's not a macro anymore.
 */
bool STRING_EQUALS(char* a, const char* b);

/**
 * Checks if the first string starts with the second string,
 * including case-insensitive comparison
 * @param[in] The first string
 * @param[in] The second string
 * @returns True if it does, false if it doesn't
 * @todo Make the function name lowercase; it's not a macro anymore.
 */
bool STRING_STARTS_WITH(char* a, const char* b);

/**
 * Checks if the first string contains the second string
 * @param[in] The first string
 * @param[in] The second string
 * @returns True if it does, false if it doesn't
 */
#define STRING_CONTAINS(a, b) (strstr(a, b) != NULL)

void combine_strings(char* line);

/**
 * Checks if blocking mode is on
 * @returns True if it is, false if it isn't
 */
bool IsBlocking(void);



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

/**
 * Gets input from the user
 * @param[out] The user's input will be stored here
 */
void ReadLine(char* buffer);

/**
 * Gets the path where the program should look for an auto-run file
 * @pparam[in, out] Path where the auto-run file will be, if there is one 
 */
void get_autorun_file(char* path);



/************************************************************************/
/**** VALIDATION FUNCTIONS (defined in is.c)                         ****/
/************************************************************************/

/**
 * Checks if a line is a valid expression
 * @param[in] The line the user just typed
 * @param[in, out] Pointer to the start of the string; when this function is
 * done, it will move the pointer to the first character AFTER the variable.
 * @returns True if it is, false if it isn't
 */
bool is_expr(Line line, char** position);

/**
 * Checks if a line of code is a valid statement
 * @param[in] The line the user just typed
 * @returns True if it is, false if it isn't
 */
bool is_statement(Line line);

/**
 * These all check if a string is a specific statement
 * @param[in] The line the user just typed
 * @returns True if it is, false if it isn't
 */
bool is_alias(Line line);
bool is_bg(Line line);
bool is_blink(Line line);
bool is_bold(Line line);
bool is_cd(Line line);
bool is_center(Line line);
bool is_cursor(Line line);
bool is_esc(Line line);
bool is_fg(Line line);
bool is_gosub(Line line);
bool is_goto(Line line);
bool is_hidden(Line line);
bool is_if(Line line);
bool is_input(Line line);
bool is_italic(Line line);
bool is_keyword(Line line);
bool is_let(Line line);
bool is_list(Line line);
bool is_load(Line line);
bool is_move(Line line);
bool is_print(Line line);
bool is_prompt(Line line);
bool is_reverse(Line line);
bool is_save(Line line);
bool is_sys(Line line);
bool is_underline(Line line);

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

/**
 * And these all check for types of tokens
 * @param[in] The line to be tested
 * @param[in, out] Same as line, except it gets moved
 * to the first character _after_ the string/expr_list/etc.
 * @returns True if it is, false if it isn't
 */
bool is_string(Line line, char** position);
bool is_relop(Line line, char** position);
bool is_expr_list(Line line, char** position);
bool is_string_function(Line line, char** position);
bool is_function(Line line, char** position);
bool is_var_list(Line line, char** position);



/************************************************************************/
/**** FUNCTIONS THAT RUN CODE (defined in run.c)                     ****/
/************************************************************************/

/**
 * Shows an error message and stops the program
 * @param[in] The error message
 */
void show_error(const char* error);

/**
 * Runs the line the user just typed
 * @param[in] The memory where the user's code is stored
 * @param[in] The memory where aliases are stored
 * @param[in] The memory where variable valeus are stored
 * @param[in] The line the user just typed
 * @param[in] true if in program mode, false if in direct mode
 */
void run(Program program, Program aliases, VarList variables, Line line, bool running);

/**
 * Runs the user's program
 * @param[in] The memory where the user's code is stores
 * @param[in] The memory where aliases are stores
 * @param[in] The memory where variable valeus are stores
 * @param[in] true if in program mode, false if in direct mode
 */
void run_program(Program program, Program aliases, VarList variables);

/**
 * These all run specific instructions
 * @param[in] The memory where the user's code is stored
 * @param[in] The memory where the aliases are stored
 * @param[in] The memory where variable valeus are stored 
 * (for the ones with VarList parameters)
 * @param[in, out] The line the user just typed (this pointer moves)
 */
void run_load(Program program, Program aliases, VarList variables, char* line);
void run_save(Program program, char* line);
void run_list(Program program, Line line);
void run_print(Program program, Line line, bool centered);
void set_alias(Line line, Program aliases);
void run_alias(Line line, Program aliases);
void run_cd(char* line);
void run_esc(char* line);
void run_let(char* line, VarList variables);
void run_move(Line line);
void run_if(Program program, Program aliases, char* line, VarList variables, bool running);
void run_input(char* line, VarList variables);
void run_sys(char* line, VarList variables);



/************************************************************************/
/**** MATH FUNCTIONS (defined in math.c)                             ****/
/************************************************************************/

void eval_expr(Line line, VarList variables);
void multiply(char* line, size_t length);
void divide(char* line, size_t length);
void add(char* line, size_t length);
void subtract(char* line, size_t length);



/************************************************************************/
/**** STRING FUNCTIONS (defined in strings.c)                        ****/
/************************************************************************/

void print_centered(const char* string);
void shift_left(char* string, size_t start, size_t length);
void replace_with_float(char* line, size_t from, size_t to, float value);
void replace_with_string(char* line, size_t start, size_t end, char* replacement);
void strip_spaces(char* string);



/************************************************************************/
/**** FUNCTIONS (defined in functions.c)                             ****/
/************************************************************************/

/** Replaces ASC("Some character") with the ASCII (or Unicode) value */
void replace_asc(Line line);

/** Replaces CHR$(number) with the character represented by that number */
void replace_chr(Line line);

/** Replaces FRE() with the bytes free */
void replace_fre(Line line);

/** Replaces COLUMNS() with the screen width, in characters */
void replace_columns(Line line);

/** Replaces RC() with the return code of the last SYS call */
void replace_rc(Line line);

/** Replaces ROWS() with the screen height, in characters */
void replace_rows(Line line);

/** Replaces TAB() with the Tab character */
void replace_tab(Line line);



/************************************************************************/
/**** TO BE SORTED                                                   ****/
/************************************************************************/

/**
 * Adds a line of code to the program
 * @param[in] The memory where the user's code is stores
 * @param[in] The line the user just typed
 */
void set_line(Program program, Line line);

size_t get_start(char* line, size_t symbol);
size_t get_end(char* line, size_t symbol);
size_t count_math_symbols(Line line, char symbol);
void replace_vars_with_values(Line line, VarList variables);

#endif
