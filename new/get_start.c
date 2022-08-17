#include "main.h"

size_t get_start(char* line, size_t symbol) {
	symbol--;
	
	while(line[symbol] == ' ') symbol--;
	while (is_digit(line[symbol])) symbol--;
	if (line[symbol] != '.' && line[symbol] != '\0') return symbol;
	while (is_digit(line[symbol])) symbol--;
	if (line[symbol] == '+' || line[symbol] == '-') symbol--;
	return symbol;
}
