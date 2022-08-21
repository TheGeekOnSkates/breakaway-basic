#include "main.h"

extern int rc;

void replace_rc(Line line) {
	char* where;
	size_t start, end;
	while(true) {
		where = strstr(line, "RC()");
		if (where == NULL) break;
		start = where - line;
		end = start + 4;
		replace_with_float(line, start, end, (float)rc);
	}
}
