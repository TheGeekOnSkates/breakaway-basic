#include "main.h"

extern char** currentProgram;

int main(int argc, const char** argv) {
	char buffer[INPUT_BUFFER_SIZE * 8];
	currentProgram = CreateProgram();
	if (currentProgram == NULL) {
		perror("CreateProgram failed");
		return 0;
	}
	srand(time(NULL));
	
	printf("BREAKAWAY BASIC 2022.07.14");
	NewLine();
	
	while(true) {
		NewLine();
		printf("READY.");
		NewLine();
		memset(buffer, 0, INPUT_BUFFER_SIZE);
		fgets(buffer, 255, stdin);
		Interpret(buffer);
	}
	FreeProgram(currentProgram);
	return 0;
}
