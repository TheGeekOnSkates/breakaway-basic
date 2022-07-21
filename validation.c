#include "main.h"

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
	if (string[0] == '-') string++;
	size_t i=0, length = strlen(string);
	bool pastDot = false;
	for(; i<length; i++) {
		if (string[i] == '.') {
			if (pastDot) return false;
			pastDot = true;
		}
		if (string[i] < '0' || string[i] > '9') return false;
	}
	return true;
}
