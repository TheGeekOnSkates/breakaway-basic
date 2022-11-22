#include "main.h"

void StringToUpperCase(char* source, char* destination, size_t length) {
	memset(destination, 0, INPUT_BUFFER_SIZE);
	size_t i;
	for (i = 0; i < length; i++)
		destination[i] = toupper(source[i]);
}
