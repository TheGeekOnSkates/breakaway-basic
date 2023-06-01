#include "strings.h"
#include <vector>
#include <unistd.h>

typedef std::vector<char[80]> Program;

void RunLine(char* line) {
	char* here = NULL;
	if (StringStartsWith(line, "cd")) {
		here = line + 2;
		while(here[0] == ' ') here++;
		chdir(here);
	}
	else system((const char*)line);
}

int main() {
	char buffer[80], * newline;
	bool isProgramMode = false;
	Program program;

	printf("BREAKAWAY BASIC 1.0\n\n");
	while(true) {
		/* Read user input and strip out new lines */
		memset(buffer, 0, 80);
		fgets(buffer, 80, stdin);
		newline = strchr(buffer, '\n');
		if (newline != NULL) newline[0] = '\0';
		
		/* EXIT, BYE, or QUIT exit the program. */
		if (
			StringEquals(buffer, "exit")
			|| StringEquals(buffer, "quit")
			|| StringEquals(buffer, "bye")
		) break;
		
		/* If it's not one of those, the next thing we need to do is figure
		out if we're in "direct mode" or "program mode". */
		isProgramMode = buffer[0] >= '0' && buffer[0] < '9';
		if (isProgramMode)
			printf("Program mode\n");
		else RunLine(buffer);
	}
	return 0;
}
