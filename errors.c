#include "main.h"

extern uint8_t lastError;
extern bool programMode;
extern size_t currentLine;

/************************************************************************/

void SyntaxError() {
	printf("?SYNTAX ERROR");
	if (programMode)
		printf("IN %ld", currentLine);
	NewLine();
}

/************************************************************************/

void MemoryError() {
	printf("?MEMORY ERROR");
	if (programMode)
		printf("IN %ld", currentLine);
	NewLine();
}

/************************************************************************/

void OverflowError() {
	printf("?OVERFLOW ERROR");
	if (programMode)
		printf("IN %ld", currentLine);
	NewLine();
}

/************************************************************************/

/************************************************************************/

void TypeMismatch() {
	printf("?TYPE MISMATCH ERROR");
	if (programMode)
		printf("IN %ld", currentLine);
	NewLine();
}

/************************************************************************/

void PrintLastError() {
	switch(lastError) {
		case NO_ERROR: return;
		case SYNTAX_ERROR: SyntaxError(); return;
		case MEMORY_ERROR: MemoryError(); return;
		case TYPE_MISMATCH_ERROR: TypeMismatch(); return;
		case OVERFLOW_ERROR: OverflowError(); return;
		default: printf("%d\n", lastError);
	}
}
