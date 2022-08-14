#include "main.h"

bool is_string(Line line, char** position) {
	/* Declare variables */
	char* pos;
	bool result;
	
	/* If it doesn't start with a quotation mark, then no */
	if (line[0] != '"') return false;
	
	/* IF there's a closing quote to match the opening quote, then yes */
	pos = strchr((const char*)line + 1, '"');
	result = pos != NULL;
	if (result) *position = pos;
	return result;
}
