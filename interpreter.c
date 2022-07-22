#include "main.h"

char** currentProgram = NULL;
size_t currentLine = 0, currentSub = 0;
bool programMode = false;
extern uint8_t lastError;
int64_t subs[PROGRAM_MAX];
extern Variable* firstVar, * firstAlias;

/************************************************************************/

void RunIF(char* buffer) {
	/* Declare variables */
	char line[BUFFER_MAX],
		left[BUFFER_MAX],
		right[BUFFER_MAX],
		* end = NULL,
		* temp = NULL;
	float leftF = 0, rightF = 0;
	bool answer;
	size_t i, length;
	
	/* Make a copy of the buffer.  I'm not sure if this is really necessary,
	but it seems this has fixed (or at least worked around) a lot of bugs. */
	strncpy(line, buffer, BUFFER_MAX);
	
	/* Replace variables with their values,
	then get rid of unnecessary spaces,
	then replace math equations with their results */
	ReplaceVariablesWithValues(line);
	StripSpaces(line);
	EvalMath(line);
	
	/* Make sure there's a THEN */
	if (strstr(line, "THEN") == NULL) {
		lastError = SYNTAX_ERROR;
		return;
	}
	#if DEBUG_MODE
	printf("if: %s\n", line);
	#endif
	
	/* For now, let's just handle less-than */
	end = strstr(line, "<");
	if (end != NULL) {
		temp = CopySubstring(line, end);
		if (temp == NULL) {
			lastError = MEMORY_ERROR;
			return;
		}
		if (!StringIsFloat(temp)) {
			#if DEBUG_MODE
			printf("temp = \"%s\"\n", temp);
			#endif
			free(temp);
			lastError = TYPE_MISMATCH_ERROR;
			return;
		}
		leftF = atof(temp);
		free(temp);
		temp = NULL;
		temp = CopySubstring(end + 1, strstr(end + 1, "THEN"));
		if (temp == NULL) {
			lastError = MEMORY_ERROR;
			return;
		}
		if (!StringIsFloat(temp)) {
			#if DEBUG_MODE
			printf("temp = \"%s\"\n", temp);
			#endif
			free(temp);
			lastError = TYPE_MISMATCH_ERROR;
			return;
		}
		rightF = atof(temp);
		free(temp);
		temp = NULL;
		answer = leftF < rightF;
	}
	
	/* Then do stuff based on the outcome */
	if (answer) {
		end = strstr(line, "THEN") + 4;
		#if DEBUG_MODE
		printf("end = \"%s\"\n", end);
		#endif
		if (end[0] < '0' || end[0] > '9') {
			/* Non-number after THEN */
			lastError = SYNTAX_ERROR;
		}
		else currentLine = atol(end) - 1;
		return;
	}
	
	/* If it gets here, look for an ELSE */
	end = strstr(line, "ELSE") + 4;
	if (end == NULL) return;
	if (end[0] < '0' || end[0] > '9') {
		/* Non-number after THEN */
		lastError = SYNTAX_ERROR;
	}
	else currentLine = atol(end) - 1;
}

/************************************************************************/

void RunSYS(char* buffer) {
	char code[BUFFER_MAX];
	int returnCode = system((const char*)buffer);
	sprintf(code, "RC=%d", returnCode);
	#if DEBUG_MODE
	printf("code = '%s'\n", code);
	#endif
	if (firstVar == NULL) {
		firstVar = CreateVariable(code);
		return;
	}
	SetVariable(code, false);
}

/************************************************************************/

void RunLET(char* line) {
	char copy[BUFFER_MAX];
	memset(copy, 0, BUFFER_MAX);
	strcpy(copy, line);
	if (firstVar == NULL) {
		firstVar = CreateVariable(copy);
		return;
	}
	SetVariable(copy, false);
}

/************************************************************************/

void RunNEW() {
	/* Clear the program memory */
	FreeProgram(currentProgram);
	currentProgram = NULL;
	currentProgram = CreateProgram();
	if (currentProgram == NULL)
		lastError = MEMORY_ERROR;
	
	/* Clear variables */
	FreeVariables(firstVar);
	firstVar = NULL;
	FreeVariables(firstAlias);
	firstAlias = NULL;
}

/************************************************************************/

void LoadFile(char* name) {
	char temp[BUFFER_MAX];
	
	/* Clear whatever old program was in memory */
	RunNEW();
	
	FILE* file = fopen((const char*)name, "r");
	if (file == NULL) {
		//lastError = FILE_NOT_FOUND;
		printf("?FILE NOT FOUND");
		NewLine();
		return;
	}
	while(!feof(file)) {
		fgets(temp, BUFFER_MAX, file);
		AddToProgram(currentProgram, temp);
	}
	fclose(file);
}

/************************************************************************/

void SaveFile(char* name) {
	size_t i = 0;
	FILE* file = NULL;
	char* newline = NULL;
	
	file = fopen((const char*)name, "w");
	if (file == NULL) {
		printf("?FILE WRITE ERROR");
		NewLine();
		return;
	}
	for (i=0; i<PROGRAM_MAX; i++) {
		if (currentProgram[i] == NULL) continue;
		/* Keep in mind, the line already includes a newline */
		fprintf(file, "%ld %s\n", i, currentProgram[i]);
	}
	fclose(file);
}

/************************************************************************/

void RunOrContinue() {
	int temp = -1;
	
	programMode = true;
	SetBlocking(false);
	for(; currentLine<PROGRAM_MAX; currentLine++) {
		/* If it's NULL, skip it */
		if (currentProgram[currentLine] == NULL) continue;
		
		/* If the user pressed Escape, we're done. */
		temp = getchar();
		if (temp == 27) {
			NewLine();
			printf("BREAK IN %ld", currentLine);
			NewLine();
			SetBlocking(true);
			programMode = false;
			return;
		}
		
		/* If it's END, end the program */
		if (STRING_EQUALS(currentProgram[currentLine], "END")) {
			programMode = false;
			currentLine = 0;
			SetBlocking(true);
			return;
		}
		
		/* Otherwise, interpret the line and handle errors */
		Interpret(currentProgram[currentLine]);
		if (lastError != NO_ERROR) {
			NewLine();
			programMode = false;
			SetBlocking(true);
			return;
		}
	}
	programMode = false;
	currentLine = 0;
	SetBlocking(true);
}

/************************************************************************/

void Interpret(char* buffer) {
	lastError = NO_ERROR;
	char* token = NULL, input[BUFFER_MAX];
	int tempInt = 0, x = -1, y = -1, x2 = -1, y2 = -1;
	#if DEBUG_MODE
	size_t i = 0;
	#endif
	
	/* If it's NULL, do nothing. */
	if (buffer == NULL) {
		lastError = NO_ERROR;
		return;
	}
	
	/* If the user deletes a line, the pointer is just a new line
	NOTE: Kinda makes me wonder about my NewLine() function... I use
	a lot of \n characters in my code, but on other systems that
	wouldn't look the same.  But that's a 2.0 issue when I really
	care deeply about portability. :D */
	if (buffer[0] == '\n' || buffer[0] == '\r' || STRING_EQUALS(buffer, "\r\n")) return;
	
	/* Those checks aside, the next step to do is... */
	ReplaceAliases(buffer);
	#if DEBUG_MODE
	printf("After ReplaceAliases:  \"%s\"\n", buffer);
	#endif
	
	/* ALIAS NAME = value */
	if (STRING_STARTS_WITH(buffer, "ALIAS ")) {
		char copy[BUFFER_MAX - 6];
		strcpy(copy, buffer + 6);
		if (firstAlias == NULL) {
			firstAlias = CreateVariable(copy);
			return;
		}
		SetVariable(copy, true);
		return;
	}
	
	/* BG number - set the background */
	if (STRING_STARTS_WITH(buffer, "BG ")) {
		buffer += 3;
		if (buffer[0] < '0' || buffer[0] > '9')
			lastError = SYNTAX_ERROR;
		else {
			printf("\033[4%dm", atoi(buffer));
		}
		return;
	}
	
	/* BLINK ON/OFF - text blink mode on */
	if (STRING_EQUALS(buffer, "BLINK ON")) {
		printf("\033[5m");
		return;
	}
	if (STRING_EQUALS(buffer, "BLINK OFF")) {
		printf("\033[25m");
		return;
	}
	
	/* BOLD ON/OFF - bold text */
	if (STRING_EQUALS(buffer, "BOLD ON")) {
		printf("\033[1m");
		return;
	}
	if (STRING_EQUALS(buffer, "BOLD OFF")) {
		printf("\033[22m");
		return;
	}
	
	/* CD or cd - like in every modern OS */
	if (STRING_STARTS_WITH(buffer, "CD ") || STRING_STARTS_WITH(buffer, "cd ")) {
		GoToFolder(buffer + 3);
		return;
	}

	/* CLEAR or CLS - clear screen */
	if (STRING_STARTS_WITH(buffer, "CLEAR") || STRING_STARTS_WITH(buffer, "CLS")) {
		printf("\033[H\033[J");
		return;
	}
	
	/* CONT or CONTINUE - continue program */
	if (STRING_EQUALS(buffer, "CONT") || STRING_EQUALS(buffer, "CONTINUE")) {
		RunOrContinue();
		return;
	}
	
	/* END (in program mode) is handled by the RunOrContinue function */
	if (STRING_EQUALS(buffer, "END")) {
		lastError = SYNTAX_ERROR;
		return;
	}
	
	/* ESC string - ANSI escape code */
	if (STRING_STARTS_WITH(buffer, "ESC ")) {
		printf("\033%s", buffer + 4);
		return;
	}
	
	/* EXIT - exit Breakaway Basic */
	if (STRING_EQUALS(buffer, "EXIT")) {
		printf("\033[0m");		/* RESET */
		printf("\033[H\033[J");		/* CLEAR */
		FreeProgram(currentProgram);
		exit(0);
	}
	
	/* FAINT ON/OFF - text dim/faint colors */
	if (STRING_EQUALS(buffer, "FAINT ON")) {
		printf("\033[2m");
		return;
	}
	if (STRING_EQUALS(buffer, "FAINT OFF")) {
		printf("\033[22m");
		return;
	}
	
	/* FG number - set the text foreground color */
	if (STRING_STARTS_WITH(buffer, "FG ")) {
		buffer += 3;
		if (buffer[0] < '0' || buffer[0] > '9')
			lastError = SYNTAX_ERROR;
		else {
			printf("\033[3%dm", atoi(buffer));
		}
		return;
	}

	/* GOSUB line number */
	if (STRING_STARTS_WITH(buffer, "GOSUB") || STRING_STARTS_WITH(buffer, "GO SUB")) {
		buffer += 2;	/* past GO */
		if (buffer[0] == ' ') buffer++;
		buffer += 3;	/* past SUB */
		
		/* Then move past the spaces */
		while(buffer[0] == ' ') buffer++;
		
		tempInt = atoi(buffer);
		#if DEBUG_MODE
		printf("buffer = \"%s\", tempInt = %d\n", buffer, tempInt);
		#endif
		if (tempInt < 0 || tempInt > PROGRAM_MAX) {
			lastError = SYNTAX_ERROR;
			return;
		}
		if (currentSub == PROGRAM_MAX) {
			lastError = MEMORY_ERROR;
			return;
		}
		subs[currentSub] = currentLine;
		currentLine = tempInt - 1;
		currentSub++;

		#if DEBUG_MODE
		printf("GOSUB: ");
		for(i=0; i<PROGRAM_MAX; i++) {
			if (subs[i] == -1) {
				printf("\n");
				break;
			}
			printf("%ld ", subs[i]);
		}
		printf("Going to line %d\n", tempInt);
		#endif
		return;
	}
	
	/* GOTO line */
	if (STRING_STARTS_WITH(buffer, "GOTO") || STRING_STARTS_WITH(buffer, "GO TO")) {
		if (!programMode) {
			lastError = SYNTAX_ERROR;
			return;
		}
		buffer += 2;	/* past GO */
		if (buffer[0] == ' ') buffer++;
		buffer += 2;	/* past TO */
		
		/* Then move past the spaces */
		while(buffer[0] == ' ') buffer++;
		
		tempInt = atoi(buffer);
		if (tempInt < 0 || tempInt > PROGRAM_MAX)
			lastError = SYNTAX_ERROR;
		else currentLine = tempInt - 1;	/* -1 because the for-loop does a ++ */
		return;
	}
	
	/* IF condition THEN line ELSE line */
	if (STRING_STARTS_WITH(buffer, "IF ")) {
		RunIF(buffer + 3);
		return;
	}
	
	/* INPUT variable */
	if (STRING_STARTS_WITH(buffer, "INPUT ")) {
		if (!programMode) {
			lastError = SYNTAX_ERROR;
			return;
		}
		/* Get the user's input */
		printf("? ");
		memset(input, 0, BUFFER_MAX);
		SetBlocking(true);
		fgets(input, BUFFER_MAX - strlen(buffer) + 6, stdin);
		SetBlocking(false);
		
		/* Build the string that will be the variable's value */
		char varValue[BUFFER_MAX];
		strcpy(varValue, buffer + 6);
		strcat(varValue, "=");
		strcat(varValue, input);
		#if DEBUG_MODE
		printf("\n\"%s\"\n", varValue);
		#endif
		
		/* Then make it a variable */
		RunLET(varValue);
		return;
	}
	
	/* HIDDEN ON/OFF - hidden text */
	if (STRING_EQUALS(buffer, "HIDDEN ON")) {
		printf("\033[8m");
		return;
	}
	if (STRING_EQUALS(buffer, "HIDDEN OFF")) {
		printf("\033[28m");
		return;
	}
	
	/* ITALIC ON/OFF - italic text */
	if (STRING_EQUALS(buffer, "ITALIC ON")) {
		printf("\033[3m");
		return;
	}
	if (STRING_EQUALS(buffer, "ITALIC OFF")) {
		printf("\033[23m");
		return;
	}
	
	/* LET var = value */
	if (STRING_STARTS_WITH(buffer, "LET ")) {
		RunLET(buffer + 4);
		return;
	}
	
	/* LIST [line numbers] - List the contents of the program */
	if (STRING_STARTS_WITH(buffer, "LIST")) {
		ListProgram(currentProgram, buffer + 4);
		return;
	}
	
	/* LOAD - Load a file */
	if (STRING_STARTS_WITH(buffer, "LOAD ")) {
		LoadFile(buffer + 5);
		return;
	}
	
	/* MOVE x y - Move the cursor */
	if (STRING_STARTS_WITH(buffer, "MOVE ")) {
		buffer += 5;
		tempInt = sscanf(buffer, "%d %d", &x, &y);
		GetScreenSize(&x2, &y2);
		if (tempInt != 2 || x < 0 || y < 0 || x > x2 || y > y2)
			lastError = SYNTAX_ERROR;
		else printf("\033[%d;%dH", y, x);
		return;
	}
	
	/* NEW - clear contents of program */
	if (STRING_EQUALS(buffer, "NEW")) {
		RunNEW();
		return;
	}
	
	/* REM - comment - do nothing */
	if (STRING_STARTS_WITH(buffer, "REM")) return;
	
	/* RESET - reset the terminal settings */
	if (STRING_EQUALS(buffer, "RESET")) {
		printf("\033[0m");
		return;
	}

	/* RETURN - return from subrouting */
	if (STRING_EQUALS(buffer, "RETURN")) {
		tempInt = subs[currentSub - 1]; //+ 1;
		#if DEBUG_MODE
		printf("RETURN: ");
		for(i=0; i<PROGRAM_MAX; i++) {
			if (subs[i] == -1) {
				printf("\n");
				break;
			}
			printf("%ld ", subs[i]);
		}
		printf("Returning to line %d\n", tempInt);
		#endif
		if (tempInt == 0) return;
		currentLine = tempInt;
		subs[currentSub] = -1;
		if (currentSub > 0) currentSub--;
		return;
	}
	
	/* REVERSE ON/OFF */
	if (STRING_EQUALS(buffer, "REVERSE ON")) {
		printf("\033[7m");
		return;
	}
	if (STRING_EQUALS(buffer, "REVERSE OFF")) {
		printf("\033[27m");
		return;
	}
	if (STRING_STARTS_WITH(buffer, "RENUMBER ")) {
		RenumberProgram(currentProgram, buffer + 9);
		return;
	}
	
	/* RUN - self-explanatory :) */
	if (STRING_EQUALS(buffer, "RUN")) {
		currentLine = 0;
		RunOrContinue();
		return;
	}
	
	/* SAVE - Save a file */
	if (STRING_STARTS_WITH(buffer, "SAVE ")) {
		SaveFile(buffer + 5);
		return;
	}
	
	/* SYS - run an external command */
	if (STRING_STARTS_WITH(buffer, "SYS ")) {
		token = buffer + 4;
		RunSYS(token);
		return;
	}
	
	/* Testing variables */
	if (STRING_STARTS_WITH(buffer, "TEST ")) {
		#if DEBUG_MODE
		printf("Looking for a variable named \"%s\"\n", buffer + 5);
		#endif
		Variable* tempVar = GetVariable(buffer + 5, false);
		printf("%s", tempVar == NULL || tempVar->value == NULL ? "0" : tempVar->value);
		return;
	}
	
	/* UNDERLINE ON/OFF - underlined text */
	if (STRING_EQUALS(buffer, "UNDERLINE ON")) {
		printf("\033[4m");
		return;
	}
	if (STRING_EQUALS(buffer, "UNDERLINE OFF")) {
		printf("\033[24m");
		return;
	}
	
	/* Line number - Add it to the program */
	if (buffer[0] >= '0' && buffer[0] <= '9') {
		AddToProgram(currentProgram, buffer);
		return;
	}
	
	/* And if it gets here, the user goofed */
	RunSYS(buffer);
}
