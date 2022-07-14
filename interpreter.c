#include "main.h"

void Interpret(char* buffer) {
	char* token = NULL;
	/* Call strtok, using spaces as a delimiter. */
	
	if (STRING_EQUALS(buffer, "EXIT\n")) exit(0);
	if (STRING_STARTS_WITH(buffer, "SYS ")) {
		token = buffer + 4;
		system((const char*)token);
		return;
	}
	printf("Left off on interpreter.c");
	NewLine();
}

