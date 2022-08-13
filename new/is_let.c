#include "main.h"

bool is_let(Line line) {
	char* temp;
	
	/* If it doesn't start with LET, then no. */
	if (!STRING_STARTS_WITH(line, "LET")) return false;
	
	/* Skip spaces */
	temp = line + 3;
	while (temp[0] == ' ') temp++;
	
	/* If what follows is not a variable, then no. */
	if (!is_var(temp, &temp)) return false;
	
	/* Skip spaces again */
	while (temp[0] == ' ') temp++;
	
	/* If the next char is not an euqals sign, then no */
	if (temp[0] != '=') return false;
	
	/* Skip spaces again */
	while (temp[0] == ' ') temp++;
	
	/* LEFT OFF HERE - add is_expression :) */
	
	
	/* If it gets here, then yeah! */
	return true;
}
