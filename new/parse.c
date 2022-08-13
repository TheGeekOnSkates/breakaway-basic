#include "main.h"

void parse(Program program, VarList variables, Line line) {
	/* Declare variables */
	char* temp;
	
	/* Delete the trailing new-line character, if there is one */
	temp = strstr(line, "\n");
	if (temp != NULL) temp[0] = '\0';
	temp = NULL;
	
	/* Move past any leading spaces */
	temp = line;
	while(temp[0] == ' ') temp++;
	
	/* If it's a line number, store it in memory */
	if (temp[0] >= '0' && temp[0] <= '9') {
		set_line(program, line);
	}
	else if (is_statement(line))
		printf("statement\n");
	else printf("LEFT OFF HERE\n");
}
