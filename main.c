#include "main.h"

extern char** currentProgram;
extern int64_t subs[PROGRAM_MAX];
extern Variable* firstVar, * firstAlias;

int main(int argc, const char** argv) {
	/* Declare variables */
	char buffer[BUFFER_MAX];
	char* temp = NULL;
	size_t i = 0;
	
	/* Set up the program's memory */
	currentProgram = CreateProgram();
	if (currentProgram == NULL) {
		perror("CreateProgram failed");
		return 0;
	}
	srand(time(NULL));
	
	/* Clear the "subs" array for subroutines */
	for(; i<PROGRAM_MAX; i++) {
		subs[i] = -1;
	}
	
	/* Set a couple aliases */
	firstAlias = CreateVariable("ECHO=echo");
	
	/* Show the title message */
	printf("\033[H\033[J");
	PrintCentered("**** BREAKAWAY BASIC 2022.07.24.3 ****");
	NewLine();
	sprintf(buffer, "%lu BYTES FREE", GetBytesFree());
	PrintCentered(buffer);
	NewLine();
	
	/* Main event loop */
	while(true) {
		/* Let the user know we're ready for input */
		printf("READY.");
		NewLine();
		
		/* Actually prompt the user for input */
		memset(buffer, 0, INPUT_BUFFER_SIZE);
		/* fgets(buffer, INPUT_BUFFER_SIZE, stdin); */
		temp = ReadLine("");
		if (temp == NULL) {
			MemoryError();
			return 0;
		}
		
		/* And interpret that input */
		Interpret(temp);
		AddToHistory(temp);
		PrintLastError();
		free(temp);
		temp = NULL;
	}
	
	/* If it gets here (which it actually shouldn't, we're done. */
	printf("\033[0m");		/* RESET */
	printf("\033[H\033[J");		/* CLEAR */
	FreeProgram(currentProgram);
	FreeVariables(firstVar);
	FreeVariables(firstAlias);
	return 0;
}
