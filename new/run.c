#include "main.h"

size_t programCounter;
bool keepRunning = true;
size_t subs[PROGRAM_SIZE];
size_t subCounter = 0;
bool thereWasAnError;

void run(Program program, VarList variables, Line line, bool running) {
	/* Declare vars */
	thereWasAnError = false;
	size_t temp;
	keepRunning = running;
	Line copy;
	
	/* And figure out what to do from there */
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
	if (STRING_STARTS_WITH(line, "IF")) {
		run_if(program, line, variables, running);
		return;
	}
	if (STRING_STARTS_WITH(line, "INPUT")) {
		run_input(line + 5, variables);
		return;
	}
	if (STRING_STARTS_WITH(line, "LET")) {
		line += 3;
		strncpy(copy, line, LINE_SIZE);
		run_let(copy, variables);
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
	
	/* If it gets here, the user goofed */
	printf("?SYNTAX ERROR");
	if (!running) return;
	printf(" IN %ld\n", programCounter);
}

void run_input(char* line, VarList variables) {
	/* Declare vars */
	Line buffer, buffer2;
	char* temp;
	
	/* Get and validate user input (again, for version 0.1, this is
	super easy cuz only expressions are allowed */
	memset(buffer, 0, LINE_SIZE);
	printf("? ");
	fgets(buffer, LINE_SIZE, stdin);
	temp = buffer;
	if (!is_expr(temp, &temp)) {
		printf("?INVALID INPUT ERROR\n");
		return;
	}
	eval_expr(buffer, variables);
	while(line[0] == ' ') line++;
	memset(buffer2, 0, LINE_SIZE);
	snprintf(buffer2, LINE_SIZE, "%c=%g", line[0], atof(buffer));
	run_let(buffer2, variables);
}

void run_if(Program program, char* line, VarList variables, bool running) {
	/* Declare vars */
	size_t i, counter;
	bool past_relop;
	Line left, right;
	float f1, f2;
	bool answer;
	char* then;
	
	/* Get the expressions on the left and right hand sizes */
	counter = 0;
	past_relop = false;
	memset(left, 0, LINE_SIZE);
	memset(right, 0, LINE_SIZE);
	for (i=2; i<LINE_SIZE; i++) {
		if (line[i] == '=' || line[i] == '<' || line[i] == '>') {
			counter = 0;
			past_relop = true;
			if (line[i] == '<' || line[i + 1] == '>') i++;
			continue;
		}
		if (past_relop) {
			if (STRING_STARTS_WITH(line + i, "THEN")) break;
			right[counter] = line[i];
			counter++;
			continue;
		}
		left[counter] = line[i];
		counter++;
	}
	
	/* Evaluate the left and right hand side of the equation */
	eval_expr(left, variables);
	eval_expr(right, variables);
	f1 = atof(left);
	f2 = atof(right);
	
	/* Figure out the answer */
	if (strstr(line, "<>") != NULL)
		answer = f1 != f2;
	else if (strstr(line, "<") != NULL)
		answer = f1 < f2;
	else if (strstr(line, ">") != NULL)
		answer = f1 > f2;
	else answer = (int)f1 == (int)f2;
	
	/* And IF it returns true, RUN the next bit */
	if (!answer) return;
	then = strstr(line, "THEN");
	then += 4;
	while(then[0] == ' ') then++;
	if (is_digit(then[0]))
		programCounter = atol(then) - 1;
	else run(program, variables, then, running);
}

void run_let(char* line, VarList variables) {
	char* temp;
	int i;
	strip_spaces(line);
	temp = strchr(line, '=');
	if (temp == NULL) {
		printf("?SYNTAX ERROR");
		if (keepRunning) printf (" IN %ld", programCounter);
		printf("\n");
		keepRunning = false;
		return;
	}
	temp++;
	eval_expr(temp, variables);
	i = line[0] - 'A';
	strncpy(variables[i], line, LINE_SIZE);
}

void run_list(Program program, Line line) {
	/* Declare vars */
	char* temp;
	size_t i, from = 0, to = PROGRAM_SIZE;
	
	/* If there's a number after LIST, get it */
	temp = line;
	if (is_number(temp, &temp)) {
		from = atoi(line);
	
		/* If there's also a dash followed by another number, get that */
		temp = strchr(line, '-');
		if (temp != NULL) {
			temp++;
			to = atoi(temp);
		}
		else to = from;
	}
	
	/* Validate the numbers */
	if (from < 0 || from > PROGRAM_SIZE || to < 0 || to > PROGRAM_SIZE) {
		printf("?SYNTAX ERROR\n");
		return;
	}
	
	/* Validation passes, so LIST away! */
	if (from == to) {
		temp = program[to];
		while(temp[0] == ' ') temp++;
		if (temp[0] == '\0') return;
		printf(" %ld %s\n", to, temp);
		return;
	}
	for (i=from; i<=to; i++) {
		temp = program[i];
		while(temp[0] == ' ') temp++;
		if (temp[0] == '\0') continue;
		printf(" %ld %s\n", i, temp);
	}
}

void run_print(Program program, Line line) {
	/* Declare vars */
	size_t i, length;
	char copy[LINE_SIZE], * temp;
	bool in_quotes = false, newline = true;
	
	/* Replaces the commas and quotation marks with spaces */
	length = strlen(line);
	strncpy(copy, line, LINE_SIZE);
	for (i=0; i<length; i++) {
		while (copy[i] == '"') {
			in_quotes = !in_quotes;
			shift_left(copy, i, length);
		}
		if (copy[i] == ',' && !in_quotes ) {
			copy[i] = ' ';
			continue;
		}
	}
	
	/* Figure out if it should print a new line at the end */
	i = length - 1;
	while(copy[i] == '\0' || copy[i] == ' ') i--;
	newline = copy[i] != ';';
	if (!newline) copy[i] = '\0';
	
	/* And print away! */
	temp = copy;
	while(temp[0] == ' ') temp++;
	printf("%s", temp);
	if (newline) printf("\n");
}

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

// End of code-running functions
