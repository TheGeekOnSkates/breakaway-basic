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

The issue is definitely in replace_with_float, and apparently is some kind of infinite loop?  What the puck?!  Obviously, the issue has something to do with something that *CALLS* replace_with_float... but hot dang!  This stupid bug is a real son of a bit shift operator!  What the?!  WHAT THE?!   Siiiiiiiigh.... okay, here's my latest valgrind data dump.  Stupid.



==51359== Invalid write of size 1
==51359==    at 0x483F5D4: __strncpy_sse2_unaligned (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==51359==    by 0x10D92A: replace_with_float (strings.c:8)
==51359==  Address 0x1fff001000 is not stack'd, malloc'd or (recently) free'd
==51359== 
==51359== 
==51359== Process terminating with default action of signal 11 (SIGSEGV): dumping core
==51359==  Access not within mapped region at address 0x1FFF001000
==51359==    at 0x483F5D4: __strncpy_sse2_unaligned (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==51359==    by 0x10D92A: replace_with_float (strings.c:8)
==51359==  If you believe this happened as a result of a stack
==51359==  overflow in your program's main thread (unlikely but
==51359==  possible), you can try to increase the size of the
==51359==  main thread stack using the --main-stacksize= flag.
==51359==  The main thread stack size used in this run was 8388608.
==51359== 
==51359== HEAP SUMMARY:
==51359==     in use at exit: 0 bytes in 0 blocks
==51359==   total heap usage: 4 allocs, 4 frees, 6,616 bytes allocated
==51359== 
==51359== All heap blocks were freed -- no leaks are possible
==51359== 
==51359== For lists of detected and suppressed errors, rerun with: -s
==51359== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
