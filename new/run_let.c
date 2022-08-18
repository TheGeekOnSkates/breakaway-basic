#include "main.h"

extern size_t programCounter;
extern bool keepRunning;

void run_let(char* line, VarList variables) {
	char* temp;
	int i;
	strip_spaces(line);
	temp = strchr(line, '=');
	if (temp == NULL) {
		printf("?SYNTAX ERROR");
		if (keepRunning) printf (" IN %ld", programCounter);
		printf("\n");
		keepRunning = false;
		return;
	}
	temp++;
	eval_expr(temp, variables);
	i = line[0] - 'A';
	strncpy(variables[i], line, LINE_SIZE);
}
