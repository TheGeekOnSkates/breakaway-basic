#include "main.h"

bool is_input(Line line) {
	if (!STRING_STARTS_WITH(line, "INPUT")) return false;
	line += 5;
	while(line[0] == ' ') line++;
	return is_var(line, &line);
}
