#include "main.h"

void run_print(Program program, Line line) {
	/* Declare vars */
	size_t i, length;
	char copy[LINE_SIZE], * temp;
	bool in_quotes = false;
	
	/* Replaces the commas and quotation marks with spaces */
	length = strlen(line);
	strncpy(copy, line, LINE_SIZE);
	for (i=0; i<length; i++) {
		while (copy[i] == '"') {
			in_quotes = !in_quotes;
			shift_left(copy, i, length);
		}
		if (copy[i] == ',' && !in_quotes ) {
			copy[i] = ' ';
			continue;
		}
	}
	temp = copy;
	while(temp[0] == ' ') temp++;
	printf("%s\n", temp);
}
