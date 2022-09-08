#include "main.h"

char* substring(char* a, const char* b) {
	/* Declare variables */
	size_t i = 0, length = strlen(a);
	char* c = NULL, * result = NULL;

	/* Create a temporary string where we will backup "a" */
	c = calloc(length + 1, sizeof(char));
	if (c == NULL) {
		show_error("MEMORY ERROR");
		return result;
	}

	/* Copy a into c, and make a all-caps */
	for (; i<length; i++) {
		c[i] = a[i];
		a[i] = toupper(a[i]);
	}

	/* Figure out where the result pointer should be */
	result = strstr(a, b);

	/* copy c back into a, free c and we're done */
	strncpy(a, c, length);
	free(c);
	return result;
}

bool STRING_EQUALS(char* a, const char* b) {
	bool result = false;
	size_t i = 0, length = strlen(a);
	char* c = NULL;

	c = calloc(length + 1, sizeof(char));
	if (c == NULL) {
		show_error("MEMORY ERROR");
		return result;
	}
	for (; i<length; i++)
		c[i] = toupper(a[i]);
	result = strcmp(c, b) == 0;
	free(c);
	return result;
}

bool STRING_STARTS_WITH(char* a, const char* b) {
	bool result = false;
	size_t i = 0, length = strlen(a);
	char* c = NULL;

	c = calloc(length + 1, sizeof(char));
	if (c == NULL) {
		show_error("MEMORY ERROR");
		return result;
	}
	for (; i<length; i++)
		c[i] = toupper(a[i]);
	result = strstr(c, b) == c;
	free(c);
	return result;
}

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
	Line copy;
	size_t i;

	/* We start with a blank line.  Into this copy,
	add the text to the left of the replacement */
	memset(copy, 0, LINE_SIZE);
	for (i=0; i<start; i++)
		copy[i] = line[i];	

	/* Copy the replacement into the string */
	strncat(copy, replacement, LINE_SIZE - 1);

	/* Copy the text after the replacement */
	strncat(copy, line + end, LINE_SIZE - 1);

	/* And update the "line" with the new string */
	strncpy(line, copy, LINE_SIZE);
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

void combine_strings(char* line) {
	size_t start, end, i, j, length;
	length = strlen(line);
	for (i = 0; i<length; i++) {
		if (line[i] != '"') continue;
		start = i;
		i++;
		while(line[i] == ' ') i++;
		if (line[i] != '+') continue;
		i++;
		while(line[i] == ' ') i++;
		if (line[i] != '"') continue;
		i++;
		end = i - start;
		for (j = 0; j < end; j++) {
			shift_left(line, start, LINE_SIZE);
		}
		length = strlen(line);
		i = -1;
	}
}

void print_centered(const char* string) {
	int rows = 48, columns = 25;
	size_t i = 0, length = 40;
	
	GetScreenSize(&rows, &columns);
	length = (columns / 2) - strlen(string) / 2;
	for (i=0; i<length; i++) printf(" ");
	printf("%s", string);
	if (length + strlen(string) + length > columns) length--;
	for (i=0; i<length; i++) printf(" ");
}

// End of string functions
