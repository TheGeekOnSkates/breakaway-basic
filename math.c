#include "main.h"

/* These are all defined in run.c */
extern size_t programCounter;
extern bool thereWasAnError;
extern bool keepRunning;

size_t count_math_symbols(Line line, char symbol) {
	bool in_quotes;
	size_t i, length, total;
	
	in_quotes = false;
	length = strlen(line);
	total = 0;
	
	for (i=0; i<length; i++) {
		if (line[i] == '"')
			in_quotes = !in_quotes;
		if (in_quotes) continue;
		if (line[i] == symbol) total++;
	}
	return total;
}

void eval_expr(Line line, VarList variables) {
	/* Handle string functions first */
	replace_chr(line);
	replace_tab(line);
	combine_strings(line);
	
	/* Unfortunately, all this needs to be handled first (see below) */
	replace_asc(line);
	replace_columns(line);
	replace_fre(line);
	replace_rc(line);
	replace_rows(line);
	
	/* Bug I'll need to address in 0.3:
	If I call this first (which is what I'd like),
	all the one-letter variables get replaced with zeroes.
	This makes sense (cuz the only variables 0.2 supports
	are capital letters A-Z, which default to zero), but
	I think is_var will have to check that the variable is
	doesn't contain a keyword before replacing */
	replace_vars_with_values(line, variables);

	/* Then we can crunch numbers (which again, I would like to do first)*/
	multiply(line, LINE_SIZE);
	divide(line, LINE_SIZE);
	add(line, LINE_SIZE);
	subtract(line, LINE_SIZE);
}

size_t get_start(char* line, size_t symbol) {
	/* Move past the math symbol (+*-/) */
	symbol--;
	if (symbol <= 0) return 0;
	
	/* Move past any spaces */
	while(line[symbol] == ' ') symbol--;
	if (symbol <= 0) return 0;
	
	/* Here there should be digits */
	while (symbol > 0 && is_digit(line[symbol])) symbol--;
	if (symbol <= 0) return 0;
	
	/* Move past the decimal point, if there is one */
	if (line[symbol] != '.' && line[symbol] != '\0') return symbol;
	if (symbol <= 0) return 0;
	
	/* Move past the whole (not factional) digits, if there were any */
	while (symbol > 0 && is_digit(line[symbol])) symbol--;
	if (symbol <= 0) return 0;
	
	/* If there was a sign, move past that */
	if (line[symbol] == '+' || line[symbol] == '-') symbol--;
	
	/* And we're done */
	symbol--;
	return symbol <= 0 ? 0 : symbol;
}

size_t get_end(char* line, size_t symbol) {
	/* First, move past the math symbol (+*-/) */
	symbol++;
	
	/* Move past spaces */
	while(line[symbol] == ' ') symbol++;
	
	/* If there is a sign, move past that */
	if (line[symbol] == '+' || line[symbol] == '-') symbol++;
	
	/* Move past digits */
	while (is_digit(line[symbol])) symbol++;
	
	/* Here we might have reached the end of the string, or there is
	something other than a decimal point after the numbers */
	if (line[symbol] != '.') return symbol;
	symbol++;
	
	/* If the next char was a decimal point, expect more digits */
	while (is_digit(line[symbol])) symbol++;
	
	/* And we're done */
	return symbol;
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

bool parens_match(char* string) {
	size_t i, length, extras;
	length = strlen(string);
	extras = 0;
        for (i = 0; i<length; i++) {
                if (string[i] == '(') extras++;
                else if (string[i] == ')') extras--;
        }
        return extras == 0;
}

// End of math functions
