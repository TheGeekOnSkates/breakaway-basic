#include "main.h"

/* These are all defined in run.c */
extern size_t programCounter;
extern bool thereWasAnError;
extern bool keepRunning;

void eval_expr(Line line, VarList variables) {
	/* Declare vars */
	size_t length = strlen(line);
	
	/* And for now, these are all the steps involved. */
	replace_vars_with_values(line, variables);
	multiply(line, length);
	divide(line, length);
	add(line, length);
	subtract(line, length);
}

void add(char* line, size_t length) {
	/* Declare vars */
	size_t i, start, end, count;
	bool in_quotes;
	float left, right;
	
	/* Count how many *s are in th eline, not
	counting any stars between quotation marks */
	count = count_math_symbols(line, '+');
	
	/* Now for that many times, do the math */
	while(count > 0) {
		in_quotes = false;
		for (i=0; i<length; i++) {
			/* Skip anything in quotes */
			if (line[i] == '"')
				in_quotes = !in_quotes;
			if (in_quotes) continue;
			
			/* Not the char we want, not a problem */
			if (line[i] != '+') continue;
			
			/* Otherwise, go for it */
			start = get_start(line, i);
			end = get_end(line, i);
			left = atof(line + start);
			right = atof(line + i + 1);
			replace_with_float(line, start, end, left + right);
		}
		
		/* And continue the loop */
		count--;
		if (count == 0) break;
	}
}

void subtract(char* line, size_t length) {
	/* Declare vars */
	size_t i, start, end, count;
	bool in_quotes;
	float left, right;
	
	/* Count how many *s are in th eline, not
	counting any stars between quotation marks */
	count = count_math_symbols(line, '-');
	
	/* Now for that many times, do the math */
	while(count > 0) {
		in_quotes = false;
		for (i=0; i<length; i++) {
			/* Skip anything in quotes */
			if (line[i] == '"')
				in_quotes = !in_quotes;
			if (in_quotes) continue;
			
			/* Not the char we want, not a problem */
			if (line[i] != '-') continue;
			
			/* Otherwise, go for it */
			start = get_start(line, i);
			end = get_end(line, i);
			left = atof(line + start);
			right = atof(line + i + 1);
			replace_with_float(line, start, end, left - right);
		}
		
		/* And continue the loop */
		count--;
		if (count == 0) break;
	}
}

void multiply(char* line, size_t length) {
	/* Declare vars */
	size_t i, start, end, count;
	bool in_quotes;
	float left, right;
	
	/* Count how many *s are in th eline, not
	counting any stars between quotation marks */
	count = count_math_symbols(line, '*');
	
	/* Now for that many times, do the math */
	while(count > 0) {
		in_quotes = false;
		for (i=0; i<length; i++) {
			/* Skip anything in quotes */
			if (line[i] == '"')
				in_quotes = !in_quotes;
			if (in_quotes) continue;
			
			/* Not the char we want, not a problem */
			if (line[i] != '*') continue;
			
			/* Otherwise, go for it */
			start = get_start(line, i);
			end = get_end(line, i);
			left = atof(line + start);
			right = atof(line + i + 1);
			replace_with_float(line, start, end, left * right);
		}
		
		/* And continue the loop */
		count--;
		if (count == 0) break;
	}
}

void divide(char* line, size_t length) {
	/* Declare vars */
	size_t i, start, end, count;
	bool in_quotes;
	float left, right;
	
	/* Count how many /s are in th eline, not
	counting any stars between quotation marks */
	count = count_math_symbols(line, '/');
	
	/* Now for that many times, do the math */
	while(count > 0) {
		length = strlen(line);
		in_quotes = false;
		for (i=0; i<length; i++) {
			/* Skip anything in quotes */
			if (line[i] == '"')
				in_quotes = !in_quotes;
			if (in_quotes) continue;
			
			/* Not the char we want, not a problem */
			if (line[i] != '/') continue;
			
			/* Otherwise, go for it */
			start = get_start(line, i);
			end = get_end(line, i);
			left = atof(line + start);
			right = atof(line + i + 1);
			
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
