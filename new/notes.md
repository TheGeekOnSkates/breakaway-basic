# BREAKAWAY BASIC OVERHAUL

## DONE

CLEAR
END
EXIT
GOSUB <expression>
GOTO <expression>
LET <variable> = <expression>
LIST [<number>[ - <number>]]
NEW
PRINT <expression>[, <expression>...]
REM <comment>
RETURN
RUN

## TO-DO

IF <conditions> THEN <number or statement>
INPUT <variable>[, <variable>...]

## BTW...

* Set up eval_expr to get a substring that is just the expression part.  Cuz what happens if I do PRINT "THE ANSWER IS:", 4 + 4, " AND ALSO ", 42 * 1?  Probably gonna fail, and miserably. :D
	**EDIT:** I think this will be done in run.c and run functions, not eval_expr itself (that's working well so far, for PRINT and LET)
* Get IF working (should be easy once the math stuff is done)
* Get INPUT working (seriously thinking about just making it one variable, like on the C64).
* Clean up main.h, and consolidate some of these .c files
* Write tests for all 14 instructions
* Push to master and write docs - I just wrote a BASIC! :)

# Pipe dreaming about version 0.2 - now it starts to get fun!

* SYS <string> like before
* ESC <string> like before
* LOAD <string> like before
* SAVE <string> like before
* REVERSE like before
* BG like before
* FG like before
* RESET like before
* Variables ending in $ being strings
* Support for "string expressions" - what I mean is, "something like" + " this" + STR$(whatever the character code for "." is)
* Maybe add support for parens again; for people like me, who are not Algebrainiacs, parens help.  3 * 4 / 2 is not as clear to me as 3 * (4 / 2).
* And when I go there, may as well add in all my other work - meaningless functions like ABS, ATN, COS, TAN, ETC, ETC, ETC, that some people will appreciate.  idk, might be a 0.2 thing :)
* FOR and arrays will probably be a 0.3 or even 1.0 thing :)


# Known issues

* Math sucks ice :)
