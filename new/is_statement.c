#include "main.h"

bool is_statement(Line line) {
	if (
		!STRING_STARTS_WITH(line, "CLEAR")
		&& !STRING_STARTS_WITH(line, "END")
		&& !STRING_STARTS_WITH(line, "GOSUB")
		&& !STRING_STARTS_WITH(line, "GOTO")
		&& !STRING_STARTS_WITH(line, "IF")
		&& !STRING_STARTS_WITH(line, "INPUT")
		&& !STRING_STARTS_WITH(line, "LET")
		&& !STRING_STARTS_WITH(line, "LIST")
		&& !STRING_STARTS_WITH(line, "PRINT")
		&& !STRING_STARTS_WITH(line, "RETURN")
		&& !STRING_STARTS_WITH(line, "RUN")
	) return false;
	
	return true;
}
