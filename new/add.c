#include "main.h"

void add(char* line) {
	/* Declare variables */
	int i, plus, start, end;
	float answer;
	bool pastDot;
	
	/* Figure out where the + sign is */
	plus = 0;
	while(line[plus] != '+' && plus < LINE_SIZE) plus++;
	
	/* If it didn't find one, then we're done. */
	if (plus == LINE_SIZE) return;
	
	/* Get the position of the left-hand number */
	pastDot = false;
	for (i=plus - 1; i>-1; i--) {
		if (line[i] >= '0' && line[i] <= '9') {
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
		if (line[i] == '-' && (i == 0 || line[i - 1] < '0' || line[i - 1] > '9'))
			start = i;
		else start = i + 1;
		break;
	}
	
	/* Get the position of the end of the number at the right */
	pastDot = false;
	for (i = plus + 1; i< LINE_SIZE; i++) {
		if (i == plus + 1 && line[i] == '-')
			continue;
		if (line[i] >= '0' && line[i] < '9') {
			if (i == LINE_SIZE - 1) {
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
	replace_with_float(line, start, start + end, answer);
}
