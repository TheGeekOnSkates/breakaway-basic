#include "main.h"

void replace_vars_with_values(Line line, VarList variables) {
	/* Declare vars */
	size_t i = 0, length = strlen(line);
	float value = 0;
	int var = 0;
	bool in_quotes = false;
	
	/* For version 0.1, this is pretty easy stuff.
	Each variable is just one character, so... */
	for (i=0; i<length; i++) {
		if (line[i] == '"')
			in_quotes = !in_quotes;
		if (in_quotes) continue;
		if (line[i] < 'A' || line[i] > 'Z') continue;
		var = (int)line[i];
		value = atof(variables[var - 'A'] + 2);
		replace_with_float(line, i, i + 1, value);
		length = strlen(line);
		i = 0;
	}
}
