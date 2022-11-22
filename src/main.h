#ifndef _MAIN_H
#define _MAIN_H

/** -------------------------------------------------------------------------- **/
/** DEPENDENCIES                                                               **/
/** -------------------------------------------------------------------------- **/

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#include "ANSI.h"



/** -------------------------------------------------------------------------- **/
/** MACROS                                                                     **/
/** -------------------------------------------------------------------------- **/

/* Delete/comment out this line if not building for DOS/Windows */
#define DOS 1

/* Program size = 256 K */
#define PROGRAM_SIZE 262144U

/* Input buffer size = 81 bytes */
#define INPUT_BUFFER_SIZE 81

/* Delete/comment out this line if you are building for a platform that doesn't support ANSI escape codes */
#define USE_ANSI_ESCAPES 1

#define STRING_EQUALS(a, b) (strcmp(a, b) == 0)
#define STRING_STARTS_WITH(a, b) (strstr(a, b) == a)




/** -------------------------------------------------------------------------- **/
/** ENUMERATIONS                                                               **/
/** -------------------------------------------------------------------------- **/



/**
 * Defines every token Breakaway BASIC uses - every math symbol, instruction,
 * function etc.  The Tokenize function converts users' code to these "tokens",
 * and the UnTokenize (used for LIST and SAVE) converts them back into a human-
 * readable format.
 */
enum Tokens {
	NONE,                  /** Not a token; usually means "end of line" */
	ABS,                   /** Function (something math-y) */
	ALL,                   /** Instruction: "ALL" (meaning unknown) */
	AND,                   /** Instruction: "AND" (same on most basics; bitwise if in comparison, or AND to mean do another comparison) */
	AS,                    /** Instruction: "AS" (meaning unknown - could be like VBA?  Dim var As Int?) */
	ASC,                   /** Function: "ASC" (like on the C64 - gets the ASCII value of a character) */
	ATN,                   /** Function (something math-y) */
	AUTO,                  /** Instruction: "AUTO" (usage unknown) */
	BACKSLASH,             /** Character: "\\" */
	BEEP,                  /** Instruction: "BEEP" (usage unknown) */
	BIN,                   /** Function: "BIN$(" (usage unknown) */
	BOLD,                  /** Instruction: "BOLD" (should by followed by "ON" or "OFF" - it's a terminal setting) */
	CD,                    /** Instruction: "CD" (like in DOS and most other shells, changes which folder you're in) */
	CDBL,                  /** Function: "CDBL(" (usage unknown) */
	CHAIN,                 /** Instruction: "CHAIN" (meaning unknown) */
	CHR,                   /** Function: "CHR$(" (like on the C64) */
	CINT,                  /** Function: "CINT(" (meaning unknown) */
	CLEAR,                 /** Instruction: "CLEAR" (meaning unknown) */
	CLOSE,                 /** Instruction: "CLOSE" (usage unknown - like the C64 maybe?) */
	CLS,                   /** Instruction: "CLS" (like on DOS, or the TRS-80 Model 100); clears the screen */
	COMMON,                /** Instruction: "COMMON" (meaning unknown) */
	COLON,                 /** Character: ":" */
	COS,                   /** Function (something math-y) */
	COMMA,                 /** Character: "," */
	CVD,                   /** Instruction: "CVD" (meaning unknown) */
	CVI,                   /**  */
	CVL,                   /**  */
	CVS,                   /**  */
	COLOR,                 /**  */
	CSNG,                  /**  */
	CSRLIN,                /**  */
	CONT,                  /** Instruction: "CONT" (continues the program, like on the C64) */
	CURSES,                /** Meaning unknown */
	EQUALS,                /** Character: "=" */
	NUMBER,                /** Digit 0-9 or a decimal point */
	DASH,                  /** Character: "-" */
	DATA,                  /** Instruction: "DATA" (possibly like on the C64) */
	DATE,                  /**  */
	DBL,                   /**  */
	DATES,                 /**  */
	DEF,                   /**  */
	DELETE,                /**  */
	DIM,                   /**  */
	DOUBLE_STAR,           /**  */
	EDIT,                  /**  */
	ELSE,                  /** Instruction: "ELSE" (pretty much the same on all BASICs lol) */
	END,                   /** Instruction: "END" (like on the C64, a kind of "end of program" marker) */
	ENVIRONS,              /**  */
	ENVIRON,               /**  */
	BASIC_EOF,             /**  */
	ERASE,                 /**  */
	EQV,                   /**  */
	ERL,                   /**  */
	ERROR,                 /**  */
	ERR,                   /**  */
	EXIT,                  /** Instruction: "EXIT" (exits Breakaway BASIC) */
	EXP,                   /**  */
	FREEFILE,              /**  */
	FREE,                  /** Instruction: "FREE" (similar to on the C64 - prints free memory) */
	FIX,                   /**  */
	FIELD,                 /**  */
	FILES,                 /** Instruction: "FILES" (lists files in the current folder) */
	FN,                    /**  */
	FOR,                   /** Instruction: "FOR" (same across all BASICs that have it - starts a loop) */
	GET,                   /**  */
	GOSUB,                 /** Instruction: "GOSUB" (same across nearly all BASICs - goes to a subroutine) */
	GOTO,                  /** Instruction: "GOTO" (same across all BASICs - goes to a line number) */
	GREATER_THAN,          /** Comparison: ">" */
	GREATER_THAN_OR_EQUAL, /** Comparison: ">=" */
	HASH,                  /** Character: "#" */
	HAT,                   /** Character: "^" */
	HEX,                   /** Function: HEX$(number); converts decimal numbers to a string showing what it looks like in hexadecimal (i.e. pass it 65535, get "FFFF") */
	IF,                    /** Instruction: "IF" (the same across all LANGUAGES that support it, lol... tells the program we're gonna do some comparison) */
	INP,                   /**  */
	INPUT,                 /** Instruction: "INPUT" (like on the C64 and most others - prompts the user for input) */
	INSTR,                 /**  */
	INT,                   /**  */
	INKEY,                 /**  */
	INPUTS,                /**  */
	INTERPRET,             /** Meaning unknown */
	IMP,                   /**  */
	INT2,                  /** Meaning unknown (there was an INT without a "("... so not the C64-like INT("5") lol */
	KILL,                  /** Instruction: "KILL" (like on the TRS-80 Model 100, deletes a file) */
	LCASE,                 /**  */
	LEFT,                  /**  */
	LEFT_BRACKET,          /** Character: "[" */
	LEFT_PAREN,            /** Character: "(" */
	LEN,                   /** Function: "LEN(" (like on the C64, get a string's length) */
	LESS_THAN,             /** Comparison: "<" */
	LESS_THAN_OR_EQUAL,    /** Comparison: "<=" */
	LET,                   /** Instruction: "LET" (pretty much the same on all BASICs - sets a veriable) */
	LINE,                  /**  */
	LIST,                  /** Instruction: "LIST" (same on all BASICs that have it - lists the program) */
	LLIST,                 /**  */
	LOAD,                  /** Instruction: "LOAD" (like on the C64, loads a program) */
	LOC,                   /**  */
	LOCATE,                /**  */
	LOF,                   /**  */
	LOG,                   /** Function (something math-y) */
	LPOS,                  /**  */
	LPRINT,                /**  */
	LSET,                  /**  */
	LTRIM,                 /**  */
	MERGE,                 /**  */
	MID,                   /**  */
	MKD,                   /**  */
	MKDIR,                 /**  */
	MKI,                   /**  */
	MKS,                   /**  */
	MKL,                   /**  */
	MOD,                   /**  */
	NAME,                  /**  */
	NEW,                   /**  */
	NEXT,                  /** Instruction: "NEXT" (like on the C64, used in loops) */
	NOT,                   /**  */
	NOT_EQUAL,             /**  */
	BASIC_NULL,            /**  */
	OCT,                   /**  */
	OFF,                   /**  */
	ON,                    /**  */
	OR,                    /**  */
	OUT,                   /**  */
	OPEN,                  /**  */
	OPTION,                /**  */
	PEEK,                  /**  */
	PLUS,                  /**  */
	POKE,                  /**  */
	POS,                   /**  */
	PRINT,                 /**  */
	PUT,                   /**  */
	RANDOMIZE,             /**  */
	READ,                  /**  */
	REM,                   /**  */
	RENUMBER,              /**  */
	RESTORE,               /**  */
	RESUME,                /**  */
	RETURN,                /** Instruction: "RETURN" (like on the C64 and most other BASICs) return from GOSUB */
	RIGHT,                 /** Function: "RIGHT$(" (like on several BASICs), get the right part of a string (example: PRINT RIGHT$("GEEK", 3) gives us the 3 right-most characters: "EEK" lol */
	RIGHT_BRACKET,         /** Character: "]" */
	RIGHT_PAREN,           /** Character: ")" */
	RMDIR,                 /** Instruction: "RMDIR" (like in DOS and other shells; deletes a folder) */
	RND,                   /**  */
	RSET,                  /**  */
	RTRIM,                 /**  */
	RUN,                   /**  */
	SAVE,                  /**  */
	SEG,                   /**  */
	SEMICOLON,             /** Character: ";" */
	SGN,                   /**  */
	SIN,                   /**  */
	SLASH,                 /** Character: "/" */
	SLEEP,                 /**  */
	SNG,                   /**  */
	SPACE,                 /**  */
	SPC,                   /**  */
	SQR,                   /**  */
	STAR,                  /**  */
	STEP,                  /**  */
	STOP,                  /**  */
	STR,                   /**  */
	STRING,                /**  */
	STRING_LITERAL,        /**  */
	SWAP,                  /**  */
	SYSTEM,                /**  */
	TAB,                   /**  */
	TAN,                   /**  */
	THEN,                  /**  */
	TIME,                  /**  */
	TIMER,                 /**  */
	TO,                    /**  */
	TROFF,                 /**  */
	TRON,                  /**  */
	UCASE,                 /**  */
	USING,                 /**  */
	VAL,                   /**  */
	VARIABLE,              /**  */
	VARS,                  /**  */
	VARPTR,                /**  */
	WAIT,                  /**  */
	WEND,                  /**  */
	WHILE,                 /**  */
	WIDTH,                 /**  */
	WRITE,                 /**  */
	XOR                    /**  */
};



/** -------------------------------------------------------------------------- **/
/** CUSTOM TYPE DEFINITIONS                                                    **/
/** -------------------------------------------------------------------------- **/



/** -------------------------------------------------------------------------- **/
/** OS-DEPENDENT CODE                                                          **/
/** -------------------------------------------------------------------------- **/

/** Prints a newline character to standard output */
void NewLine(void);



/** -------------------------------------------------------------------------- **/
/** TO BE SORTED                                                               **/
/** -------------------------------------------------------------------------- **/

/**
 * Gets user input
 * @param [in, out] The user's input is stored here
 */
void GetInput(char* input);

/**
 * Converts a string to uppercase
 * @param [in] source The original string (we want to keep this as-is)
 * @param [out] destination The uppercase version will be stored here
 * @param [in] length The length of the lowercase string (the first parameter)
 * @remarks Assumes both strings are INPUT_BUFFER_SIZE bytes in length
 */
void StringToUpperCase(char* source, char* destination, size_t length);

/**
 * Runs a line of tokens
 * @param [in] The tokens
 * @returns True unless the user exited Breakaway BASIC
 */
bool RunLine(unsigned char * tokens);

/**
 * Translates a line of user input into a format the program can understand
 * @param [in] source The user's input
 * @param [out] tokens The translated code (an array of "tokens"0 will go here
 */
void Tokenize(char* source, unsigned char* tokens);

/**
 * Un-tokenizes a line of tokens (converts it back to user-readable code)
 * @param [in] The tokens
 * @param [in] Where to print the un-tokenized BASIC code
 */
void UnTokenize(unsigned char* tokens, FILE* where);

#endif
