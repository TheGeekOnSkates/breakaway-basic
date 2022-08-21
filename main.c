#include "main.h"

int main() {
	/* Declare variables */
	char title[480];
	Program code;
	VarList variables;
	Line buffer;
	
	/* Clear all memory (no "garbage characters") */
	memset(code, 0, PROGRAM_SIZE * LINE_SIZE);
	memset(variables, 0, VARIABLE_SIZE * sizeof(Line));
	
	/* Title */
	CLEAR_SCREEN();
	print_centered("**** BREAKAWAY BASIC  0.2 ****\n");
	sprintf(title, "%lu BYTES FREE\n", GetBytesFree());
	print_centered(title);
	printf("READY.\n");
	
	/* Main event loop */
	while(true) {
		memset(buffer, 0, LINE_SIZE);
		fgets(buffer, LINE_SIZE, stdin);
		parse(code, variables, buffer);
	}
	return 0;
}
