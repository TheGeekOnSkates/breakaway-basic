#include "main.h"

bool RunLine(unsigned char * tokens) {
	size_t i;
	for (i=0; i<INPUT_BUFFER_SIZE; i++) {
		if (tokens[i] == EXIT) return false;
	}
	return true;
}
