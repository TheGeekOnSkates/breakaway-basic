# BREAKAWAY BASIC OVERHAUL

## Completed functions

CD <string>
CLEAR
END
ESC <string>
EXIT
GOSUB <expression>
GOTO <expression>
IF <conditions> THEN <number or statement>
INPUT <variable>
LET <variable> = <expression>
LIST [<number>[ - <number>]]
LOAD <string>
NEW
PRINT <expression>[, <expression>...]
REM <comment>
RETURN
RUN
SAVE <string>
SYS <string>

## TO-DO

* REVERSE ON/OFF
* BG <expression>
* FG <expression>
* BOLD ON/OFF
* BLINK ON/OFF
* UNDERLINE ON/OFF
* ITALIC ON/OFF
* RESET
* Continue to clean up main.h and all those .c files
* Write tests for all instructions
* Fix the bugs (see below)
* WTFM :)
* Push to master

# If I make it to 0.2 :)

* Set up LET so I can just do i.e. X = 7
* Set up SYS to set an "RC" variable (maybe make it "RC()" since I'll be doing that later)
* Add support for parens again (already started); for people like me, who are not Algebrainiacs, parens help.  3 * 4 / 2 is not as clear to me as 3 * (4 / 2).
* Add in all my other mathing work - meaningless functions like ABS, ATN, COS, TAN, ETC, ETC, ETC, that some people will appreciate.
* Maybe add some stuff I haven't yet - like  ROWS(), COLUMNS(), and anything else that's easy

# Pipe dreaming about version 1.0

* Aliases - that was really cool on the old version
* Variables with names longer than 1 character (unnecessary, but useful).
* Variables ending in $ being strings
* Support for "string expressions" - what I mean is, "something like" + " this" + STR$(whatever the character code for "." is)
* FOR <expr> TO <expr> STEP <expression>
* NEXT (can't have FOR without it) :)
* Variables with parens being arrays
* Sound (technically possible with SYS "play somesound.wav" but a built-in API would be nice).

# Known issues

* For some reason, when you run LIST, the LIST command ends up at line...6400?  There are only 6399 lines, so I don't get that at all.
* The bug with the math functions is still not fixed.
	10 INPUT A
	20 INPUT B
	30 PRINT A * B
I can even reproduce it without variables:
	PRINT 3.141 * 1.234
Definitely seems to be the replace_with_* functions
**EDIT:** Seems to be fixed; the issue was with get_end.  However, I still need to test the BASIC code above.

* Math sucks ice :)


## How to add new instructions

1. Define an is_* function for it
2. Add a check for it to is_statement
3. Add a check for it in RUN to make it do whatever it's supposed to do
