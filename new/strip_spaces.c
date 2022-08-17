#include "main.h"

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
