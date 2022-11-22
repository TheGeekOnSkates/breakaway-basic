#include "main.h"

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
			else if (STRING_STARTS_WITH(&upper[i], "AND")) {
				tokens[current] = AND;
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
			else if (STRING_STARTS_WITH(&upper[i], "BOLD")) {
				tokens[current] = BOLD;
				current++;
				i += 3;
				continue;
			}
		}
		else if (upper[i] == 'C') {
			if (STRING_STARTS_WITH(&upper[i], "CDBL(")) {
				tokens[current] = CDBL;
				current++;
				i += 4;
				continue;
			}
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
				tokens[current] = CVI;
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
			if (STRING_STARTS_WITH(&upper[i], "CVS(")) {
				tokens[current] = CVS;
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
			if (STRING_STARTS_WITH(&upper[i], "EXIT")) {
				tokens[current] = EXIT;
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
		else if (upper[i] == 'S') {	/* TO-DO: Add "STRING$(" and "STR" once I understand how they are not the same as "STR$(" */
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
			if (STRING_STARTS_WITH(&upper[i], "SGN(")) {
				tokens[current] = SGN;
				current++;
				i += 3;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "SIN(")) {
				tokens[current] = SIN;
				current++;
				i += 3;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "SLEEP")) {
				tokens[current] = SLEEP;
				current++;
				i += 4;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "SNG")) {
				tokens[current] = SNG;
				current++;
				i += 2;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "SPACE$(")) {
				tokens[current] = SPACE;
				current++;
				i += 6;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "SPC(")) {
				tokens[current] = SPC;
				current++;
				i += 3;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "SQR(")) {
				tokens[current] = SQR;
				current++;
				i += 3;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "STEP")) {
				tokens[current] = STEP;
				current++;
				i += 3;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "STOP")) {
				tokens[current] = STOP;
				current++;
				i += 3;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "STR$(")) {
				tokens[current] = STR;
				current++;
				i += 4;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "SWAP")) {
				tokens[current] = SWAP;
				current++;
				i += 3;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "SYSTEM")) {
				tokens[current] = SYSTEM;
				current++;
				i += 5;
				continue;
			}
		}
		else if (upper[i] == 'T') {
			if (STRING_STARTS_WITH(&upper[i], "TAB")) {
				tokens[current] = TAB;
				current++;
				i += 2;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "TAN(")) {
				tokens[current] = TAN;
				current++;
				i += 3;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "THEN")) {
				tokens[current] = THEN;
				current++;
				i += 3;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "TIME$")) {
				tokens[current] = TIME;
				current++;
				i += 3;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "TIMER")) {
				tokens[current] = TIMER;
				current++;
				i += 4;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "TO")) {
				tokens[current] = TO;
				current++;
				i++;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "TROFF")) {
				tokens[current] = TROFF;
				current++;
				i += 4;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "TRON")) {
				tokens[current] = TRON;
				current++;
				i += 3;
				continue;
			}
		}
		else if (upper[i] == 'U') {
			if (STRING_STARTS_WITH(&upper[i], "USING")) {
				tokens[current] = USING;
				current++;
				i += 4;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "UCASE$(")) {
				tokens[current] = RTRIM;
				current++;
				i += 6;
				continue;
			}
		}
		else if (upper[i] == 'V') {
			if (STRING_STARTS_WITH(&upper[i], "VAL(")) {
				tokens[current] = VAL;
				current++;
				i += 3;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "VARS")) {
				tokens[current] = VARS;
				current++;
				i += 3;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "VARPTR(")) {
				tokens[current] = VARPTR;
				current++;
				i += 6;
				continue;
			}
		}
		else if (upper[i] == 'W') {
			if (STRING_STARTS_WITH(&upper[i], "WAIT")) {
				tokens[current] = WAIT;
				current++;
				i += 3;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "WEND")) {
				tokens[current] = WEND;
				current++;
				i += 3;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "WHILE")) {
				tokens[current] = WHILE;
				current++;
				i += 4;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "WIDTH")) {
				tokens[current] = WIDTH;
				current++;
				i += 4;
				continue;
			}
			if (STRING_STARTS_WITH(&upper[i], "WRITE")) {
				tokens[current] = WRITE;
				current++;
				i += 4;
				continue;
			}
		}
		else if (upper[i] == 'X') {
			if (STRING_STARTS_WITH(&upper[i], "XOR")) {
				tokens[current] = XOR;
				current++;
				i += 2;
				continue;
			}
		}
		else if (upper[i] == '"') {
			tokens[current] = STRING_LITERAL;
			current++;
			while (upper[i] != '"' && i < INPUT_BUFFER_SIZE) {
				i++;
				tokens[current] = (uint16_t)upper[i];
				current++;
			}
		}
		else {
			// Could be the name of a variable.
			// Or it could be a really goofy syntax error :)
		}
	}
}
