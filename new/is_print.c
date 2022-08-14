#include "main.h"

bool is_print(Line line) {
	if (!STRING_STARTS_WITH(line, "PRINT")) return false;
	line += 5;
	while(line[0] == ' ') line++;
	return is_expr_list(line, &line);
}
