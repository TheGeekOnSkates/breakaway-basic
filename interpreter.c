#include "main.h"

char** currentProgram = NULL;

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

bool IsUnsignedInt(char* string) {
	size_t i=0, length = strlen(string);
	for(; i<length; i++) {
		if (string[i] == '\n' && i + 1 == length) return true;
		if (string[i] < '0' || string[i] > '9') return false;
	}
	return true;
}

/************************************************************************/

void Interpret(char* buffer) {
	char* token = NULL;
	
	/* Call strtok, using spaces as a delimiter. */
	
	if (STRING_EQUALS(buffer, "EXIT\n")) exit(0);
	if (STRING_STARTS_WITH(buffer, "SYS ")) {
		token = buffer + 4;
		system((const char*)token);
		return;
	}
	token = strtok(buffer, " ");
	if (IsUnsignedInt(token)) {
		AddToProgram(currentProgram, buffer);
		return;
	}
	if (STRING_EQUALS(token, "LIST")) {
		ListProgram(currentProgram, buffer);
		return;
	}
	
	NewLine();
}

