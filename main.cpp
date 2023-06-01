#include "strings.h"
#include <vector>
#include <string>
#include <unistd.h>

void RunLine(char* line) {
	char* here = NULL;

	/* If we're in program mode, skip past the line number */
	here = line;
	while(here[0] >= '0' && here[0] <= '9') here++;
	while(here[0] == ' ') here++;
	
	/* "rem" is a comment - do nothing */
	if (StringStartsWith(here, "rem")) return;
	
	/* "cd" is a built-in shell feature, not an external program, so I need
	to actually DIY it, and I'm doing that here */
	if (StringStartsWith(here, "cd")) {
		here += 2;
		while(here[0] == ' ') here++;
		chdir(here);
		return;
	}
	
	/* And run it */
	system((const char*)here);
}

int main() {
	char buffer[80], * newline;
	bool isProgramMode = false;
	std::vector<std::string> program;
	int lineNumber = 0;
	size_t i = 0, programSize = 0;

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
		
		/* RUN runs the program, obviously :) */
		if (StringEquals(buffer, "run")) {
			programSize = program.size();
			for (i=0; i<programSize; i++) {
				RunLine((char*)program[i].c_str());
			}
			continue;
		}
		
		/* If it's not one of those, the next thing we need to do is figure
		out if we're in "direct mode" or "program mode". */
		isProgramMode = buffer[0] >= '0' && buffer[0] < '9';
		if (isProgramMode) {
			lineNumber = atoi(buffer);
			if (lineNumber == 0) {
				/* Note: This could also be caused by atoi failing, though
				there's no reason if char 0 is between '0' and '9' */
				printf("LINE NUMBERS START AT 1.\n");
				continue;
			}
			if (program.size() < (size_t)lineNumber)
				program.resize((size_t)lineNumber + 1);
			program[lineNumber] = buffer;
		}
		else RunLine(buffer);
	}
	return 0;
}
