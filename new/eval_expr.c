#include "main.h"

void eval_expr(Line line) {
	/* Declare vars */
	size_t length = strlen(line);
	
	multiply(line, length);
	divide(line, length);
	add(line, length);
	subtract(line, length);
}
