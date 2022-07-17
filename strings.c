#include "main.h"

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
