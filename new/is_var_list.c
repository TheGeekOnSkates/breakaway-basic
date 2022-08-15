#include "main.h"

bool is_var_list(Line line, char** position) {
	/* Variables */
	char* pos;
	bool result = is_var(line, position);
	
	/* From here, we can have a comma, followed by another varession
	(but trailing commas are not allowed).  Kind of like is_var :) */
	pos = *position;
	while(true) {
		/* Skip spaces */
		while(pos[0] == ' ') pos++;
		
		/* No comma?  We're done. */
		if (pos[0] != ',') break;
		pos++;
		
		/* Skip spaces */
		while(pos[0] == ' ') pos++;
		
		/* No var after the comma?  Syntax error. */
		if (!is_var(pos, &pos)) {
			*position = pos;
			return false;
		}
	}
	
	/* And we're done */
	*position = pos;
	return result;
}

