#include "main.h"

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
