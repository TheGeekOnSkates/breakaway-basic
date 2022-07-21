#include "main.h"

void ReplaceCHR(char* buffer) {
	/*
	Replace CHR$(number) with the character
	1. if (!ParensMatch) syntax error
	2. Replace variables with values
	3. Crunch numbers (so i.e. CHR$(3*(3+4)) becomes CHR$(21)
	4. If ! everything in parens is a digit, syntax error
	5. use atol (not atoi) so we can do Unicode chars
	6. replace with \"%lc\", the character
	*/
}
