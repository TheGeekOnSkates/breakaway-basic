#include "main.h"

int main() {
	/* Declare variables */
	Program code;
	VarList variables;
	Line buffer;
	
	/* Title */
	printf("BREAKAWAY BASIC 2022.08.13\n");
	
	/* Main event loop */
	while(true) {
		memset(buffer, 0, LINE_SIZE);
		printf("READY.\n");
		fgets(buffer, LINE_SIZE, stdin);
		parse(code, variables, buffer);
	}
	return 0;
}
