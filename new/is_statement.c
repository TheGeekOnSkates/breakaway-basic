#include "main.h"

bool is_statement(Line line) {
	/* These don't have anything after them, so they're easy */
	if (
		STRING_EQUALS(line, "CLEAR")
		|| STRING_EQUALS(line, "END")
		|| STRING_EQUALS(line, "LIST")
		|| STRING_EQUALS(line, "RETURN")
		|| STRING_EQUALS(line, "RUN")
	) return true;
	
	/* I don't think this is actually the way to go;
	have it check for each of these, one at a time,
	cuz they all have very different requirements. */
	if (
		!STRING_STARTS_WITH(line, "GOSUB")
		&& !STRING_STARTS_WITH(line, "GOTO")
		&& !STRING_STARTS_WITH(line, "IF")
		&& !STRING_STARTS_WITH(line, "INPUT")
		&& !STRING_STARTS_WITH(line, "LET")
		&& !STRING_STARTS_WITH(line, "PRINT")
	) return false;
	
	
	
	
	return true;
}
