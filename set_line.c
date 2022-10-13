#include "main.h"

void set_line(Program program, Line line) {
	/* Declare variables */
	char* temp;
	unsigned int lineNumber;
	
	/* Move past the line number and any spaces after that */
	temp = line;
	while(temp[0] >= '0' && temp[0] <= '9') temp++;
	while(temp[0] == ' ') temp++;
	
	/* Get the line number */
	lineNumber = atoi(line);
	if (lineNumber >= PROGRAM_SIZE) {
		show_error("SYNTAX ERROR");
		return;
	}
	
	/* Copy the string into the program */
	memset(program[lineNumber], 0, LINE_SIZE);
	strncpy(program[lineNumber], temp, LINE_SIZE);
}
