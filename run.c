#include "main.h"

size_t programCounter;
bool keepRunning = true;
size_t subs[PROGRAM_SIZE];
size_t subCounter = 0;
bool thereWasAnError;
int rc = 0;
Line prompt;

void show_error(const char* error) {
	printf("?%s", error);
	if (keepRunning) printf (" IN %ld", programCounter);
	printf("\n");
	keepRunning = false;
	SetBlocking(true);
}

void run(Program program, Program aliases, VarList variables, Line line, bool running) {
	/* Declare vars */
	thereWasAnError = false;
	size_t temp;
	keepRunning = running;
	Line copy;
	char* tempChar, *tempChar2;

	/* If it's an empty string, ignore it */
	if (STRING_EQUALS(line, "")) return;
	
	/* Delete the trailing new-line character, if there is one */
	tempChar = strchr((const char*)line, '\n');
	if (tempChar != NULL) tempChar[0] = '\0';
	tempChar = NULL;

	/* Move past any leading spaces */
	tempChar = line;
	while(tempChar[0] == ' ') temp++;
	
	/* If it's a line number, store it in memory */
	if (tempChar[0] >= '0' && tempChar[0] <= '9') {
		set_line(program, line);
		return;
	}
	
	/* If it's an ALIAS statement, set the alias */
	if (is_alias(line)) {
		set_alias(line, aliases);
		return;
	}

	/* Otherwise, check for aliases */
	run_alias(line, aliases);

	/* And figure out what to do from there */
	if (is_bg(line)) {
		line += 2;
		strncpy(copy, line, LINE_SIZE);
		eval_expr(copy, variables);
		temp = atoi(copy);
		if (temp > PROGRAM_SIZE)
			show_error("SYNTAX ERROR");
		else printf("\033[4%ldm", temp);
		return;
	}
	if (is_blink(line)) {
		if (STRING_CONTAINS(line, "ON"))
			printf("\033[5m");
		else if (STRING_CONTAINS(line, "OFF"))
			printf("\033[25m");
		else show_error("SYNTAX ERROR");
		return;
	}
	if (is_bold(line)) {
		if (STRING_CONTAINS(line, "ON"))
			printf("\033[1m");
		else if (STRING_CONTAINS(line, "OFF"))
			printf("\033[22m");
		else show_error("SYNTAX ERROR");
		return;
	}
	if (is_center(line)) {
		line += 6;
		strncpy(copy, line, LINE_SIZE);
		eval_expr(copy, variables);
		if (!thereWasAnError) run_print(program, copy, true);
		return;
	}
	if (STRING_EQUALS(line, "CLEAR")) {
		CLEAR_SCREEN();
		return;
	}
	if (STRING_EQUALS(line, "CLEAR HISTORY")) {
		clear_history();
		return;
	}
	if (STRING_EQUALS(line, "CONT")) {
		keepRunning = true;
		run_program(program, aliases, variables);
		return;
	}
	if (is_cursor(line)) {
		if (STRING_CONTAINS(line, "ON"))
			printf("\033[?25h");
		else if (STRING_CONTAINS(line, "OFF"))
			printf("\033[?25l");
		else show_error("SYNTAX ERROR");
		return;
	}
	if (STRING_EQUALS(line, "END")) {
		keepRunning = false;
		return;
	}
	if (is_esc(line)) {
		run_esc(line + 3);
		return;
	}
	if (STRING_EQUALS(line, "EXIT")) {
		RESET();
		CLEAR_SCREEN();
		exit(0);
	}
	if (is_fg(line)) {
		line += 2;
		strncpy(copy, line, LINE_SIZE);
		eval_expr(copy, variables);
		temp = atoi(copy);
		if (temp > PROGRAM_SIZE)
			show_error("SYNTAX ERROR");
		else printf("\033[3%ldm", temp);
		return;
	}
	if (is_for(line) || is_next(line)) {
		if (!running)
			show_error("ILLEGAL DIRECT MODE ERROR");
		return;
	}
	if (is_gosub(line)) {
		temp = atoi(line + 5);
		if (temp > PROGRAM_SIZE)
			show_error("SYNTAX ERROR");
		else if (subCounter + 1 == PROGRAM_SIZE) {
			/* Should never happen, but if so, handle it gracefully  :D */
			show_error("TOO MANY SUBS ERROR");
		}
		else {
			subs[subCounter] = programCounter;
			subCounter++;
			programCounter = temp - 1;
			keepRunning = true;
			if (!running) run_program(program, aliases, variables);
		}
		return;
	}
	if (is_goto(line)) {
		temp = atoi(line + 4);
		if (temp > PROGRAM_SIZE)
			show_error("SYNTAX ERROR");
		else {
			programCounter = temp - 1;
			if (!running) {
				keepRunning = true;
				run_program(program, aliases, variables);
			}
		}
		return;
	}
	if (is_hidden(line)) {
		if (STRING_CONTAINS(line, "ON"))
			printf("\033[8m");
		else if (STRING_CONTAINS(line, "OFF"))
			printf("\033[28m");
		else show_error("SYNTAX ERROR");
		return;
	}
	if (is_if(line)) {
		run_if(program, aliases, line, variables, running);
		return;
	}
	if (is_include(line)) {
		run_load(program, aliases, variables, line + 4);
		return;
	}
	if (is_input(line)) {
		if (!running) {
			show_error("ILLEGAL DIRECT MODE ERROR");
			return;
		}
		SetBlocking(true);
		run_input(line + 5, variables);
		SetBlocking(false);
		return;
	}
	if (is_italic(line)) {
		if (STRING_CONTAINS(line, "ON"))
			printf("\033[3m");
		else if (STRING_CONTAINS(line, "OFF"))
			printf("\033[23m");
		else show_error("SYNTAX ERROR");
		return;
	}
	if (STRING_STARTS_WITH(line, "LET")) {
		line += 3;
		strncpy(copy, line, LINE_SIZE);
		run_let(copy, variables);
		return;
	}
	if (is_list(line)) {
		run_list(program, line + 4);
		return;
	}
	if (is_load(line)) {
		memset(program, 0, PROGRAM_SIZE * LINE_SIZE);
		memset(variables, 0, 26);
		run_load(program, aliases, variables, line + 4);
		return;
	}
	if (is_move(line)) {
		line += 4;
		strncpy(copy, line, LINE_SIZE);
		eval_expr(copy, variables);
		run_move(copy);
		return;
	}
	if (STRING_EQUALS(line, "NEW")) {
		memset(program, 0, PROGRAM_SIZE * LINE_SIZE);
		memset(variables, 0, 26);
		return;
	}
	if (is_print(line)) {
		line += 5;
		strncpy(copy, line, LINE_SIZE);
		eval_expr(copy, variables);
		if (!thereWasAnError) run_print(program, copy, false);
		return;
	}
	if (is_prompt(line)) {
		line += 6;
		while(line[0] == ' ') line++;
		strncpy(copy, line, LINE_SIZE);
		replace_chr(copy);
		combine_strings(copy);	/* We don't want to replace variables with values etc. */
		tempChar = strchr(copy, '"');
		tempChar2 = strchr(copy + 1, '"');
		if (tempChar2 != NULL) tempChar2[0] = '\0';
		strncpy(prompt, tempChar + 1, LINE_SIZE - 6);
		return;
	}
	if (STRING_STARTS_WITH(line, "REM")) return;
	if (STRING_EQUALS(line, "RESET")) {
		RESET();
		return;
	}
	if (is_reverse(line)) {
		if (STRING_CONTAINS(line, "ON"))
			printf("\033[7m");
		else if (STRING_CONTAINS(line, "OFF"))
			printf("\033[27m");
		else show_error("SYNTAX ERROR");
		return;
	}
	if (STRING_EQUALS(line, "RUN")) {
		programCounter = 0;
		keepRunning = true;
		run_program(program, aliases, variables);
		return;
	}
	if (STRING_EQUALS(line, "RETURN")) {
		subCounter--;
		if (subCounter >= PROGRAM_SIZE)
			show_error("RETURN WITHOUT GOSUB ERROR");
		programCounter = subs[subCounter];
		keepRunning = true;
		if (!running) run_program(program, aliases, variables);
		return;
	}
	if (is_save(line)) {
		run_save(program, line + 4);
		return;
	}
	if (is_sys(line)) {
		run_sys(line + 3, variables);
		return;
	}
	if (is_underline(line)) {
		if (STRING_CONTAINS(line, "ON"))
			printf("\033[4m");
		else if (STRING_CONTAINS(line, "OFF"))
			printf("\033[24m");
		else show_error("SYNTAX ERROR");
		return;
	}

	/* Check if it's LET without the keyword LET */
	if (is_let(line)) {
		strncpy(copy, line, LINE_SIZE);
		run_let(copy, variables);
		return;
	}

	/* Another scenario that can happen is if the user tries to
	create an alias that is a Breakaway BASIC keyword.  So... */
	if (STRING_STARTS_WITH(line, "ALIAS")) {
		show_error("THAT'S A KEYWORD");
		return;
	}
	
	/* If the user typed cd wherver, like in DOS or Bash,
		let it "just work".  It looks weird in BASIC, but
		considering terminals have been doing it this way
		for decades, it's the right thing to do.  :)  */
	if (STRING_STARTS_WITH(line, "CD")) {
		line += 2;
		while(line[0] == ' ') line++;
		if (!GoToFolder(line)) show_error("?DIRECTORY NOT FOUND ERROR");
		return;
	}

	/* If the "command" name is a Breakaway BASIC keyword,
	it's most likely a syntax error; on the off-chance it's not,
	users could just run i.e. SYS "PRINT whatever" */
	if (is_keyword(line)) {
		show_error("SYNTAX ERROR");
		return;
	}
	
	/* Otherwise, run it */
	rc = system(line);
}

void set_alias(Line line, Program aliases) {
	size_t i = 0;
	for (; i<PROGRAM_SIZE; i++) {
		if (aliases[i][0] != '\0') continue;
		strncpy(aliases[i], line, LINE_SIZE);
		return;
	}
}

void run_alias(Line line, Program aliases) {
	Line left, right;
	char* temp = line;
	size_t i = 0, j = 0;

	/* Loop through the list of aliases looking for one that matches
	the instruction the user typed to do a find-&-replace */
	for (i=0; i<PROGRAM_SIZE; i++) {

		/* If we've reached an alias that isn't set yet,
		at the end of the list, then exit the loop */
		temp = aliases[i];
		if (temp[0] == '\0') return;

		/* Get the text between the first quotes (the name/key) */
		memset(left, 0, LINE_SIZE);
		while(temp[0] != '\0' && temp[0] != '"') temp++;
		if (temp[0] != '"') return;
		temp++;
		j = 0;
		while(temp[0] != '\0' && temp[0] != '"') {
			left[j] = temp[0];
			j++;
			temp++;
		}
		if (temp[0] != '"') return;
		temp++;	/* The closing quote on the name */

		/* Move past the equals sign and get the right-hand string */
		while(temp[0] != '\0' && temp[0] != '"') temp++;
		if (temp[0] != '"') return;
		temp++;
		j = 0;
		memset(right, 0, LINE_SIZE);
		while(temp[0] != '\0' && temp[0] != '"') {
			right[j] = temp[0];
			j++;
			temp++;
		}

		/* Now that we have our left and our right, do this:
		IF instruction = an alias, THEN replace the alias with its value
		and exit the loop */
		if (STRING_STARTS_WITH(line, left)) {
			replace_with_string(line, 0, strlen(left), right);
			return;
		}
	}
}

void run_esc(char* line) {
	/* Declare vars */
	Line copy;
	char* temp;
	size_t i;
	
	/* Set default values */
	memset(copy, 0, LINE_SIZE);
	temp = line;
	i = 0;
	
	/* Move past spaces and the first quote */
	while (temp[0] == ' ' || temp[0] == '"') temp++;
	
	/* Copy up to the closing quote */
	while(temp[0] != '"' && temp[0] != '\0') {
		copy[i] = temp[0];
		temp++;
		i++;
	}
	
	/* And here we go... */
	printf("\033%s", copy);
}

void run_load(Program program, Program aliases, VarList variables, char* line) {
	/* Declare vars */
	Line copy, code;
	char* temp;
	size_t i;
	FILE* file;
	
	/* Set default values */
	memset(copy, 0, LINE_SIZE);
	temp = line;
	i = 0;
	
	/* Move past spaces and the first quote */
	while (temp[0] != '"') temp++;
	temp++;
	
	/* Copy up to the closing quote */
	while(temp[0] != '"' && temp[0] != '\0') {
		copy[i] = temp[0];
		temp++;
		i++;
	}
	
	/* And here we go... */
	file = NULL;
	file = fopen(copy, "r");
	if (file == NULL) {
		perror("?ERROR OPENING FILE");
		return;
	}
	while(true) {
		memset(code, 0, LINE_SIZE);
		fgets(code, LINE_SIZE, file);
		if (feof(file)) break;
		if (ferror(file)) {
			perror("?ERROR READING FILE");
			fclose(file);
			return;
		}
		run(program, aliases, variables, code, false);
	}
	fclose(file);
}


void run_save(Program program, char* line) {
	/* Declare vars */
	Line copy;
	char* temp;
	size_t i;
	FILE* file;
	
	/* Set default values */
	memset(copy, 0, LINE_SIZE);
	temp = line;
	i = 0;
	
	/* Move past spaces and the first quote */
	while (temp[0] == ' ' || temp[0] == '"') temp++;
	
	/* Copy up to the closing quote */
	while(temp[0] != '"' && temp[0] != '\0') {
		copy[i] = temp[0];
		temp++;
		i++;
	}
	
	/* And here we go... */
	file = NULL;
	file = fopen(copy, "w");
	if (file == NULL) {
		perror("?ERROR OPENING FILE");
		return;
	}
	for (i=0; i<PROGRAM_SIZE; i++) {
		if (program[i][0] == '\0') continue;
		fprintf(file, "%ld %s\n", i, program[i]);
	}
	fclose(file);
}

void run_sys(char* line, VarList variables) {
	/* Declare vars */
	Line copy;
	char* temp;
	size_t i;
	
	/* Set default values */
	memset(copy, 0, LINE_SIZE);
	temp = line;
	i = 0;
	
	/* Move past spaces and the first quote */
	while (temp[0] == ' ' || temp[0] == '"') temp++;
	
	/* Copy up to the closing quote */
	while(temp[0] != '"' && temp[0] != '\0') {
		copy[i] = temp[0];
		temp++;
		i++;
	}

	/* Do any string-joining that may be necessary */
	eval_expr(copy, variables);
	
	/* And here we go... */
	rc = system(copy);
}


void run_input(char* line, VarList variables) {
	/* Declare vars */
	Line buffer, buffer2;
	char* temp;
	
	/* Get and validate user input (again, for version 0.1, this is
	super easy cuz only expressions are allowed */
	memset(buffer, 0, LINE_SIZE);
	printf("? ");
	ReadLine(buffer);
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

void run_if(Program program, Program aliases, char* line, VarList variables, bool running) {
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
	else run(program, aliases, variables, then, running);
}

void run_let(char* line, VarList variables) {
	char* temp;
	int i;
	strip_spaces(line);
	temp = strchr(line, '=');
	if (temp == NULL) {
		show_error("SYNTAX ERROR");
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
	size_t i, from = 0, to = PROGRAM_SIZE - 1;
	
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
	if (from > PROGRAM_SIZE || to > PROGRAM_SIZE) {
		show_error("SYNTAX ERROR");
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

void run_move(Line line) {
	int tempInt = 0, x = -1, y = -1, x2 = -1, y2 = -1;
	tempInt = sscanf(line, "%d %d", &x, &y);
	if (tempInt != 2 || x < 0 || y < 0) {
		show_error("SYNTAX ERROR");
		return;
	}
	GetScreenSize(&y2, &x2);
	if (x > x2 || y > y2) {
		show_error("SYNTAX ERROR");
		return;
	}
	printf("\033[%d;%dH", y, x);
}

void run_print(Program program, Line line, bool centered) {
	/* Declare vars */
	size_t i, length;
	char copy[LINE_SIZE], * temp;
	bool in_quotes = false, newline = true;

	/* Replace the commas and quotation marks with spaces */
	length = strlen(line);
	strncpy(copy, line, LINE_SIZE);
	while(copy[0] == ' ') shift_left(copy, 0, length);
	for (i=0; i<length; i++) {
		while (copy[i] == '"') {
			in_quotes = !in_quotes;
			shift_left(copy, i, length);
		}
		if (copy[i] == ',' && !in_quotes ) {
			/* This used to replace it with a space, but by doing a shift
			left, you can do i.e. PRINT CHR$(65),"BC" and get "ABC". */
			shift_left(copy, i, length);
			continue;
		}
	}
	
	/* Figure out if it should print a new line at the end */
	i = length - 1;
	while(copy[i] == '\0' || (copy[i] == ' ' && !in_quotes)) i--;
	newline = copy[i] != ';';
	if (!newline) copy[i] = '\0';
	
	/* And print away! */
	temp = copy;
	if (centered)
		print_centered(temp);
	else {
		printf("%s", temp);
		if (newline) printf("\n");
	}
}

void run_program(Program program, Program aliases, VarList variables) {
	/* Declare variables */
	char* currentLine, temp;
	size_t lastLine, i, forStart, next;
	int nFor, nTo, nStep;
	char var;
	Line tempLine;

	SetBlocking(false);
	while(true) {

		/* Let the Escape key end the currently running program */
		temp = getchar();
		if (temp == 27) {
			lastLine = programCounter;
			while(program[lastLine][0] == '\0') lastLine--;
			printf("\nBREAK IN %ld\n", lastLine);
			keepRunning = false;
		}

		/* If the user pressed Escape, or we've reached last line, we're done. */
		if (!keepRunning || programCounter == PROGRAM_SIZE) {
			SetBlocking(true);
			return;
		}

		/* Skip empty lines */
		currentLine = program[programCounter];
		if (currentLine[0] == '\0') {
			programCounter++;
			if (programCounter == PROGRAM_SIZE) {
				SetBlocking(true);
				return;
			}
			continue;
		}

		/* Handle FOR */
		currentLine = program[programCounter];
		if (is_for(currentLine)) {

			/* Step 1: Get the variable and the numbers */

			forStart = programCounter;
			currentLine += 3;	/* Skip FOR */
			while(currentLine[0] == ' ') currentLine++;
			var = currentLine[0];
			currentLine++;
			while(currentLine[0] == ' ' || currentLine[0] == '=')
				currentLine++;
			nFor = atoi(currentLine);
			if (currentLine[0] == '+' || currentLine[0] == '-')
				currentLine++;
			while(is_digit(currentLine[0]) || currentLine[0] == ' ')
				currentLine++;
			currentLine += 2;	/* Skip "TO" */
			while(currentLine[0] == ' ') currentLine++;
			nTo = atoi(currentLine);
			if (currentLine[0] == '+' || currentLine[0] == '-')
				currentLine++;
			while(is_digit(currentLine[0]) || currentLine[0] == ' ')
				currentLine++;
			if (STRING_STARTS_WITH(currentLine, "STEP")) {
				currentLine += 4;	/* Skip "STEP" */
				while(currentLine[0] == ' ') currentLine++;
				nStep = atoi(currentLine);
			}
			else nStep = 1;

			/* Step 2: Make sure there's a NEXT */
			
			for (next = programCounter; next<PROGRAM_SIZE; next++) {
				if (!is_next(program[next])) continue;
				currentLine = program[next] + 4;	/* Past "NEXT" */
				while(currentLine[0] == ' ') currentLine++;
				if (currentLine[0] == var) break;
			}
			if (next == PROGRAM_SIZE) {
				show_error("FOR WITHOUT NEXT ERROR");
				lastLine = programCounter;
				keepRunning = false;
				SetBlocking(true);
				return;
			}

			/* Step 3: Run the loop! */
			
			programCounter = forStart;
			i = nFor;
			snprintf(tempLine, LINE_SIZE, "LET %c = %d", var, i);
			run_let(tempLine, variables);
			while(true) {

				// Update the program counter
				programCounter++;
				if (programCounter == PROGRAM_SIZE) {
					SetBlocking(true);
					return;
				}

				// If it hits NEXT, go back to line forStart
				// NOTE: I'll also want it to make sure the
				// NEXT line is the same variable (so nested
				// loops will work - it won't break on NEXT J
				// when what it should be looking for is NEXT I)
				currentLine = program[programCounter];
				if (is_next(currentLine)) {
					programCounter = forStart;
					i += nStep;
					snprintf(tempLine, LINE_SIZE, "%c = %d", var, i);
					run_let(tempLine, variables);
					if (i >= nTo) break;
					continue;
				}

				// Otherwise, run it
				run(program, aliases, variables, currentLine, true);
			}
			
			programCounter++;
			continue;
		}
		run(program, aliases, variables, currentLine, true);
		programCounter++;
		if (programCounter == PROGRAM_SIZE) {
			SetBlocking(true);
			return;
		}
	}
	SetBlocking(true);
}

// End of code-running functions
