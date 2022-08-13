#include "main.h"

extern uint8_t lastError;
extern bool programMode;
extern size_t currentLine;

/************************************************************************/

void DivBy0Error() {
	printf("?DIVISION BY ZERO ERROR");
	if (programMode)
		printf("IN %ld", currentLine);
	NewLine();
}

/************************************************************************/

void IllegalDirectError() {
	printf("?ILLEGAL DIRECT ERROR");
	if (programMode)
		printf("IN %ld", currentLine);
	NewLine();
}

/************************************************************************/

void IllegalQtyError() {
	printf("?ILLEGAL QUANTITY ERROR");
	if (programMode)
		printf("IN %ld", currentLine);
	NewLine();
}

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

void SystemError() {
	perror("?SYSTEM ERROR");
	if (programMode)
		printf("IN %ld", currentLine);
	NewLine();
}

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
		case ILLEGAL_DIRECT_ERROR: IllegalDirectError(); return;
		case ILLEGAL_QTY_ERROR: IllegalQtyError(); return;
		case OVERFLOW_ERROR: OverflowError(); return;
		case SYSTEM_ERROR: SystemError(); return;
		case DIVISION_BY_SERO_ERROR: DivBy0Error(); return;
		default: printf("%d\n", lastError);
	}
}
