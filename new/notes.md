# BREAKAWAY BASIC OVERHAUL

## Completed functions

BG <expression>
BLINK ON/OFF
BOLD ON/OFF
CD <string>
CLEAR
END
ESC <string>
EXIT
FG <expression>
GOSUB <expression>
GOTO <expression>
HIDDEN ON/OFF
IF <conditions> THEN <number or statement>
INPUT <variable>
ITALIC ON/OFF
LET <variable> = <expression>
LIST [<number>[ - <number>]]
LOAD <string>
MOVE <number> <number>
NEW
PRINT <expression>[, <expression>...]
REM <comment>
RESET
RETURN
REVERSE ON/OFF
RUN
SAVE <string>
SYS <string>
UNDERLINE ON/OFF

## TO-DO

* Write the docs, testing the functions as I go (the tests will end up as examples)
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

## How to add new instructions

1. Define an is_* function for it
2. Add a check for it to is_statement
3. Add a check for it in RUN to make it do whatever it's supposed to do
