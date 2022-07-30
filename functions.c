#include "main.h"

void ReplaceROWSandCOLS(char* buffer) {
	int cols = -1, rows = -1;
	uint16_t start = 0;
	char* temp = NULL;
	
	GetScreenSize(&rows, &cols);
	
	while(true) {
		temp = strstr(buffer, "ROWS()");
		if (temp == NULL) break;
		start = temp - buffer;
		ReplaceWithFloat(buffer, start, start + 6, (float)rows);
	}
	
	while(true) {
		temp = strstr(buffer, "COLS()");
		if (temp == NULL) break;
		start = temp - buffer;
		ReplaceWithFloat(buffer, start, start + 6, (float)cols);
	}
}

void ReplaceCHR(char* buffer) {
	/*
	Replace CHR$(number) with the character
	1. if (!ParensMatch) syntax error
	2. Replace variables with values
	3. Crunch numbers (so i.e. CHR$(3*(3+4)) becomes CHR$(21)
	4. If ! everything in parens is a digit, syntax error
	5. use atol (not atoi) so we can do Unicode chars
	6. replace with \"%lc\", the character
	*/
}

void ReplaceSTR(char* line) {
	/* Declare variables */
	/*
	char temp[BUFFER_MAX], replacement[BUFFER_MAX];
	char* functionName;
	size_t i, start, end;
	bool pastDot;
	#if DEBUG_MODE
	printf("line = \"%s\"\n", line);
	#endif
	
	functionName = strstr(line, "STR$");
	if (functionName == NULL) return;
	start = functionName - line;
	
	#if DEBUG_MODE
	printf("Before ReplaceSTR: \"%s\"\n", line);
	printf("functionName = \"%s\"\n", functionName);
	printf("start = %d\n", start);
	#endif
	
	pastDot = false;
	for (i=start + 5; i<BUFFER_MAX; i++) {
		if (IsNumeric(line[i])) continue;
		if (!pastDot && line[i] == '.') {
			pastDot = true;
			continue;
		}
		end = i;
		break;
	}
	#if DEBUG_MODE
	printf("end is at %d\n", end);
	#endif
	memset(replacement, 0, BUFFER_MAX);
	snprintf(replacement, BUFFER_MAX, "\"%s\"", functionName + 4);
	#if DEBUG_MODE
	printf("replacement = \"%s\"\n", replacement);
	#endif
	ReplaceWithString(line, start, end, replacement);
	*/
}

void ReplaceFunctions(char* buffer) {
	ReplaceROWSandCOLS(buffer);
	/* Replace others later :) */
}
