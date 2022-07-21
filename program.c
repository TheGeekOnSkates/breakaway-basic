#include "main.h"

uint8_t lastError;

/************************************************************************/

char** CreateProgram(void) {
	/* Declare variables */
	char** result;
	uint32_t i;
	
	/* Allocate memory for the array */
	result = malloc(PROGRAM_MAX * sizeof(char*));
	if (result == NULL) return NULL;
	
	/* Set all PROGRAM_MAX pointers to NULL, and we're done */
	for (i=0; i<PROGRAM_MAX; i++)
		result[i] = NULL;
	return result;
}

/************************************************************************/

void FreeProgram(char** program) {
	size_t i;
	if (program == NULL) return;
	for (i=0; i<PROGRAM_MAX; i++) {
		if (program[i] == NULL) continue;
		free(program[i]);
	}
	free(program);
}

/************************************************************************/

bool AddToProgram(char** program, char* line) {
	/* Declare variables */
	uint32_t lineNumber;
	char* temp, * newline;
	
	/* Get the line number and make sure it's valid */
	lineNumber = atol(line);
	if (lineNumber < 0 || lineNumber > PROGRAM_MAX) {
		lastError = SYNTAX_ERROR;
		return false;
	}
	
	/* Move the pointer past the digits */
	while(line[0] != 0 && (line[0] >= '0' && line[0] <= '9'))
		line++;
	
	/* Then move it past any spaces after the line number */
	while(line[0] != 0 && line[0] == ' ')
		line++;
	
	/* Allocate / re-allocate program[lineNumber] */
	if (program[lineNumber] == NULL) {
		temp = realloc(program[lineNumber], BUFFER_MAX);
		if (temp == NULL) {
			lastError = MEMORY_ERROR;
			return false;
		}
		program[lineNumber] = temp;
	}
	else {
		program[lineNumber] = calloc(BUFFER_MAX, sizeof(char));
		if (program[lineNumber] == NULL) {
			lastError = MEMORY_ERROR;
			return false;
		}
	}
	
	/* If there is a newline character at the end (which can happen
	in LoadFile but not from user input/readliine), get rid of it. */
	newline = strstr(line, "\r");
	if (newline != NULL) newline[0] = '\0';
	newline = strstr(line, "\n");
	if (newline != NULL) newline[0] = '\0';
	
	/* Copy the line into the program and we're done */
	strncpy(program[lineNumber], line, BUFFER_MAX);
	#if DEBUG_MODE
	printf("line %d is \"%s\"\n", lineNumber, program[lineNumber]);
	#endif
	return true;
}

/************************************************************************/

void ListProgram(char** program, char* instruction) {
	/* Variables */
	uint32_t i, start, end;
	char* temp;
	bool pastDash;
	
	/* Move the pointer past any spaces between the word
	"LIST" and a possible line number */
	while (instruction[0] != 0 && instruction[0] == ' ')
		instruction++;
	
	/* Run a syntax-check */
	pastDash = false;
	for (i=0; i<BUFFER_MAX; i++) {
		if (instruction[i] == '\n' || instruction[i] == '\0') break;
		if (instruction[i] == ' ')
			continue;
		if (instruction[i] == '-') {
			if (pastDash) {
				lastError = SYNTAX_ERROR;
				return;
			}
			pastDash = true;
			continue;
		}
		if (instruction[i] < '0' || instruction[i] > '9') {
			lastError = SYNTAX_ERROR;
			return;
		}
	}
	
	/* If there is none, we want to list all lines */
	if (instruction[0] == '\n' || instruction[0] == 0) {
		start = 0;
		end = PROGRAM_MAX;
	}
	else {
		start = atoi(instruction);
		temp = strchr(instruction, '-');
		if (temp != NULL)
			end = atoi(temp + 1);
		else end = start;
	}
	for (i=start; i<=end; i++) {
		if (IsLineEmpty(program, i)) continue;
		printf(" %d %s", i, program[i]);
		NewLine();
	}
	NewLine();
}

/************************************************************************/

void RenumberProgram(char** program, char* instruction) {
	/* Variables */
	char* temp;
	size_t i, step, counter;
	char* newProgram[PROGRAM_MAX];
	
	/* Move the pointer past any spaces between the word
	"RENUMBER" and the next part */
	while (instruction[0] == ' ')
		instruction++;
	
	/* Run a syntax-check */
	if (instruction[0] == '\n' || instruction[0] == 0) {
		lastError = SYNTAX_ERROR;
		return;
	}
	for (i=0; i<BUFFER_MAX; i++) {
		if (instruction[i] == '\n' || instruction[i] == 0) break;
		if (instruction[i] < '0' || instruction[i] > '9') {
			lastError = SYNTAX_ERROR;
			return;
		}
	}
	
	/* Get the steps the user wants to */
	step = atoi(instruction);
	#if DEBUG_MODE
	printf("instruction = '%s', step = %ld\n", instruction, step);
	#endif
	if (step < 1 || step > PROGRAM_MAX) {
		lastError = SYNTAX_ERROR;
		return;
	}
	
	/* Clear the contents of newProgram */
	memset(newProgram, 0, PROGRAM_MAX);
	
	/* Do the renumbering */
	counter = 0;
	for (i=0; i<PROGRAM_MAX; i++) {
		if (program[i] == NULL) continue;
		counter++;
		if (step * counter > PROGRAM_MAX) {
			lastError = MEMORY_ERROR;
			return;
		}
		newProgram[step * counter] = program[i];
		program[i] = NULL;
	}
	
	/* Copy the pointers in newProgram to the current program */
	memcpy(program, newProgram, PROGRAM_MAX);
}
