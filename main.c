#include "main.h"

int main() {
	/* Declare variables */
	/* char title[480], * temp; */
	char code[LINE_SIZE], configPath[512];
	Program program, aliases;
	VarList variables;
	Line line;
	FILE* file = NULL;
	
	/* Clear all memory (no "garbage characters") */
	memset(program, 0, PROGRAM_SIZE * LINE_SIZE);
	memset(aliases, 0, PROGRAM_SIZE * LINE_SIZE);
	memset(variables, 0, VARIABLE_SIZE * sizeof(Variable));
	
	/* Run the auto-run file is there is one */
	/* If there is a config file, LOAD and RUN it */
	get_autorun_file(configPath);
	file = fopen(configPath, "r");
	if (file != NULL) {
		while(true) {
			memset(code, 0, LINE_SIZE);
			fgets(code, LINE_SIZE, file);
			if (feof(file)) break;
			else if (ferror(file)) {
				perror("?ERROR READING AUTO-RUN FILE");
				fclose(file);
				break;
			}
			else if (code[0] >= '0' && code[0] <= '9')
				run(program, aliases, variables, code, false);
			else {
				show_error("ILLEGAL DIRECT MODE ERROR");
				fclose(file);
				memset(program, 0, PROGRAM_SIZE * LINE_SIZE);
				memset(variables, 0, 26 * sizeof(Variable));
				break;
			}
		}
		strncpy(code, "RUN", LINE_SIZE);
		run(program, aliases, variables, code, false);
		memset(program, 0, PROGRAM_SIZE * LINE_SIZE);
		memset(variables, 0, 26 * sizeof(Variable));
		fclose(file);
	}
	else printf("READY.\n");
	
	/* Main event loop - prompt the user for input, then run it */
	while(true) {
		/* Get the user's input */
		memset(line, 0, LINE_SIZE);
		ReadLine(line);
		run(program, aliases, variables, line, false);
	}
	return 0;
}
