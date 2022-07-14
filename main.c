#include "main.h"

int main(int argc, const char** argv) {
	char buffer[INPUT_BUFFER_SIZE];
	
	printf("BREAKAWAY BASIC 2022.07.14");
	NewLine(); NewLine();
	
	while(true) {
		printf("READY."); NewLine();
		memset(buffer, 0, INPUT_BUFFER_SIZE);
		fgets(buffer, 255, stdin);
		Interpret(buffer);
	}
	return 0;
}
