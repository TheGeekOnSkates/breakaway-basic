#include "main.h"

void replace_with_float(char* line, size_t from, size_t to, float value) {
	char temp[15];
	Line copy;
	size_t i, length;
	
	memset(temp, 0, 15);
	memset(copy, 0, LINE_SIZE);
	
	snprintf(temp, 15, "%g", value);
	length = strlen(temp);
	
	for (i=0; i<from; i++)
		copy[i] = line[i];	
	for (i=from; i<from + length; i++)
		copy[i] = temp[i - from];
	strncat(copy, line + to, LINE_SIZE - 1);
	strncpy(line, copy, LINE_SIZE);
}

void replace_with_string(char* line, size_t start, size_t end, char* replacement) {
	char temp[LINE_SIZE];
	size_t i;
	
	for (i=0; i<start; i++) temp[i] = line[i];
	snprintf(temp + start, LINE_SIZE - start, "%s%s", replacement, line + end);
	strncpy(line, temp, LINE_SIZE);
}

void shift_left(char* string, size_t start, size_t length) {
        size_t i;
        for (i = start + 1; i < length; i++) {
                string[i - 1] = string[i];
                string[i] = ' ';
        }
}

void strip_spaces(char* string) {
	size_t i = 0, length = strlen(string);
	bool in_quotes = false;
	for (; i<length; i++) {
		if (string[i] == '"')
			in_quotes = !in_quotes;
		if (in_quotes) continue;
		if (string[i] == ' ')
			shift_left(string, i, length);
	}
}


void print_centered(const char* string) {
	int rows = 48, columns = 25;
	size_t i = 0, length = 40;
	
	GetScreenSize(&rows, &columns);
	length = (columns / 2) - strlen(string) / 2;
	for (i=0; i<length; i++) printf(" ");
	printf("%s", string);
}

// End of string functions
