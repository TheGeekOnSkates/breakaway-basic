# TO-DO'S

1. If possible, fix the bugs; if tired, work around them. :)
2. Create an "eval" type function like I was starting to do before.

This function should:

* Replace functions I haven't written yet (CHR$, ASC, etc.) with their values
* Replace variables with their values (maybe just rewrite that function, lol)
* Check for type mismatches
* Crunch numbers (turn "2+2" into "4" and so on).
* Continue until we have either a number or a string in quotes.

3. Use that to finish IF

# KNOWN ISSUES

There's a bug in ReplaceVariablesWithValues; if I do this:

LET PI = 3.14159
LET X = 7
LET Y = 3
IF X + Y < PI THEN 10

The if-statement works correctly:
IF 7 + 3 < 3.14159 THEN 10

But if I leave the spaces out of the equation:

IF X+Y<PI THEN 10
I get:
IF 7.14159+3.14159<3.14159 THEN 10

One of those lovely logic-defying mind-grinding goobers.  For now, work around it; eventually, attack it with a fresh brain and (Lord willing) squash it.



# FEATURES TO BE ADDED

* RENUMBER (like I think it was the TI 99 4/A had)
* Type-checking on variables
* PROMPT string (so instead of "READY." users could have "Ok" like on the Tandy M-100, or "]" like on the Apple ][ etc.)
* As I create/change BASIC commands, keep updating the docs.
* Add PUT x y character
* Add COLOR x y color, or maybe COLORS x y fg bg
* Playing with the idea of aliases.  For example:

	ALIAS CD SYS cd
	REM THIS IS LIKE A FIND-&-REPLACE, SO...
	CD /path/to/whatever
	REM IT WOULD REPLACE "CD " WITH "SYS cd "
	REM NOTE THE SPACES ABOVE

If I really wanted to get fancy, I could have an auto-run file to set these aliases up automagically - but that's *waaaay* down the road...

* Arrays
* GET
* Looping (FOR, _maybe_ WHILE)
* All the math stuff from my old calculator program
* With the math stuff done, PRINT (have it eval math, combine strings, and call the echo command which already works kinda like PRINT)
* Advanced file I/O: OPEN and CLOSE, GET# and INPUT#, PRINT#, CLEAR# etc.
* __MAYBE__ an auto-run file (kinda like a config file, but not really... think autoexec.bat in DOS :D)
* Maybe a history like Bash has; not important, but it would be kinda nice.
* But that would also involve putting text into STDIN (and if I can do that I'd also want an EDIT command like the TI 99 4/A has)

And by the time I get here, idk what else I could possibley need/want.  I can write aliases for things like speech (i.e. `ALIAS SAY SYS easpeak `), sound, and things like listing files.  And if I'm using this with a screen reader, the screen reader will automatically speak stuff as I PRINT it anyway... now 3D sound is a bit tricky, but IMO that's a different project entirely.  And if I write that program, I can make aliases for that in Breakaway BASIC too :)
