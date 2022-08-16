# BREAKAWAY BASIC OVERHAUL

## DONE

CLEAR
END
GOTO <expression>
LIST [<number>[ - <number>]]
NEW
PRINT <expression>[, <expression>...]
REM <comment>
RUN

## TO-DO

GOSUB <expression>
IF <conditions> THEN <number or statement>
INPUT <variable>[, <variable>...]
LET <variable> = <expression<
RETURN

## BTW...

* Finish that darn mathing; when it's done, this BASIC is as good as finished. :)
* At some point, add comments to main.h.  That file exists to work around what I've always felt to be one of C's ugliest warts: its need for you to "declare".  No other language on the planet (except for its far uglier superset, C++) has such a demand.  Like, "Hale, ye ancient tools!  Behold!  I shall write a function, and call it... run!"  Seriously?  lol... so really, main.h has become kind of a dumping ground for declarations to keep the compiler happy.  I need toa actually write what all those functions _do_. :)

# Known issues

## GOSUB can go out-of-bounds

There is a problem with GOSUB that I can't get to yet: currently, GOSUB -4 and GOSUB 100000000 pass validation.  When I get to the running phase, after I have functions in place to replace variables with their values, and evaluate expressions, THEN I will have to validate whether numbers in GOTO/GOSUB are too big or too small.
