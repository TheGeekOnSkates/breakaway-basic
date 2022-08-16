# BREAKAWAY BASIC OVERHAUL

## DONE

CLEAR
END
EXIT
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

* I'm really at a point where I need to puzzle out the math junk.  The only instructions left to do are the ones that depend on it.
* Clean up main.h, and maybe consolidate some of these .c files
* Write tests for all 14 instructions
* Push to master and write docs - I just wrote a BASIC! :)
* Start planning version 0.2: SYS, ESC, and other fun functions.  FOR, arrays, etc. can wait for 0.3 :)

# Known issues

* Math sucks ice :)
