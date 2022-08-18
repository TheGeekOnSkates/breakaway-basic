# BREAKAWAY BASIC OVERHAUL

## DONE

CLEAR
END
EXIT
GOSUB <expression>
GOTO <expression>
INPUT <variable>
LET <variable> = <expression>
LIST [<number>[ - <number>]]
NEW
PRINT <expression>[, <expression>...]
REM <comment>
RETURN
RUN

## TO-DO

IF <conditions> THEN <number or statement>

## BTW...

* Get IF working (should be easy once the math stuff is done)
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

* There is a bug in multiply(); sometimes there is a * left behind; for example:
	10 INPUT A
	20 INPUT B
	30 PRINT A * B
Gives me "0B".  But it's not an issue with INPUT, cuz the same happens if I set the vars with LET.  Best guess: It has to do with replace_vars_with_values()

* Math sucks ice :)
