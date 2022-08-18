#include "main.h"

void replace_vars_with_values(Line line, VarList variables) {
	/* Declare vars */
	size_t i, length;
	float value;
	int var;
	
	/* For version 0.1, this is pretty easy stuff.
	Each variable is just one character, so... */
	length = strlen(line);
	for (i=0; i<length; i++) {
		if (line[i] < 'A' || line[i] > 'Z') continue;
		var = (int)line[i];
		value = atof(variables[var - 'A'] + 2);
		replace_with_float(line, i, i + 1, value);
	}
}
