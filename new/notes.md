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
IF <conditions> THEN <number or statement>
INPUT <variable>
LET <variable> = <expression>
LIST [<number>[ - <number>]]
LOAD <string>
NEW
PRINT <expression>[, <expression>...]
REM <comment>
RESET
RETURN
REVERSE ON/OFF
RUN
SAVE <string>
SYS <string>

## TO-DO

* UNDERLINE ON/OFF
* ITALIC ON/OFF
* Fix the bugs (see below)
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

# Known issues

* For some reason, when you run LIST, the LIST command ends up at line...6400?  There are only 6399 lines, so I don't get that at all.
* The math bug is almost fixed; it's not printing funky garbage chars anymore, but if I do this:
	10 LET A = 5
	20 LET B = 7
	30 PRINT A * B
It crashes.  Valgrind has not been much help yet, but hopefully, eventually, sense will come.

* Math sucks ice :)


## How to add new instructions

1. Define an is_* function for it
2. Add a check for it to is_statement
3. Add a check for it in RUN to make it do whatever it's supposed to do

## Latest intel on the stupid mathing bug (which may actually be a stupid string-replace bug)

==46467== Conditional jump or move depends on uninitialised value(s)
==46467==    at 0x10B0FC: replace_vars_with_values

==46467== Use of uninitialised value of size 8
==46467==    at 0x48BADBB: ____strtod_l_internal (strtod_l.c:611)
==46467==    by 0x10B0AA: replace_vars_with_values

==46467== Conditional jump or move depends on uninitialised value(s)
==46467==    at 0x483EFA9: __strlen_sse2 (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==46467==    by 0x48E6E94: __vfprintf_internal (vfprintf-internal.c:1688)
==46467==    by 0x48FA119: __vsnprintf_internal (vsnprintf.c:114)
==46467==    by 0x48CFF75: snprintf (snprintf.c:31)
==46467==    by 0x10CA75: replace_with_float

-------------------------------------------------------------------------------------------------
THEN THE ACTUAL CRASH...

==46467== Invalid write of size 1
==46467==    at 0x483F5D4: __strncpy_sse2_unaligned (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==46467==    by 0x10CA3A: replace_with_float

==46467==  Access not within mapped region at address 0x1FFF001000
==46467==    at 0x483F5D4: __strncpy_sse2_unaligned (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==46467==    by 0x10CA3A: replace_with_float
