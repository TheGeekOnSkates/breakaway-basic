#include "main.h"

bool is_goto(Line line) {
	if (!STRING_STARTS_WITH(line, "GOTO")) return false;
	
	
	return true; /* for now */
}
