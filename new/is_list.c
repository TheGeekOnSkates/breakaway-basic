#include "main.h"

bool is_list(Line line) {
	if (!STRING_STARTS_WITH(line, "LIST")) return false;
	line += 4;
	while(line[0] == ' ') line++;
	if (!is_number(line, &line)) return false;
	while(line[0] == ' ') line++;
	if (line[0] == '-') {
		line++;
		while(line[0] == ' ') line++;
		if (!is_number(line, &line)) return false;
	}
	return line[0] == '\0';
}
