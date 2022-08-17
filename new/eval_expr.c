#include "main.h"

void eval_expr(Line line) {
	size_t i, start, end, length;
	bool in_quotes = false;
	float left, right, answer;
	
	length = strlen(line);
	for (i=0; i<length; i++) {
		if (line[i] == '"')
			in_quotes = !in_quotes;
		if (in_quotes) continue;
		if (line[i] == '*') {
			start = get_start(line, i);
			end = get_end(line, i);
			left = atof(line + start);
			right = atof(line + i + 1);
			answer = left * right;
			replace_with_float(line, start, end, answer);
		}
	}
}
