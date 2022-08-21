#include "main.h"

char** currentProgram = NULL;
size_t currentLine = 0, currentSub = 0;
bool programMode = false;
extern uint8_t lastError;
int64_t subs[PROGRAM_MAX];
extern Variable* firstVar, * firstAlias;

/************************************************************************/

void Eval(char* line) {
	#if DEBUG_MODE
	printf("Line = \"%s\"\n", line);
	#endif
	
	StripSpaces(line);
	#if DEBUG_MODE
	printf("After StripSpaces: \"%s\"\n", line);
	#endif
	
	CombineStrings(line);
	#if DEBUG_MODE
	printf("After CombineStrings: \"%s\"\n", line);
	#endif
	
	ReplaceVariablesWithValues(line);
	#if DEBUG_MODE
	printf("After ReplaceVariablesWithValues: \"%s\"\n", line);
	#endif
	
	EvalMath(line);
	#if DEBUG_MODE
	printf("After EvalMath: \"%s\"\n", line);
	#endif
}

/************************************************************************/

void RunPRINT(char* line) {
	char output[BUFFER_MAX], temp[BUFFER_MAX];
	size_t i = 0, length = strlen(line), counter = 0, counter2 = 0;
	bool inQuotes = false;
	
	memset(output, 0, BUFFER_MAX);
	memset(temp, 0, BUFFER_MAX);
	for(; i<length; i++) {
		/* If it's a quotation mark, toggle inQuotes */
		if (line[i] == '"') {
			if (!inQuotes) {
				Eval(temp);
				snprintf(output + counter, BUFFER_MAX, "%s", temp);
				counter += strlen(temp);
				counter2 = 0;
				memset(temp, 0, BUFFER_MAX);
			}
			inQuotes = !inQuotes;
			continue;
		}
		
		/* Otherwise, if we're in quotes, append to the string */
		if (inQuotes) {
			output[counter] = line[i];
			counter++;
			continue;
		}
		
		/* If we're at the last char, and it's a semicolon, we're
		done - see the lines below (semicolong is like the -n switch
		in the "echo" command; it's like saying, "don't put a new
		line there." */
		if (line[i] == ';' && i + 1 == length) {
			Eval(temp);
			snprintf(output + counter, BUFFER_MAX, "%s", temp);
			counter += strlen(temp);
			counter2 = 0;
			memset(temp, 0, BUFFER_MAX);
			break;
		}
		
		/* Otherwise, add it to the temp string.
		This string, when we hit a quote or the end of the line,
		will be evaluated as variables/math stuff/functions etc. */
		temp[counter2] = line[i];
		counter2++;
	}
	Eval(temp);
	snprintf(output + counter, BUFFER_MAX, "%s", temp);
	counter += strlen(temp);
	
	/* Print it, and also a newline if the last char is not ';' */
	printf("%s", output);
	if (line[length - 1] != ';')
		NewLine();
}

/************************************************************************/

void RunIF(char* buffer) {
	/* Declare variables */
	char line[BUFFER_MAX],
		* end = NULL,
		* temp = NULL;
	float leftF = 0, rightF = 0;
	
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
	
	/* Handle equal */
	end = strstr(line, "=");
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
		
		/* And handle THEN/ELSE */
		then(line, leftF == rightF);
		return;
	}
	
	/* Handle not-equal */
	end = strstr(line, "<>");
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
		temp = CopySubstring(end + 2, strstr(end + 1, "THEN"));
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
		
		/* And handle THEN/ELSE */
		then(line, leftF != rightF);
		return;
	}
	
	/* Handle less-than */
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
		
		/* And handle THEN/ELSE */
		then(line, leftF < rightF);
		return;
	}
	
	/* Greater-than */
	end = strstr(line, ">");
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
		
		/* And handle THEN/ELSE */
		then(line, leftF > rightF);
		return;
	}
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
	
	/* HIDDEN ON/OFF - hidden text */
	if (STRING_EQUALS(buffer, "HIDDEN ON")) {
		printf("\033[8m");
		return;
	}
	if (STRING_EQUALS(buffer, "HIDDEN OFF")) {
		printf("\033[28m");
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
	
	/* REVERSE ON/OFF */
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
