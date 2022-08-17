#include "main.h"

void replace_with_float(char* line, size_t from, size_t to, float value) {
        size_t i;
	char temp[LINE_SIZE];
        memset(temp, 0, LINE_SIZE);
        for (i=0; i<from; i++) temp[i] = line[i];
        snprintf(temp + from, LINE_SIZE, "%g%s", value, line + to);
        strncpy(line, temp, LINE_SIZE);
}


