#include "main.h"

void eval_expr(Line line) {
	/* Brainstorming/guesswork, probly not a solution lol */
	char* temp = line;
	char expr[LINE_SIZE];
	size_t i, diff;
	if (is_expr(line, &line)) {
		diff = line - temp;
		for (i=0; i<diff; i++) {
			expr[i] = line[i];
		}
		printf("Before:  %s\n", expr);
		add(expr);
		printf("After:  %s\n", expr);
	}
}
