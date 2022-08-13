#include "main.h"

bool is_gosub(Line line) {
	if (!STRING_STARTS_WITH(line, "GOSUB")) return false;
	
	
	
	return true; /* for now */
}
