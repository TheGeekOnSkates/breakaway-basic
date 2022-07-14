#include "main.h"

char** currentProgram = NULL;
extern uint8_t lastError;


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

void Interpret(char* buffer) {
	char* token = NULL;
	
	if (STRING_EQUALS(buffer, "EXIT\n")) {
		FreeProgram(currentProgram);
		exit(0);
	}
	
	if (STRING_STARTS_WITH(buffer, "SYS ")) {
		token = buffer + 4;
		system((const char*)token);
		return;
	}
	
	if (buffer[0] >= '0' && buffer[0] <= '9') {
		AddToProgram(currentProgram, buffer);
		return;
	}
	
	if (STRING_STARTS_WITH(buffer, "LIST")) {
		ListProgram(currentProgram, buffer + 4);
		if (lastError == SYNTAX_ERROR)
			printf("?SYNTAX  ERROR");
		return;
	}
	
	token = strstr(buffer, " ");
	if (token == NULL) {
		printf("?SYNTAX ERROR");
		return;
	}
	printf("?SYNTAX ERROR");
}

