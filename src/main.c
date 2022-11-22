#include "main.h"

/**
 * The program starts here.
 */
int main() {
	/* Declare variables */
	char input[INPUT_BUFFER_SIZE];
	unsigned char tokens[INPUT_BUFFER_SIZE],
		* program = NULL;
	
	/* Show the title */
	#if USE_ANSI_ESCAPES
	ANSI_CLEAR();
	#endif
	printf("BREAKAWAY BASIC 1.0");
	NewLine();
	NewLine();
	
	/* Set up the program memory */
	program = calloc((size_t)PROGRAM_SIZE, 2);	/* 2 = sizeof(uint16_t) */
	if (program == NULL) {
		perror("Setup error (1)");
		return 1;
	}
	
	/* Main loop */
	while(true) {
		GetInput(input);
		Tokenize(input, tokens);
		UnTokenize(tokens, stdout);				// for now
		if (!RunLine(tokens)) break;
	}
	
	/* Final cleanup */
	free(program);
}
