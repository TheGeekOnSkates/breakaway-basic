#include "main.h"

void run(Program program, VarList variables, Line line) {
	if (STRING_EQUALS(line, "CLEAR")) {
		printf("\033[H\033[J");
		return;
	}
	if (STRING_STARTS_WITH(line, "LIST")) {
		run_list(program, line + 4);
		return;
	}
	if (STRING_STARTS_WITH(line, "PRINT")) {
		line += 5;
		eval_expr(line);
		run_print(program, line);
		return;
	}
	if (STRING_STARTS_WITH(line, "REM")) return;
	printf("Syntax error or not started yet :)\n");
}
