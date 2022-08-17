#include "main.h"

extern size_t programCounter;
extern bool keepRunning, thereWasAnError;

void divide(char* line, size_t length) {
	/* Declare vars */
	size_t i, start, end, count;
	bool in_quotes;
	float left, right;
	
	/* Attempting to prevent a segfault due to "uninitialized memory".
	May as well "initialize" (set default value for?) everything and
	see what happens next. :D */
	start = 0; end = 0; left = 0; right = 0; count = 0;
	/*
	Nope, no dice.  To reproduce the glitch, run:
	PRINT 11 * 4 / 2.  Valgrind says it starts in get_start; however,
	there's nothing "uninitialized" in that function (it just wroks with
	both line and i (which is initially set to zero).  This is one of
	those lovely "eventually mode" bugs; someday, Lord willing, I will
	arrive at such an incredibly perfect understanding of this stuff that
	it makes as much sense to me as it does valgrind. :P :D :/ :D
	*/
	
	/* Count how many /s are in th eline, not
	counting any stars between quotation marks */
	count = count_math_symbols(line, '/');
	
	/* Now for that many times, do the math */
	while(count > 0) {
		in_quotes = false;
		for (i=0; i<length; i++) {
			/* Skip anything in quotes */
			if (line[i] == '"')
				in_quotes = !in_quotes;
			if (in_quotes) continue;
			
			/* Not the char we want, not a problem */
			if (line[i] != '/') continue;
			
			/* Otherwise, go for it */
			printf("How about here?\n");
			start = get_start(line, i);
			printf("Or here?\n");
			end = get_end(line, i);
			printf("Maybe here?\n");
			left = atof(line + start);
			printf("Could it be here?\n");
			right = atof(line + i + 1);
			printf("Dad burn it!  Where are you?  Here buggy buggy buggy... :D\n");
			/* Handle division by zero */
			if (right == 0) {
				printf("?DIVISION BY ZERO ERROR");
				if (keepRunning) printf(" IN %ld", programCounter);
				printf("\n");
				keepRunning = false;
				thereWasAnError = true;
				return;
			}
			
			/* Okay, now we're good */
			replace_with_float(line, start, end, left / right);
		}
		
		/* And continue the loop */
		count--;
		if (count == 0) break;
	}
}
