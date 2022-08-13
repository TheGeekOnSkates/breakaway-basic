#include "main.h"

int main() {
	/* Declare variables */
	Program code, variables;
	Line buffer;
	
	/* Main event loop */
	while(true) {
		memset(buffer, 0, LINE_SIZE);
		fgets(buffer, LINE_SIZE, stdin);
		parse(&code, &variables, buffer);
	}
	return 0;
}
