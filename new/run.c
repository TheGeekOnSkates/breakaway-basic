#include "main.h"

extern size_t programCounter;
extern bool keepRunning;

size_t subs[PROGRAM_SIZE];
size_t subCounter = 0;

void run(Program program, VarList variables, Line line, bool running) {
	size_t temp;
	keepRunning = running;
	
	/* When all that's left to do is the math,
	and replacing vars with their values etc. do that here */
	
	if (STRING_EQUALS(line, "CLEAR")) {
		printf("\033[H\033[J");
		return;
	}
	if (STRING_EQUALS(line, "END")) {
		keepRunning = false;
		return;
	}
	if (STRING_EQUALS(line, "EXIT")) exit(0);
	if (STRING_STARTS_WITH(line, "GOSUB")) {
		temp = atoi(line + 5);
		if (temp < 0 || temp > PROGRAM_SIZE) {
			printf("?SYNTAX ERROR");
			if (running) printf (" IN %ld", programCounter);
			printf("\n");
			keepRunning = false;
		}
		else if (subCounter + 1 == PROGRAM_SIZE) {
			/* Should never happen, but if so, handle it gracefully  :D */
			printf("?TOO MANY SUBS ERROR");
			if (running) printf (" IN %ld", programCounter);
			printf("\n");
		}
		else {
			subs[subCounter] = programCounter;
			subCounter++;
			programCounter = temp - 1;
			keepRunning = true;
			if (!running) run_program(program, variables);
		}
		return;
	}
	if (STRING_STARTS_WITH(line, "GOTO")) {
		temp = atoi(line + 4);
		if (temp < 0 || temp > PROGRAM_SIZE) {
			printf("?SYNTAX ERROR");
			if (running) printf (" IN %ld", programCounter);
			printf("\n");
			keepRunning = false;
		}
		else {
			programCounter = temp;
			if (!running) run_program(program, variables);
		}
		return;
	}
	if (STRING_STARTS_WITH(line, "LIST")) {
		run_list(program, line + 4);
		return;
	}
	if (STRING_EQUALS(line, "NEW")) {
		memset(program, 0, PROGRAM_SIZE * LINE_SIZE);
		memset(variables, 0, 26);
		return;
	}
	if (STRING_STARTS_WITH(line, "PRINT")) {
		line += 5;
		run_print(program, line);
		return;
	}
	if (STRING_STARTS_WITH(line, "REM")) return;
	if (STRING_EQUALS(line, "RUN")) {
		programCounter = 0;
		keepRunning = true;
		run_program(program, variables);
		return;
	}
	if (STRING_STARTS_WITH(line, "RETURN")) {
		subCounter--;
		if (subCounter < 0 || subCounter >= PROGRAM_SIZE) {
			printf("?RETURN WITHOUT GOSUB ERROR");
			if (running) printf (" IN %ld", programCounter);
			printf("\n");
			return;
		}
		programCounter = subs[subCounter];
		keepRunning = true;
		if (!running) run_program(program, variables);
		return;
	}
	printf("Syntax error or not started yet :)\n");
}
