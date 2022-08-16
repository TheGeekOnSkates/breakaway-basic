# BREAKAWAY BASIC OVERHAUL

## DONE

CLEAR
GOTO <expression>
LIST [<number>[ - <number>]]
NEW
PRINT <expression>[, <expression>...]
REM <comment>
RUN

## TO-DO

END
GOSUB <expression>
IF <conditions> THEN <number or statement>
INPUT <variable>[, <variable>...]
LET <variable> = <expression<
RETURN

## BTW...

* Keep fighting the math problems (lol the gurus call them "problems" for good reason! :D).  However, they don't necessarily have to be all about math.  A lot of it can be expressed as language.  Maybe try a "get_next_symbol" function that checks is_number/is_expr/is_string and reacts as needed... lol idk, my creative juices for code are totally drained tonight, but I think there are way around the stupid mathing that are still efficient and whatever). :)  Seriously tho, PRINT, IF, and even GOTO/GOSUB will eventually need a way to evaluate expressions, so this will require extensive strategizing.  Here's my last thought on the subject at the moment;
	- Rather than check if is_expr, check if is_number; WAIT, why not build it into an array of numbers, and then deal with it from there?  For example:
		[2, PLUS, -4, TIMES, 3];
		Assuming PLUS and TIMES are the characters between them.  I could chop that down to [2, PLUS, -12] and then to just -10 following that logic (kind of like what I did in Cheese, lol - a stack in the Forth sense).
	- Once LET is working, replace variables with their values.  Don't count on them being one letter (cuz maybe in 0.2 and on they won't be).  For now, I can at least use numbers without mathing
	- Handle the math actions, remembering to Duck the old "order of operations" baloney from high school to see how the Algebresians do it.  There is a specific way BASICs and other languages do (me personally I just go overboard with parens lol)
* At some point, add comments to main.h.  That file exists to work around what I've always felt to be one of C's ugliest warts: its need for you to "declare".  No other language on the planet (except for its far uglier superset, C++) has such a demand.  Like, "Hale, ye ancient tools!  Behold!  I shall write a function, and call it... run!"  Seriously?  lol... so really, main.h has become kind of a dumping ground for declarations to keep the compiler happy.  I need toa actually write what all those functions _do_. :)

# Known issues

## GOTO/GOSUB can go out-of-bounds

There is a problem with GOTO/GOSUB that I can't get to yet: currently, GOSUB -4 and GOSUB 100000000 pass validation.  When I get to the running phase, after I have functions in place to replace variables with their values, and evaluate expressions, THEN I will have to validate whether numbers in GOTO/GOSUB are too big or too small.
