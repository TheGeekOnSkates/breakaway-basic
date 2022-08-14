#include "main.h"

bool is_goto(Line line) {
	/* Variables */
	char* pos = line;
	
	/* If it doesn't start with GOTO, then no */
	if (!STRING_STARTS_WITH(line, "GOTO")) return false;
	pos += 4;
	
	/* Skip spaces if there are any */
	while(pos[0] == ' ') pos++;
	
	/* If the text after GOSUB is not an expression, then no */
	return is_expr(pos, &pos);
}
