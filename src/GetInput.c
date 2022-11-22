#include "main.h"

void GetInput(char* input) {
	/* Declare variables */
	char* temp = NULL;

	/* Clear the contents of the buffer */
	memset(input, 0, INPUT_BUFFER_SIZE);

	/* Get the user's input */
	fgets(input, INPUT_BUFFER_SIZE, stdin);

	/* Strip trailing new-line characters */
	temp = strchr(input, '\n');
	if (temp != NULL) temp[0] = '\0';
	temp = strchr(input, '\r');
	if (temp != NULL) temp[0] = '\0';
}
