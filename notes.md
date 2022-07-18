# GOALS FOR A "PRODUCTION" RELEASE

Before I have something that I would be willing to use instead of Bash - before I "breakaway" from Bash, there are some features I would really like this BASIC to have:

* CD; turns out, it was hard-coded into Bash, so just running "cd ../" etc. doesn't work - this is a must-have.
* IF; variables are pretty useless without it.
* Aliases; they're such a useful feature, and would make adding more commands a lot easier.
* In SYS calls, a way to insert variables and other stuff.  I'm thinking percent signs - i.e. SYS echo -n %someVariable CHR$(250)%
* Evaluating math; for example, even without FOR, to be able to do I = I + 1 makes looping possible.  Might come with IF, but we'll see

Not saying I'll do them all, but this is the goal. :)

# TO-DO'S

* Wake up with a fresh brain, attack aliases from different angles, and see what hits.  It seems to work, sometimes, but it's inconsistent.  Weird.  Senseless.  That's debugging in C if you don't understand the Deep Magic from the Dawn of Time that is "core dumps".  I gotta take a hard core dump right now. :D
* Get on the "CD" command.

# KNOWN ISSUES


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

And by the time I get here, idk what else I could possibley need/want.  I can write aliases for things like speech (i.e. `ALIAS SAY SYS easpeak `), sound, and things like listing files.  And if I'm using this with a screen reader, the screen reader will automatically speak stuff as I PRINT it anyway... now 3D sound is a bit tricky, but IMO that's a different project entirely.  And if I write that program, I can make aliases for that in Breakaway BASIC too :)
