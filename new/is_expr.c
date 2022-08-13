#include "main.h"

bool char_works_in_expr(char ch) {
	if (ch >= '0' && ch <= '9') return true;
	if (ch >= 'A' && ch <= 'Z') return true;
	return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

bool is_expr(Line line, char** position) {
	char* pos = *position;
	size_t i, length = strlen(line);
	bool result = char_works_in_expr(line[0]);
	for (i=0; i<length; i++) {
		if (!char_works_in_expr(line[i])) break;
		pos++;
	}
	*position = pos;
	return result;
}
