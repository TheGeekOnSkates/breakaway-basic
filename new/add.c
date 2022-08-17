#include "main.h"

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
