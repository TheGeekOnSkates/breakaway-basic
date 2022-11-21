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



/** -------------------------------------------------------------------------- **/
/** CUSTOM TYPE DEFINITIONS                                                    **/
/** -------------------------------------------------------------------------- **/

enum Tokens {
	NONE,
	ABS, ALL, AS, ASC, ATN, AUTO,
	BACKSLASH, BEEP, BIN,
	CD, CDBL, CHAIN, CHR, CINT, CLEAR, CLOSE, CLS, COMMON, COLON, COS, COMMA,
	CVD, CVI, CVL, CVS, COLOR, CSNG,
	ELSE, END, ENVIRON, ENVIRONS, EQUALS,
	LEFT_BRACKET,
	LEFT_PAREN,
	NUMBER,
	DASH,
	DOUBLE_STAR,
	GREATER_THAN,
	GREATER_THAN_OR_EQUAL,
	HASH,
	HAT,
	LESS_THAN,
	LESS_THAN_OR_EQUAL,
	NOT_EQUAL,
	RIGHT_BRACKET,
	RIGHT_PAREN,
	SEMICOLON,
	SLASH,
	STAR,
	PLUS,
	PRINT,
	REM
};



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
/** GLOBAL VARIABLES                                                           **/
/** -------------------------------------------------------------------------- **/

/*
We don't actually need any of this - the original dev used a of lookup table,
and a token struct with a name (string) and value (number).  That might save a
* few bytes on the download size, but performance-wise that's a lot of strcmp
* calls (lol).  The Tokenize and UnTokenize (which is used in LIST, and IMO also
* should have been used for SAVE) functions can just use const char pointers.
static const char* instructions[] = {
	"DATA", "DATE$", "DEF", "DELETE", "DIM", 
	"ELSE", "END", "ENVIRON$(", "ENVIRON", "EOF(", "ERASE", "ERL", "ERROR", "ERR", "EXP(",
	"FREEFILE", "FREE", "FIX(", "FIELD", "FOR",
	"GET", "GOSUB", "GOTO", "HEX$(",
	"IF", "INPUT", "INSTR(", "INT(",
	"KILL", "LEFT$(", "LEN(",
	"LET", "LINE", "LIST", "LOF(", "LOG(", "LSET",
	"MERGE", "MID$(", "MKD$(",
	"MKI$(", "MKS$(", "NAME", "NEW",
	"NEXT", "OCT$(", "ON", "OPEN",
	"TO", "LOCATE", "STEP", "SLEEP", "POS(",
	"PRINT", "USING", "PUT",
	"RANDOMIZE", "READ", "REM",
	"RESTORE", "RETURN",
	"RIGHT$(", "RND(", "RSET", "RUN",
	"SAVE", "SGN(", "SIN(",
	"SPACE$(", "SPC(", "SQR(",
	"STOP", "STR$(", "STRING$(",
	"SWAP", "SYSTEM", "TAB(",
	"TAN(", "TIME$", "TIMER",
	"TROFF", "TRON", "VAL(", "WEND",
	"WHILE", "WIDTH", "WRITE",
	"MKDIR", "RMDIR",
	"SEG", "EDIT",
	"FILES", "INKEY$", "INPUT$(",
	"INP(", "LLIST", "LPOS(",
	"LPRINT", "NULL", "OUT", "PEEK(", "POKE", "RENUM",
	"RESUME",  "THEN", "OFF", "VARPTR(", "WAIT",
	"MOD", "LOAD", "LOC(", "AND", "OR", "NOT", "XOR", "IMP", "EQV",
	"MKL$(", "INT", "SNG", "FN", "STR", "DBL",
	"VARS",
	"][",
	"LCASE$(", "UCASE$(", "LTRIM$(", "RTRIM$(", "INTERPRET", "OPTION"
};
*/

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

void StringToUpperCase(char* source, char* destination, size_t length) {
	memset(destination, 0, INPUT_BUFFER_SIZE);
	size_t i;
	for (i = 0; i < length; i++)
		destination[i] = toupper(source[i]);
}

void UnTokenize(char* tokens) {
	size_t i;
	for (i = 0; i < INPUT_BUFFER_SIZE; i++) {
		switch(tokens[i]) {
			case ABS: printf(" ABS("); break;
			case ALL: printf(" ALL"); break;
			case AS: printf(" AS"); break;
			case ASC: printf(" ASC("); break;
			case ATN: printf(" ATN("); break;
			case AUTO: printf(" AUTO"); break;
			case BEEP: printf(" BEEP"); break;
			case BIN: printf(" BIN$("); break;
			case CDBL: printf(" CDBL("); break;
			case CD: printf(" CHDIR"); break;
			case CHAIN: printf(" CHAIN"); break;
			case CHR: printf(" CHR$("); break;
			case CINT: printf(" CINT("); break;
			case CLEAR: printf(" CLEAR"); break;
			case CLOSE: printf(" CLOSE"); break;
			case CLS: printf(" CLS"); break;
			case COLON: printf(":"); break;
			case COLOR: printf(" COLOR"); break;
			case COMMA: printf(","); break;
			case COMMON: printf(" COMMON"); break;
			case COS: printf(" COS("); break;
			case CSNG: printf(" CSNG("); break;
			/* LEFT OFF HERE */
			case DASH: printf("-"); break;
			case DOUBLE_STAR: printf(" **"); break;
			case GREATER_THAN_OR_EQUAL: printf(">="); break;
			case GREATER_THAN: printf(">"); break;
			case LEFT_BRACKET: printf("["); break;
			case LEFT_PAREN: printf("("); break;
			case LESS_THAN_OR_EQUAL: printf("<="); break;
			case LESS_THAN: printf("<="); break;
			case NUMBER: printf("{number}"); break;
			case PLUS: printf("+"); break;
			case REM: printf(" REM%s", &tokens[1]); break;
			case RIGHT_BRACKET: printf("]"); break;
			case RIGHT_PAREN: printf(")"); break;
			case SLASH: printf("/"); break;
			case STAR: printf(" *"); break;
			case NONE:
				/* 0, like a NULL terminator, end of line */
				return;
			default:
				NewLine();
				printf("TO-DO: un-tokenize %d", tokens[i]);
				break;
		}
	}
}

void Tokenize(char* source, char* tokens) {
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
		strncpy(tokens, source + 1, length - 1);
		return;
	}
	if (STRING_STARTS_WITH(upper, "REM")) {
		tokens[0] = REM;
		strncpy(tokens, source + 3, length - 1);
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
		if (source[i] == ']') {
			tokens[current] = RIGHT_BRACKET;
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
			// "CSRLIN", "CONT", "CURSES",
		}
		else if (upper[i] == 'D') {
			// TO-DO
		}
		else if (upper[i] == 'E') {
			// TO-DO
		}
		else if (upper[i] == 'F') {
			// TO-DO
		}
		else if (upper[i] == 'G') {
			// TO-DO
		}
		else if (upper[i] == 'H') {
			// TO-DO
		}
		else if (upper[i] == 'I') {
			// TO-DO
		}
		else if (upper[i] == 'J') {
			// TO-DO
		}
		else if (upper[i] == 'K') {
			// TO-DO
		}
		else if (upper[i] == 'L') {
			// TO-DO
		}
		else if (upper[i] == 'M') {
			// TO-DO
		}
		else if (upper[i] == 'N') {
			// TO-DO
		}
		else if (upper[i] == 'O') {
			// TO-DO
		}
		else if (upper[i] == 'P') {
			// TO-DO
		}
		else if (upper[i] == 'Q') {
			// TO-DO
		}
		else if (upper[i] == 'R') {
			// TO-DO
		}
		else if (upper[i] == 'S') {
			// TO-DO
		}
		else if (upper[i] == 'T') {
			// TO-DO
		}
		else if (upper[i] == 'U') {
			// TO-DO
		}
		else if (upper[i] == 'V') {
			// TO-DO
		}
		else if (upper[i] == 'W') {
			// TO-DO
		}
		else {
			// Could be a number, or the name of a variable.
			// Or it could be a really goofy syntax error
		}
	}
}

/**
 * The program starts here.
 */
int main() {
	/* Declare variables */
	char input[INPUT_BUFFER_SIZE],
		tokens[INPUT_BUFFER_SIZE];
	unsigned char * program = NULL;
	
	/* Show the title */
	#if USE_ANSI_ESCAPES
	ANSI_CLEAR();
	#endif
	printf("BREAKAWAY BASIC 1.0");
	NewLine();
	NewLine();
	
	/* Set up the program memory */
	program = calloc((size_t)PROGRAM_SIZE, 1);
	if (program == NULL) {
		perror("Setup error (1)");
		return 1;
	}
	
	/* Main loop */
	while(true) {
		GetInput(input);
		if (strcmp(input, "exit") == 0) break;	// for now
		Tokenize(input, tokens);
		UnTokenize(tokens);	// for now
		printf("You typed: \"%s\"", input);
		NewLine();
	}
	
	/* Final cleanup */
	free(program);
}
