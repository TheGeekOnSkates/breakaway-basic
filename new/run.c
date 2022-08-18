#include "main.h"

extern size_t programCounter;
extern bool keepRunning;

size_t subs[PROGRAM_SIZE];
size_t subCounter = 0;
bool thereWasAnError;

void run(Program program, VarList variables, Line line, bool running) {
	thereWasAnError = false;
	size_t temp;
	keepRunning = running;
	Line copy;
	
	if (STRING_EQUALS(line, "CLEAR")) {
		CLEAR_SCREEN();
		return;
	}
	if (STRING_EQUALS(line, "END")) {
		keepRunning = false;
		return;
	}
	if (STRING_EQUALS(line, "EXIT")) {
		CLEAR_SCREEN();
		exit(0);
	}
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
			programCounter = temp - 1;
			if (!running) run_program(program, variables);
		}
		return;
	}
	if (STRING_STARTS_WITH(line, "LET")) {
		line += 3;
		run_let(line, variables);
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
		strncpy(copy, line, LINE_SIZE);
		eval_expr(copy, variables);
		if (!thereWasAnError) run_print(program, copy);
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
