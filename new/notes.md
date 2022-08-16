# BREAKAWAY BASIC OVERHAUL

## DONE

CLEAR
END
GOSUB <expression>
GOTO <expression>
LIST [<number>[ - <number>]]
NEW
PRINT <expression>[, <expression>...]
REM <comment>
RETURN
RUN

## TO-DO

IF <conditions> THEN <number or statement>
INPUT <variable>[, <variable>...]
LET <variable> = <expression<

## BTW...

* I keep wanting to type EXIT like I did on the old one - add an EXIT command
* I'm really at a point where I need to puzzle out the math junk.  The only instructions left to do are the ones that depend on it.
* Clean up main.h, and maybe consolidate some of these .c files
* Write tests for all 14 instructions
* Push to master and write docs - I just wrote a BASIC! :)

# Known issues

* PRINT replaces commas in strings (i.e. "YUP, IT WORKS" becomes "YUP  IT WORKS"); I'll have to add a check for that.
* Math sucks ice :)
