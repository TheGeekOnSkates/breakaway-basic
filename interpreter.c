#include "main.h"

char** currentProgram = NULL;
int RC = 0;
size_t currentLine = 0;
bool programMode = false;
extern uint8_t lastError;

/************************************************************************/

void LoadFile(char* name) {
	char temp[BUFFER_MAX];
	
	/* Delete the trailing new line character */
	name[strlen(name) - 1] = '\0';
	
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
	
	/* Delete the trailing new line character */
	name[strlen(name) - 1] = '\0';
	
	file = fopen((const char*)name, "w");
	if (file == NULL) {
		printf("?FILE WRITE ERROR");
		NewLine();
		return;
	}
	for (i=0; i<PROGRAM_MAX; i++) {
		if (currentProgram[i] == NULL) continue;
		/* Keep in mind, the line already includes a newline */
		fprintf(file, "%ld %s", i, currentProgram[i]);
	}
	fclose(file);
}

/************************************************************************/

void ReplaceWithString(char* line, uint16_t start, uint16_t end, char* replacement) {
	char temp[BUFFER_MAX];
	uint16_t i;
	
	for (i=0; i<start; i++) temp[i] = line[i];
	snprintf(temp + start, BUFFER_MAX - start, "%s%s", replacement, line + end);
	strncpy(line, temp, BUFFER_MAX);
}

/************************************************************************/

void ReplaceWithFloat(char* line, uint16_t from, uint16_t to, float value) {
        size_t i;
	char temp[BUFFER_MAX];
        memset(temp, 0, BUFFER_MAX);
        for (i=0; i<from; i++) temp[i] = line[i];
        snprintf(temp + from, BUFFER_MAX, "%g%s", value, line + to);
        strncpy(line, temp, BUFFER_MAX);
}

/************************************************************************/

bool ParensMatch(char* string) {
        size_t i, length, extras;
	length = strlen(string);
	extras = 0;
        for (i = 0; i<length; i++) {
                if (string[i] == '(') extras++;
                else if (string[i] == ')') extras--;
        }
        return extras == 0;
}

/************************************************************************/

void SyntaxError() {
	printf("?SYNTAX ERROR");
	if (programMode)
		printf(" IN LINE %ld", currentLine);
	NewLine();
}

/************************************************************************/

void MemoryError() {
	printf("?MEMORY ERROR");
	if (programMode)
		printf(" IN LINE %ld", currentLine);
	NewLine();
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
			SetBlocking(true);
			programMode = false;
			return;
		}
		
		/* If it's END, end the program */
		if (STRING_EQUALS(currentProgram[currentLine], "END\n")) {
			programMode = false;
			currentLine = 0;
			SetBlocking(true);
			return;
		}
		
		/* Otherwise, interpret the line and handle errors */
		Interpret(currentProgram[currentLine]);
		if (lastError == SYNTAX_ERROR) {
			SyntaxError();
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
	char* token = NULL;
	int tempInt = 0;
	
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
	
	/* END (in program mode) is handled by the RunOrContinue function */
	if (STRING_EQUALS(buffer, "END\n")) {
		SyntaxError();
		return;
	}
	
	/* CLEAR or CLS - clear screen */
	if (STRING_STARTS_WITH(buffer, "CLEAR") || STRING_STARTS_WITH(buffer, "CLS")) {
		printf("\x1b[2J\x1b[H");
		return;
	}
	
	/* EXIT - exit Breakaway Basic */
	if (STRING_EQUALS(buffer, "EXIT\n")) {
		FreeProgram(currentProgram);
		exit(0);
	}
	
	/* GOTO line */
	if (STRING_STARTS_WITH(buffer, "GOTO") || STRING_STARTS_WITH(buffer, "GO TO")) {
		if (!programMode) {
			SyntaxError();
			return;
		}
		buffer += 2;	/* past GO */
		if (buffer[0] == ' ') buffer++;
		buffer += 2;	/* past TO */
		
		/* Then move past the spaces */
		while(buffer[0] != '\0' && buffer[0] != ' ') buffer++;
		tempInt = atoi(buffer);
		if (tempInt < 0 || tempInt > PROGRAM_MAX)
			lastError = SYNTAX_ERROR;
		else currentLine = tempInt - 1;	/* -1 because the for-loop does a ++ */
		return;
	}
	
	/* LOAD - Load a file */
	if (STRING_STARTS_WITH(buffer, "LOAD ")) {
		LoadFile(buffer + 5);
		return;
	}
	
	/* NEW - clear contents of program */
	if (STRING_EQUALS(buffer, "NEW\n")) {
		FreeProgram(currentProgram);
		currentProgram = NULL;
		currentProgram = CreateProgram();
		if (currentProgram == NULL)
			lastError = MEMORY_ERROR;
		return;
	}
	
	/* REM - comment - do nothing */
	if (STRING_STARTS_WITH(buffer, "REM")) return;
	
	/* RUN - self-explanatory :) */
	if (STRING_EQUALS(buffer, "RUN\n")) {
		currentLine = 0;
		RunOrContinue();
		return;
	}
	
	/* CONT or CONTINUE - continue program */
	if (STRING_EQUALS(buffer, "CONT\n") || STRING_EQUALS(buffer, "CONTINUE\n")) {
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
		RC = system((const char*)token);
		return;
	}
	
	/* Line number - Add it to the program */
	if (buffer[0] >= '0' && buffer[0] <= '9') {
		AddToProgram(currentProgram, buffer);
		return;
	}
	
	/* LIST [line numbers] - List the contents of the program */
	if (STRING_STARTS_WITH(buffer, "LIST")) {
		ListProgram(currentProgram, buffer + 4);
		switch (lastError) {
			case SYNTAX_ERROR:
				SyntaxError(); break;
			case MEMORY_ERROR:
				MemoryError(); break;
		}
		return;
	}
	
	/* Do I need this?  Maybe in another function 
	token = strstr(buffer, " ");
	if (token == NULL) {
		lastError = SYNTAX_ERROR;
		return;
	}
	*/
	
	/* And if it gets here, the user goofed */
	SyntaxError();
}
