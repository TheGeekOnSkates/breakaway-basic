#include "main.h"

void run(Program program, VarList variables, Line line, bool running) {
	size_t counter = 0;
	char* currentLine;
	
	if (STRING_EQUALS(line, "CLEAR")) {
		printf("\033[H\033[J");
		return;
	}
	if (STRING_STARTS_WITH(line, "LIST")) {
		run_list(program, line + 4);
		return;
	}
	if (STRING_EQUALS(line, "NEW")) {
		memset(program, 0, PROGRAM_SIZE * LINE_SIZE);
		memset(variables, 0, 26);
		return;
	}
	if (STRING_STARTS_WITH(line, "PRINT")) {
		line += 5;
		eval_expr(line);
		run_print(program, line);
		return;
	}
	if (STRING_STARTS_WITH(line, "REM")) return;
	if (STRING_EQUALS(line, "RUN")) {
		counter = 0;
		while(true) {
			currentLine = program[counter];
			if (currentLine[0] == '\0') {
				counter++;
				if (counter == PROGRAM_SIZE) return;
				continue;
			}
			if (!is_statement(currentLine)) {
				printf("?SYNTAX ERROR IN %ld\n", counter);
				return;
			}
			currentLine = program[counter];
			run(program, variables, currentLine, true);
			counter++;
			if (counter == PROGRAM_SIZE) return;
		}
	}
	printf("Syntax error or not started yet :)\n");
}
