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

* Depuzzle the current mathing glitch (stupid mathing). :D
* At some point, eval_expr will have to get a substring that is just the expression part.  Cuz what happens if I do PRINT "THE ANSWER IS:", 4 + 4, " AND ALSO ", 42 * 1?  Probably gonna fail, and miserably. :D
* Clean up main.h, and maybe consolidate some of these .c files
* Write tests for all 14 instructions
* Push to master and write docs - I just wrote a BASIC! :)
* Start planning version 0.2: SYS, ESC, and other fun functions.  FOR, arrays, etc. can wait for 0.3 :)

# Known issues

* Math sucks ice :)
