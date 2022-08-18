#include "main.h"

void eval_expr(Line line, VarList variables) {
	/* Declare vars */
	size_t length = strlen(line);
	
	replace_vars_with_values(line, variables);
	multiply(line, length);
	divide(line, length);
	add(line, length);
	subtract(line, length);
}
