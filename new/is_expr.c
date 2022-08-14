#include "main.h"

bool is_math_action(char ch) {
	return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

bool is_expr(Line line, char** position) {
	/* Variables */
	char* pos;
	bool result = is_number(line, position) || is_var(line, position);
	
	/* Skip spaces again */
	pos = *position;
	while(pos[0] == ' ') pos++;
	
	/* From here, we already know if it starts with an expression or not.
	But let's move the pointer to the end of the expression, because some
	functions (IF, PRINT etc.) involve more than one on the same line */
	while(true) {
		/* Skip spaces again */
		while(pos[0] == ' ') pos++;
		
		if (!is_math_action(pos[0])) break;
		pos++;
		
		/* Here we get into a kinda weird scenario:
		What if I enter 3 + 4 * (nothing at the end?)
		We can't have that, so... */
		if (!is_number(pos, &pos)) {
			*position = pos;
			return false;
		}
	}
	*position = pos;
	return result;
}
