#include "main.h"

extern char** currentProgram;
extern int64_t subs[PROGRAM_MAX];

void PrintCentered(const char* string) {
	int rows = 48, columns = 25;
	size_t i = 0, length = 40;
	
	GetScreenSize(&rows, &columns);
	length = (columns / 2) - strlen(string) / 2;
	for (i=0; i<length; i++) printf(" ");
	printf("%s", string);
}

int main(int argc, const char** argv) {
	/* Declare variables */
	char buffer[BUFFER_MAX];
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
	
	/* Show the title message */
	printf("\033[H\033[J");
	PrintCentered("** BREAKAWAY BASIC 2022.07.15 **");
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
		fgets(buffer, INPUT_BUFFER_SIZE, stdin);
		
		/* And interpret that input */
		Interpret(buffer);
	}
	
	/* If it gets here (which it actually shouldn't, we're done. */
	FreeProgram(currentProgram);
	return 0;
}
