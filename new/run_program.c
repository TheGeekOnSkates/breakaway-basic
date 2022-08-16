#include "main.h"

size_t programCounter;
bool keepRunning = true;

void run_program(Program program, VarList variables) {
	char* currentLine;
	
	while(true) {
		if (!keepRunning) {
			printf("READY.\n");
			return;
		}
		if (programCounter == PROGRAM_SIZE) return;
		currentLine = program[programCounter];
		if (currentLine[0] == '\0') {
			programCounter++;
			if (programCounter == PROGRAM_SIZE) return;
			continue;
		}
		if (!is_statement(currentLine)) {
			printf("?SYNTAX ERROR IN %ld\n", programCounter);
			printf("READY.\n");
			return;
		}
		currentLine = program[programCounter];
		run(program, variables, currentLine, true);
		programCounter++;
		if (programCounter == PROGRAM_SIZE) {
			printf("READY.\n");
			return;
		}
	}
}
