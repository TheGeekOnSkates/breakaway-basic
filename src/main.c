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
	ALL,                   /**  */
	AND,                   /**  */
	AS,                    /**  */
	ASC,                   /** Function: "ASC" (like on the C64 - gets the ASCII value of a character) */
	ATN,                   /** Function (something math-y) */
	AUTO,                  /**  */
	BACKSLASH,             /** Character: "\\" */
	BEEP,                  /**  */
	BIN,                   /**  */
	BOLD,                  /** Instruction: "BOLD" (should by followed by "ON" or "OFF" - it's a terminal setting) */
	CD,                    /** Instruction: "CD" (like in DOS and most other shells, changes which folder you're in) */
	CDBL,                  /**  */
	CHAIN,                 /**  */
	CHR,                   /** Function: "CHR$(" (like on the C64) */
	CINT,                  /**  */
	CLEAR,                 /**  */
	CLOSE,                 /**  */
	CLS,                   /**  */
	COMMON,                /**  */
	COLON,                 /** Character: ":" */
	COS,                   /** Function (something math-y) */
	COMMA,                 /** Character: "," */
	CVD,                   /**  */
	CVI,                   /**  */
	CVL,                   /**  */
	CVS,                   /**  */
	COLOR,                 /**  */
	CSNG,                  /**  */
	CSRLIN,                /**  */
	CONT,                  /** Instruction: "CONT" (continues the program, like on the C64) */
	CURSES,                /** Meaning unknown */
	EQUALS,                /** Character: "=" */
	
	/* Again, this one could be a weirdo */
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
	EXP,                   /**  */
	FREEFILE,              /**  */
	FREE,                  /** Instruction: "FREE" (similar to on the C64 - prints free memory) */
	FIX,                   /**  */
	FIELD,                 /**  */
	FILES,                 /**  */
	FN,                    /**  */
	FOR,                   /**  */
	GET,                   /**  */
	GOSUB,                 /**  */
	GOTO,                  /**  */
	GREATER_THAN,          /**  */
	GREATER_THAN_OR_EQUAL, /**  */
	HASH,                  /**  */
	HAT,                   /**  */
	HEX,                   /**  */
	IF,                    /**  */
	INP,                   /**  */
	INPUT,                 /**  */
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
	VAR,                   /**  */
	VARPTR,                /**  */
	WAIT,                  /**  */
	WENT,                  /**  */
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

#if BUILD_TARGET == DOS

void NewLine() {
	printf("\r\n");
}

#else

void NewLine() {
	printf("\n");
}

#endif



/** -------------------------------------------------------------------------- **/
/** TO BE SORTED                                                               **/
/** -------------------------------------------------------------------------- **/

/**
 * Gets user input
 * @param [in, out] The user's input is stored here
 */
void GetInput(char* input) {
	/* Declare variables */
	char* temp = NULL;

	/* Clear the contents of the buffer */
	memset(input, 0, INPUT_BUFFER_SIZE);

	/* Get the user's input */
	fgets(input, INPUT_BUFFER_SIZE, stdin);

	/* Strip trailing new-line characters */
	temp = strchr(input, '\n');
	if (temp != NULL) temp[0] = '\0';
	temp = strchr(input, '\r');
	if (temp != NULL) temp[0] = '\0';
}

/**
 * Converts a string to uppercase
 * @param [in] source The original string (we want to keep this as-is)
 * @param [out] destination The uppercase version will be stored here
 * @param [in] length The length of the lowercase string (the first parameter)
 * @remarks Assumes both strings are INPUT_BUFFER_SIZE bytes in length
 */
void StringToUpperCase(char* source, char* destination, size_t length) {
	memset(destination, 0, INPUT_BUFFER_SIZE);
	size_t i;
	for (i = 0; i < length; i++)
		destination[i] = toupper(source[i]);
}

/**
 * Un-tokenizes a line of tokens
 * @param [in] The tokens
 * @param [in] Where to print the un-tokenized BASIC code
 */
void UnTokenize(unsigned char* tokens, FILE* where) {
	size_t i;
	for (i = 0; i < INPUT_BUFFER_SIZE; i++) {
		switch(tokens[i]) {
			case ABS: fprintf(where, " ABS("); break;
			case ALL: fprintf(where, " ALL"); break;
			case AND: fprintf(where, " AND"); break;
			case AS: fprintf(where, " AS"); break;
			case ASC: fprintf(where, " ASC("); break;
			case ATN: fprintf(where, " ATN("); break;
			case AUTO: fprintf(where, " AUTO"); break;
			case BACKSLASH: printf("\\"); break;
			case BEEP: fprintf(where, " BEEP"); break;
			case BIN: fprintf(where, " BIN$("); break;
			case CDBL: fprintf(where, " CDBL("); break;
			case CD: fprintf(where, " CHDIR"); break;
			case CHAIN: fprintf(where, " CHAIN"); break;
			case CHR: fprintf(where, " CHR$("); break;
			case CINT: fprintf(where, " CINT("); break;
			case CLEAR: fprintf(where, " CLEAR"); break;
			case CLOSE: fprintf(where, " CLOSE"); break;
			case CLS: fprintf(where, " CLS"); break;
			case COLON: fprintf(where, ":"); break;
			case COLOR: fprintf(where, " COLOR"); break;
			case COMMA: fprintf(where, ","); break;
			case COMMON: fprintf(where, " COMMON"); break;
			case COS: fprintf(where, " COS("); break;
			case CSNG: fprintf(where, " CSNG("); break;
			case DATA: fprintf(where, " DATA"); break;
			case DATE: fprintf(where, " DATE$"); break;
			case DBL: fprintf(where, " DBL"); break;
			case DEF: fprintf(where, " DEF"); break;
			case DIM: fprintf(where, " DIM"); break;
			case FIELD: fprintf(where, " FIELD"); break;
			case FILES: fprintf(where, " FILES"); break;
			case FN: fprintf(where, " FN"); break;
			case FOR: fprintf(where, " FOR"); break;
			case GET: fprintf(where, " GET"); break;
			case GOSUB: fprintf(where, " GOSUB"); break;
			case GOTO: fprintf(where, " GOTO"); break;
			case HASH: fprintf(where, "#"); break;
			case HAT: fprintf(where, "^"); break;
			case HEX: fprintf(where, " HEX$"); break;
			case IF: fprintf(where, " IF"); break;
			case INPUT: fprintf(where, " INPUT"); break;
			case KILL: fprintf(where, " KILL"); break;
			case LIST: fprintf(where, " LIST"); break;
			case LOCATE: fprintf(where, " LOCATE"); break;
			case MKDIR: fprintf(where, " MKDIR"); break;
			/* LEFT OFF HERE */
			case DASH: fprintf(where, "-"); break;
			case DOUBLE_STAR: fprintf(where, "**"); break;
			case GREATER_THAN_OR_EQUAL: fprintf(where, ">="); break;
			case GREATER_THAN: fprintf(where, ">"); break;
			
			case LEFT_BRACKET: fprintf(where, "["); break;
			case LEFT_PAREN: fprintf(where, "("); break;
			case LESS_THAN_OR_EQUAL: fprintf(where, "<="); break;
			case LESS_THAN: fprintf(where, "<="); break;
			case NUMBER: fprintf(where, "{number}"); break;
			case PLUS: fprintf(where, "+"); break;
			case PRINT: fprintf(where, " PRINT"); break;
			case REM: fprintf(where, " REM%s", &tokens[1]); return;
			case RIGHT_BRACKET: fprintf(where, "]"); break;
			case RIGHT_PAREN: fprintf(where, ")"); break;
			case SLASH: printf("/"); break;
			case STAR: fprintf(where, "*"); break;
			case NONE:
				/* 0, like a NULL terminator, end of line */
				return;
			default:
				fprintf(where, "\r\nTO-DO: un-tokenize %d\r\n", tokens[i]);
				break;
		}
	}
}

void Tokenize(char* source, unsigned char* tokens) {
	size_t i = 0, length = strlen(source), current = 0;
	char upper[INPUT_BUFFER_SIZE];
		
	StringToUpperCase(source, upper, length);
	memset(tokens, 0, INPUT_BUFFER_SIZE);
	
	/*
	Comments are easier than other stuff - handle those first.
	Note that in fbasic, Commodore BASIC and others, you can't do this:
	REM this is a comment:PRINT "this is not".  Same in Breakaway BASIC.
	*/
	if (upper[0] == '\'') {
		tokens[0] = REM;
		memcpy(tokens, source + 1, length - 1);
		return;
	}
	if (STRING_STARTS_WITH(upper, "REM")) {
		tokens[0] = REM;
		memcpy(tokens, source + 3, length - 1);
		return;
	}
	
	for (; i<length; i++) {
		/* First, handle the one-character tokens */
		if (source[i] == '+') {
			tokens[current] = PLUS;
			current++;
			continue;
		}
		if (source[i] == '-') {
			tokens[current] = DASH;
			current++;
			continue;
		}
		if (source[i] == '/') {
			tokens[current] = SLASH;
			current++;
			continue;
		}
		if (source[i] == ':') {
			tokens[current] = COLON;
			current++;
			continue;
		}
		if (source[i] == ';') {
			tokens[current] = SEMICOLON;
			current++;
			continue;
		}
		if (source[i] == '?') {
			tokens[current] = PRINT;
			current++;
			continue;
		}
		if (source[i] == '[') {
			tokens[current] = LEFT_BRACKET;
			current++;
			continue;
		}
		if (source[i] == '(') {
			tokens[current] = LEFT_PAREN;
			current++;
			continue;
		}
		if (source[i] == ')') {
			tokens[current] = RIGHT_PAREN;
			current++;
			continue;
		}
		if (source[i] == ',') {
			tokens[current] = COMMA;
			current++;
			continue;
		}
		if (source[i] == '#') {
			tokens[current] = HASH;
			current++;
			continue;
		}
		if (source[i] == '^') {
			/* Not sure why he called it HAT and not CARET, but I'm sure it'll make sense later lol */
			tokens[current] = HAT;
			current++;
			continue;
		}
		if (source[i] == '\\') {
			tokens[current] = BACKSLASH;
			current++;
			continue;
		}
		
		/* Another easy one is numbers... OR IS IT?  
		I'm gonna have to see how fbasic does numbers.
		Cuz on un-tokenizing, I can say it's a number but nto WHICH number.
		*/
		if (source[i] >= '0' && source[i] <= '9') {
			while (source[i] >= '0' && source[i] <= '9');
			tokens[current] = NUMBER;
			current++;
			continue;
		}
		
		/* Another bit of "low-hanging fruit" is the 2-char instructions */
		if (source[i] == '*') {
			tokens[current] = STAR;
			if (source[i + 1] == '*') {
				tokens[current] = DOUBLE_STAR;
				i++;
			}
			current++;
			continue;
		}
		if (source[i] == '=') {
			tokens[current] = EQUALS;
			if (source[i + 1] == '>') {
				tokens[current] = GREATER_THAN_OR_EQUAL;
				i++;
			}
			else if (source[i + 1] == '<') {
				tokens[current] = LESS_THAN_OR_EQUAL;
				i++;
			}
			current++;
			continue;
		}
		if (source[i] == '<') {
			if (source[i + 1] == '>') {
				tokens[current] = NOT_EQUAL;
				i++;
			}
			else if (source[i + 1] == '=') {
				tokens[current] = LESS_THAN_OR_EQUAL;
				i++;
			}
			else tokens[current] = NOT_EQUAL;
			current++;
			continue;
		}
		if (source[i] == '>') {
			if (source[i + 1] == '<') {
				tokens[current] = NOT_EQUAL;
				i++;
			}
			else if (source[i + 1] == '=') {
				tokens[current] = GREATER_THAN_OR_EQUAL;
				i++;
			}
			else tokens[current] = GREATER_THAN;
			current++;
			continue;
		}
		if (source[i] == ']') {
			if (source[i + 1] == '[') {
				tokens[current] = COMMA;
				i++;
			}
			else tokens[current] = RIGHT_BRACKET;
			current++;
			continue;
		}
		
		/*
		Those checks aside, compare to all the other BASIC instructions.
		Since I don't want to go nuts with nested loops and the possible
		performance drawbacks that come with them, I'll go one letter at
		a time; checking the first letter cuts down on the strcmp calls.
		*/
		if (upper[i] == 'A') {
			if (STRING_STARTS_WITH(&upper[i], "ABS(")) {
				tokens[current] = ABS;
				current++;
				i += 3;
				continue;
			}
			else if (STRING_STARTS_WITH(&upper[i], "ALL")) {
				tokens[current] = ALL;
				current++;
				i += 2;
				continue;
			}
			else if (STRING_STARTS_WITH(&upper[i], "ASC(")) {
				tokens[current] = ASC;
				current++;
				i += 3;
				continue;
			}
			else if (STRING_STARTS_WITH(&upper[i], "AS")) {
				tokens[current] = AS;
				current++;
				i++;
				continue;
			}
			else if (STRING_STARTS_WITH(&upper[i], "ATN(")) {
				tokens[current] = ATN;
				current++;
				i += 3;
				continue;
			}
			else if (STRING_STARTS_WITH(&upper[i], "AUTO")) {
				tokens[current] = AUTO;
				current++;
				i += 3;
				continue;
			}
		}
		else if (upper[i] == 'B') {
			if (STRING_STARTS_WITH(&upper[i], "BEEP")) {
				tokens[current] = BEEP;
				current++;
				i += 3;
				continue;
			}
			else if (STRING_STARTS_WITH(&upper[i], "BIN$(")) {
				tokens[current] = BIN;
				current++;
				i += 4;
				continue;
			}
		}
		else if (upper[i] == 'C') {
			if (STRING_STARTS_WITH(&upper[i], "CD")) {
				tokens[current] = CD;
				current++;
				i++;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "CHAIN")) {
				tokens[current] = CHAIN;
				current++;
				i += 4;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "CHDIR")) {
				tokens[current] = CD;
				current++;
				i += 4;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "CHR$(")) {
				tokens[current] = CHR;
				current++;
				i += 4;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "CINT(")) {
				tokens[current] = CINT;
				current++;
				i += 4;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "CLEAR")) {
				tokens[current] = CLEAR;
				current++;
				i += 4;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "CLOSE")) {
				tokens[current] = CLOSE;
				current++;
				i += 4;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "CLS")) {
				tokens[current] = CLS;
				current++;
				i += 4;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "COMMON")) {
				tokens[current] = COMMON;
				current++;
				i += 5;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "COS(")) {
				tokens[current] = COS;
				current++;
				i += 3;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "CVD(")) {
				tokens[current] = CVD;
				current++;
				i += 3;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "CVI(")) {
				tokens[current] = CVL;
				current++;
				i += 3;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "CVL(")) {
				tokens[current] = CVL;
				current++;
				i += 3;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "COLOR")) {
				tokens[current] = COLOR;
				current++;
				i += 4;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "COLOUR")) {
				tokens[current] = COLOR;
				current++;
				i += 5;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "CSNG(")) {
				tokens[current] = CSNG;
				current++;
				i += 4;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "CDBL(")) {
				tokens[current] = CDBL;
				current++;
				i += 4;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "CSRLIN")) {
				tokens[current] = CSRLIN;
				current++;
				i += 5;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "CONT")) {
				tokens[current] = CONT;
				current++;
				i += 3;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "CURSES")) {
				tokens[current] = CURSES;
				current++;
				i += 5;
				continue;
			}
		}
		else if (upper[i] == 'D') {
			if (STRING_STARTS_WITH(&upper[i], "DATA")) {
				tokens[current] = DATA;
				current++;
				i += 3;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "DATE$")) {
				tokens[current] = DATE;
				current++;
				i += 4;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "DBL")) {
				tokens[current] = DBL;
				current++;
				i += 2;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "DEF")) {
				tokens[current] = DEF;
				current++;
				i += 2;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "DELETE")) {
				tokens[current] = DELETE;
				current++;
				i += 5;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "DIM")) {
				tokens[current] = DIM;
				current++;
				i += 2;
				continue;
			}
		}
		else if (upper[i] == 'E') {
			if (STRING_STARTS_WITH(&upper[i], "ELSE")) {
				tokens[current] = ELSE;
				current++;
				i += 3;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "END")) {
				tokens[current] = END;
				current++;
				i += 2;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "ENVIRON$(")) {
				tokens[current] = ENVIRONS;
				current++;
				i += 8;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "ENVIRON")) {
				tokens[current] = ENVIRON;
				current++;
				i += 6;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "EOF(")) {
				tokens[current] = BASIC_EOF;
				current++;
				i += 3;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "ERASE")) {
				tokens[current] = ERASE;
				current++;
				i += 4;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "ERL")) {
				tokens[current] = ERL;
				current++;
				i += 2;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "ERROR")) {
				tokens[current] = ERROR;
				current++;
				i += 4;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "ERR")) {
				tokens[current] = ERR;
				current++;
				i += 2;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "EXP(")) {
				tokens[current] = EXP;
				current++;
				i += 3;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "EDIT")) {
				tokens[current] = EDIT;
				current++;
				i += 3;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "EQV")) {
				tokens[current] = EDIT;
				current++;
				i += 2;
				continue;
			}
		}
		else if (upper[i] == 'F') {
			if (STRING_STARTS_WITH(&upper[i], "FREEFILE")) {
				tokens[current] = FREEFILE;
				current++;
				i += 7;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "FREE")) {
				tokens[current] = FREE;
				current++;
				i += 3;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "FIX(")) {
				tokens[current] = FIX;
				current++;
				i += 3;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "FIELD")) {
				tokens[current] = FIELD;
				current++;
				i += 4;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "FILES")) {
				tokens[current] = FILES;
				current++;
				i += 4;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "FOR")) {
				tokens[current] = FOR;
				current++;
				i += 2;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "FN")) {
				tokens[current] = FN;
				current++;
				i++;
				continue;
			}
		}
		else if (upper[i] == 'G') {
			if (STRING_STARTS_WITH(&upper[i], "GET")) {
				tokens[current] = GET;
				current++;
				i += 2;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "GOSUB")) {
				tokens[current] = GOSUB;
				current++;
				i += 4;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "GOTO")) {
				tokens[current] = GOTO;
				current++;
				i += 4;
				continue;
			}
		}
		else if (upper[i] == 'H') {
			if (STRING_STARTS_WITH(&upper[i], "HEX$(")) {
				tokens[current] = HEX;
				current++;
				i += 4;
				continue;
			}
		}
		else if (upper[i] == 'I') {
			if (STRING_STARTS_WITH(&upper[i], "IF")) {
				tokens[current] = IF;
				current++;
				i++;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "INP(")) {
				tokens[current] = INP;
				current++;
				i += 3;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "INPUT")) {
				tokens[current] = INPUT;
				current++;
				i += 4;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "INPUT$(")) {
				tokens[current] = INPUTS;
				current++;
				i += 6;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "INSTR(")) {
				tokens[current] = INSTR;
				current++;
				i += 5;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "INKEY$")) {
				tokens[current] = INSTR;
				current++;
				i += 5;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "IMP")) {
				tokens[current] = IMP;
				current++;
				i += 2;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "INTERPRET")) {
				tokens[current] = INTERPRET;
				current++;
				i += 8;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "INT(")) {
				tokens[current] = INT;
				current++;
				i += 3;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "INT")) {
				tokens[current] = INT2;
				current++;
				i += 2;
				continue;
			}
		}
		/* There are no commands starting with J */
		else if (upper[i] == 'K') {
			if (STRING_STARTS_WITH(&upper[i], "KILL")) {
				tokens[current] = KILL;
				current++;
				i += 3;
				continue;
			}
		}
		else if (upper[i] == 'L') {
			if (STRING_STARTS_WITH(&upper[i], "LCASE$(")) {
				tokens[current] = LCASE;
				current++;
				i += 6;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "LEFT$(")) {
				tokens[current] = LEFT;
				current++;
				i += 6;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "LEN(")) {
				tokens[current] = LEN;
				current++;
				i += 3;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "LET")) {
				tokens[current] = LET;
				current++;
				i += 2;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "LINE")) {
				tokens[current] = LINE;
				current++;
				i += 3;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "LIST")) {
				tokens[current] = LIST;
				current++;
				i += 3;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "LOAD")) {
				tokens[current] = LOAD;
				current++;
				i += 3;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "LOC(")) {
				tokens[current] = LOC;
				current++;
				i += 3;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "LOF(")) {
				tokens[current] = LOF;
				current++;
				i += 3;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "LOG(")) {
				tokens[current] = LOG;
				current++;
				i += 3;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "LSET")) {
				tokens[current] = LSET;
				current++;
				i += 3;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "LOCATE")) {
				tokens[current] = LOCATE;
				current++;
				i += 5;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "LLIST")) {
				tokens[current] = LLIST;
				current++;
				i += 4;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "LPOS(")) {
				tokens[current] = LPOS;
				current++;
				i += 3;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "LPRINT")) {
				tokens[current] = LPRINT;
				current++;
				i += 5;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "LTRIM$(")) {
				tokens[current] = LTRIM;
				current++;
				i += 3;
				continue;
			}
		}
		else if (upper[i] == 'M') {
			if (STRING_STARTS_WITH(&upper[i], "MERGE")) {
				tokens[current] = MERGE;
				current++;
				i += 4;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "MID$(")) {
				tokens[current] = MID;
				current++;
				i += 4;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "MKDIR")) {
				tokens[current] = MKDIR;
				current++;
				i += 4;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "MKD$(")) {
				tokens[current] = MKD;
				current++;
				i += 4;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "MKI$(")) {
				tokens[current] = MKI;
				current++;
				i += 4;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "MKS$(")) {
				tokens[current] = MKS;
				current++;
				i += 2;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "MKL$(")) {
				tokens[current] = MKL;
				current++;
				i += 4;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "MOD")) {
				tokens[current] = MOD;
				current++;
				i += 2;
				continue;
			}
		}
		else if (upper[i] == 'N') {
			if (STRING_STARTS_WITH(&upper[i], "NAME")) {
				tokens[current] = NAME;
				current++;
				i += 3;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "NEW")) {
				tokens[current] = NEW;
				current++;
				i += 2;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "NEXT")) {
				tokens[current] = NEXT;
				current++;
				i += 3;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "NULL")) {
				tokens[current] = BASIC_NULL;
				current++;
				i += 3;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "NOT")) {
				tokens[current] = NOT;
				current++;
				i += 2;
				continue;
			}
		}
		else if (upper[i] == 'O') {
			if (STRING_STARTS_WITH(&upper[i], "OCT$(")) {
				tokens[current] = OCT;
				current++;
				i += 4;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "ON")) {
				tokens[current] = ON;
				current++;
				i++;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "OPEN")) {
				tokens[current] = OPEN;
				current++;
				i += 3;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "OUT")) {
				tokens[current] = OUT;
				current++;
				i += 2;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "OR")) {
				tokens[current] = OR;
				current++;
				i++;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "OFF")) {
				tokens[current] = OFF;
				current++;
				i += 2;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "OPTION")) {
				tokens[current] = OPTION;
				current++;
				i += 5;
				continue;
			}
		}
		else if (upper[i] == 'P') {
			if (STRING_STARTS_WITH(&upper[i], "POS(")) {
				tokens[current] = POS;
				current++;
				i += 3;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "PRINT")) {
				tokens[current] = PRINT;
				current++;
				i += 4;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "PUT")) {
				tokens[current] = PUT;
				current++;
				i += 2;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "PEEK(")) {
				tokens[current] = PEEK;
				current++;
				i += 4;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "POKE")) {
				tokens[current] = POKE;
				current++;
				i += 3;
				continue;
			}
		}
		/* No tokens starting with Q :) */
		else if (upper[i] == 'R') {
			if (STRING_STARTS_WITH(&upper[i], "RANDOMIZE")) {
				tokens[current] = RANDOMIZE;
				current++;
				i += 8;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "READ")) {
				tokens[current] = READ;
				current++;
				i += 4;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "RESTORE")) {
				tokens[current] = RESTORE;
				current++;
				i += 6;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "RETURN")) {
				tokens[current] = RETURN;
				current++;
				i += 5;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "RIGHT$(")) {
				tokens[current] = RIGHT;
				current++;
				i += 6;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "RMDIR")) {
				tokens[current] = RMDIR;
				current++;
				i += 4;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "RND(")) {
				tokens[current] = RND;
				current++;
				i += 3;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "RSET")) {
				tokens[current] = RSET;
				current++;
				i += 3;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "RUN")) {
				tokens[current] = RANDOMIZE;
				current++;
				i += 2;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "RENUMBER")) {
				tokens[current] = RENUMBER;
				current++;
				i += 7;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "RESUME")) {
				tokens[current] = RESUME;
				current++;
				i += 5;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "RTRIM$(")) {
				tokens[current] = RTRIM;
				current++;
				i += 6;
				continue;
			}
		}
		else if (upper[i] == 'S') {
			if (STRING_STARTS_WITH(&upper[i], "SAVE")) {
				tokens[current] = RTRIM;
				current++;
				i += 3;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "SEG")) {
				tokens[current] = SEG;
				current++;
				i += 2;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "SLEEP")) {
				tokens[current] = SLEEP;
				current++;
				i += 4;
				continue;
			}
			// "SGN(", "SIN(", "SPACE$(", "SPC(", "SQR(", "STOP", "STR$(", "STRING$(", "SWAP", "SYSTEM", "STEP", "STR", "SNG", 
		}
		else if (upper[i] == 'T') {
			// "TAB(", "TAN(", "TIME$", "TIMER", "TO", "TROFF", "TRON", "THEN", 
		}
		else if (upper[i] == 'U') {
			// "USING", "UCASE$(",
		}
		else if (upper[i] == 'V') {
			// "VAL(", "VARS", "VARPTR(",
		}
		else if (upper[i] == 'W') {
			// "WAIT", "WEND", "WHILE", "WIDTH", "WRITE", 
		}
		else if (upper[i] == 'X') {
			// "XOR"
		}
		else {
			// Could be the name of a variable.
			// Or it could be a really goofy syntax error :)
		}
	}
}

/**
 * The program starts here.
 */
int main() {
	/* Declare variables */
	char input[INPUT_BUFFER_SIZE];
	unsigned char tokens[INPUT_BUFFER_SIZE],
		* program = NULL;
	
	/* Show the title */
	#if USE_ANSI_ESCAPES
	ANSI_CLEAR();
	#endif
	printf("BREAKAWAY BASIC 1.0");
	NewLine();
	NewLine();
	
	/* Set up the program memory */
	program = calloc((size_t)PROGRAM_SIZE, 2);	/* 2 = sizeof(uint16_t) */
	if (program == NULL) {
		perror("Setup error (1)");
		return 1;
	}
	
	/* Main loop */
	while(true) {
		GetInput(input);
		if (strcmp(input, "exit") == 0) break;	// for now
		Tokenize(input, tokens);
		UnTokenize(tokens, stdout);	// for now
		printf("You typed: \"%s\"", input);
		NewLine();
	}
	
	/* Final cleanup */
	free(program);
}
