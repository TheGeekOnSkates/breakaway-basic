#include "main.h"

int main() {
	/* Declare variables */
	Program code;
	VarList variables;
	Line buffer;
	
	/* Clear all memory (no "garbage characters") */
	memset(code, 0, PROGRAM_SIZE * LINE_SIZE);
	memset(variables, 0, VARIABLE_SIZE * sizeof(Line));
	
	/* Title */
	CLEAR_SCREEN();
	printf("BREAKAWAY BASIC 0.1\n");
	printf("READY.\n");
	
	/* Main event loop */
	while(true) {
		memset(buffer, 0, LINE_SIZE);
		fgets(buffer, LINE_SIZE, stdin);
		parse(code, variables, buffer);
	}
	return 0;
}
