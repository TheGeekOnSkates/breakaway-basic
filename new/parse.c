#include "main.h"

void parse(Program program, VarList variables, Line line) {
	/* Declare variables */
	char* temp;
	
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
	}
	
	/* NOTE: Only is_statement should work once these other checks
	are done.  I have is_number/string/relop/etc. here for testing */
	else if (
		!is_statement(line)
		&& !is_number(line, &line)
		&& !is_string(line, &line)
		&& !is_relop(line, &line)
	) printf("?SYNTAX ERROR\n");
}
