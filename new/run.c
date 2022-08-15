#include "main.h"

void run(Program program, VarList variables, Line line) {
	if (STRING_EQUALS(line, "CLEAR")) {
		printf("\033[H\033[J");
		return;
	}
	if (STRING_STARTS_WITH(line, "REM")) return;
	printf("Syntax error or not started yet :)\n");
}