#include "main.h"

void replace_with_float(char* line, size_t from, size_t to, float value) {
        size_t i;
	char temp[LINE_SIZE];
        memset(temp, 0, LINE_SIZE);
        for (i=0; i<from; i++) temp[i] = line[i];
        snprintf(temp + from, LINE_SIZE, "%g%s", value, line + to);
        strncpy(line, temp, LINE_SIZE);
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

// End of string functions
