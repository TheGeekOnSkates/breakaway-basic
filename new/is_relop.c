#include "main.h"

bool is_relop(Line line, char** position) {
	/* Declare variables */
	char* pos = *position;
	bool result;
	
	/* If it's a comparison operator, we hve our answer */
	switch(line[0]) {
		case '<':
			result = true;
			pos++;
			/* no break; "<>" is like "!=" in BASICs */
		case '>':
			result = true;
			pos++;
			break;
		case '=':
			result = true;
			pos++;
			break;
		default:
			result = false;
	}
	
	/* And we're done */
	*position = pos;
	return result;
}
