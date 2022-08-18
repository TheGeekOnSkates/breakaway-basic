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
* Fix any bugs (see "known issues")
* Push to master and write docs - I just wrote a BASIC! :)

# Goals/plans for 0.2

* I would kind of like to get LOAD and SAVE working again; it would be nice not to have to write the same test programs over and over again.  :)
* Also, PRINT doesn't flag a semicolon at the end; this is a good thing; I want to add the behavior like Commodore stuff had, where putting a semicolon at the end tells BASIC, "Don't put a new line here".
* SYS <string> like before - I kinda like not having to use SYS (just like not having to use LET); reuse that code if possible)
* ESC <string> like before
* LOAD <string> like before
* SAVE <string> like before
* REVERSE like before
* BG like before
* FG like before
* RESET like before

# If I make it to 0.3 :)

* Add support for parens again; for people like me, who are not Algebrainiacs, parens help.  3 * 4 / 2 is not as clear to me as 3 * (4 / 2).
* Add in all my other mathing work - meaningless functions like ABS, ATN, COS, TAN, ETC, ETC, ETC, that some people will appreciate.
* Maybe add some stuff I haven't yet - like  ROWS(), COLUMNS(), and anything else that's easy

# Pipe dreaming about version 1.0

* Variables ending in $ being strings
* Support for "string expressions" - what I mean is, "something like" + " this" + STR$(whatever the character code for "." is)
* FOR <expr> TO <expr> STEP <expression>
* NEXT (can't have FOR without it) :)
* Variables with parens being arrays

# Known issues

* There is a bug in multiply(); sometimes there is a * left behind; for example:
	10 INPUT A
	20 INPUT B
	30 PRINT A * B
Gives me "0B".  But it's not an issue with INPUT, cuz the same happens if I set the vars with LET.  Best guess: It has to do with replace_vars_with_values()

**EDIT:** It's not just multiplication; did it with addition too.


* Math sucks ice :)
