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
NEW
PRINT <expression>[, <expression>...]
REM <comment>
RETURN
RUN

## TO-DO

* LOAD <string>
* SAVE <string>
* SYS <string>
* RESET
* Continue to clean up main.h and all those .c files
* Write tests for all 20 instructions
* Fix any bugs (see "known issues")
* Push to master and write docs - I just wrote a BASIC! :)

# Goals/plans for 0.2

* REVERSE ON/OFF
* BG <expression>
* FG <expression>
* BOLD ON/OFF
* BLINK ON/OFF

# If I make it to 0.3 :)

* Set up LET so I can just do i.e. X = 7
* Set up SYS so I can just do i.e. ls -la
* Add support for parens again (already started); for people like me, who are not Algebrainiacs, parens help.  3 * 4 / 2 is not as clear to me as 3 * (4 / 2).
* Add in all my other mathing work - meaningless functions like ABS, ATN, COS, TAN, ETC, ETC, ETC, that some people will appreciate.
* Maybe add some stuff I haven't yet - like  ROWS(), COLUMNS(), and anything else that's easy

# Pipe dreaming about version 1.0

* Variables ending in $ being strings
* Aliases - that was really cool on the old version
* Support for "string expressions" - what I mean is, "something like" + " this" + STR$(whatever the character code for "." is)
* FOR <expr> TO <expr> STEP <expression>
* NEXT (can't have FOR without it) :)
* Variables with parens being arrays

# Known issues

* For some reason, when you run LIST, the LIST command ends up at line...6400?  There are only 6399 lines, so I don't get that at all.
* The bug with the math functions is still not fixed.
	10 INPUT A
	20 INPUT B
	30 PRINT A * B
Gives me "0B".  But it's not an issue with INPUT, cuz the same happens if I set the vars with LET.  Best guess: It has to do with replace_vars_with_values()

* Math sucks ice :)


## How to add new instructions

1. Define an is_* function for it
2. Add a check for it to is_statement
3. Add a check for it in RUN to make it do whatever it's supposed to do



