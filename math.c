#include "main.h"

extern uint8_t lastError;

void ReplaceABS(char* line) {
	/* Declare variables */
	char* functionName;
	char temp[BUFFER_MAX];
	size_t i, start, end;
	bool pastDot, pastSign;
	float answer;
	
	/* Get the position of the function name */
	functionName = strstr(line, "ABS");
	if (functionName == NULL) return;
	start = functionName - line;
	
	#if DEBUG_MODE
	printf("Before ReplaceABS: \"%s\"\n", line);
	printf("functionName = \"%s\"\n", functionName);
	printf("start = %ld\n", start);
	#endif
	
	/* Get the number after the function name */
	pastDot = false; pastSign = false;
	for (i=start + 3; i<BUFFER_MAX; i++) {
		if (IsNumeric(line[i])) continue;
		if (!pastDot && line[i] == '.') {
			pastDot = true;
			continue;
		}
		if (!pastSign && line[i] == '-') {
			pastSign = true;
			continue;
		}
		end = i;
		break;
	}
	#if DEBUG_MODE
	printf("end is at %ld\n", end);
	#endif
	
	/* Do the actual math, replace the string and we're done */
	answer = atof(functionName + 3);
	answer = fabsf(answer);
	if (answer == INFINITY) {
		lastError = OVERFLOW_ERROR;
		return;
	}
	ReplaceWithFloat(line, start, end, answer);
}

void ReplaceATN(char* line) {
	/* Declare variables */
	char temp[BUFFER_MAX];
	char* functionName;
	size_t i, start, end;
	bool pastDot, pastSign;
	float answer;
	
	/* Get the position of the function name */
	functionName = strstr(line, "ATN");
	if (functionName == NULL) return;
	start = functionName - line;
	
	#if DEBUG_MODE
	printf("Before ReplaceATN: \"%s\"\n", line);
	printf("functionName = \"%s\"\n", functionName);
	printf("start = %ld\n", start);
	#endif
	
	/* Get the end position (the number to be replaced */
	pastDot = false; pastSign = false;
	for (i=start + 3; i<BUFFER_MAX; i++) {
		if (IsNumeric(line[i])) continue;
		if (!pastDot && line[i] == '.') {
			pastDot = true;
			continue;
		}
		if (!pastSign && line[i] == '-') {
			pastSign = true;
			continue;
		}
		end = i;
		break;
	}
	#if DEBUG_MODE
	printf("end is at %ld\n", end);	
	#endif
	
	/* Do the math, replace the string, and we're done */
	answer = atof(functionName + 3);
	answer = atanf(answer);
	if (answer == INFINITY) {
		strncpy(line, "?OVERFLOW ERROR", BUFFER_MAX);
		return;
	}
	ReplaceWithFloat(line, start, end, answer);
}

void ReplaceCOS(char* line) {
	char temp[BUFFER_MAX];
	char* functionName;
	size_t i, start, end;
	bool pastDot, pastSign;
	float answer;
	
	functionName = strstr(line, "COS");
	if (functionName == NULL) return;
	start = functionName - line;
	
	#if DEBUG_MODE
	printf("Before ReplaceCOS: \"%s\"\n", line);
	printf("functionName = \"%s\"\n", functionName);
	printf("start = %ld\n", start);
	#endif
	
	pastDot = false; pastSign = false;
	for (i=start + 3; i<BUFFER_MAX; i++) {
		if (IsNumeric(line[i])) continue;
		if (!pastDot && line[i] == '.') {
			pastDot = true;
			continue;
		}
		if (!pastSign && line[i] == '-') {
			pastSign = true;
			continue;
		}
		end = i;
		break;
	}
	#if DEBUG_MODE
	printf("end is at %ld\n", end);	
	#endif
	answer = atof(functionName + 3);
	answer = cosf(answer);
	if (answer == INFINITY) {
		strncpy(line, "?OVERFLOW ERROR", BUFFER_MAX);
		return;
	}
	ReplaceWithFloat(line, start, end, answer);
}

void ReplaceEXP(char* line) {
	char temp[BUFFER_MAX];
	char* functionName;
	size_t i, start, end;
	bool pastDot, pastSign;
	float answer;
	
	functionName = strstr(line, "EXP");
	if (functionName == NULL) return;
	start = functionName - line;
	
	#if DEBUG_MODE
	printf("Before ReplaceEXP: \"%s\"\n", line);
	printf("functionName = \"%s\"\n", functionName);
	printf("start = %ld\n", start);
	#endif
	
	pastDot = false; pastSign = false;
	for (i=start + 3; i<BUFFER_MAX; i++) {
		if (IsNumeric(line[i])) continue;
		if (!pastDot && line[i] == '.') {
			pastDot = true;
			continue;
		}
		if (!pastSign && line[i] == '-') {
			pastSign = true;
			continue;
		}
		end = i;
		break;
	}
	#if DEBUG_MODE
	printf("end is at %ld\n", end);	
	#endif
	answer = atof(functionName + 3);
	answer = expf(answer);
	if (answer == INFINITY) {
		lastError = OVERFLOW_ERROR;
		return;
	}
	ReplaceWithFloat(line, start, end, answer);
}

void ReplaceINT(char* line) {
	char temp[BUFFER_MAX];
	char* functionName;
	size_t i, start, end;
	bool pastDot, pastSign;
	int answer;
	
	functionName = strstr(line, "INT");
	if (functionName == NULL) return;
	start = functionName - line;
	
	#if DEBUG_MODE
	printf("Before ReplaceINT: \"%s\"\n", line);
	printf("functionName = \"%s\"\n", functionName);
	printf("start = %ld\n", start);
	#endif
	
	pastDot = false; pastSign = false;
	for (i=start + 3; i<BUFFER_MAX; i++) {
		if (IsNumeric(line[i])) continue;
		if (!pastDot && line[i] == '.') {
			pastDot = true;
			continue;
		}
		if (!pastSign && line[i] == '-') {
			pastSign = true;
			continue;
		}
		end = i;
		break;
	}
	#if DEBUG_MODE
	printf("end is at %ld\n", end);	
	#endif
	answer = atoi(functionName + 3);
	if (answer == INFINITY) {
		strncpy(line, "?OVERFLOW ERROR", BUFFER_MAX);
		return;
	}
	ReplaceWithFloat(line, start, end, (float)answer);
}

void ReplaceLOG(char* line) {
	char temp[BUFFER_MAX];
	char* functionName;
	size_t i, start, end;
	bool pastDot, pastSign;
	float answer;
	
	functionName = strstr(line, "LOG");
	if (functionName == NULL) return;
	start = functionName - line;
	
	#if DEBUG_MODE
	printf("Before ReplaceLOG: \"%s\"\n", line);
	printf("functionName = \"%s\"\n", functionName);
	printf("start = %ld\n", start);
	#endif
	
	pastDot = false; pastSign = false;
	for (i=start + 3; i<BUFFER_MAX; i++) {
		if (IsNumeric(line[i])) continue;
		if (!pastDot && line[i] == '.') {
			pastDot = true;
			continue;
		}
		if (!pastSign && line[i] == '-') {
			pastSign = true;
			continue;
		}
		end = i;
		break;
	}
	#if DEBUG_MODE
	printf("end is at %ld\n", end);
	#endif
	answer = atof(functionName + 3);
	answer = logf(answer);
	if (answer == INFINITY || answer == -INFINITY) {
		lastError = OVERFLOW_ERROR;
		return;
	}
	if (isnan(answer)) {
		lastError = ILLEGAL_QTY_ERROR;
		return;
	}
	#if DEBUG_MODE
	printf("answer := %g\n", answer);
	#endif
	ReplaceWithFloat(line, start, end, answer);
}

void ReplaceRND(char* line) {
	char temp[BUFFER_MAX];
	char* functionName;
	size_t i, start, end;
	bool pastDot, pastSign;
	float answer;
	
	functionName = strstr(line, "RND");
	if (functionName == NULL) return;
	start = functionName - line;
	
	#if DEBUG_MODE
	printf("Before ReplaceRND: \"%s\"\n", line);
	printf("functionName = \"%s\"\n", functionName);
	printf("start = %ld\n", start);
	#endif
	
	pastDot = false; pastSign = false;
	for (i=start + 3; i<BUFFER_MAX; i++) {
		if (IsNumeric(line[i])) continue;
		if (!pastDot && line[i] == '.') {
			pastDot = true;
			continue;
		}
		if (!pastSign && line[i] == '-') {
			pastSign = true;
			continue;
		}
		end = i;
		break;
	}
	#if DEBUG_MODE
	printf("end is at %ld\n", end);	
	#endif
	answer = atof(functionName + 3);
	answer = (rand() % (int)answer) + 1;
	ReplaceWithFloat(line, start, end, answer);
}

void ReplaceSGN(char* line) {
	char temp[BUFFER_MAX];
	char* functionName;
	size_t i, start, end;
	bool pastDot, pastSign;
	float answer;
	
	functionName = strstr(line, "SGN");
	if (functionName == NULL) return;
	start = functionName - line;
	
	#if DEBUG_MODE
	printf("Before ReplaceSGN: \"%s\"\n", line);
	printf("functionName = \"%s\"\n", functionName);
	printf("start = %ld\n", start);
	#endif
	
	pastDot = false; pastSign = false;
	for (i=start + 3; i<BUFFER_MAX; i++) {
		if (IsNumeric(line[i])) continue;
		if (!pastDot && line[i] == '.') {
			pastDot = true;
			continue;
		}
		if (!pastSign && line[i] == '-') {
			pastSign = true;
			continue;
		}
		end = i;
		break;
	}
	#if DEBUG_MODE
	printf("end is at %ld\n", end);	
	#endif
	answer = atof(functionName + 3);
	if (answer > 0) answer = 1;
	else if (answer < 0) answer = -1;
	/* else answer = 0; :) */
	ReplaceWithFloat(line, start, end, answer);
}

void ReplaceSIN(char* line) {
	char temp[BUFFER_MAX];
	char* functionName;
	size_t i, start, end;
	bool pastDot, pastSign;
	float answer;
	
	functionName = strstr(line, "SIN");
	if (functionName == NULL) return;
	start = functionName - line;
	
	#if DEBUG_MODE
	printf("Before ReplaceSIN: \"%s\"\n", line);
	printf("functionName = \"%s\"\n", functionName);
	printf("start = %ld\n", start);
	#endif
	
	pastDot = false; pastSign = false;
	for (i=start + 3; i<BUFFER_MAX; i++) {
		if (IsNumeric(line[i])) continue;
		if (!pastDot && line[i] == '.') {
			pastDot = true;
			continue;
		}
		if (!pastSign && line[i] == '-') {
			pastSign = true;
			continue;
		}
		end = i;
		break;
	}
	#if DEBUG_MODE
	printf("end is at %ld\n", end);	
	#endif
	answer = atof(functionName + 3);
	answer = sinf(answer);
	if (answer == INFINITY) {
		strncpy(line, "?OVERFLOW ERROR", BUFFER_MAX);
		return;
	}
	ReplaceWithFloat(line, start, end, answer);
}

void ReplaceSQR(char* line) {
	char temp[BUFFER_MAX];
	char* functionName;
	size_t i, start, end;
	bool pastDot;
	float answer;
	
	functionName = strstr(line, "SQR");
	if (functionName == NULL) return;
	start = functionName - line;
	
	#if DEBUG_MODE
	printf("Before replace_sqr: \"%s\"\n", line);
	printf("functionName = \"%s\"\n", functionName);
	printf("start = %ld\n", start);
	#endif
	
	pastDot = false;
	for (i=start + 4; i<BUFFER_MAX; i++) {
		if (IsNumeric(line[i])) continue;
		if (!pastDot && line[i] == '.') {
			pastDot = true;
			continue;
		}
		end = i;
		break;
	}
	#if DEBUG_MODE
	printf("end is at %ld\n", end);
	#endif
	answer = atof(functionName + 3);
	answer = sqrtf(answer);
	ReplaceWithFloat(line, start, end, answer);
}

void ReplaceTAN(char* line) {
	char temp[BUFFER_MAX];
	char* functionName;
	size_t i, start, end;
	bool pastDot, pastSign;
	float answer;
	
	functionName = strstr(line, "TAN");
	if (functionName == NULL) return;
	start = functionName - line;
	
	#if DEBUG_MODE
	printf("Before ReplaceTAN: \"%s\"\n", line);
	printf("functionName = \"%s\"\n", functionName);
	printf("start = %ld\n", start);
	#endif
	
	pastDot = false; pastSign = false;
	for (i=start + 3; i<BUFFER_MAX; i++) {
		if (IsNumeric(line[i])) continue;
		if (!pastDot && line[i] == '.') {
			pastDot = true;
			continue;
		}
		if (!pastSign && line[i] == '-') {
			pastSign = true;
			continue;
		}
		end = i;
		break;
	}
	#if DEBUG_MODE
	printf("end is at %ld\n", end);	
	#endif
	answer = atof(functionName + 3);
	answer = tanf(answer);
	if (answer == INFINITY) {
		strncpy(line, "?OVERFLOW ERROR", BUFFER_MAX);
		return;
	}
	ReplaceWithFloat(line, start, end, answer);
}

void EvalParens(char* line) {
	/* Declare variables */
	size_t i, left, right, length;
	char temp[BUFFER_MAX], temp2[BUFFER_MAX];
	
	/* Get the position of the last '(' character */
	left = 0;
	length = strlen(line);
	for (i=length-1; i>0; i--) {
		if (line[i] != '(') continue;
		left = i;
		break;
	}
	#if DEBUG_MODE
	printf("    left ( is at position %ld\n", left);
	#endif
	
	/* Find the first ')' character after that */
	for (i=left; i<length; i++) {
		if (line[i] != ')') continue;
		right = i;
		break;
	}
	#if DEBUG_MODE
	printf("    right ) is at position %ld\n", right);
	#endif
	
	/* Fill our temp string everything between those two parens */
	memset(temp, 0, BUFFER_MAX);
	for (i=left + 1; i<right; i++) {
		temp[i - left - 1] = line[i];
	}
	#if DEBUG_MODE
	printf("    string to be evaluated: %s\n", temp);
	#endif
	
	/* Crunch the numbers */
	EvalMath(temp);
	#if DEBUG_MODE
	printf("After EvalMath (still in paren-check): %s\n", temp);
	#endif
	
	/* Create a second temporary string, with the result instead */
	memset(temp2, 0, BUFFER_MAX);
	for (i=0; i<left; i++) temp2[i] = line[i];
	#if DEBUG_MODE
	printf("    temp2: %s\n", temp);
	#endif
	snprintf(temp2 + left, BUFFER_MAX - left - 1, "%s%s", temp, line + right + 1);
	#if DEBUG_MODE
	printf("    temp2: %s\n", temp);
	#endif
	strncpy(line, temp2, BUFFER_MAX);
	#if DEBUG_MODE
	printf("After replacing parens: %s", line);
	#endif
	
	
}

void ReplacePI(char* line) {
	/* Declare variables */
	size_t start;
	char* pi;
	char temp[BUFFER_MAX];
	
	while(true) {
		/* Find the next instance of the string "PI" */
		pi = strstr(line, "PI");
		
		/* If there isn't one, we're done */
		if (pi == NULL) return;
		
		/* Get the position of the string to be replaced */
		start = pi - line;
		
		/* Replace it and continue the loop */
		ReplaceWithFloat(line, start, start + 2, M_PI);
	}
}

void Exponent(char* line) {
	/* Declare variables */
	int i, exp, start, end;
	float answer;
	bool pastDot;
	
	/* If the first character is a ^, the's a syntax error */
	if (line[0] == '^') {
		lastError = SYNTAX_ERROR;
		return;
	}
	
	/* Figure out where the ^ sign is */
	exp = 1;
	while(line[exp] != '^' && exp < BUFFER_MAX) exp++;
	
	/* If it didn't find one, then we're done. */
	if (exp == BUFFER_MAX) return;
	
	/* Get the position of the left-hand number */
	pastDot = false;
	for (i=exp - 1; i>-1; i--) {
		if (IsNumeric(line[i])) {
			if (i == 0) {
				start = 0;
				break;
			}
			continue;
		}
		if (line[i] == '.' && !pastDot) {
			pastDot = true;
			continue;
		}
		if (line[i] == '-' && (i == 0 || !IsNumeric(line[i - 1])))
			start = i;
		else start = i + 1;
		break;
	}
	
	// Get the position of the end of the number at the right
	pastDot = false;
	for (i = exp + 1; i<BUFFER_MAX; i++) {
		if (i == exp + 1 && line[i] == '-')
			continue;
		if (IsNumeric(line[i])) {
			if (i == BUFFER_MAX - 1) {
				end = i;
				break;
			}
			continue;
		}
		if (line[i] == '.' && !pastDot) {
			pastDot = true;
			continue;
		}
		end = i;
		break;
	}
	
	// Do the actual math
	answer = atof(line + exp + 1);
	answer = powf(atof(line + start), answer);
	
	/* Copy the answer back to the original line */
	ReplaceWithFloat(line, start, end, answer);
}



void Multiply(char* line) {
	/* Declare variables */
	char tmep[BUFFER_MAX];
	int i, times, start, end;
	float answer;
	bool pastDot;
	
	/* Figure out where the * sign is */
	times = 1;
	while(line[times] != '*' && times < BUFFER_MAX) times++;
	
	/* If it didn't find one, then we're done. */
	if (times == BUFFER_MAX) return;
	
	/* Get the position of the left-hand number */
	pastDot = false;
	for (i=times - 1; i>-1; i--) {
		if (IsNumeric(line[i])) {
			if (i == 0) {
				start = 0;
				break;
			}
			continue;
		}
		if (line[i] == '.' && !pastDot) {
			pastDot = true;
			continue;
		}
		if (line[i] == '-' && (i == 0 || !IsNumeric(line[i - 1])))
			start = i;
		else start = i + 1;
		break;
	}
	
	/* Get the position of the end of the number at the right */
	pastDot = false;
	for (i = times + 1; i<BUFFER_MAX; i++) {
		if (i == times + 1 && line[i] == '-')
			continue;
		if (IsNumeric(line[i])) {
			if (i == BUFFER_MAX - 1) {
				end = i;
				break;
			}
			continue;
		}
		if (line[i] == '.' && !pastDot) {
			pastDot = true;
			continue;
		}
		end = i;
		break;
	}
	
	/* Do the actual math */
	answer = atof(line + start) * atof(line + times + 1);
	
	/* Replace the question in the line with the answer */
	ReplaceWithFloat(line, start, start + end, answer);
}

void Divide(char* line) {
	/* Declare variables */
	char tmep[BUFFER_MAX];
	int i, div, start, end;
	float answer;
	bool pastDot;
	
	/* Figure out where the / sign is */
	div = 1;
	while(line[div] != '/' && div < BUFFER_MAX) div++;
	
	/* If it didn't find one, then we're done. */
	if (div == BUFFER_MAX) return;
	
	/* Get the position of the left-hand number */
	pastDot = false;
	for (i=div - 1; i>-1; i--) {
		if (IsNumeric(line[i])) {
			if (i == 0) {
				start = 0;
				break;
			}
			continue;
		}
		if (line[i] == '.' && !pastDot) {
			pastDot = true;
			continue;
		}
		if (line[i] == '-' && (i == 0 || !IsNumeric(line[i - 1])))
			start = i;
		else start = i + 1;
		break;
	}
	
	// Get the position of the end of the number at the right
	pastDot = false;
	for (i = div + 1; i< BUFFER_MAX; i++) {
		if (i == div + 1 && line[i] == '-')
			continue;
		if (IsNumeric(line[i])) {
			if (i == BUFFER_MAX - 1) {
				end = i;
				break;
			}
			continue;
		}
		if (line[i] == '.' && !pastDot) {
			pastDot = true;
			continue;
		}
		end = i;
		break;
	}
	
	// Do the actual math
	float temp2 =  atof(line + div + 1);
	if (temp2 == 0) {
		strcpy(line, "?DIVISION BY ZERO ERROR");
		return;
	}
	
	/* Do the actual math */
	answer = atof(line + start) / temp2;
	
	/* Replace the question in the line with the answer */
	ReplaceWithFloat(line, start, start + end, answer);
}

void Add(char* line) {
	/* Declare variables */
	char tmep[BUFFER_MAX];
	int i, plus, start, end;
	float answer;
	bool pastDot;
	
	/* Figure out where the + sign is */
	plus = 0;
	while(line[plus] != '+' && plus < BUFFER_MAX) plus++;
	
	/* If it didn't find one, then we're done. */
	if (plus == BUFFER_MAX) return;
	
	/* Get the position of the left-hand number */
	pastDot = false;
	for (i=plus - 1; i>-1; i--) {
		if (IsNumeric(line[i])) {
			if (i == 0) {
				start = 0;
				break;
			}
			continue;
		}
		if (line[i] == '.' && !pastDot) {
			pastDot = true;
			continue;
		}
		if (line[i] == '-' && (i == 0 || !IsNumeric(line[i - 1])))
			start = i;
		else start = i + 1;
		break;
	}
	
	/* Get the position of the end of the number at the right */
	pastDot = false;
	for (i = plus + 1; i< BUFFER_MAX; i++) {
		if (i == plus + 1 && line[i] == '-')
			continue;
		if (IsNumeric(line[i])) {
			if (i == BUFFER_MAX - 1) {
				end = i;
				break;
			}
			continue;
		}
		if (line[i] == '.' && !pastDot) {
			pastDot = true;
			continue;
		}
		end = i;
		break;
	}
	
	/* Do the actual math */
	answer = atof(line + start) + atof(line + plus + 1);
	
	/* Replace the question in the line with the answer */
	ReplaceWithFloat(line, start, start + end, answer);
}

void Subtract(char* line) {
	/* Declare variables */
	char tmep[BUFFER_MAX];
	int i, minus, start, end;
	float answer;
	bool pastDot;
	
	/* Figure out where the - sign is */
	minus = 1;	/* Was 0 (still is in add).  The difference here,
			leading + signs get stripped out (but not minus
			signs, cuz that would goof up the result).  So
			then when it tries to find the "start" position,
			it sees the leading '-' sign as the one we found in
			this step.  So starting at 1 solves that. */
	while(line[minus] != '-' && minus < BUFFER_MAX) minus++;
	
	// If it didn't find one, then we're done.
	if (minus == BUFFER_MAX) return;
	
	// Get the position of the left-hand number
	pastDot = false;
	for (i=minus - 1; i>-1; i--) {
		if (IsNumeric(line[i])) {
			if (i == 0) {
				start = 0;
				break;
			}
			continue;
		}
		if (line[i] == '.' && !pastDot) {
			pastDot = true;
			continue;
		}
		if (line[i] == '-' && (i == 0 || !IsNumeric(line[i - 1])))
			start = i;
		else start = i + 1;
		break;
	}
	
	// Get the position of the end of the number at the right
	pastDot = false;
	for (i = minus + 1; i<BUFFER_MAX; i++) {
		if (i == minus + 1 && line[i] == '-')
			continue;
		if (IsNumeric(line[i])) {
			if (i == BUFFER_MAX - 1) {
				end = i;
				break;
			}
			continue;
		}
		if (line[i] == '.' && !pastDot) {
			pastDot = true;
			continue;
		}
		end = i;
		break;
	}
	
	/* Do the actual math */
	answer = atof(line + start) - atof(line + minus + 1);
	
	/* Replace the question in the line with the answer */
	ReplaceWithFloat(line, start, start + end, answer);
}



void EvalMath(char* line) {
	/* Declare variables */
	size_t i;
	
	/* Handle parentheses */
	while(strchr(line, '(') != NULL) {
		EvalParens(line);
		#if DEBUG_MODE
		printf("After EvalParens: %s\n", line);
		#endif
	}
	
	/* Replace "PI" with 3.141592.... (however many %g can do) */
	ReplacePI(line);
	#if DEBUG_MODE
	printf("After ReplacePI: %s\n", line);
	#endif
	
	/* Handle ABS(number) */
	while(strstr(line, "ABS") != NULL) {
		ReplaceABS(line);
		if (lastError != NO_ERROR) {
			PrintLastError();
			return;
		}
	}
	
	/* Handle ATN(number) */
	while(strstr(line, "ATN") != NULL) {
		ReplaceATN(line);
		if (lastError != NO_ERROR) {
			PrintLastError();
			return;
		}
	}
	
	/* Handle COS(number) */
	while(strstr(line, "COS") != NULL) {
		ReplaceCOS(line);
		if (lastError != NO_ERROR) {
			PrintLastError();
			return;
		}
	}
	
	/* Handle EXP(number) */
	while(strstr(line, "EXP") != NULL) {
		ReplaceEXP(line);
		if (lastError != NO_ERROR) {
			PrintLastError();
			return;
		}
	}
	
	/* Handle INT(number) */
	while(strstr(line, "INT") != NULL) {
		ReplaceINT(line);
		if (lastError != NO_ERROR) {
			PrintLastError();
			return;
		}
	}
	
	/* Handle LOG(number) */
	while(strstr(line, "LOG") != NULL) {
		ReplaceLOG(line);
		if (lastError != NO_ERROR) {
			PrintLastError();
			return;
		}
	}
	
	/* Handle RND(number) */
	while(strstr(line, "RND") != NULL) {
		ReplaceRND(line);
		if (lastError != NO_ERROR) {
			PrintLastError();
			return;
		}
	}
	
	/* Handle SGN(number) */
	while(strstr(line, "SGN") != NULL) {
		ReplaceSGN(line);
		if (lastError != NO_ERROR) {
			PrintLastError();
			return;
		}
	}
	
	/* Handle SIN(number) */
	while(strstr(line, "SIN") != NULL) {
		ReplaceSIN(line);
		if (lastError != NO_ERROR) {
			PrintLastError();
			return;
		}
	}
	
	/* Handle SQR(number) */
	while(strstr(line, "SQR") != NULL) {
		ReplaceSQR(line);
		if (lastError != NO_ERROR) {
			PrintLastError();
			return;
		}
	}
	
	/* Handle TAN(number) */
	while(strstr(line, "TAN") != NULL) {
		ReplaceTAN(line);
		if (lastError != NO_ERROR) {
			PrintLastError();
			return;
		}
	}
	
	/* Handle exponents */
	while(strchr(line, '^') != NULL) {
		Exponent(line);
		if (lastError != NO_ERROR) {
			PrintLastError();
			return;
		}
	}
	#if DEBUG_MODE
	printf("After Exponent: %s\n", line);
	#endif
	
	/* Handle multiplication */
	while(strchr(line, '*') != NULL) {
		Multiply(line);
		if (lastError != NO_ERROR) {
			PrintLastError();
			return;
		}
	}
	#if DEBUG_MODE
	printf("After Multiply:  %s\n", line);
	#endif
	
	/* Handle division */
	while(strchr(line, '/') != NULL) {
		Divide(line);
		if (lastError != NO_ERROR) {
			PrintLastError();
			return;
		}
	}
	#if DEBUG_MODE
	printf("After Divide:   %s\n", line);
	#endif
	
	/* Handle addition/subtraction */
	for(i = 0; i<BUFFER_MAX; i++) {
		if (line[i] == '+') {
			Add(line);
			#if DEBUG_MODE
			printf("Then:    %s\n", line);
			#endif
			i = 0;
			continue;
		}
		if (line[i] == '-') {
			Subtract(line);
			#if DEBUG_MODE
			printf("Then:    %s\n", line);
			#endif
			i = 0;
			continue;
		}
	}
	#if DEBUG_MODE
	printf("After Add/Sub:  %s\n", line);
	#endif
}
