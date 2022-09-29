#include "main.h"

extern int rc;

void replace_asc(Line line, VarList variables) {
	/* Declare variables */
	char* where = NULL, *temp = NULL, buffer[8];
	size_t start = 0, end = 0;

	/* And replace ASC() with the ASCII (or Unicode) character */
	while(true) {
		where = substring(line, "ASC(");
		if (where == NULL) break;
		temp = get_text_between_parens(line);
		if (temp == NULL) return;	/* get_text_between_parens will have logged an error already */
		start = where - line;
		end = start + 4;
		while(line[end] != ')' && line[end] != '\0' && end < LINE_SIZE) end++;
		if (end + 1 < LINE_SIZE) end++;
		where += 5;

		/* And do the replacing */
		eval_expr(temp, variables);
		snprintf(buffer, 8, "%lc", atoi(temp));
		free(temp);
		replace_with_string(line, start, end, buffer);
	}
}

void replace_chr(Line line) {
	/* Declare variables */
	char* where = NULL, buffer[8];
	size_t end = 0, chr = 0;

	/* And replace ROWS() with rows */
	while(true) {
		/* Find the next one, or exit if not found */
		where = substring(line, "CHR$(");
		if (where == NULL) break;

		/* Copy the character into a buffer */
		chr = atol(where + 5);
		memset(buffer, 0, 8);
		snprintf(buffer, 8, "\"%lc\"", (wchar_t)chr);

		/* Figure out the end point (to include the closing ")") */
		end = 0;
		while(where[end] != ')') end++;
		if (end < LINE_SIZE) end++;

		/* And replace the string */
		replace_with_string(line, where - line, where - line + end, buffer);
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
		where = substring(line, "COLUMNS()");
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
		where = substring(line, "FRE()");
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
		where = substring(line, "RC()");
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
		where = substring(line, "ROWS()");
		if (where == NULL) break;
		start = where - line;
		end = start + 6;
		
		replace_with_float(line, start, end, (float)rows);
	}
}

void replace_tab(Line line) {
	/* Declare variables */
	char* where = NULL, buffer[4];
	size_t start = 0, end = 0;

	/* Set up the "buffer" */
	buffer[0] = '"';
	buffer[1] = '\t';
	buffer[2] = '"';
	buffer[3] = '\0';

	/* And replace ROWS() with rows */
	while(true) {
		where = substring(line, "TAB()");
		if (where == NULL) break;
		start = where - line;
		end = start + 5;
		if (end + 1 < LINE_SIZE) end++;
		replace_with_string(line, start, end, buffer);
	}
}

// End of "function-replacing functions" (lol)
