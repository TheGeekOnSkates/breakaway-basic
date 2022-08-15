#include "main.h"

void run_print(Program program, Line line) {
	/* Declare vars */
	size_t i, length;
	char copy[LINE_SIZE], * temp;
	
	/* Replaces the commas and quotation marks with spaces */
	length = strlen(line);
	strncpy(copy, line, LINE_SIZE);
	for (i=0; i<length; i++) {
		if (copy[i] == ',') {
			copy[i] = ' ';
			continue;
		}
		while (copy[i] == '"')
			shift_left(copy, i, length);
	}
	temp = copy;
	while(temp[0] == ' ') temp++;
	printf("%s\n", temp);
}
