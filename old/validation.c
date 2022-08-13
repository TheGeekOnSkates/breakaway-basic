#include "main.h"

bool IsKeyword(char* string) {
	if (string == NULL) return false;
	return STRING_CONTAINS(string, "ABS")
		|| STRING_CONTAINS(string, "ATN")
		|| STRING_CONTAINS(string, "ALIAS")
		|| STRING_CONTAINS(string, "BG")
		|| STRING_CONTAINS(string, "BLINK")
		|| STRING_CONTAINS(string, "BOLD")
		|| STRING_CONTAINS(string, "CLS")
		|| STRING_CONTAINS(string, "CLEAR")
		|| STRING_CONTAINS(string, "COS")
		|| STRING_CONTAINS(string, "ELSE")
		|| STRING_CONTAINS(string, "END")
		|| STRING_CONTAINS(string, "EXIT")
		|| STRING_CONTAINS(string, "EXP")
		|| STRING_CONTAINS(string, "FG")
		|| STRING_CONTAINS(string, "GO")
		||  STRING_CONTAINS(string, "IF")
		|| STRING_CONTAINS(string, "INPUT")
		|| STRING_CONTAINS(string, "INT")
		|| STRING_CONTAINS(string, "ITALIC")
		|| STRING_CONTAINS(string, "LIST")
		|| STRING_CONTAINS(string, "LOG")
		|| STRING_CONTAINS(string, "RETURN")
		|| STRING_CONTAINS(string, "RND")
		|| STRING_CONTAINS(string, "SGN")
		|| STRING_CONTAINS(string, "SIN")
		|| STRING_CONTAINS(string, "SQR")
		|| STRING_CONTAINS(string, "TAN")
		|| STRING_CONTAINS(string, "THEN")
		|| STRING_CONTAINS(string, "UNDERLINE");
}

bool IsStringLiteral(char* string) {
	/* Declare variables */
	size_t i = 0, quoteCount = 0, length;
	
	/* If it's NULL or doesn't start with a quote... */
	if (string == NULL || string[0] != '"') return false;
	
	/* If it doesn't end with a quote, same deal */
	length = strlen(string);
	if (string[length - 1] != '"') return false;
	
	/*
	Now the only thing left to do is make sure there is an even
	number of quotes; BASICs didn't have an "escaped" quote; users
	use the CHR$ (or in some basics I think it's just CHR) to put
	a literal quotation mark in the string.  Also, in Apple ][ or
	Commdoore BASIC, I can do PRINT "STR" "ING" and it will print
	"STRING".  So the last check will be:
	*/
	length--;
	for (i=1; i<length; i++) {
		if (string[i] == '"') quoteCount++;
	}
	return quoteCount % 2 == 0;
}

bool StringIsInt(char* string) {
	if (string[0] == '-') string++;
	return StringIsUInt(string);
}

bool StringIsUInt(char* string) {
	size_t i=0, length = strlen(string);
	for(; i<length; i++) {
		if (string[i] < '0' || string[i] > '9') return false;
	}
	return true;
}

bool StringIsFloat(char* string) {
	size_t i=0, length = strlen(string);
	bool pastDot = false;

	if (string[0] == '-') {
		string++;
		length--;
	}
	for(; i<length; i++) {
		if (string[i] == '.') {
			if (pastDot) return false;
			pastDot = true;
			continue;
		}
		if (string[i] < '0' || string[i] > '9') return false;
	}
	return true;
}
