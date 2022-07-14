#include "main.h"

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

void Interpret(char* buffer) {
	char* token = NULL;
	/* Call strtok, using spaces as a delimiter. */
	
	if (STRING_EQUALS(buffer, "EXIT\n")) exit(0);
	if (STRING_STARTS_WITH(buffer, "SYS ")) {
		token = buffer + 4;
		system((const char*)token);
		return;
	}
	printf("ParensMatch: %s\n", ParensMatch(buffer) ? "true" : "false");
	printf("Left off on interpreter.c");
	NewLine();
}

