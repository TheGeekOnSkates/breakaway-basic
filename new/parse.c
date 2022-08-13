#include "main.h"

void parse(Program program, Program variables, Line line) {
	/* Declare variables */
	char* temp;
	
	/* Move past any leading spaces */
	temp = line;
	while(temp[0] == ' ') temp++;
	
	/* If it's a line number, store it in memory */
	if (temp[0] >= '0' && temp[0] <= '9') {
		set_line(program, line);
	}
	else printf("LEFT OFF HERE\n");
}
