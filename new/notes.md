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
* An "expression" a math problem
* A variable is a capital letter from A to Z.
* A number is an int (Tiny BASIC didn't do floats).  I won't define "digit" lol
* A "relop" is a comparison (for IF): <, >, <>, or =
* And a string is exactly what you'd find in C.

## One important change from the "formal grammar" linked to above

Since I'm getting closer to the running phase, I went back to that page to figure out what CLEAR was supposed to do, and it varied from one implementation to the other.  On some Tiny BASICs, it cleared variables, and NEW worked cleared code; on others, CLEAR was equivalent to NEW.  So despite having a formal grammar, Tiny BASIC's grammar was not a standard like ANSI C.  With that in mind:

* CLEAR will clear the screen (using an ANSI escape code).  Windows, Linux, and even DOS support ANSI escape codes, and my pre-overhaul version used CLEAR this way, so it makes a bit more sense.
* NEW will work like it does on the C64 and most other BASICs: It will clear both variables and code, leaving the user with a new program.


## TO-DO's:

* Write is_if
* Once the program correctly validates any line I throw at it (with exception to GOTO/GOSUB shown below), it's time to actually get them working!
	Look at the Wikipedia article again; I think CLEAR was like NEW on the BASICs I know, and there are other things like that too.
* When everything I've described above - Tiny BASIC as I understand it - is fully functional, push version 1.0 to master and start planning more features; start with stuff common in 8-bit BASICs (FOR, arrays, functions like CHR$ and ASC, instructions like SYS, file I/O etc.).  Nail down 2.0 project goals before starting :)

# Known issues

## GOTO/GOSUB can go out-of-bounds

There is a problem with GOTO/GOSUB that I can't get to yet: currently, GOSUB -4 and GOSUB 100000000 pass validation.  When I get to the running phase, after I have functions in place to replace variables with their values, and evaluate expressions, THEN I will have to validate whether numbers in GOTO/GOSUB are too big or too small.
