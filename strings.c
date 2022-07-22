#include "main.h"

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

void ShiftLeft(char* string, size_t start, size_t length) {
        size_t i;
        for (i = start + 1; i < length; i++) {
                string[i - 1] = string[i];
                string[i] = ' ';
        }
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

void StripSpaces(char* line) {
	bool inQuotes;
	uint8_t i, j, length;
	
	inQuotes = false;
	length = strlen(line);
	for (i=0; i<length; i++) {
		
		/* Skip anything between quotation marks */
		if (inQuotes) {
			if (line[i] == '"')
				inQuotes = false;
			continue;
		}
		if (line[i] == '"') {
			inQuotes = true;
			continue;
		}
		
		/* If it gets here, it's no in quotes.
		So if it's not a space, skip it. */
		if (line[i] != ' ') continue;
		
		/* If it gets here, it's a space to be stripped. */
		for (j=i; j<length; j++) {
			line[j] = line[j + 1];
		}
		i--;
	}
}


/************************************************************************/

void PrintCentered(const char* string) {
	int rows = 48, columns = 25;
	size_t i = 0, length = 40;
	
	GetScreenSize(&rows, &columns);
	length = (columns / 2) - strlen(string) / 2;
	for (i=0; i<length; i++) printf(" ");
	printf("%s", string);
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
