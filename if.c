#include "main.h"

extern size_t currentLine, currentSub;
extern uint8_t lastError;

void then(char* line, bool answer) {
	char* end = NULL;
	if (answer) {
		end = strstr(line, "THEN") + 4;
		#if DEBUG_MODE
		printf("end = \"%s\"\n", end);
		#endif
		if (end[0] < '0' || end[0] > '9') {
			/* Non-number after THEN */
			lastError = SYNTAX_ERROR;
		}
		else currentLine = atol(end) - 1;
		return;
	}
	
	/* If it gets here, look for an ELSE */
	end = strstr(line, "ELSE") + 4;
	if (end == NULL) return;
	if (end[0] < '0' || end[0] > '9') {
		/* Non-number after THEN */
		lastError = SYNTAX_ERROR;
	}
	else currentLine = atol(end) - 1;
}
