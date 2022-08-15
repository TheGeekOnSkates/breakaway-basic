#include "main.h"

bool is_if(Line line) {
	if (!STRING_STARTS_WITH(line, "IF")) return false;
	line += 2;
	while (line[0] == ' ') line++;
	if (!is_expr(line, &line)) return false;
	while (line[0] == ' ') line++;
	if (!is_relop(line, &line)) return false;
	while (line[0] == ' ') line++;
	if (!is_expr(line, &line)) return false;
	while (line[0] == ' ') line++;
	if (!STRING_STARTS_WITH(line, "THEN")) return false;
	line += 4;
	while (line[0] == ' ') line++;
	return is_number(line, &line) || is_statement(line);
}
