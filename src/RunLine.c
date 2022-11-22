#include "main.h"

bool RunLine(unsigned char * tokens) {
	size_t i;
	for (i=0; i<INPUT_BUFFER_SIZE; i++) {
		
		/*
		Exit - the only situation where this function should return false,
		to tell the program the user wants to exit Breakaway BASIC
		*/
		if (tokens[i] == EXIT) return false;
		
		/* BOLD ON/OFF */
		if (tokens[i] == BOLD) {
			#if USE_ANSI_ESCAPES
			i++;
			if (tokens[i] == ON) {
				ANSI_BOLD_ON();
				goto CheckIfAtEnd;
			}
			if (tokens[i] == OFF) {
				ANSI_BOLD_OFF();
				goto CheckIfAtEnd;
			}
			else {
				printf("SYNTAX ERROR");
				NewLine();
				return true;
			}
			#else
			printf("Not supported");
			NewLine();
			goto CheckIfAtEnd;
			#endif
			
		}
		
		/* CLS (no parameters */
		if (tokens[i] == CLS) {
			#if USE_ANSI_ESCAPES
			ANSI_CLEAR();
			#else
			printf("Not supported");
			NewLine();
			#endif
			goto CheckIfAtEnd;
		}
	}
	return true;

CheckIfAtEnd:
	i++;
	if (tokens[i] != COLON && tokens[i] != NONE) {
		printf("SYNTAX ERROR");
		NewLine();
	}
	return true;
}
