#include "main.h"

/************************************************************************/

bool IsAssignment(char* line) {
	size_t i=0, length = strlen(line);
	bool inQuotes = false;
	for(; i<length; i++) {
		if (line[i] == '"')
			inQuotes = !inQuotes;
		if (inQuotes) continue;
		if (line[i] == '=') return true;
	}
	return false;
}

/************************************************************************/

char* CopySubstring(char* from, char* to) {
	/* Declare variables */
	size_t i = 0, length = 0;
	char* result = NULL;
	
	/* Handle obvious user errors */
	if (from == NULL || to == NULL) return NULL;
	
	/* Allocate memory */
	length = to - from;
	result = calloc(length + 1, sizeof(char));
	if (result == NULL) return NULL;
	
	/* Copy the data into it */
	for (i=0; i<length; i++) result[i] = from[i];
	
	/* And we're done */
	return result;
}

/************************************************************************/

void CombineStrings(char* line) {
	char* temp;
	uint16_t i;
	while(true) {
		temp = strstr(line, "\"+\"");
		if (temp == NULL) break;
		for (i=0; i<3; i++)
			ShiftLeft(line, temp - line, strlen(line));
	}
}

/************************************************************************/

