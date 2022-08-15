# BREAKAWAY BASIC OVERHAUL

## Mini-reference (since I'm close to having to actually write docs :D)

CLEAR
END
GOTO <expression>
GOSUB <expression>
IF <conditions> THEN <number or statement>
INPUT <variable>[, <variable>...]
LET <variable> = <expression<
LIST [<number>[ - <number>]]
PRINT <expression>[, <expression>...]
NEW
REM <comment>
RETURN
RUN

## TO-DO's:

* Rework old functions as needed to evaluate expressions
* Once that works, get LET working
* To get LET working (and test it) I'll also need to get PRINT working
* Then, may as well get RUN and LIST working
* We'll see where we go from there :)

# Known issues

## GOTO/GOSUB can go out-of-bounds

There is a problem with GOTO/GOSUB that I can't get to yet: currently, GOSUB -4 and GOSUB 100000000 pass validation.  When I get to the running phase, after I have functions in place to replace variables with their values, and evaluate expressions, THEN I will have to validate whether numbers in GOTO/GOSUB are too big or too small.
