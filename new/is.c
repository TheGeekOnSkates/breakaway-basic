#include "main.h"

/************************************************************************/

bool is_statement(Line line) {
	/* These don't have anything after them, so they're easy */
	if (
		STRING_EQUALS(line, "CLEAR")
		|| STRING_EQUALS(line, "END")
		|| STRING_EQUALS(line, "EXIT")
		|| STRING_EQUALS(line, "LIST")
		|| STRING_EQUALS(line, "NEW")
		|| STRING_EQUALS(line, "RETURN")
		|| STRING_STARTS_WITH(line, "REM")
		|| STRING_EQUALS(line, "RUN")
	) return true;
	
	/* The others have specific requirements, so check for each of those */
	return is_gosub(line)
		|| is_goto(line)
		|| is_if(line)
		|| is_input(line)
		|| is_let(line)
		|| is_list(line)
		|| is_print(line);
}

/************************************************************************/

bool is_input(Line line) {
	if (!STRING_STARTS_WITH(line, "INPUT")) return false;
	line += 5;
	while(line[0] == ' ') line++;
	return is_var(line, &line);
}

/************************************************************************/

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

/************************************************************************/

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

/************************************************************************/

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

/************************************************************************/

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

/************************************************************************/

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

/************************************************************************/

bool is_list(Line line) {
	if (!STRING_STARTS_WITH(line, "LIST")) return false;
	line += 4;
	while(line[0] == ' ') line++;
	if (!is_number(line, &line)) return false;
	while(line[0] == ' ') line++;
	if (line[0] == '-') {
		line++;
		while(line[0] == ' ') line++;
		if (!is_number(line, &line)) return false;
	}
	return line[0] == '\0';
}


/************************************************************************/

bool is_let(Line line) {
	char* temp;
	
	/* If it doesn't start with LET, then no. */
	if (!STRING_STARTS_WITH(line, "LET")) return false;
	
	/* Skip spaces */
	temp = line + 3;
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

/************************************************************************/

bool is_print(Line line) {
	if (!STRING_STARTS_WITH(line, "PRINT")) return false;
	line += 5;
	while(line[0] == ' ') line++;
	return is_expr_list(line, &line);
}

/************************************************************************/

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

/************************************************************************/

bool is_expr(Line line, char** position) {
	/* Variables */
	char* pos;
	bool result = is_number(line, position) || is_var(line, position);
	
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
		if (!is_number(pos, &pos) && ! is_var(pos, &pos)) {
			*position = pos;
			return false;
		}
	}
	*position = pos;
	return result;
}

/************************************************************************/

bool is_expr_list(Line line, char** position) {
	/* Variables */
	char* pos;
	bool result = is_string(line, position) || is_expr(line, position);
	
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
		if (!is_string(pos, &pos) && !is_expr(pos, &pos)) {
			*position = pos;
			return false;
		}
	}
	
	/* And we're done */
	*position = pos;
	return result;
}


/************************************************************************/

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

/************************************************************************/

bool is_var(Line line, char** position) {
	char* pos = *position;
	bool result = line[0] >= 'A' && line[0] <= 'Z';
	bool twoLetters = line[1] >= 'A' && line[1] <= 'Z';
	pos++;
	*position = pos;
	return twoLetters ? false : result;
}