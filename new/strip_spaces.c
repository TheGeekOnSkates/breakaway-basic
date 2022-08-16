#include "main.h"

void strip_spaces(char* string) {
	size_t i = 0, length = strlen(string);
	for (; i<length; i++)
		if (string[i] == ' ')
			shift_left(string, i, length);
}
