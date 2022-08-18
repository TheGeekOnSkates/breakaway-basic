#include "main.h"

void eval_expr(Line line, VarList variables) {
	/* Declare vars */
	size_t length = strlen(line);
	
	/* And for now, these are all the steps involved. */
	replace_vars_with_values(line, variables);
	multiply(line, length);
	divide(line, length);
	add(line, length);
	subtract(line, length);
}
