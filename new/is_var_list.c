#include "main.h"

bool is_var_list(Line line, char** position) {
	/* Variables */
	char* pos;
	bool result = is_string(line, position) || is_var(line, position);
	
	/* From here, we can have a comma, followed by another varession
	(but trailing commas are not allowed).  Kind of like is_var :) */
	while(true) {
		/* Skip spaces */
		while(pos[0] == ' ') pos++;
		
		/* No comma?  We're done. */
		if (pos[0] != ',') break;
		pos++;
		
		/* No varession after the comma?  Syntax error. */
		if (!is_string(pos, &pos) && !is_var(pos, &pos)) {
			*position = pos;
			return false;
		}
	}
	
	/* And we're done */
	*position = pos;
	return result;
}

