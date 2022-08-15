#include "main.h"

bool is_statement(Line line) {
	/* These don't have anything after them, so they're easy */
	if (
		STRING_EQUALS(line, "CLEAR")
		|| STRING_EQUALS(line, "END")
		|| STRING_EQUALS(line, "LIST")
		|| STRING_EQUALS(line, "NEW")
		|| STRING_EQUALS(line, "RETURN")
		|| STRING_EQUALS(line, "RUN")
	) return true;
	
	/* The others have specific requirements, so check for each of those */
	return is_gosub(line)
		|| is_goto(line)
		|| is_if(line)
		|| is_input(line)
		|| is_let(line)
		|| is_print(line);
}
