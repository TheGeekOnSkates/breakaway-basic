#include "main.h"

int main() {
	/* Declare variables */
	char title[480], * temp;
	Program program, aliases;
	VarList variables;
	Line line;
	
	/* Clear all memory (no "garbage characters") */
	memset(program, 0, PROGRAM_SIZE * LINE_SIZE);
	memset(aliases, 0, PROGRAM_SIZE * LINE_SIZE);
	memset(variables, 0, VARIABLE_SIZE * sizeof(Line));
	
	/* Title */
	CLEAR_SCREEN();
	print_centered("**** BREAKAWAY BASIC  0.3 ****\n");
	sprintf(title, "%lu BYTES FREE\n", GetBytesFree());
	print_centered(title);
	printf("READY.\n");
	
	/* Main event loop */
	while(true) {
		/* Get the user's input */
		memset(line, 0, LINE_SIZE);
		ReadLine(line);
		
		/* Delete the trailing new-line character, if there is one */
		temp = strchr((const char*)line, '\n');
		if (temp != NULL) temp[0] = '\0';
		temp = NULL;

		/* Move past any leading spaces */
		temp = line;
		while(temp[0] == ' ') temp++;
		
		/* If it's a line number, store it in memory */
		if (temp[0] >= '0' && temp[0] <= '9') {
			set_line(program, line);
			continue;
		}
		
		/* Otherwise, run it */
		run(program, aliases, variables, line, false);
	}
	return 0;
}
