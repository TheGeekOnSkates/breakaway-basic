#include "main.h"

extern int rc;

void replace_chr(Line line) {
	/* Declare variables */
	char* where;
	int rows, columns;
	size_t start, end;
	size_t chr;
	
	/* Set rows and columns */
	GetScreenSize(&rows, &columns);

	/* And replace ROWS() with rows */
	while(true) {
		where = strstr(line, "CHR$(");
		if (where == NULL) break;
		start = where - line;
		end = start + 5;
		chr = atol(where + end);
		/* LEFT OFF HERE */
		printf("CHR = '%lc'\n", (wchar_t)chr);
	}
}

void replace_columns(Line line) {
	/* Declare variables */
	char* where;
	int rows, columns;
	size_t start, end;
	
	/* Set rows and columns */
	GetScreenSize(&rows, &columns);

	/* And replace COLUMNS() with columns */
	while(true) {
		where = strstr(line, "COLUMNS()");
		if (where == NULL) break;
		start = where - line;
		end = start + 9;
		
		replace_with_float(line, start, end, (float)columns);
	}
}

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

void replace_rows(Line line) {
	/* Declare variables */
	char* where;
	int rows, columns;
	size_t start, end;
	
	/* Set rows and columns */
	GetScreenSize(&rows, &columns);

	/* And replace ROWS() with rows */
	while(true) {
		where = strstr(line, "ROWS()");
		if (where == NULL) break;
		start = where - line;
		end = start + 6;
		
		replace_with_float(line, start, end, (float)rows);
	}
}
