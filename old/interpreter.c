#include "main.h"

void Interpret(char* buffer) {
	lastError = NO_ERROR;
	char* token = NULL, input[BUFFER_MAX];
	int tempInt = 0, x = -1, y = -1, x2 = -1, y2 = -1;
	char varValue[BUFFER_MAX];
	
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
	
	/* CLEAR ALIASES */
	if (STRING_EQUALS(buffer, "CLEAR ALIASES")) {
		FreeVariables(firstAlias);
		firstAlias = NULL;
		return;
	}
	
	/* CLEAR HISTORY */
	if (STRING_EQUALS(buffer, "CLEAR HISTORY")) {
		DeleteHistory();
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
	
	/* FAINT ON/OFF - text dim/faint colors */
	if (STRING_EQUALS(buffer, "FAINT ON")) {
		printf("\033[2m");
		return;
	}
	if (STRING_EQUALS(buffer, "FAINT OFF")) {
		printf("\033[22m");
		return;
	}
	
	/* GET variable */
	if (STRING_STARTS_WITH(buffer, "GET ")) {
		if (!programMode) {
			lastError = ILLEGAL_DIRECT_ERROR;
			return;
		}
		/* Get the user's input */
		printf("Started. ");
		SetBlocking(false);
		tempInt = (int)getchar();
		SetBlocking(true);
		printf("Ended.\n");
		#if DEBUG_MODE
		printf("tempInt = %d\n", tempInt);
		#endif
		memset(input, 0, BUFFER_MAX);
		snprintf(input, BUFFER_MAX, "%d", tempInt);
		
		/* Build the string that will be the variable's value */
		memset(varValue, 0, BUFFER_MAX);
		strcpy(varValue, buffer + 4);
		strcat(varValue, "=");
		strcat(varValue, input);
		#if DEBUG_MODE
		printf("\n\"%s\"\n", varValue);
		#endif
		
		/* Then make it a variable */
		RunLET(varValue);
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
			lastError = ILLEGAL_DIRECT_ERROR;
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
			lastError = ILLEGAL_DIRECT_ERROR;
			return;
		}
		/* Get the user's input */
		memset(input, 0, BUFFER_MAX);
		SetBlocking(true);
		char* tempString = ReadLine("? ");
		if (tempString == NULL) {
			lastError = MEMORY_ERROR;
			return;
		}
		strncpy(input, tempString, BUFFER_MAX);
		SetBlocking(false);
		
		/* Build the string that will be the variable's value */
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
	
	/* RENUMBER */
	if (STRING_STARTS_WITH(buffer, "RENUMBER ")) {
		RenumberProgram(currentProgram, buffer + 9);
		return;
	}
	
	/* If it gets here, it's either a variable assignment
	(i.e. "X = 7") or a system command (i.e. "ls") */
	if (IsAssignment(buffer))
		RunLET(buffer);
	else RunSYS(buffer);
}
