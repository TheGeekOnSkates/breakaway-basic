#include "main.h"

size_t get_start(char* line, size_t symbol) {
	symbol--;
	
	while(line[symbol] == ' ') symbol--;
	if (symbol <= 0) return 0;
	while (is_digit(line[symbol])) symbol--;
	if (symbol <= 0) return 0;
	if (line[symbol] != '.' && line[symbol] != '\0') return symbol;
	if (symbol <= 0) return 0;
	while (is_digit(line[symbol])) symbol--;
	if (symbol <= 0) return 0;
	if (line[symbol] == '+' || line[symbol] == '-') symbol--;
	if (symbol <= 0) return 0;
	return symbol;
}
