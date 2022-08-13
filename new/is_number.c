#include "main.h"

bool is_number(Line line, char** position) {
	/* Variables */
	char* pos = *position;
	bool result;
	
	/* Skip spaces, if there are any */
	while(pos[0] == ' ') pos++;
	
	/* Move past the sign (- or +) at the beginning, if there is one */
	if (pos[0] == '+' || pos[0] == '-') pos++;
	
	/* Skip spaces again, if there are any */
	while(pos[0] == ' ') pos++;
	
	/* Now we need at least one digit */
	result = is_digit(pos[0]);
	
	/* Move the pointer past any additional digits */
	while (is_digit(pos[0])) pos++;
	
	/* And we're done */
	*position = pos;
	return result;
}
