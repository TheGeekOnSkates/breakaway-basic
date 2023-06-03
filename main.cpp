/***********************************************************************/
/* PRE-PROCESSOR MACROS                                                */
/***********************************************************************/

/* If defined, include Linux-specific dependencies */
#define TARGET_LINUX 1

/* If defined, include GNU Readling */
#define USE_READLINE 1



/***********************************************************************/
/* DEPENDENCIES                                                        */
/***********************************************************************/

#include "strings.h"
#include <vector>
#include <string>
#ifdef TARGET_LINUX
	#include <unistd.h>
	#include <fcntl.h>
	#include <termios.h>
	#include <sys/resource.h>
	#include <sys/ioctl.h>
	#include <pwd.h>
#endif
#ifdef USE_READLINE
	#include <readline/readline.h>
	#include <readline/history.h>
#endif

/***********************************************************************/
/* GLOBAL VARIABLES AND COMPILE-TIME CONSTANTS                         */
/***********************************************************************/

/* Stores the return value of the last call to system() */
int lastReturnCode = 0;

/* Used with and without Readline; this is the size of the input buffer */
const int LINE_SIZE = 512;



/***********************************************************************/
/* CUSTOM DATA TYPE DEFINITIONS                                        */
/***********************************************************************/

/**
 * Stores info about a for-loop in memory
 * @remarks Eventually, this same structure can be used for other variables.
 * That's why I'm calling it a Var even though in v1.0 it's just for loops.
 * Yes it's 3 extra ints that per variable, but what's 12 bytes on a modern
 * Linux or other OS?  This thing wouldn't even compile on retro stuff, so I
 * think we can spare the RAM (especially since programs are not likely to
 * use more than 20-30 variables tops). :D
 */
typedef struct _variable {
	std::string name;	/** The name of the variable */
	int start;			/** The initial value (for for-loops) */
	int end;			/** The last/max value (for for-loops) */
	int current;		/** The current value (for for-loops) */
	int step;			/** The step to run in a for-loop */
	size_t lineNumber;	/** The line number to go back to (for-loops) */
} Var;




/***********************************************************************/
/* FUNCTION DEFINITIONS                                                */
/***********************************************************************/

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
	lastReturnCode = system((const char*)here);
}

int main() {
	char buffer[LINE_SIZE], prompt[20],
		* newline = NULL, * currentLine = NULL;
	std::vector<std::string> program;
	std::vector<size_t> gosubStack;
	std::vector<Var> vars;
	int lineNumber = 0;
	size_t i = 0, j = 0, programSize = 0, listFrom = 0, listTo = 0;
	bool foundIt = false;
	
	/* For now, I want my prompt to be "READY." */
	memset(prompt, 0, 20);
	strcpy(prompt, "\nREADY\n");

	/* This prevents crashes if you do a LIST before you add stuff :D */
	program.push_back("");
	
	printf("BREAKAWAY BASIC 1.0-alpha\n\n");
	while(true) {
		/* Read user input and strip out new lines */
#ifdef USE_READLINE
		char* temp = readline("");
		if (temp == NULL) {
			printf("?MEMORY ERROR\n");
			return 0;
		}
		strncpy(buffer, temp, LINE_SIZE);
		add_history(buffer);
		free(temp);
#else
		memset(buffer, 0, LINE_SIZE);
		fgets(buffer, LINE_SIZE, stdin);
		newline = strchr(buffer, '\n');
		if (newline != NULL) newline[0] = '\0';
#endif
		
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
				
				// FOR starts a for-loop, obviously :) */
				if (StringStartsWith(currentLine, "for")) {
					/* Move past FOR and any spaces */
					currentLine += 3;
					while(currentLine[0] == ' ') currentLine++;
					
					/* Get the name of the variable */
					Var v;
					v.lineNumber = i;
					while(currentLine[0] != ' ' && currentLine[0] != '='
					&& currentLine[0] != '\0') {
						v.name += currentLine[0];
						currentLine++;
					}
					
					/* Move past any spaces and past the equals sign */
					while(currentLine[0] == ' ') currentLine++;
					if (currentLine[0] != '=') {
						printf("?SYNTAX ERROR IN %zd", i);
						break;
					}
					currentLine++;
					while(currentLine[0] == ' ') currentLine++;
					
					/* Get the start number */
					if (currentLine[0] < '0' || currentLine[0] > '9') {
						/*
						NOTE: Eventually, I'll want to support variables
						here (i.e. FOX X = Y TO Z) but not just yet.
						*/
						printf("?SYNTAX ERROR IN %zd", i);
						break;
					}
					v.start = v.current = atoi(currentLine);

					while(currentLine[0] >= '0' && currentLine[0] <= '9')
						currentLine++;
					while(currentLine[0] == ' ') currentLine++;
					
					/* Move past TO (or throw a syntax error if missing) */
					if (!StringStartsWith(currentLine, "to")) {
						printf("?SYNTAX ERROR IN %zd", i);
						break;
					}
					currentLine += 2;
					while(currentLine[0] == ' ') currentLine++;
					
					/* Get the end number */
					if (currentLine[0] < '0' || currentLine[0] > '9') {
						/*
						NOTE: Eventually, I'll want to support variables
						here (i.e. FOX X = Y TO Z) but not just yet.
						*/
						printf("?SYNTAX ERROR IN %zd", i);
						break;
					}
					v.end = atoi(currentLine);

					while(currentLine[0] >= '0' && currentLine[0] <= '9')
						currentLine++;
					while(currentLine[0] == ' ') currentLine++;
					
					/* If there is no STEP, we're done */
					if (!StringStartsWith(currentLine, "step")) {
						v.step = 1;
						vars.push_back(v);
						continue;
					}
					
					/* Otherise, get it.  THEN we're done :) */
					currentLine += 4;
					while(currentLine[0] == ' ') currentLine++;
					if (currentLine[0] < '0' || currentLine[0] > '9') {
						/*
						NOTE: Eventually, I'll want to support variables
						here (i.e. FOX X = Y TO Z STEP Q) but not now :)
						*/
						printf("?SYNTAX ERROR IN %zd", i);
						break;
					}
					v.step = atoi(currentLine);
					v.step = 1;
					vars.push_back(v);
					continue;
				}
				
				/* NEXT is the other half of FOR, obviously :) */
				if (StringStartsWith(currentLine, "next")) {
					currentLine += 4;
					while(currentLine[0] == ' ') currentLine++;
					
					/* Next, get the name of the variable */
					std::string name = "";
					while(currentLine[0] != ' '
					&& currentLine[0] != '\0') {
						name += currentLine[0];
						currentLine++;
					}
					
					/* Now look for a variable matching that name */
					foundIt = false;
					for (j=0; j<vars.size(); j++) {
						if (vars[j].name != name) continue;
						foundIt = true;
						
						/* We found it, so move the line number back to
						Where it was right after the FOR.  Note that in
						most BASICs, the end number also gets included in
						the loop (unlike in C), which is why the + 1 */
						vars[j].current += vars[j].step;
						if (vars[j].current == vars[j].end + 1) break;
						i = vars[j].lineNumber;
						break;
					}
					
					/* If found, we're done; if not, it's an error */
					if (foundIt) continue;
					printf("?NEXT WITHOUT FOR ERROR IN %zd", i);
					break;
				}
				
				/* GOTO should change i, obviously :) */
				if (StringStartsWith(currentLine, "goto")) {
					/* Move past GOTO and any spaces */
					currentLine += 4;
					while(currentLine[0] == ' ') currentLine++;
					
					/* TO-DO: When I get variables set up, add support for
					GOTO myVariable - but for now, that's an error */
					if (currentLine[0] < '0' || currentLine[0] > '9') {
						printf("SYNTAX ERROR IN LINE %zd\r\n", i);
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
				
				/* GOSUB works kinda similar */
				if (StringStartsWith(currentLine, "gosub")) {
					/* Move past GOTO and any spaces */
					currentLine += 5;
					while(currentLine[0] == ' ') currentLine++;
					
					/* TO-DO: When I get variables set up, add support for
					GOSUB myVariable - but for now, that's an error */
					if (currentLine[0] < '0' || currentLine[0] > '9') {
						printf("SYNTAX ERROR ON LINE %zd\r\n", i);
						break;
					}
					
					/* Otherwise, get the line number, subtract 1 (because
					of the "i++") and set i to that */
					gosubStack.push_back(i);
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
				
				/* And here's its counterpart, RETURN */
				if (StringEquals(currentLine, "return")) {
					if (!gosubStack.size()) {
						printf("RETURN WITHOUT GOSUB IN %zd\n", i);
						break;
					}
					i = gosubStack.back();
					gosubStack.pop_back();
					continue;
				}
				
				/* END ends the program, obviously :) */
				if (StringEquals(currentLine, "end")) break;
				
				/* Otherwise, run the line */
				RunLine(currentLine);
			}
			printf("%s", prompt);
			continue;
		}
		
		/* If it's not one of those, the next thing we need to do is figure
		out if we're in "direct mode" or "program mode". */
		if (buffer[0] >= '0' && buffer[0] <= '9') {
			lineNumber = atoi(buffer);
			if (lineNumber == 0) {
				/* Note: This could also be caused by atoi failing, though
				there's no reason if char 0 is between '0' and '9' */
				printf("?LINE NUMBERS START AT 1");
				continue;
			}
			if (program.size() < (size_t)lineNumber)
				for (i=0; i<(size_t)lineNumber + 10; i++)
					program.push_back("");
			currentLine = buffer;
			while(currentLine[0] >= '0' && currentLine[0] < '9')
				currentLine++;
			while(currentLine[0] == ' ') currentLine++;
			if (strlen(currentLine) == 0)
				program[lineNumber] = "";
			else program[lineNumber] = buffer;
		}
		else {
			RunLine(buffer);
			printf("%s", prompt);
		}
	}
	return 0;
}

