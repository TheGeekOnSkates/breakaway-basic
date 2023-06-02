#include "strings.h"
#include <vector>
#include <string>
#include <unistd.h>

void RunLine(char* line) {
	char* here = line;

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
	char buffer[80], * newline = NULL, * currentLine = NULL;
	std::vector<std::string> program;
	int lineNumber = 0;
	size_t i = 0, programSize = 0, listFrom = 0, listTo = 0;

	/* This prevents crashes if you do a LIST before you add stuff :D */
	program.push_back("");
	
	printf("BREAKAWAY BASIC 1.0\n\n");
	while(true) {
		/* Read user input and strip out new lines */
		printf("READY.\n");
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
		
		/* LIST lists the program, obviously :) */
		if (StringStartsWith(buffer, "list")) {
			/* Start out covering the entire program */
			listFrom = 0;
			listTo = programSize = program.size() - 1;
			
			/* Move past the word LIST and any spaces */
			currentLine = buffer + 4;
			while (currentLine[0] == ' ') currentLine++;
			
			/* If there's a number there, we want something other than
			the entire program.  So edit from/to based on those. */
			if (currentLine[0] >= '0' && currentLine[0] <= '9') {
				
				/* Get the starting number */
				listFrom = atoi(currentLine);
				if (listFrom > programSize) {
					printf("Error reading line number\n");
					continue;
				}
				
				/* In case there's no end number, make them the same */
				listTo = listFrom;
				
				/* If there's a dash after that, we need to set the end
				number too */
				currentLine = strchr(currentLine, '-');
				if (currentLine != NULL) {
					/* Move past the dash and any spaces */
					currentLine++;
					while (currentLine[0] == ' ') currentLine++;
					
					/* And get the end number */
					listTo = atoi(currentLine);
					if (listTo > programSize) {
						printf("Error reading line number\n");
						continue;
					}
				}
			}
			
			/* Now with our start and end numbers defined, list the code */
			for (i=listFrom; i<=listTo; i++) {
				if (program[i] == "") continue;
				printf(" %s\n", program[i].c_str());
			}
			
			/* And we're done with LIST */
			continue;
		}
		
		/* NEW clears the program, obviously :) */
		if (StringEquals(buffer, "new")) {
			program.clear();
			program.push_back("");
			continue;
		}
		
		/* RUN runs the program, obviously :) */
		if (StringEquals(buffer, "run")) {
			programSize = program.size();
			for (i=0; i<programSize; i++) {
				
				/* Get the code after the line number */
				currentLine = (char*)program[i].c_str();
				while(currentLine[0] >= '0' && currentLine[0] <= '9')
					currentLine++;
				while(currentLine[0] == ' ') currentLine++;
	
				/* GOTO should change i, obviously :) */
				if (StringStartsWith(currentLine, "goto")) {
					/* Move past GOTO and any spaces */
					currentLine += 4;
					while(currentLine[0] == ' ') currentLine++;
					
					/* TO-DO: When I get variables set up, add support for
					GOTO myVariable - but for now, that's an error */
					if (currentLine[0] < '0' || currentLine[0] > '9') {
						printf("Syntax error on line %zd\r\n", i);
						break;
					}
					
					/* Otherwise, get the line number, subtract 1 (because
					of the "i++") and set i to that */
					i = (size_t)atoi(currentLine) - 1;
					
					/* If users enter a number that is greater than the size
					of the program, or atoi fails, don't crash :D */
					if (i > programSize) {
						printf("Line number out of bounds: %zd\n", i);
						break;
					}
					
					/* Otherwise, keep running */
					continue;
				}
				
				/* Otherwise, run the line */
				RunLine(currentLine);
			}
			continue;
		}
		
		/* If it's not one of those, the next thing we need to do is figure
		out if we're in "direct mode" or "program mode". */
		if (buffer[0] >= '0' && buffer[0] <= '9') {
			lineNumber = atoi(buffer);
			if (lineNumber == 0) {
				/* Note: This could also be caused by atoi failing, though
				there's no reason if char 0 is between '0' and '9' */
				printf("LINE NUMBERS START AT 1.\n");
				continue;
			}
			if (program.size() < (size_t)lineNumber)
				for (i=0; i<(size_t)lineNumber + 10; i++)
					program.push_back("");
			program[lineNumber] = buffer;
		}
		else RunLine(buffer);
	}
	return 0;
}

