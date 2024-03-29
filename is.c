#include "main.h"

bool is_alias(Line line) {
	/* Declare vars */
	char* temp = line, name[LINE_SIZE];
	size_t i;

	/* Skip spaces */
	while(temp[0] == ' ') temp++;

	/* If it doesn't start with ALIAS, then no */
	if (!STRING_STARTS_WITH(temp, "ALIAS")) return false;
	temp += 5;

	/* Skip spaces again */
	while(temp[0] == ' ') temp++;
	
	/* If the name of the alias is a keyword, then no */
	memset(name, 0, LINE_SIZE);
	if (temp[0] != '"') return false;
	for (i=0; i<LINE_SIZE-1; i++) {
		if (temp[i+1] == '"' || temp[i+1] == '\0') break;
		name[i] = temp[i+1];
	}
	if (is_keyword(name)) return false;

	/* Temp is still at the quote, so if it's not a string, then no */
	if (!is_string(temp, &temp)) return false;
	temp++;

	/* Skip spaces again */
	while(temp[0] == ' ') temp++;

	/* If it's not an equals sign, then no */
	if (temp[0] != '=') return false;
	
	/* Skip spaces for the last time :)  */
	temp++;
	while(temp[0] == ' ') temp++;
		
	return is_string(temp, &temp);
}

bool is_asc(Line line, char** position) {
	char* temp = line;
	while(temp[0] == ' ') temp++;
	if (!STRING_STARTS_WITH(temp, "ASC(\"")) return false;
	temp = line + 5;
	if (temp[0] == '\0') return false;
	temp++;	/* The character we want the ASCII value for */
	if (temp[0] != '"') return false;
	temp++;
	if (temp[0] != ')') return false;
	temp++;
	*position = temp;
	return true;
}

bool is_bg(Line line) {
	char* temp;
	if (!STRING_STARTS_WITH(line, "BG")) return false;
	temp = line + 2;
	while(temp[0] == ' ') temp++;
	return is_number(temp, &temp) || is_var(temp, &temp) || is_function(temp, &temp);
}

bool is_chr(Line line, char** position) {
	char* temp = line;
	while(temp[0] == ' ') temp++;
	if (!STRING_STARTS_WITH(temp, "CHR$(")) return false;
	temp = line + 5;
	while(temp[0] == ' ') temp++;
	if (!is_number(temp, &temp) && !is_expr(temp, &temp)) return false;
	while(temp[0] == ' ') temp++;
	if (temp[0] != ')') return false;
	temp++;
	*position = temp;
	return true;
}

bool is_blink(Line line) {
	char* temp;
	if (!STRING_STARTS_WITH(line, "BLINK")) return false;
	temp = line + 5;
	while(temp[0] == ' ') temp++;
	return STRING_EQUALS(temp, "ON") || STRING_EQUALS(temp, "OFF");
}

bool is_bold(Line line) {
	char* temp;
	if (!STRING_STARTS_WITH(line, "BOLD")) return false;
	temp = line + 4;
	while(temp[0] == ' ') temp++;
	return STRING_EQUALS(temp, "ON") || STRING_EQUALS(temp, "OFF");
}

bool is_center(Line line) {
	if (!STRING_STARTS_WITH(line, "CENTER")) return false;
	line += 6;
	while(line[0] == ' ') line++;
	return is_expr_list(line, &line);
}

bool is_cursor(Line line) {
	char* temp;
	if (!STRING_STARTS_WITH(line, "CURSOR")) return false;
	temp = line + 6;
	while(temp[0] == ' ') temp++;
	return STRING_EQUALS(temp, "ON") || STRING_EQUALS(temp, "OFF");
}

bool is_esc(Line line) {
	char* temp;
	if (!STRING_STARTS_WITH(line, "ESC")) return false;
	temp = line + 3;
	while(temp[0] == ' ') temp++;
	return is_string(temp, &temp);
}

bool is_expr(Line line, char** position) {
	/* Variables */
	char* pos;
	bool result = is_number(line, position) || is_var(line, position) || is_function(line, position);
	
	/* Skip spaces again */
	pos = *position;
	while(pos[0] == ' ') pos++;
	
	/* From here, we already know if it starts with an expression or not.
	But let's move the pointer to the end of the expression, because some
	functions (IF, PRINT etc.) involve more than one on the same line */
	while(true) {
		/* Skip spaces again */
		while(pos[0] == ' ') pos++;
		
		if (!is_math_action(pos[0])) break;
		pos++;
		
		/* Here we get into a kinda weird scenario:
		What if I enter 3 + 4 * (nothing at the end?)
		We can't have that, so... */
		if (!is_number(pos, &pos) && !is_var(pos, &pos) && !is_function(pos, &pos)) {
			*position = pos;
			return false;
		}
	}
	*position = pos;
	return result;
}

bool is_expr_list(Line line, char** position) {
	/* Variables */
	char* pos;
	bool result = is_string(line, position) || is_expr(line, position) || is_function(line, position);
	
	/* From here, we can have a comma, followed by another expression
	(but trailing commas are not allowed).  Kind of like is_expr :) */
	pos = *position;
	while(true) {
		/* Skip spaces */
		while(pos[0] == ' ') pos++;
		
		/* No comma?  We're done. */
		if (pos[0] != ',') break;
		pos++;
		
		/* No expression after the comma?  Syntax error. */
		if (!is_string(pos, &pos) && !is_expr(pos, &pos) && !is_function(pos, &pos)) {
			*position = pos;
			return false;
		}
	}
	
	/* And we're done */
	*position = pos;
	return result;
}

bool is_fg(Line line) {
	char* temp;
	if (!STRING_STARTS_WITH(line, "FG")) return false;
	temp = line + 2;
	while(temp[0] == ' ') temp++;
	return is_number(temp, &temp) || is_var(temp, &temp) || is_function(temp, &temp);
}

bool is_string_function(Line line, char** position) {
	if (STRING_STARTS_WITH(line, "TAB()")) {
		*position += 5;
		return true;
	}
	if (is_chr(line, position))
		return true;
	return false;
}

bool is_for(Line line) {
	bool result;
	
	if (!STRING_STARTS_WITH(line, "FOR")) return false;
	line += 3;
	while (line[0] == ' ') line++;
	if (!is_var(line, &line)) return false;
	while (line[0] == ' ') line++;
	if (line[0] != '=') return false;
	line++;
	while (line[0] == ' ') line++;
	if (!is_number(line, &line)) return false;
	while (line[0] == ' ') line++;
	if (!STRING_STARTS_WITH(line, "TO")) return false;
	line += 2;
	while (line[0] == ' ') line++;
	result = is_number(line, &line);
	while (line[0] == ' ') line++;
	if (!STRING_STARTS_WITH(line, "STEP")) return result;
	line += 4;
	while (line[0] == ' ') line++;
	return is_number(line, &line);
}

bool is_function(Line line, char** position) {
	if (is_asc(line, position)) {
		*position += 4;
		return true;
	}
	if (STRING_STARTS_WITH(line, "COLUMNS()")) {
		*position += 9;
		return true;
	}
	if (STRING_STARTS_WITH(line, "FRE()")) {
		*position += 5;
		return true;
	}
	if (STRING_STARTS_WITH(line, "RC()")) {
		*position += 4;
		return true;
	}
	if (STRING_STARTS_WITH(line, "ROWS()")) {
		*position += 6;
		return true;
	}
	return is_string_function(line, position);
}

bool is_gosub(Line line) {
	/* Variables */
	char* pos = line;
	
	/* If it doesn't start with GOSUB, then no */
	if (!STRING_STARTS_WITH(line, "GOSUB")) return false;
	pos += 5;
	
	/* Skip spaces if there are any */
	while(pos[0] == ' ') pos++;
	
	/* If the text after GOSUB is not an expression, then no */
	return is_expr(pos, &pos);
}

bool is_goto(Line line) {
	/* Variables */
	char* pos = line;
	
	/* If it doesn't start with GOTO, then no */
	if (!STRING_STARTS_WITH(line, "GOTO")) return false;
	pos += 4;
	
	/* Skip spaces if there are any */
	while(pos[0] == ' ') pos++;
	
	/* If the text after GOSUB is not an expression, then no */
	return is_expr(pos, &pos);
}

bool is_hidden(Line line) {
	char* temp;
	if (!STRING_STARTS_WITH(line, "HIDDEN")) return false;
	temp = line + 6;
	while(temp[0] == ' ') temp++;
	return STRING_EQUALS(temp, "ON") || STRING_EQUALS(temp, "OFF");
}

bool is_if(Line line) {
	if (!STRING_STARTS_WITH(line, "IF")) return false;
	line += 2;
	while (line[0] == ' ') line++;
	if (!is_expr(line, &line)) return false;
	while (line[0] == ' ') line++;
	if (!is_relop(line, &line)) return false;
	while (line[0] == ' ') line++;
	if (!is_expr(line, &line)) return false;
	while (line[0] == ' ') line++;
	if (!STRING_STARTS_WITH(line, "THEN")) return false;
	line += 4;
	while (line[0] == ' ') line++;
	return is_number(line, &line) || is_statement(line);
}

bool is_input(Line line) {
	if (!STRING_STARTS_WITH(line, "INPUT")) return false;
	line += 5;
	while(line[0] == ' ') line++;
	return is_var(line, &line);
}

bool is_italic(Line line) {
	char* temp;
	if (!STRING_STARTS_WITH(line, "ITALIC")) return false;
	temp = line + 6;
	while(temp[0] == ' ') temp++;
	return STRING_EQUALS(temp, "ON") || STRING_EQUALS(temp, "OFF");
}

bool is_keyword(Line line) {
	if (line[0] == 'A') return STRING_STARTS_WITH(line, "ASC");
	if (line[0] == 'B') return STRING_STARTS_WITH(line, "BG")
		|| STRING_STARTS_WITH(line, "BLINK")
		|| STRING_STARTS_WITH(line, "BOLD");
	if (line[0] == 'C') return STRING_STARTS_WITH(line, "CD")
		|| STRING_STARTS_WITH(line, "CLEAR")
		|| STRING_STARTS_WITH(line, "COLUMNS")
		|| STRING_STARTS_WITH(line, "CONT")
		|| STRING_STARTS_WITH(line, "CURSOR");
	if (line[0] == 'E') return STRING_STARTS_WITH(line, "END")
		|| STRING_STARTS_WITH(line, "ESC")
		|| STRING_STARTS_WITH(line, "EXIT");
	if (line[0] == 'F') return STRING_STARTS_WITH(line, "FG")
		|| STRING_STARTS_WITH(line, "FOR")
		|| STRING_STARTS_WITH(line, "FRE");
	if (line[0] == 'G') return STRING_STARTS_WITH(line, "GOSUB")
		|| STRING_STARTS_WITH(line, "GOTO");
	if (line[0] == 'H') return STRING_STARTS_WITH(line, "HIDDEN");
	if (line[0] == 'I') return STRING_STARTS_WITH(line, "IF")
		|| STRING_STARTS_WITH(line, "INCLUDE")
		|| STRING_STARTS_WITH(line, "INPUT")
		|| STRING_STARTS_WITH(line, "ITALIC");
	if (line[0] == 'L') return STRING_STARTS_WITH(line, "LET")
		|| STRING_STARTS_WITH(line, "LIST")
		|| STRING_STARTS_WITH(line, "LOAD");
	if (line[0] == 'M') return STRING_STARTS_WITH(line, "MOVE");
	if (line[0] == 'N') return STRING_STARTS_WITH(line, "NEW")
		|| STRING_STARTS_WITH(line, "NEXT");
	if (line[0] == 'O') return STRING_STARTS_WITH(line, "ON")
		|| STRING_STARTS_WITH(line, "OFF");
	if (line[0] == 'P') return STRING_STARTS_WITH(line, "PI")
		|| STRING_STARTS_WITH(line, "PRINT");
	if (line[0] == 'R') return STRING_STARTS_WITH(line, "REM")
		|| STRING_STARTS_WITH(line, "REVERSE")
		|| STRING_STARTS_WITH(line, "RUN")
		|| STRING_STARTS_WITH(line, "RETURN");
	if (line[0] == 'S') return STRING_STARTS_WITH(line, "SAVE")
		|| STRING_STARTS_WITH(line, "STEP")
		|| STRING_STARTS_WITH(line, "SYS");
	if (line[0] == 'T') return STRING_STARTS_WITH(line, "TAB")
		|| STRING_STARTS_WITH(line, "TAN")
		|| STRING_STARTS_WITH(line, "TO");
	if (line[0] == 'U') return STRING_STARTS_WITH(line, "UNDERLINE");
	return false;
}

bool is_let(Line line) {
	char* temp = line;
	
	/* If it doesn't start with LET, then no. */
	// if (!STRING_STARTS_WITH(line, "LET")) return false;
	if (STRING_STARTS_WITH(line, "LET")) temp += 3;
	
	/* Skip spaces */
	while (temp[0] == ' ') temp++;
	
	/* If what follows is not a variable, then no. */
	if (!is_var(temp, &temp)) return false;
	
	/* Skip spaces again */
	while (temp[0] == ' ') temp++;
	
	/* If the next char is not an euqals sign, then no */
	if (temp[0] != '=') return false;
	temp++;
	
	/* Skip spaces again */
	while (temp[0] == ' ') temp++;
	
	/* If the next part is not an expression, then no */
	if (!is_expr(temp, &temp)) return false;
	
	/* If it gets here, then yeah! */
	return true;
}

bool is_list(Line line) {
	if (!STRING_STARTS_WITH(line, "LIST")) return false;
	line += 4;
	while(line[0] == ' ') line++;
	if (line[0] == '\0') return true;	/* User just typed "LIST" */
	if (!is_number(line, &line)) return false;
	while(line[0] == ' ') line++;
	if (line[0] != '-') return true;	/* User just i.e. "LIST 10" */
	line++;
	while(line[0] == ' ') line++;
	if (!is_number(line, &line)) return false;
	return line[0] == '\0';
}

bool is_move(Line line) {
	char* temp;
	if (!STRING_STARTS_WITH(line, "MOVE")) return false;
	temp = line + 4;
	while(temp[0] == ' ') temp++;
	if (!is_number(temp, &temp) && !is_var(temp, &temp) && !is_function(temp, &temp))
		return false;
	while(temp[0] == ' ') temp++;
	return is_number(temp, &temp) || is_var(temp, &temp) || is_function(temp, &temp);
}

bool is_next(Line line) {
	char* temp;
	if (!STRING_STARTS_WITH(line, "NEXT")) return false;
	temp = line + 4;
	while(temp[0] == ' ') temp++;
	return is_number(temp, &temp) || is_var(temp, &temp) || is_function(temp, &temp);
}

bool is_number(Line line, char** position) {
	/* Variables */
	char* pos = *position;
	bool result;
	
	/* Skip spaces, if there are any */
	while(pos[0] == ' ') pos++;
	
	/* Move past the sign (- or +) at the beginning, if there is one */
	if (pos[0] == '+' || pos[0] == '-') pos++;
	
	/* Skip spaces again, if there are any */
	while(pos[0] == ' ') pos++;
	
	/* Now we need at least one digit */
	result = is_digit(pos[0]);
	
	/* Move the pointer past any additional digits */
	while (is_digit(pos[0])) pos++;
	
	/* And we're done */
	*position = pos;
	return result;
}

bool is_print(Line line) {
	if (!STRING_STARTS_WITH(line, "PRINT")) return false;
	line += 5;
	while(line[0] == ' ') line++;
	return is_expr_list(line, &line);
}

bool is_relop(Line line, char** position) {
	/* Declare variables */
	char* pos = *position;
	bool result;
	
	/* If it's a comparison operator, we hve our answer */
	switch(line[0]) {
		case '<':
			result = true;
			pos++;
			/* no break; "<>" is like "!=" in BASICs */
		case '>':
			result = true;
			pos++;
			break;
		case '=':
			result = true;
			pos++;
			break;
		default:
			result = false;
	}
	
	/* And we're done */
	*position = pos;
	return result;
}

bool is_statement(Line line) {
	/* These don't have anything after them, so they're easy */
	if (
		STRING_EQUALS(line, "CLEAR")
		|| STRING_EQUALS(line, "CONT")
		|| STRING_EQUALS(line, "END")
		|| STRING_EQUALS(line, "EXIT")
		|| STRING_EQUALS(line, "LIST")
		|| STRING_EQUALS(line, "NEW")
		|| STRING_EQUALS(line, "RETURN")
		|| STRING_EQUALS(line, "RESET")
		|| STRING_STARTS_WITH(line, "REM")
		|| STRING_EQUALS(line, "RUN")
	) return true;
	
	/* The others have specific requirements, so check for each of those */
	return is_bg(line)
		|| is_blink(line)
		|| is_center(line)
		|| is_cursor(line)
		|| is_esc(line)
		|| is_fg(line)
		|| is_gosub(line)
		|| is_goto(line)
		|| is_hidden(line)
		|| is_if(line)
		|| is_include(line)
		|| is_input(line)
		|| is_italic(line)
		|| is_let(line)
		|| is_list(line)
		|| is_load(line)
		|| is_move(line)
		|| is_print(line)
		|| is_prompt(line)
		|| is_reverse(line)
		|| is_save(line)
		|| is_sys(line)
		|| is_underline(line);
}

bool is_string(Line line, char** position) {
	/* Declare variables */
	char* pos;
	bool result;
	
	/* If it doesn't start with a quotation mark, then no */
	if (line[0] != '"') return false;
	
	/* IF there's a closing quote to match the opening quote, then yes */
	pos = strchr((const char*)line + 1, '"');
	result = pos != NULL;
	if (result) *position = pos;
	return result;
}

bool is_var(Line line, char** position) {
	char* pos = *position;
	bool result = line[0] >= 'A' && line[0] <= 'Z';
	bool twoLetters = line[1] >= 'A' && line[1] <= 'Z';
	pos++;
	*position = pos;
	return twoLetters ? false : result;
}

bool is_var_list(Line line, char** position) {
	/* Variables */
	char* pos;
	bool result = is_var(line, position);
	
	/* From here, we can have a comma, followed by another varession
	(but trailing commas are not allowed).  Kind of like is_var :) */
	pos = *position;
	while(true) {
		/* Skip spaces */
		while(pos[0] == ' ') pos++;
		
		/* No comma?  We're done. */
		if (pos[0] != ',') break;
		pos++;
		
		/* Skip spaces */
		while(pos[0] == ' ') pos++;
		
		/* No var after the comma?  Syntax error. */
		if (!is_var(pos, &pos)) {
			*position = pos;
			return false;
		}
	}
	
	/* And we're done */
	*position = pos;
	return result;
}

bool is_include(Line line) {
	char* temp;
	if (!STRING_STARTS_WITH(line, "INCLUDE")) return false;
	temp = line + 7;
	while(temp[0] == ' ') temp++;
	return is_string(temp, &temp);
}

bool is_load(Line line) {
	char* temp;
	if (!STRING_STARTS_WITH(line, "LOAD")) return false;
	temp = line + 4;
	while(temp[0] == ' ') temp++;
	return is_string(temp, &temp);
}

bool is_prompt(Line line) {
	char* temp;
	if (!STRING_STARTS_WITH(line, "PROMPT")) return false;
	temp = line + 6;
	while(temp[0] == ' ') temp++;
	return is_string(temp, &temp) || is_string_function(temp, &temp);
}

bool is_reverse(Line line) {
	char* temp;
	if (!STRING_STARTS_WITH(line, "REVERSE")) return false;
	temp = line + 7;
	while(temp[0] == ' ') temp++;
	return STRING_EQUALS(temp, "ON") || STRING_EQUALS(temp, "OFF");
}

bool is_save(Line line) {
	char* temp;
	if (!STRING_STARTS_WITH(line, "SAVE")) return false;
	temp = line + 4;
	while(temp[0] == ' ') temp++;
	return is_string(temp, &temp);
}

bool is_sys(Line line) {
	char* temp;
	if (!STRING_STARTS_WITH(line, "SYS")) return false;
	temp = line + 3;
	while(temp[0] == ' ') temp++;
	return is_string(temp, &temp);
}

bool is_underline(Line line) {
	char* temp;
	if (!STRING_STARTS_WITH(line, "UNDERLINE")) return false;
	temp = line + 9;
	while(temp[0] == ' ') temp++;
	return STRING_EQUALS(temp, "ON") || STRING_EQUALS(temp, "OFF");
}

// End of validation functions
