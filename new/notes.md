# BREAKAWAY BASIC OVERHAUL

## Syntax

For now, my goal is to make it meet the [Tiny BASIC grammar](https://en.wikipedia.org/wiki/Tiny_BASIC#Formal_grammar).  For my own purposes (and future editing), here is that grammar:

line ::= number statement CR | statement CR
statement ::= PRINT expr-list
	IF expression relop expression THEN statement
	GOTO expression
	INPUT var-list
	LET var = expression
	GOSUB expression
	RETURN
	CLEAR
	LIST
	RUN
	END
expr-list ::= (string|expression) (, (string|expression) )*
var-list ::= var (, var)*
expression ::= (+|-|ε) term ((+|-) term)*
term ::= factor ((*|/) factor)*
factor ::= var | number | (expression)
var ::= A | B | C ... | Y | Z
number ::= digit digit*
digit ::= 0 | 1 | 2 | 3 | ... | 8 | 9
relop ::= < (>|=|ε) | > (<|=|ε) | =
string ::= " ( |!|#|$ ... -|.|/|digit|: ... @|A|B|C ... |X|Y|Z)* "

-----------------------------------------------------------------

And here's my attempt at translating that into something meaningful to humans (lol);

* A "line" is a number (optional), then a statement, then a newline
* A "statement" is one of the BASIC instructions (see above for the complete list).
* An "expression list" ("expr-list" in the original) is one or more expressions, separated by commas
* A "variable list" ("var-list" in the original) is one or more variables, separated by commas
* An "expression" is one or more of the following structure (no delimiter):
	A optional plus or minus sign
	then one or more variables, numbers, or expressions
  So really, it looks like an expression is a math thing.
* A variable is a capital letter from A to Z.
* A number is an int (Tiny BASIC didn't do floats).  I won't define "digit" lol
* A "relop" is a comparison (for IF): <, >, <>, or =
* And a string is exactly what you'd find in C.

## TO-DO's:

* Write, is_goto and is_gosub
* Write is_relop and is_string (should be easy)
* Use these to build is_expr_list etc.
* And use these to finish the validation phase

* Once the program correctly validates any line I throw at it, it's time to actually get them working!
	Look at the Wikipedia article again; I think CLEAR was like NEW on the BASICs I know, and there are other things like that too.
* When everything I've described above - Tiny BASIC as I understand it - is fully functional, push version 1.0 to master and start planning more features; start with stuff common in 8-bit BASICs (FOR, arrays, functions like CHR$ and ASC, instructions like SYS, file I/O etc.).  Nail down 2.0 project goals before starting :)
