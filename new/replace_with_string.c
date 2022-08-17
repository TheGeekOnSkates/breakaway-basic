#include "main.h"

void replace_with_string(char* line, size_t start, size_t end, char* replacement) {
	char temp[LINE_SIZE];
	size_t i;
	
	for (i=0; i<start; i++) temp[i] = line[i];
	snprintf(temp + start, LINE_SIZE - start, "%s%s", replacement, line + end);
	strncpy(line, temp, LINE_SIZE);
}

