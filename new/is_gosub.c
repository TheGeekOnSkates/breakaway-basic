#include "main.h"

bool is_gosub(Line line) {
	/* Variables */
	char* pos = line;
	
	/* If it doesn't start with GOSUB, then no */
	if (!STRING_STARTS_WITH(line, "GOSUB")) return false;
	pos += 5;
	
	/* Skip spaces if there are any */
	while(pos[0] == ' ') pos++;
	
	/* If the text after GOSUB is not an expression, then no */
	return is_expr(pos, &pos);
}
