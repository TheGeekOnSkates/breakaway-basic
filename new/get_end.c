#include "main.h"

size_t get_end(char* line, size_t symbol) {
	symbol++;
	
	/* The validation step (is_expr function) should have already made
	sure we're dealing with an "expression", so no need to do that here */
	while(
		line[symbol] == ' '
		|| line[symbol] == '-'
		|| line[symbol] == '+'
		|| line[symbol] == '\0'
	) symbol++;
	while (is_digit(line[symbol]) && line[symbol] != '\0') symbol++;
	if (line[symbol] != '.' && line[symbol] != '\0') return symbol;
	while (is_digit(line[symbol]) && line[symbol] != '\0') symbol++;
	return symbol;
}
