#include "main.h"

extern int rc;

void replace_asc(Line line) {
	/* Declare variables */
	char* where = NULL, buffer[8];
	size_t start = 0, end = 0;

	/* And replace ROWS() with rows */
	while(true) {
		where = strstr(line, "ASC(");
		if (where == NULL) break;
		start = where - line;
		end = start + 4;
		while(line[end] != ')' && line[end] != '\0' && end < LINE_SIZE) end++;
		if (end + 1 < LINE_SIZE) end++;
		where += 5;

		/* And do the replacing */
		memset(buffer, 0, 8);
		snprintf(buffer, 8, "%d", where[0]);
		replace_with_string(line, start, end, buffer);
	}
}

void replace_chr(Line line) {
	/* Declare variables */
	char* where = NULL, buffer[8];
	size_t start = 0, end = 0;
	size_t chr = 0;

	/* And replace ROWS() with rows */
	while(true) {
		where = strstr(line, "CHR$(");
		if (where == NULL) break;
		start = where - line;
		end = start + 4;
		while(line[end] != ')' && end < LINE_SIZE) end++;
		if (end + 1 < LINE_SIZE) end++;
		chr = atol(where + start + 4);
		/* LEFT OFF HERE */
		memset(buffer, 0, 8);
		snprintf(buffer, 8, "%lc", (wchar_t)chr);
		replace_with_string(line, start, end, buffer);
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

void replace_fre(Line line) {
	/* Declare variables */
	char* where, buffer[20];
	uint64_t bytes;
	size_t start, end;
	
	/* Get the bytes free */
	bytes = GetBytesFree();
	memset(buffer, 0, 20);
	snprintf(buffer, 20, "%ld", bytes);
	
	/* And replace ROWS() with rows */
	while(true) {
		where = strstr(line, "FRE()");
		if (where == NULL) break;
		start = where - line;
		end = start + 5;
		replace_with_string(line, start, end, buffer);
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
